/*(Copyright 2005-2020 Kendall F. Morris

This file is part of the USF Neural Simulator suite.

    The Neural Simulator suite is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation, either
    version 3 of the License, or (at your option) any later version.

    The suite is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the suite.  If not, see <https://www.gnu.org/licenses/>.
*/



// Here lives the real event handlers for the launch popup non-modal window

#include <QtGlobal>
#include <QHostInfo>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#ifdef Q_OS_LINUX
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#elif defined Q_OS_WIN
#include <libloaderapi.h>
#endif
#include <QMessageBox>
#include <QString>
#include <QTextStream>

#include "lin2ms.h"
#include "ui_launchwindow.h"
#include "simwin.h"
#include "c_globals.h"
#include "sim2build.h"
#include "fileio.h"
#include "wavemarkers.h"

using namespace std;

void launchWindow::closeEvent(QCloseEvent *evt)
{
   launchExit();
   evt->accept();
}


// Tell parent that we are going away
void launchWindow::launchExit()
{
   mainwin->launchIsClosing();
}


// Dialogs can be closed with ESC key. We don't want that here.
bool launchWindow::event(QEvent* event)
{
   QKeyEvent *key = static_cast<QKeyEvent*>(event);
   if (key && key->key() == Qt::Key_Escape)
   {
      key->accept();
      return true;
   }
   return QDialog::event(event);
}

// The way we reset these are different since
// they are discrete controls.
void launchWindow::initAnalogRecs()
{
   analogRec aRec;
   int instance;

   analogModel->reset();
   analogModel->blockSignals(true);
   for (instance = 0; instance < MAX_LAUNCH; ++instance)
   {
      aRec.rec[ANALOG_ID]      = sp_aid[instance];
      aRec.rec[ANALOG_CELLPOP] = sp_apop[instance];
      aRec.rec[ANALOG_RATE]    = sp_arate[instance];
      aRec.rec[ANALOG_TIME]    = sp_atk[instance];
      aRec.rec[ANALOG_SCALE]   = sp_ascale[instance];
      analogModel->addRec(aRec,instance);
   }
   analogModel->setCurrentModel(currModel);
   analogMapper->setCurrentIndex(currModel);
   analogModel->layoutChanged();
   analogModel->blockSignals(false);
}

// Currently unused, can in theory have simrun run on a different host.
// More for testing possible SPARC simcore architecture.
void launchWindow::initHostNameRecs()
{
   hostNameRec nRec;
   int instance;

   hostNameModel->reset();
   hostNameModel->blockSignals(true);
   for (instance = 0; instance < MAX_LAUNCH; ++instance)
   {
      nRec.rec = sp_hostname[instance];
      hostNameModel->addRec(nRec,instance);
   }
   hostNameModel->setCurrentModel(currModel);
   hostNameMapper->setCurrentIndex(currModel);
   hostNameModel->layoutChanged();
   hostNameModel->blockSignals(false);
}

// new launch number, do we have data to show for it?
void launchWindow::launchNumChanged(int num)
{
   currModel = num;
   plotDeskModel->setCurrentModel(currModel);
   bdtListModel->setCurrentModel(currModel);
   analogModel->setCurrentModel(currModel);
   analogMapper->setCurrentIndex(currModel);
   hostNameModel->setCurrentModel(currModel);
   hostNameMapper->setCurrentIndex(currModel);
   plotDeskModel->layoutChanged();
   bdtListModel->layoutChanged();
   analogModel->layoutChanged();
   hostNameModel->layoutChanged();

     // check prog state and update buttons
   simChild *launch = &simLaunches[currModel];
   if (launch->simProc)
   {
      ui->pauseResume->setEnabled(true);
      ui->midRunUpdateButton->setEnabled(true);
      ui->launchKill->setEnabled(true);
      ui->launchButton->setEnabled(false);
      if (launch->simProc->isPaused())
         ui->pauseResume->setText("Resume");
      else
         ui->pauseResume->setText("Pause");
   }
   else
   {
      ui->pauseResume->setEnabled(false);
      ui->midRunUpdateButton->setEnabled(false);
      ui->launchKill->setEnabled(false);
      ui->launchButton->setEnabled(true);
      ui->pauseResume->setText("Pause");
   }
}


void launchWindow::addLungRow()
{
   QString plot, binwid, scale;
   plotRec plot_row;

   plot.setNum(-1);
   binwid.setNum(120000);
   scale.setNum(0);
   plot_row.maxRndVal = 0;
   plot_row.rec[PLOT_POP] = QString();
   plot_row.rec[PLOT_MEMB] = QString();
   plot_row.rec[PLOT_PLOT] = plot;
   plot_row.rec[PLOT_BINWID] = binwid;
   plot_row.rec[PLOT_SCALE] = scale;
   plot_row.popType = LUNG_CELL;
   plotDeskModel->addRow(plot_row);
}

