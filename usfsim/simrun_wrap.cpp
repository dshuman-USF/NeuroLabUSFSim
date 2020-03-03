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

void closeSpike()
{
   if (sFile)
   {
      sFile->Close();
      delete sFile;
      sFile == nullptr;
   }
}


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

#ifdef __cplusplus
}
#endif




