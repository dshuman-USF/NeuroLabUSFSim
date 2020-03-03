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

#ifdef __cplusplus
extern "C" {
#endif

#include "inode.h"
#include "util.h"
#include "fileio.h"
#include "simulator.h"
#include "hash.h"
#include "c_globals.h"

/*
  Global Variables
*/


inode_global D;        // main database for model
simulator_global S;    // simbuild exports this, simrun uses it to run the sim

struct StructInfo *(*struct_info_fn) (const char *str, unsigned int len) = 0;
struct StructMembers *(*struct_members_fn) (const char *str, unsigned int len) = 0;


// newsned manages pop numbers differently by keeping track of
// allocated numbers by never really freeing up a used node.
// simbuild does this differently, but in order to be backwards compatible
// with existing .snd files and to generate .sim files that look the
// same as the ones generated by newsned, we keep track of the max used
// pop number, even if it was deleted and is no longer used.
int maxCellPop;
int maxFiberPop;

#define MAX_ARGS 20

I_NODE  def_fiber;    /*  Create default fiber parameters  */
I_NODE  def_cell;     /*  Create default cell parameters  */

bool cellsInUse[MAX_INODES];  // population numbers
bool fibersInUse[MAX_INODES];

/*   spawn system area variables to follow ******************************/

int  currModel=0;
int  bdt_flag;
int  smr_flag;
int  analog_flag;
int  condi_flag;

// analog info
long  sp_inter[MAX_SPAWN];
int  sp_aid[MAX_SPAWN];
int  sp_apop[MAX_SPAWN];
int  sp_arate[MAX_SPAWN];
float  sp_atk[MAX_SPAWN];
float  sp_ascale[MAX_SPAWN];

// bdt window items
int  sp_bcf[MAX_ENTRIES][MAX_SPAWN];  // cell or fiber
int  sp_bpn[MAX_ENTRIES][MAX_SPAWN];  // pop num
int  sp_bm[MAX_ENTRIES][MAX_SPAWN];

// simviewer plot window items
int  sp_bpn2[MAX_ENTRIES][MAX_SPAWN]; // pop #
int  sp_bm2[MAX_ENTRIES][MAX_SPAWN];  // member of pop
int  sp_bv2[MAX_ENTRIES][MAX_SPAWN];  // plot type 
char sp_hostname[MAX_SPAWN][64];


#ifdef __cplusplus
}
#endif