void launchWindow::bdtSel()
{
   ui->selLaunchBdt->setText("Create bdt file");
   fnameSel = BDT;
}

void launchWindow::edtSel()
{
   ui->selLaunchBdt->setText("Create edt file");
   fnameSel = EDT;
}
void launchWindow::customSel()
{
   ui->selLaunchBdt->setText("Create custom bdt file");
   fnameSel = BDT;
}

void launchWindow::loadModels()
{
   int instance, row;
   plotRec plot_row;
   bdtRec  bdt_row;
   analogRec a_rec;
   hostNameRec n_rec;
   int pop_num, member_num, pop_type, d_idx;
   int maxpop = 0;

   ui->lungCheck->setChecked(D.baby_lung_flag);  // one of a kind

   plotDeskModel->reset();
   bdtListModel->reset();
   analogModel->reset();
   hostNameModel->reset();
   plotDeskModel->blockSignals(true);
   bdtListModel->blockSignals(true);
   analogModel->blockSignals(true);
   hostNameModel->blockSignals(true);
   for (instance = 0; instance < MAX_LAUNCH; ++instance)
   {
      plotDeskModel->setCurrentModel(instance);
      bdtListModel->setCurrentModel(instance);
      analogModel->setCurrentModel(instance);
      for (row = 0; row < MAX_ENTRIES; ++row)
      {
         if (!valid(row,instance)) // use to stop at 0, now ignore it
            continue;
         QString pop_id,member,plot,binwid,scale;
         pop_num = sp_bpn2[row][instance];
         pop_type = sp_bv2[row][instance]; // zero based in ctrl, 1 in sim
         member_num = sp_bm2[row][instance];
         pop_id.setNum(pop_num);
         d_idx = lookupDidx(CELL,pop_num);
         if (d_idx)
            maxpop = getMaxPop(d_idx);
         else
            maxpop = 1000; // can this happen?
         plot_row.maxRndVal = maxpop;  // use member #, don't gen rnd one

         if (pop_type >= 1 && pop_type <= 3)
         {
            plot.setNum(pop_type-1); // zero-based
            member.setNum(member_num);
         }
         else
         {
            plot = "4";
            binwid.setNum(pop_type);
            scale.setNum(member_num);
         }

         if (pop_type < 0)  // a lung plot
         {
            plot.setNum(pop_type);
            binwid.setNum(member_num);
            plot_row.rec[PLOT_POP] = QString(); // blank
            plot_row.rec[PLOT_MEMB] = QString();
            plot_row.rec[PLOT_PLOT] = plot;
            plot_row.rec[PLOT_BINWID] = binwid;
            plot_row.rec[PLOT_SCALE] = pop_id;
            plot_row.popType = LUNG_CELL;
         }
         else
         {
            if (pop_type >= 1 && pop_type <= 3)
            {
               plot.setNum(pop_type-1); // zero-based
               member.setNum(member_num);
               plot_row.rec[PLOT_POP] = pop_id;
               plot_row.rec[PLOT_MEMB] = member;
               plot_row.rec[PLOT_PLOT] = plot;
               plot_row.rec[PLOT_BINWID] = QString();
               plot_row.rec[PLOT_SCALE] = QString();
            }
            else
            {
               plot = "4";
               binwid.setNum(pop_type);
               scale.setNum(member_num);
               plot_row.rec[PLOT_POP] = pop_id;
               plot_row.rec[PLOT_MEMB] = QString();
               plot_row.rec[PLOT_PLOT] = plot;
               plot_row.rec[PLOT_BINWID] = binwid;
               plot_row.rec[PLOT_SCALE] = scale;
            }
            if (d_idx)
            {
               if (D.inode[d_idx].unode.cell_node.pop_subtype == BURSTER_POP)
                  plot_row.popType = BURSTER_CELL;
               else if (D.inode[d_idx].unode.cell_node.pop_subtype == PSR_POP)
                  plot_row.popType = PSR_CELL;
               else
                  plot_row.popType = STD_CELL;
            }
            else
            {
               QMessageBox msgBox;
               msgBox.setIcon(QMessageBox::Warning);
               msgBox.setWindowTitle("FILES DISAGREE");
               msgBox.setStandardButtons(QMessageBox::Ok);
               msgBox.setText("The current .ols and .snd files are out of sync.\nBehavior is undefined");
            }
         }
         plotDeskModel->addRow(plot_row);
      }

      for (row = 0; row < MAX_ENTRIES; ++row)
      {
         if ((sp_bpn[row][instance]!=0) && (sp_bm[row][instance]!=0))
         {
            pop_num = sp_bpn[row][instance];
            pop_type = sp_bcf[row][instance];
            d_idx = lookupDidx(pop_type, pop_num);
            maxpop = getMaxPop(d_idx);
            // QString pop_type, pop_id, member;
            bdt_row.rec[BDT_CELL_FIB] = pop_type;
            bdt_row.rec[BDT_POP] = pop_num;
            bdt_row.rec[BDT_MEMB] = sp_bm[row][instance];
            bdt_row.maxRndVal = maxpop;
            bdtListModel->addRow(bdt_row,row);
         }
      }

      a_rec.rec[ANALOG_ID]      = sp_aid[instance];
      a_rec.rec[ANALOG_CELLPOP] = sp_apop[instance];
      a_rec.rec[ANALOG_RATE]    = sp_arate[instance];
      a_rec.rec[ANALOG_TIME]    = sp_atk[instance];
      a_rec.rec[ANALOG_SCALE]   = sp_ascale[instance];
      analogModel->addRec(a_rec,instance);

      n_rec.rec = sp_hostname[instance];
      hostNameModel->addRec(n_rec,instance);
   }
   currModel = 0;
   hostNameModel->layoutChanged();
   analogModel->layoutChanged();
   plotDeskModel->setCurrentModel(currModel);
   bdtListModel->setCurrentModel(currModel);
   analogModel->setCurrentModel(currModel);
   analogMapper->setCurrentIndex(currModel);
   hostNameModel->setCurrentModel(currModel);
   hostNameMapper->setCurrentIndex(currModel);
   ui->launchNum->setValue(0);
   plotDeskModel->blockSignals(false);
   bdtListModel->blockSignals(false);
   analogModel->blockSignals(false);
   hostNameModel->blockSignals(false);
}

