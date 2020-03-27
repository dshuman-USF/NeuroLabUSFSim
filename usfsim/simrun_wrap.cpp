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


// C to C++ wrapper functions to manage saving .smr files

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <ctime>
#include "simulator.h"
#include "s64.h"
#include "s3264.h"
#include "s32priv.h"
#include "simrun_wrap.h"


extern char outFname[];
using namespace ceds64;
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

extern char simmsg[];

TSon32File *sFile;
TSon32File *sFileWave;

static bool init_done = false;
void SONStart()
{
   cout << "Init son64 " << endl;
   if (!init_done)
   {
      SONInitFiles();
      init_done = true;
   }
}

void SONStop()
{
   cout << "clean up son64 " << endl;
   if (init_done)
      SONCleanUp();
}

// set up the chans for the smr file
void openSpike()
{
   int num_chans, pop, res;
   TTimeDate td;
   TChanNum chan, ourChan;
   char text[128];
   TSTime64 sampIntv;

   num_chans = S.cwrit_count + S.fwrit_count;
   if (S.save_pop_total == 'y')
      ++num_chans;
   if (num_chans < MINCHANS)  // must be at least this many chans in smr file.
      num_chans = MINCHANS;

   string smrName(outFname);
   const size_t period_idx = smrName.rfind('.');
   if (string::npos != period_idx)
      smrName.erase(period_idx);
   smrName += ".smr";

   sFile = new TSon32File(1);
   res = sFile->Create(smrName.c_str(),num_chans);

   if (res != S64_OK)
   {
      char *msg, *cmd;

      if (res == NO_ACCESS)
         asprintf(&msg,"%s %s %s%s", "\"The file ",smrName.c_str(), " is in use by another program. Close that program and re-run the simulation.","\"");
      else
         asprintf(&msg,"%s %s %s %d%s", "\"Cannot open ", smrName.c_str(), " Error is: ",res,"\"");
      asprintf(&cmd, "%s %s %s", simmsg, "\"SIMRUN ERROR\"", msg);
      cout << msg << endl;
      system (cmd);
      free(msg);
      free(cmd);

      delete sFile;
      sFile = nullptr;
      return;
   }
   double tickSize = S.step/1000.0;
   sFile->SetTimeBase(tickSize);
   time_t curr_time = time(0);
   tm* now = localtime(&curr_time);
   td.ucHun = 0;
   td.ucSec = now->tm_sec;
   td.ucMin = now->tm_min;
   td.ucHour = now->tm_hour;
   td.ucDay = now->tm_mday;
   td.ucMon = now->tm_mon;
   td.wYear = now->tm_year+1900;
   sFile->TimeDate(nullptr,&td);

    // add some comments
   stringstream strm;

   strm << "Simulator run, model file is ";
   strm << S.snd_file_name;
   res = sFile->SetFileComment(0,strm.str().c_str());
   ourChan = 101; // scope starts chans here, we will too
   chan = 0;      // smr files wants them to start a 0
    // create chans
   for (pop = 0; pop < S.cwrit_count; pop++, chan++, ++ourChan)
   {
      res = sFile->SetEventChan(chan,100,ceds64::TDataKind::EventRise,ourChan);
      if (res != S64_OK)
         cout << "event cell chan create res: " << res << " chan" << chan << endl;
      else
      {
         sFile->SetChanUnits(chan,"");
         sprintf(text,"%3d C%3d",ourChan,S.cwrit[pop].pop); // 9 chars or less
         sFile->SetChanTitle(chan,text);
         sFile->SetBuffering(chan,0x4000);
      }
   }
   for (pop = 0; pop < S.fwrit_count; pop++, chan++, ++ourChan)
   {
      res = sFile->SetEventChan(chan,100,ceds64::TDataKind::EventRise,ourChan);
      if (res != S64_OK)
         cout << "event fiber chan create res: " << res << " chan" << chan << endl;
      {
         sFile->SetChanUnits(chan,"");
         sprintf(text,"%3d F%3d",ourChan,S.fwrit[pop].pop); // 9 chars or less
         sFile->SetChanTitle(chan,text);
         sFile->SetBuffering(chan,0x4000);
      }
   }
   sampIntv = 1 / S.step * S.nanlgrate;
   if (S.save_pop_total == 'y')
   {
      res = sFile->SetWaveChan(chan,sampIntv,ceds64::TDataKind::Adc,tickSize,ourChan);
      if (res != S64_OK)
         cout << "wave chan create res: " << res << endl;
      else
      {
         sFile->SetChanUnits(chan,"");
         sprintf(text,"An %2d",ourChan); // 9 chars or less
         sFile->SetChanTitle(chan,text);
         sFile->SetBuffering(chan,0x1000);
      }
   }
}
using lookup = struct { int real; int sib;};
using sib = map <int, lookup>;
using sibIter = sib::iterator;