// notify the higher ups we have changes
void launchWindow::setScrDirty()
{
   mainwin->launchChg();
}

// If main win is our parent, we always on top of it.
// Sometimes this is annoying. Reparent so the desktop is the parent.
void launchWindow::reParent(bool child)
{
   if (child)
      setParent(mainwin,Qt::Dialog);
   else
      setParent(nullptr);
}

// Assumes currModel is index of active/visible data set
void launchWindow::copyModels()
{
   int value = ui->launchNum->value();
   int idx = currModel;
   if (idx != value)
      cout << "copy index value mismatch" << endl;

   if (value+1 < MAX_LAUNCH)
   {
      plotDeskModel->dupModel(value,value+1);
      bdtListModel->dupModel(value,value+1);
      analogModel->dupModel(value,value+1);
      // plots
      copy(begin(sp_bpn2[idx]), end(sp_bpn2[idx]), begin(sp_bpn2[idx+1]));
      copy(begin(sp_bm2[idx]), end(sp_bm2[idx]), begin(sp_bm2[idx+1]));
      copy(begin(sp_bv2[idx]), end(sp_bv2[idx]), begin(sp_bv2[idx+1]));
      // bdt or edt
      copy(begin(sp_bcf[idx]), end(sp_bcf[idx]), begin(sp_bcf[idx+1]));
      copy(begin(sp_bpn[idx]), end(sp_bpn[idx]), begin(sp_bpn[idx+1]));
      copy(begin(sp_bm[idx]), end(sp_bm[idx]), begin(sp_bm[idx+1]));
      // analog
      sp_inter[idx+1]=sp_inter[idx];
      sp_aid[idx+1]=sp_aid[idx];
      sp_apop[idx+1]=sp_apop[idx];
      sp_arate[idx+1]=sp_arate[idx];
      sp_atk[idx+1]=sp_atk[idx];
      sp_ascale[idx+1]=sp_ascale[idx];
      strncpy(sp_hostname[idx+1],sp_hostname[idx],sizeof(sp_hostname[0])); 
   }
}


// Signal from sim_proc that data is available
// First line is type of msg.
void launchWindow::chkSimRun()
{
   QString msg, toprint;
   QTextStream prnstrm(&toprint);
   QStringList line;
   float curr;
   int target, last;
   bool okay;
   simChild *launch = &simLaunches[currModel];

   launch->simProc->getMsg(msg); // This strongly assumes we get a 
   if (!msg.length())            // complete line, this is NOT guaranteed.
      return;
   target = ui->autoPause->value();
   line = msg.split('\n',QString::SkipEmptyParts);
   if (line.size())
   {
      if (line[0] == "TIME")
      {
         last = line.size()-1;
         curr = line[last].toFloat(&okay);
         if (okay)
         {
            prnstrm << "Simulation time: " << qSetRealNumberPrecision(4) << curr << " seconds.";
            mainwin->printMsg(toprint);
            if (target && curr >= target)
            {
               if (!launch->simProc->isPaused())
               {
                  launchPause();
                  mainwin->printMsg("Pause time has been reached, simulation paused.");
                  ui->autoPause->setValue(0);
               }
            }
         }
      }
      else if (line[0] == "MSG" && line.size() == 2)
         mainwin->printMsg(line[1]);
      else
      {
         mainwin->printMsg(QString("Got unknown message from simrun"));
         mainwin->printMsg(line[0]);
      }
   }
}