sib Sib;
/*
  chan real chan sib
  1        1      2
  2        3      -
  3        4      5
  4        6      7
  5        0

*/

// set up the waveform chans for smr file
// We can't mix analog waveform data and spike firing events, so
// chan 2N is waveform (0,2,4,6 . . .),
// chan 2N+1 is spikes (1,3,5,7 . . .)
void openSpikeWave()
{
   int num_chans = 0;
   int res;
   TTimeDate td;
   //TChanNum chan;
   int chan;
   char text[128];
   TSTime64 sampIntv;
   int real_chan = 0;
   lookup next;

   for (chan = 0; chan < S.plot_count; ++chan,++num_chans)
      if (S.plot[chan].var == 1) // need 2 chans for action potentials
         ++num_chans;
   if (num_chans < MINCHANS)  // must be at least this many chans in smr file.
      num_chans = MINCHANS;

   string smrName(outFname);
   const size_t period_idx = smrName.rfind('.');
   if (string::npos != period_idx)
      smrName.erase(period_idx);
   smrName += "_wave.smr";
   sFileWave = new TSon32File(1);
   res = sFileWave->Create(smrName.c_str(),num_chans);

   if (res != S64_OK)
   {
      char *msg, *cmd;

      if (res == NO_ACCESS)
         asprintf(&msg,"%s %s %s%s", "\"The file ",smrName.c_str(), " is in use by another program. Close that program and re-run the simulation.","\"");
      else
         asprintf(&msg,"%s %s %s %d%s", "\"Cannot open ", smrName.c_str(), " Error is: ",res,"\"");
      asprintf(&cmd, "%s %s %s", simmsg, "\"SIMRUN ERROR\"", msg);
      cout << msg << endl;
      system (cmd);
      free(msg);
      free(cmd);

      delete sFileWave;
      sFileWave = nullptr;
      return;
   }
   double tickSize = S.step/1000.0;
   sFileWave->SetTimeBase(tickSize);
   time_t curr_time = time(0);
   tm* now = localtime(&curr_time);
   td.ucHun = 0;
   td.ucSec = now->tm_sec;
   td.ucMin = now->tm_min;
   td.ucHour = now->tm_hour;
   td.ucDay = now->tm_mday;
   td.ucMon = now->tm_mon;
   td.wYear = now->tm_year+1900;
   sFileWave->TimeDate(nullptr,&td);

    // add some comments
   stringstream strm;

   strm << "Simulator run, waveform data.";
   res = sFileWave->SetFileComment(0,strm.str().c_str());
   strm.str("");
   strm << "Model file is ";
   strm << S.snd_file_name;
   res = sFileWave->SetFileComment(1,strm.str().c_str());
    // create chans
   sampIntv = 1;
   int plot_type = 0;
   const char *varnames[] = {"", "Vm", "gK", "Thr", "Vm", "h", "Thr"};
   const char *units[] = {"%VC", "%VC/s", "cmH2O", "frac", "frac", "frac", "L", "L", "L/s", "L/s", "cmH2O", "cmH2O", "cmH2O", "0->1", "0->1", "-1->1"};
   for (chan = 0; chan < S.plot_count; ++chan)
   {
       // this code from simviewer_launch_impl.cpp
      char *val = nullptr;
      plot_type = S.plot[chan].var;
      switch (plot_type)
      {
         case -1: // lung model
         case -2:
         case -3:
         case -4:
         case -5:
         case -6:
         case -7:
         case -8:
         case -9:
         case -10:
         case -11:
         case -12:
         case -13:
         case -14:
         case -15:
         case -16:
            if (asprintf (&val, "%.5s", units[abs(plot_type) - 1]) == -1) exit (1);
            break;
         case 0: 
            if (asprintf (&val, "mV") == -1) exit (1);
            break;
         case 1: 
         case 3: 
            if (asprintf (&val, "mV") == -1) exit (1);
            break;
         case 2: 
            if (asprintf (&val, "%.5s", varnames[S.plot[chan].type * 3 + plot_type]) == -1) exit (1);
            break;
         case 4:
            if (asprintf (&val, "%.2f ms",S.plot[chan].val) == -1) exit (1);
            break;
         default:
            if (plot_type < 1)
               break;
            if (asprintf (&val, "%d ms", S.plot[chan].var) == -1) exit (1);
            break;
      }
      sprintf(text,"%.8s", S.plot[chan].lbl); // 9 chars or less
      if (plot_type == 1) // only need this for action potentials
      {
         // event chan
         res = sFileWave->SetEventChan(real_chan,sampIntv,ceds64::TDataKind::EventRise,chan);
         if (res != S64_OK)
            cout << "wave event chan create res: " << res << endl;
         sFileWave->SetChanComment(real_chan,"Spikes");
         sFileWave->SetChanTitle(real_chan,text);
         next.sib = real_chan;
         ++real_chan;
         next.real = real_chan;
      }
      else
      {
         next.real = real_chan;
         next.sib = -1;
      }
      Sib.insert(pair(chan,next));

         // waveform chan
      res = sFileWave->SetWaveChan(real_chan,sampIntv,ceds64::TDataKind::RealWave,tickSize,chan);
      if (res != S64_OK)
         cout << "wave chan create res: " << res << endl;
      if (val)
         sFileWave->SetChanUnits(real_chan,val); // units vary
      sFileWave->SetChanTitle(real_chan,text);
      sFileWave->SetChanScale(real_chan,0.5);
      ++real_chan;
   }
   sFileWave->SetBuffering(-1,0x8000);
}