// toggle pause state
void launchWindow::launchPause()
{
   simChild *launch = &simLaunches[currModel];
   if (launch->simProc->isPaused())
   {
      launch->simProc->resumeProc();
      ui->pauseResume->setText("Pause");
      mainwin->printMsg("Simulator resumed.");
   }
   else
   {
      launch->simProc->pauseProc();
      ui->pauseResume->setText("Resume");
      mainwin->printMsg("Simulator paused.");
   }
}

// We can kill the sim by using a TERM signal, but this
// assumes the pid is still valid, which is not guaranteed if
// sim was killed by hand and another process was started.
// If we have socket connection, use it if it still exists.
void launchWindow::killProgs()
{
   simChild *launch = &simLaunches[currModel];
   if (launch->simProc)
      launch->simProc->terminateProg();
   killSim();
   if (Debug)      // Don't kill by default, most people want it left open.
      killView();  // If debugging set, kill it, otherwise I wind up with a dozen
                   // of these.
}

void launchWindow::killSim()
{
   mainwin->printMsg("Simulator program terminated");
   ui->pauseResume->setText("Pause");
   ui->pauseResume->setEnabled(false);
   ui->midRunUpdateButton->setEnabled(false);
   ui->launchKill->setEnabled(false);
   ui->launchButton->setEnabled(true);
}

void launchWindow::killView()
{
   simChild *launch = &simLaunches[currModel];
   if (launch->viewProc)
   {
      launch->viewProc->terminateProg();
      launch->viewProc->deleteLater();
      mainwin->printMsg("Simviewer program terminated");
   }
}

// connection lost, assume program has stopped
void launchWindow::notifySimConnLost(int instance)
{
   QString msg = "The simululator program instance " + QString::number(instance) + " has stopped running";
   mainwin->printMsg(msg);
   killSim();
   simChild *launch = &simLaunches[instance];
   launch->simProc->deleteLater();
}

// connection established, send info to simrun
void launchWindow::notifySimConnOk(int instance)
{
   simChild *launch = &simLaunches[instance];
   launch->simProc->sendMsg(scriptMsg);
   launch->simProc->sendMsg(simMsg);
   launch->simProc->sendMsg(sndMsg);
   scriptMsg.clear();
   simMsg.clear();
   sndMsg.clear();
}

void launchWindow::fwdMsg(QString msg)
{
   mainwin->printMsg(msg);
}

// connection established
void launchWindow::notifyViewConnOk(int instance)
{
   QString msg = "Viewer instance " + QString::number(instance) + " has established a connection with simbuild.";
   mainwin->printMsg(msg);
}

// We only expect one msg from simviewer, the port # it is
// listening on for a connection from simrun
void launchWindow::gotPort()
{
   simChild *launch = &simLaunches[currModel];
   QString port;
   launch->viewProc->getMsg(port);
   if (port.length())
   {
      QString msg1 = "Got simviewer server port number ";
      msg1 += port.toLatin1().data();
      mainwin->printMsg(msg1);
      QByteArray bytes;
      bytes.append(MSG_START);
      bytes.append(PORT_MSG);
      bytes.append(port.toUtf8());
      bytes.append("\n");
      bytes.append(MSG_END);
      QString msg2 = "LAUNCH: Send msg to simrun.";
      mainwin->printMsg(msg2);
      launch->simProc->sendMsg(bytes);
   }
}

void launchWindow::notifyViewConnLost(int instance)
{
   QString msg = "The simviewer program instance ";
   msg += QString::number(instance);
   msg += " has stopped running";
   mainwin->printMsg(msg);
   killView();
}

const char * launchWindow::get_comment1 (int cellpop, int var)
{
  if (var >= -16 && var <= -1)
  {
    const char *v[16] = {"Lung Volume", "Flow", "Alveolar Pressure", "Phr_d", "u", "lma", "Vdi", "Vab", "Vdi_t", "Vab_t", "Pdi", "Pab", "PL", "Phr_d_", "u_", "lma_"};
    return v[abs(var) - 1];
  }
  int n;
  for (n = 1; n < 99; n++)
    if (D.inode[n].node_type == CELL && D.inode[n].node_number == cellpop)
      return D.inode[n].comment1;
  return "";
}

// Copy the current values in the GUI to the various vars the .sim file needs
void launchWindow::modelsToVars()
{
   plotRec sRec;
   bdtRec eRec;
   analogRec aRec;
   hostNameRec nRec;
   int row, instance, numrecs;
   bool found;

   // The in-memory arrays may have junk in them from edits, zero them out
   // to start clean.
   for (int y=0; y<MAX_LAUNCH; y++)
   {
      for (int x=0; x<MAX_ENTRIES; x++)
      {
         sp_bcf[x][y]=UNUSED;
         sp_bpn[x][y]=0;
         sp_bm[x][y]=0;
         sp_bpn2[x][y]=0;
         sp_bm2[x][y]=0;
         sp_bv2[x][y]=0;
      }
      sp_aid[y]  = 0;
      sp_apop[y] = 0;
      sp_arate[y] = 0;
      sp_atk[y] = 0;
      sp_ascale[y] = 0;
      strcpy(sp_hostname[y],"");
   }

   for (instance = 0; instance < MAX_LAUNCH; ++instance)
   {
      plotDeskModel->setCurrentModel(instance);
      bdtListModel->setCurrentModel(instance);
      analogModel->setCurrentModel(instance);
      numrecs = plotDeskModel->numRecs();
      for (row = 0; row < numrecs; ++row)
      {
         found = plotDeskModel->readRec(sRec,row);
         if (found)
         {
            int var = sp_bv2[row][instance]=sRec.rec[PLOT_PLOT].toInt();
            if (var >= 0 && var < 4)
            {  ++var; // these are 1-based, zero based in the control
               sp_bpn2[row][instance]=sRec.rec[PLOT_POP].toInt();
               sp_bm2[row][instance]=sRec.rec[PLOT_MEMB].toInt();
               sp_bv2[row][instance]=var;
            }
            else if (var < 0 && var > -17)
            {
               sp_bpn2[row][instance]=sRec.rec[PLOT_SCALE].toInt();
               sp_bm2[row][instance]=sRec.rec[PLOT_BINWID].toInt();
               sp_bv2[row][instance]=var;
            }
            else
            {
               sp_bpn2[row][instance]=sRec.rec[PLOT_POP].toInt();
               sp_bm2[row][instance]=sRec.rec[PLOT_SCALE].toInt();
               sp_bv2[row][instance]=sRec.rec[PLOT_BINWID].toInt();
            }
         }
      }

      numrecs = bdtListModel->numRecs();
      for (row = 0; row < numrecs; ++row)
      {
         found = bdtListModel->readRec(eRec,row);
         if (found)
         {
            sp_bcf[row][instance] = eRec.rec[BDT_CELL_FIB].toInt();
            sp_bpn[row][instance] = eRec.rec[BDT_POP].toInt();
            sp_bm[row][instance] = eRec.rec[BDT_MEMB].toInt();
         }
      }
   
      found = analogModel->readRec(aRec,instance);
      if (found)
      {
         sp_aid[instance]  = aRec.rec[ANALOG_ID].toInt();
         sp_apop[instance] = aRec.rec[ANALOG_CELLPOP].toInt();
         sp_arate[instance] = aRec.rec[ANALOG_RATE].toInt();
         sp_atk[instance] = aRec.rec[ANALOG_TIME].toFloat();
         sp_ascale[instance] = aRec.rec[ANALOG_SCALE].toFloat();
      }
      found = hostNameModel->readRec(nRec,instance);
      if (found)
         strncpy(sp_hostname[instance], nRec.rec.toString().toLatin1().data(), sizeof(sp_hostname[0]));
   }

   plotDeskModel->setCurrentModel(currModel);
   bdtListModel->setCurrentModel(currModel);
   analogModel->setCurrentModel(currModel);
   analogMapper->setCurrentIndex(currModel);
   hostNameModel->setCurrentModel(currModel);
   hostNameMapper->setCurrentIndex(currModel);
   D.baby_lung_flag = ui->lungCheck->isChecked();
}

int launchWindow::lookupDidx(int type, int pop_num)
{
   int node;
   bool found = false;
   for (node=FIRST_INODE; node<SYNAPSE_INODE; ++node)
      if (D.inode[node].node_type == type && D.inode[node].node_number == pop_num)
      {
         found = true;
         break;
      }
   if (found)
      return node;
   else
      return 0; // not a valid cell/fiber index, 0 is the global inode
}


int launchWindow::getMaxPop(int d_idx)
{
   int maxpop = 0;
   if (D.inode[d_idx].node_type == FIBER)
      maxpop = D.inode[d_idx].unode.fiber_node.f_pop;
   else if (D.inode[d_idx].node_type == CELL)
      maxpop = D.inode[d_idx].unode.cell_node.c_pop;
   return maxpop;
}


int launchWindow::valid (int row, int instance)
{
  int p = sp_bpn2[row][instance];
  int m = sp_bm2[row][instance];
  int v = sp_bv2[row][instance];
  return ((v > 0 && p > 0 && m > 0)
          || (v >= -16 && v <= -1 && m != 0));
}

// This tells simrun to re-read the sim file with, presumably, changed params
void launchWindow::midRunUpdate()
{
   int val;
   QByteArray simfile;
#ifdef Q_OS_LINUX
   char  file_holder[NAME_MAX];
#elif defined Q_OS_WIN
   char  file_holder[_MAX_FNAME];
#endif
   sprintf(file_holder,"spawn%d.sim",currModel);
   Save_sim(file_holder,mainwin->currSndFile.toLatin1().data());
   QFile sim(file_holder);
   sim.open(QIODevice::ReadOnly);
   simfile = sim.readAll();
   simMsg.append(MSG_START);
   simMsg.append(SIM_MSG);
   simMsg.append(simfile);
   simMsg.append(MSG_END);
   sim.close();
   simChild *launch = &simLaunches[currModel];
   launch->simProc->updateProc();
   val = launch->simProc->sendMsg(simMsg);
   cout << "sent " << val << " mid-run update .sim file bytes" << endl;
   simMsg.clear();
}