// Close any open smr file.
void closeSpike()
{
   if (sFile)
   {
      sFile->Close();
      delete sFile;
      sFile == nullptr;
   }
   if (sFileWave)
   {
      sFileWave->Close();
      delete sFileWave;
      sFileWave == nullptr;
   }
}


// write bdt/edt type event
void writeSpike(int chan, int time)
{
   int res;
   TChanNum fileChan;
   TSTime64 fileTime = time;

   if (sFile)
   {
      fileChan = chan - 101;
      res = sFile->WriteEvents(fileChan,&fileTime,1);
      if (res != S64_OK)
         cout << "Event chan write error: " << res << endl;
   }
}

// write analog wave data 
void writeWave(int chan, int time)
{
   int res;
   TAdc a_val;
   TChanNum fileChan;
   TSTime64 fileTime = time;

   fileChan = S.cwrit_count + S.fwrit_count;
   a_val = chan % 4096 - (chan % 4096 > 2047) * 4096;
 
   if (sFile)
   {
      res = sFile->WriteWave(fileChan,&a_val,1,fileTime);
      if (res < 0)
        cout << "Wave chan write error: " << res << endl;
   }
}

// This is analog the waveform data, same stuff
// you see in simviewer. The chan is a plot row number.
// We hide the real chan from the caller, it does not know
// we have a sibling chan
void writeWaveForm(int chan, int time, float val)
{
   sibIter iter = Sib.find(chan);
   int res;
   TChanNum fileChan = iter->second.real;

   TSTime64 fileTime = time;
   if (sFileWave)
   {
      res = sFileWave->WriteWave(fileChan,&val,1,fileTime);
      if (res < 0)
        cout << "Wave chan write error: " << res << endl;
   }
}

// write bdt/edt type event.
// See above for chan info.
void writeWaveSpike(int chan, int time)
{
   int res;
   sibIter iter = Sib.find(chan);
   TChanNum fileChan = iter->second.sib;
   TSTime64 fileTime = time;

   if (sFileWave)
   {
      res = sFileWave->WriteEvents(fileChan,&fileTime,1);
      if (res != S64_OK)
         cout << "Wave Spike Event chan write error: " << res << endl;
   }
}


#ifdef __cplusplus
}
#endif