// Do all setups to launch the current launch #, then start a new simrun process
void launchWindow::launchSim()
{
   FILE  *script_ptr;
   char  script[100];
   int   row;
   char  temp[10];
   char *launchN_sim = nullptr;
   char *scriptfile;
   int result;
   bool bdt_flag, wave_flag, smr_flag, socket_flag;
   bool smr_wave_flag, analog_flag, condi_flag, have_rows;
   hostNameRec n_rec;
   QMessageBox msgBox;
   QByteArray simfile, scrptfile, sndfile;
   simChild *launch = &simLaunches[currModel];

   if (launch->simProc) // already running?
   {
      QString msg = "The simululator program instance " + QString::number(currModel) + " is already running";
      mainwin->printMsg(msg);
      return; // should not be here because button is disabled, but. . .
   }
     // make sure there is a model to simulate
   if (D.inode[GLOBAL_INODE].unode.global_node.total_populations == 0)
   {
      QString msg = "There is no model to simulate, simulator not started.";
      mainwin->printMsg(msg);
      msgBox.setIcon(QMessageBox::Warning);
      msgBox.setWindowTitle("No Model To Simulate");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setText("There is no model to simulate. Create a model or load an existing one.\nSimulator not started.");
      msgBox.exec();
      return;
   }

   socket_flag = ui->selLaunchPlotSocket->isChecked();
   bdt_flag = ui->selLaunchBdt->isChecked();
   wave_flag = ui->selLaunchPlot->isChecked();
   smr_flag = ui->selLaunchSmr->isChecked();
   smr_wave_flag = ui->selLaunchSmrWave->isChecked();
   analog_flag = ui->selLaunchAnalog->isChecked();
   condi_flag = ui->condiCheck->isChecked();
   D.baby_lung_flag =ui->lungCheck->isChecked();

   if (Version != FILEIO_FORMAT_VERSION6)
   {
      QString msg = "The current .snd file is a previous version.  You need to save the current model to the current file to upgrade the file to the current version";
      mainwin->printMsg(msg);
      msgBox.setIcon(QMessageBox::Warning);
      msgBox.setWindowTitle("Need To Upgrade .snd File");
      msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
      msgBox.setText("The current .snd file is a previous version.  You need to write the current parameters to a new file so it will be upgraded to the current version.\nNOTE: You should enter a new name for the new file or else it will over-write the old version with a new version. The newsned program will not be able to read the new version.\nDo you want to upgrade the .snd file?");
      int choice = msgBox.exec();
      if (choice == QMessageBox::Yes)
         mainwin->saveSnd();
      else
         return;
   }

   modelsToVars();
   get_maxes(&D);

   if (mainwin->needToSave()) // need to save pending changes?
      mainwin->saveSnd(); // if they cancel the save, the sim may have unexpected results

   asprintf(&launchN_sim, "spawn%d.sim", currModel);
   Save_sim(launchN_sim,mainwin->currSndFile.toLatin1().data());

   sprintf(script,"script%d.txt",currModel);
   script_ptr=fopen(script,"w");
   fprintf(script_ptr,"spawn%d.sim\n",currModel);
   fprintf(script_ptr,"%ld\n",sp_inter[currModel]);

     // stuff to plot?
   have_rows = false; // has to be at least one entry, make sure
   for (row = 0; row < MAX_ENTRIES; ++row)
      if (valid (row,currModel))
      {
         have_rows = true;
         break;
      }
   if ((wave_flag || socket_flag || smr_wave_flag) && have_rows)
   {
      fprintf(script_ptr,"E\n");
      fprintf(script_ptr,"%d\n",currModel);
      for (row = 0; row < MAX_ENTRIES; ++row)
      {
         if (!valid (row,currModel))
            continue;
         fprintf(script_ptr,"%d,%d,%d,%s\n",
            sp_bpn2[row][currModel],
            sp_bm2[row][currModel],
            sp_bv2[row][currModel],
            get_comment1(sp_bpn2[row][currModel], sp_bv2[row][currModel]));
      }
      fprintf(script_ptr,"\n"); // blank line indicates end
   }
   else
      fprintf(script_ptr,"\n");

   if (bdt_flag == true)
      fprintf(script_ptr,"Y\n");
   else
      fprintf(script_ptr,"N\n");
   if (smr_flag == true)
      fprintf(script_ptr,"Y\n");
   else
      fprintf(script_ptr,"N\n");
   if (smr_wave_flag == true)
      fprintf(script_ptr,"Y\n");
   else
      fprintf(script_ptr,"N\n");

      // create bdt table file(s)?
   if (bdt_flag || smr_flag)
   {
      have_rows = false; // has to be at least one entry, make sure
      for (row = 0; row < MAX_ENTRIES; ++row)
         if ((sp_bpn[row][currModel]!=0) && (sp_bm[row][currModel]!=0))
         {
            have_rows = true;
            break;
         }
      if (have_rows)
      {
         if (analog_flag==true)
         {
            fprintf(script_ptr,"Y\n");
            fprintf(script_ptr,"%d\n",sp_aid[currModel]);
            fprintf(script_ptr,"%d\n",sp_apop[currModel]);
            fprintf(script_ptr,"%d\n",sp_arate[currModel]);
            fprintf(script_ptr,"%f\n",sp_atk[currModel]);
            fprintf(script_ptr,"%f\n",sp_ascale[currModel]);
         }
         else
            fprintf(script_ptr,"N\n");
         if (fnameSel == EDT)
            fprintf(script_ptr,"spawn%d.edt\n",currModel);
         else
            fprintf(script_ptr,"spawn%d.bdt\n",currModel);

         for (row = 0; row < MAX_ENTRIES; ++row)
         {
            if ((sp_bpn[row][currModel]!=0) && (sp_bm[row][currModel]!=0))
            {
               if (sp_bcf[row][currModel]==CELL)
                  strcpy(temp,"C");
               if (sp_bcf[row][currModel]==FIBER)
                  strcpy(temp,"F");
               fprintf(script_ptr,"%s%d,%d\n", temp,sp_bpn[row][currModel],
               sp_bm[row][currModel]);
            }
         }
      }
      fprintf(script_ptr,"\n");
   }

   fclose(script_ptr);

      // send script
   QFile scrpt(script);
   scrpt.open(QIODevice::ReadOnly);
   scrptfile = scrpt.readAll();
   scriptMsg.append(MSG_START);
   scriptMsg.append(SCRIPT_MSG);
   scriptMsg.append(scrptfile);
   scriptMsg.append(MSG_END);
   scrpt.close();
     // send sim file
   QFile sim(launchN_sim);
   sim.open(QIODevice::ReadOnly);
   simfile = sim.readAll();
   simMsg.append(MSG_START);
   simMsg.append(SIM_MSG);
   simMsg.append(simfile);
   simMsg.append(MSG_END);
   sim.close();
   free(launchN_sim);

     // send snd file, lung models need this
   QFile snd(mainwin->currSndFile.toLatin1().data());
   snd.open(QIODevice::ReadOnly);
   sndfile = snd.readAll();
   sndMsg.append(MSG_START);
   sndMsg.append(SND_MSG);
   sndMsg.append(sndfile);
   sndMsg.append(MSG_END);
   snd.close();

   if (bdt_flag || smr_flag || wave_flag || socket_flag || smr_wave_flag) // any reason to running sim?
   {
        // prepare for a new run by cleaning out old files
      char *filename, *cmd=nullptr;
      if (bdt_flag)
      {
         asprintf(&filename, "spawn%d.bdt", currModel);
#ifdef Q_OS_LINUX
         unlink("nohup.out");
         unlink(filename);
#else
         _unlink(filename);
#endif
         free(filename);
      }
      if (smr_flag)
      {
         asprintf(&filename, "spawn%d.smr", currModel);
#ifdef Q_OS_LINUX
         unlink(filename);
#else
         bool keep_at_it = true;  // In windows, if viewing in spike2, will not be
         while (keep_at_it)       // able to delete it. Close it (or not).
         {
            int err = _unlink(filename);
            if (err == -1)
            {
               QMessageBox msgBox;
               QString msg;
               QTextStream strm(&msg);
               msgBox.setIcon(QMessageBox::Critical);
               msgBox.setWindowTitle("File in Use");
               msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Yes 
                                       | QMessageBox::No);
               strm << "The file " << filename << " is in use. The simulation will not be able to create a new one and save results to it.\n"
                  << "Close it in the app that is using it first , then press the Retry button.\nDo you want to launch the simulation now?";
               msgBox.setText(msg);
               int res =  msgBox.exec();
               if (res == QMessageBox::No)
               {
                  free(filename);
                  return;
               }
               else if (res == QMessageBox::Yes)
                  keep_at_it = false;
            }
            else
               keep_at_it = false;
         }
#endif
         free(filename);
      }

      if (wave_flag)
      {
       // delete wave files for this launch number
#ifdef Q_OS_LINUX
         asprintf(&cmd, "/bin/bash -c \'rm -f wave.%02d.????\'",currModel);
#else
         asprintf(&cmd, "cmd.exe /C del wave.%02d.????",currModel);
#endif
         result = system(cmd);
         if (result == -1)
         {
            QString fail = QString(cmd);
            fail += " failed to execute.";
            mainwin->printMsg(fail);
         }
         free(cmd);

       // possibly delete dangling incomplete last wave file for this launch number
#ifdef Q_OS_LINUX
         asprintf(&cmd, "/bin/bash -c \'rm -f wave.%02d.????.tmp\'",currModel);
#else
         asprintf(&cmd, "cmd /C del wave.%02d.????.tmp",currModel);
#endif
         result = system(cmd);
         if (result == -1)
         {
            QString fail = QString(cmd);
            fail += " failed to execute.";
            mainwin->printMsg(fail);
         }
         free(cmd);
      }
      asprintf(&scriptfile, "script%d.txt", currModel);
      QString scfile = QString("script%1.txt").arg(QString::number(currModel));
      QStringList args;

       // start simrun
      hostNameModel->readRec(n_rec,currModel);
      QString h_local = QHostInfo::localHostName();

#ifdef Q_OS_LINUX
      if(n_rec.rec.toString().size())
      {
         launch->simProc = new SimProc(this,QString("nohup"),currModel,true);
         args << "ssh";
         args << "-Y";
         args << "-l";
         args << "dshuman";  // todo: just for prototyping, need to have usr/pwd
         args << n_rec.rec.toString().toLatin1().data();  // to make this usable by others
         args << "simrun";
      }
      else
      {
         launch->simProc = new SimProc(this,QString("nohup"),currModel,true);
         args << "simrun";
      }
#else
      char path[MAX_PATH];
      GetModuleFileNameA(NULL,path,sizeof(path)-1);
      QString simbuild(path);
      simbuild = simbuild.left(simbuild.lastIndexOf("\\"));
      QString simrun = simbuild + "\\simrun.exe";
      QString simviewer = simbuild + "\\simviewer.exe";
      launch->simProc = new SimProc(this,simrun,currModel,true);
      mainwin->printMsg(simrun);
      mainwin->printMsg(simviewer);
#endif
      if (socket_flag)
      {
         args << "--socket";
         if (n_rec.rec.toString().size()) // the controls for this are
         {                                // hidden, so this never executes.
            args << "--host";
            args << "kali";
            args << n_rec.rec.toString().toLatin1().data();
         }
      }
      else if (wave_flag)
         args << "--file";
      if (condi_flag)
         args << "--condi";
      connect(launch->simProc,&SimProc::connLost,this,&launchWindow::notifySimConnLost);
      connect(launch->simProc,&SimProc::connOk,this,&launchWindow::notifySimConnOk);
      connect(launch->simProc,&SimProc::printInfo,this,&launchWindow::fwdMsg);
      connect(launch->simProc,&SimProc::haveData,this,&launchWindow::chkSimRun);
      if (!launch->simProc->progInvoke(args))
      {
         mainwin->printMsg("The simulator program failed to start, simviewer was not launched.");
         delete launch->simProc;
         launch->simProc = nullptr;
         return;
      }
      mainwin->printMsg("The simulator program is running.");
      ui->launchButton->setEnabled(false);
      ui->pauseResume->setEnabled(true);
      ui->midRunUpdateButton->setEnabled(true);
      ui->launchKill->setEnabled(true);

      // do we need to start simviewer?
      if (wave_flag || socket_flag)
      {
         QStringList vargs;
         QString spnum,title;
         spnum = QString::number(currModel);
#ifdef Q_OS_LINUX
         launch->viewProc = new SimProc(this,QString("nohup"),currModel,socket_flag);
#else
         launch->viewProc = new SimProc(this,simviewer,currModel,socket_flag);
#endif
         connect(launch->viewProc, &SimProc::connLost, this, &launchWindow::notifyViewConnLost);
         connect(launch->viewProc,&SimProc::printInfo,this,&launchWindow::fwdMsg);
         connect(launch->viewProc, &SimProc::connOk, this, &launchWindow::notifyViewConnOk);
         connect(launch->viewProc,&SimProc::haveData,this,&launchWindow::gotPort);
         vargs << "simviewer" << "-l" << spnum;
         if (socket_flag)
            vargs << "--socket";
         else
            vargs << "--file";

         if (strlen(sp_hostname[currModel])>0)
         {
            vargs << "--host";
            vargs << sp_hostname[currModel];
         }
         if (!launch->viewProc->progInvoke(vargs))
         {
            mainwin->printMsg("The simviewer program failed to start.");
            return;
         }
         else
            mainwin->printMsg("The simviewer program is running.");
      }
      if (condi_flag)
      {
         QString msg("The simulator is writing convergence/divergence information "
         "to the file condi.csv, as you requested.  This may take a few "
         "minutes, and then the simulation will begin");
         mainwin->printMsg(msg);
      }
   }
   else
   {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Warning);
      msgBox.setWindowTitle("NO OUTPUT SELECTED");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setText("At least one of Create .bdt (or other file type), Send Plot Data Directly To Simviewer, Save Plot Data To Files, or Create smr Waveform File must be selected. Simulator was not launched.");
      msgBox.exec();
   }
}

