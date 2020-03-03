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


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulator.h"
#include "inode.h"

#define BOUNDS(idx, count) ((idx) >= 0 && (idx) < (count)) || DIE
#if 0
void BOUNDS(int idx, int count)
{
   if (idx >= 0 && idx < count)
   {
      fprintf(stderr,"Bounds check fail idx: %d count: %d\n",idx,count);
      DIE;
   }
}
#endif

extern int Debug;

typedef struct
{
  Syn *ptr;
  int maxqidx;
} SynInfo;


/* The synapse variable is a 3D dynamically allocated set of arrays 
   It is used used like so:
   synapse[cellpop][cell][SynInfo].

   slots are like this:
   First index: synapse[pop], array size is # of cell pops, each slot holds a pointer to:
    Second Index: synapse[0][cells], cells is an array of pointers for each cell in pop:

   synapse[0]-> [ptr, ptr, ptr, . . .  ]

   synapse[1]-> [ptr, ptr, ptr, . . .  ]
     These point to:

     Third index, an array of pointers to a SynInfo struct, one
     for each cell synapse target.

   So, something like this:

   synapse [0][0][0]   cell pop 0, cell 0, SynInfo 0
   synapse [0][0][1]                       SynInfo 1
   synapse [0][1][0]               cell 1, SynInfo 0
   synapse [0][1][1]                       SynInfo 1
   synapse [0][1][2]               cell 1, SynInfo 2

   synapse [1][0][0]   cell pop 1, cell 0, SynInfo 0
    . . .

   There is a parallel set of arrays in the global S array that was 
   read in from the .sim file.
   S.net.cellpop holds an array of pointers, one per cell pop.
   Each one of these points to a Cell struct
   Fibers and synapses are handled similarly.
*/


static SynInfo ***synapse;

double
ran (int *i)
{
  double x;
  *i = 69069 * *i + 1;
  x = *i;
  if (x < 0) 
     x = x + 4294967296.0;
  return x / 4294967296.0; // 0.0 - 1.0
}

/* func is function to call. Choices are:
   count_to_synapses(...)
   attach_to_synapses(...) 
*/
static inline void
for_terminals (int iseed, Target *target, int target_count, TargetPop *tp, int tidx0,
          void (*func)(TargetPop*, CellPop*, Target*, int, int, int))
{
  int tidx;
  for (tidx = 0; tidx < tp->NT; tidx++) 
  {
     if(Debug) printf ("for_terminals:  tidx0 %d, tp->NT %d, tidx %d, target_count %d cell pop count %d\n", tidx0, tp->NT, tidx, target_count,S.net.cellpop_count);

    int tcpidx = tp->IRCP - 1;
    CellPop *tcp = S.net.cellpop + tcpidx;
      // tcidx is rand #0-1 * number of cells
    int tcidx = (int)(ran(&iseed) * tcp->cell_count);
      // quidx is min cond time + random #0-1 * (cond time - min cond time)
    //int qidx = tp->MCT + (int)(ran(&iseed) * (tp->NCT - tp->MCT));
   double r0 = ran(&iseed);
    //int qidx = tp->MCT + (int)(ran(&iseed) * (tp->NCT - tp->MCT));
    int qidx = tp->MCT + (int)(r0 * (tp->NCT - tp->MCT));
    if(Debug)
    {
       printf("seed:%d rand: %lf  NCT: %d MCT: %d\n",iseed,r0,tp->NCT, tp->MCT);
       printf("qidx#1: %d\n",qidx);
    }

      // if number of terminals is cond time-min cond time
    if (tp->NT == tp->NCT - tp->MCT)
      qidx = tp->MCT + tidx;     // qidx is min time plus current terminal index
    else
        // or qidx is same as # calculated above
      qidx = tp->MCT + (int)(ran(&iseed) * (tp->NCT - tp->MCT));

   // qidx seems to be determined by how long the max-min conductance time is
   // larger diffs means more elements in the q array
     if(Debug) printf("qidx#2: %d\n",qidx);
     if(Debug) fflush(stdout);

if ( tcpidx < 0 || tcpidx >= S.net.cellpop_count)
{   fprintf (stderr, "bounds1: tidx0 %d, tp->NT %d, tidx %d, target_count %d cellpopcount %d \n", tidx0, tp->NT, tidx, target_count,S.net.cellpop_count); fflush(stderr);}
    BOUNDS (tcpidx, S.net.cellpop_count);
if ( (tidx0+tidx) < 0 || tidx0+tidx >= target_count )
{   fprintf (stderr, "bounds2: tidx0 %d, tp->NT %d, tidx %d, target_count %d cellpopcount %d \n", tidx0, tp->NT, tidx, target_count,S.net.cellpop_count); fflush(stderr);}
    BOUNDS (tidx0 + tidx, target_count);
    func (tp, tcp, target + tidx0 + tidx, tcpidx, tcidx, qidx);
  }
}

static inline void
attach_to_synapses (TargetPop *tp, CellPop *tcp, Target* t, int tcpidx, int tcidx, int qidx)
{
  BOUNDS (tcpidx, S.net.cellpop_count);
  BOUNDS (tcidx, S.net.cellpop[tcpidx].cell_count);
  BOUNDS (tp->TYPE - 1, S.net.syntype_count);
  t->syn = synapse[tcpidx][tcidx][tp->TYPE-1].ptr;
  t->delay = qidx;
  t->strength = tp->STR;
  t->disabled = 0;

//  if(Debug) printf("attach syn ptr %p to synapse[%d][%d][%d]  vals: delay (qidx):%d str:%f disabled:%d\n", t->syn, tcpidx,tcidx,tp->TYPE-1, t->delay, t->strength, t->disabled);
  if(Debug) printf("attach synapse[%d][%d][%d]  vals: delay (qidx):%d str:%f disabled:%d\n", tcpidx,tcidx,tp->TYPE-1, t->delay, t->strength, t->disabled);

}

// Update the synapse[pop][cell][synapse slot] 
// If we are using this type of synapse, flag the slot for later updates.
// Also update the maxqidx value.
// Note that this STRONGLY assumes that the cell/fiber does not 
// have more than one of the same type of synapse. If so, it will not be counted.
// Of course, why would you do this?
static inline void
count_to_synapses (TargetPop *tp, CellPop *tcp, Target *target, int tcpidx, int tcidx, int qidx)
{
  Cell *tc = tcp->cell + tcidx;

  if (Debug) printf ("tgt cellpop %d tgt cell %d syntype offset %d cell count: %d\n", tcpidx, tcidx, tp->TYPE, tcp->cell_count);
  fflush(stdout);

  BOUNDS (tcpidx, S.net.cellpop_count);
  BOUNDS (tcidx, tcp->cell_count);
  BOUNDS (tcidx, S.net.cellpop[tcpidx].cell_count);
  BOUNDS (tp->TYPE - 1, S.net.syntype_count);

  if (synapse[tcpidx][tcidx][tp->TYPE-1].ptr == 0) 
  {
    synapse[tcpidx][tcidx][tp->TYPE-1].ptr++; // used as NZ flag, later replaced by real ptr
    tc->syn_count++;
  }
  if (qidx > synapse[tcpidx][tcidx][tp->TYPE-1].maxqidx)
    synapse[tcpidx][tcidx][tp->TYPE-1].maxqidx = qidx;
   if (Debug) printf("count_to_synapses: ptr, maxqidx for synapse[%d][%d][%d] is %p %d\n",tcpidx,tcidx,tp->TYPE-1, synapse[tcpidx][tcidx][tp->TYPE-1].ptr, synapse[tcpidx][tcidx][tp->TYPE-1].maxqidx);
}


/* func choices are:
   count_to_synapses(...)
   attach_to_synapses(...) 
*/
static inline void
for_cell_targets (void (*func)(TargetPop*, CellPop*, Target*, int, int, int))
{
  {if(Debug) printf(" for_cell_targets\n");}
  int cpidx;
  for (cpidx = 0; cpidx < S.net.cellpop_count; cpidx++)  // for each pop
  {
    CellPop *cp = S.net.cellpop + cpidx;
    int cidx;
    for (cidx = 0; cidx < cp->cell_count; cidx++)    // for each cell
    {
      Cell *c = cp->cell + cidx;
      int tpidx, tidx0 = 0;
      for (tpidx = 0; tpidx < cp->targetpop_count; tpidx++)  // for each target
      {
        TargetPop *tp = cp->targetpop + tpidx;
        int iseed = (cidx + 1) * tp->INSED;
        if (c->target == 0) 
        {
          if(Debug) printf ("S.net.cellpop[1].cell[4].target: %lx\n", (long)S.net.cellpop[1].cell[4].target);
          if(Debug) printf ("cell %d of pop %d target is not set.  targetpop_count = %d\n",
             cidx, cpidx, cp->targetpop_count);
          DIE;
        }
        tp->NT >= 0 || DIE;
        if (tp->NT > 0) 
        {
          BOUNDS (tidx0 + tp->NT - 1, c->target_count);
          if(Debug) printf("for cell terminals\n");
          for_terminals (iseed, c->target, c->target_count, tp, tidx0, func);
          tidx0 += tp->NT;
        }
      }
    }
  }
}

/* func choices are:
   count_to_synapses(...)
   attach_to_synapses(...) 
*/
static inline void
for_fiber_targets (void (*func)(TargetPop*, CellPop*, Target*, int, int, int))
{
if(Debug) printf("   for_fiber_targets\n");
  int fpidx;
  for (fpidx = 0; fpidx < S.net.fiberpop_count; fpidx++)  // for each pop
  {
    FiberPop *fp = S.net.fiberpop + fpidx;
    int fidx;
    for (fidx = 0; fidx < fp->fiber_count; fidx++)   // for each fiber
    {
      Fiber *f = fp->fiber + fidx;
      int tpidx, tidx0 = 0;
      for (tpidx = 0; tpidx < fp->targetpop_count; tpidx++)  // for each terminal
      {
        TargetPop *tp = fp->targetpop + tpidx;
        int iseed = (fidx + 1) * tp->INSED;
        tp->NT >= 0 || DIE;
        if (tp->NT > 0) 
        {
          BOUNDS (tidx0 + tp->NT - 1, f->target_count);
          if(Debug) printf("for fiber terminals\n");
          for_terminals (iseed, f->target, f->target_count, tp, tidx0, func);
          tidx0 += tp->NT;
        }
      }
    }
  }
}

int
st (float eq, float dcs)
{
  if (eq == 115 && fabs (dcs - 0.71653131057378925043) < .000001) return 1;
  if (eq == -25 && fabs (dcs - 0.71653131057378925043) < .000001) return 2;
  if (eq == 115 && fabs (dcs - 0.77880078307140486825) < .000001) return 3;
  if (eq == -25 && fabs (dcs - 0.77880078307140486825) < .000001) return 4;
  return 99999999;
}

// This checks the allocated q arrays to be 0 if normal
// or 1 if presynaptic modifiers are being used.
// Exits on error. This, of course, should "never" happen
void
check_synapses (void)
{
  int cpidx;
  for (cpidx = 0; cpidx < S.net.cellpop_count; cpidx++) 
  {
    CellPop *cp = S.net.cellpop + cpidx;
    int cidx;
    for (cidx = 0; cidx < cp->cell_count; cidx++) 
    {
      Cell *c = cp->cell + cidx;
      int sn;
      for (sn = 0; sn < c->syn_count; sn++) 
      {
        int qn;
        for (qn = 0; qn < c->syn[sn].q_count; qn++)
        {
          if(Debug) printf("cell->syn[%d].q[%d] = %lf\n", sn,qn,c->syn[sn].q[qn]);
          if (!(c->syn[sn].q[qn] == 0 || (c->syn[sn].q[qn] == 1 && S.ispresynaptic))) 
          {
            printf ("transmit: cell %d pop %d syn %d qval %d of %d is %a\n",
               cidx, cpidx, sn, qn, c->syn->q_count, c->syn[sn].q[qn]);
            fflush(stdout);
            DIE; // todo this should not be a fatal error
          }
        }
      }
    }
  }
}

/* Polar (Box-Mueller) method; See Knuth v2, 3rd ed, p122 */
static double
ran_gaussian (int seed)
{
  double x, y, r2;
  static int irand = 38986022; //randomly chosen seed

  if (seed) {
    irand = seed; 
    return 0;
  }
  
  do
    {
      /* choose x,y in uniform square (-1,-1) to (+1,+1) */

      x = -1 + 2 * ran (&irand);
      y = -1 + 2 * ran (&irand);

      /* see if it is in the unit circle */
      r2 = x * x + y * y;
    }
  while (r2 > 1.0 || r2 == 0);

  /* Box-Muller transform */
  return y * sqrt (-2.0 * log (r2) / r2);
}

void
build_network ()
{
  int cpidx, fpidx;

  static int seed[] = {2,3,7,12,14,15,16,17,19,20,22,23,24,25,26,29,35,36,39,
             42,45,47,48,49,50,51,52,53,54,56,57,59,61,63,64,66,67,
             69,75,78,79,80,83,84,85,86,87,89,90,91,95,97,98};

  /* values to match old behavior on sparc-v1 */
  static int rgseed[43] = {38986022, 1391292912, -146887594, -1953281662, 329184802, 1192591352,
                           -1719851788, -1818740196, 1864492360, -900638728, -1188332476,
                           341092380, -930484606, 336680986, 336680986, 829766224, 755328026,
                           1360987778, -1078372960, -1685500086, 1152748448, -1089100128,
                           -648232574, -776959814, -1810241108, -1074979646, -1932475256,
                           -814349978, 1703279180, -715985718, 362197582, -2079242792, 909292898,
                           -1932739534, -1381483014, 996303780, 1049529372, -1878520724,
                           1116996432, -631444766, -356560908, 1525966756, -516425190};


  /* Allocate the cells */
  int seed_size = (sizeof seed / sizeof seed[0])-1;
  int last_seed = seed[seed_size];

 if(Debug) printf("allocate array of ptrs for %d pops\n",S.net.cellpop_count);

  TMALLOC (synapse, S.net.cellpop_count);

  for (cpidx = 0; cpidx < S.net.cellpop_count; cpidx++) 
  {
    if(Debug) printf(" cell pop %d\n",cpidx);
    CellPop *cp = S.net.cellpop + cpidx;
    int target_count = 0, tpidx, cidx;
    cp->noise_seed = cpidx > seed_size ? last_seed + cpidx : seed[cpidx];

    if (Debug) printf("allocate array of ptrs in synapse[%d] for %d cells\n",cpidx,cp->cell_count);
    TMALLOC (synapse[cpidx], cp->cell_count);

    for (tpidx = 0; tpidx < cp->targetpop_count; tpidx++)
      target_count += cp->targetpop[tpidx].NT;

    if(Debug) printf("allocate array of ptrs in S.net.cellpop+%d for %d cells\n",cpidx,cp->cell_count);
    TCALLOC (cp->cell, cp->cell_count);
    if (!getenv ("SIM_OLDRAN")) // this is undocumented, just used for testing/debugging??
       ran_gaussian(cpidx < 43 ? rgseed[cpidx] : 100 + cpidx); // set seed for this cell pop

    for (cidx = 0; cidx < cp->cell_count; cidx++) 
    {
      Cell *c = cp->cell + cidx;
      if (Debug) printf("allocate array of %d ptrs in synapse[%d][%d] for synapse types\n",S.net.syntype_count, cpidx,cidx);
      TCALLOC (synapse[cpidx][cidx], S.net.syntype_count);
      c->Vm = S.Vm0;
      c->Thr = cp->Th0 + ran_gaussian (0) * cp->Th0_sd;
      c->target_count = target_count;
      if (Debug) printf("allocate array of ptrs in S.net.cellpop.target+%d for %d targets\n",cpidx,c->target_count);
      TMALLOC (c->target, c->target_count);
    }
  }

  /* Allocate the fibers */
  for (fpidx = 0; fpidx < S.net.fiberpop_count; fpidx++) 
  {
    FiberPop *fp = S.net.fiberpop + fpidx;
    int target_count = 0, tpidx, fidx;

    // adjust start and start in ms to ticks
    if (Debug) printf("start,stop in ms: %d  %d\n",fp->start, fp->stop);
    fp->start = ceil(fp->start / S.step);
    fp->stop = ceil(fp->stop / S.step);
    if (Debug) printf("start,stop in ticks: %d  %d\n",fp->start, fp->stop);

    if (fp->pop_subtype == ELECTRIC_STIM) // this needs a couple of other inits
    {
       fp->next_stim = fp->start;
       fp->next_fixed = fp->start;
       printf("step: %f first stim at %d  %d\n",
             S.step, 
             fp->start,
             fp->next_stim);
    }

    for (tpidx = 0; tpidx < fp->targetpop_count; tpidx++)
      target_count += fp->targetpop[tpidx].NT;

    if (Debug)printf("\nallocate array of %d fibers for fiber pop %d in S.net.fiberpop + %d\n",fp->fiber_count,fpidx, fpidx);
    TCALLOC (fp->fiber, fp->fiber_count);

    for (fidx = 0; fidx < fp->fiber_count; fidx++) {
      Fiber *f = fp->fiber + fidx;
      f->target_count = target_count;
      if (Debug)printf("allocate %d ptrs in S.net.fiberpop[%d].target\n",f->target_count,fidx);
      TMALLOC (f->target, f->target_count);
    }
  }
      if (Debug)printf("call for_cell_targets, fnc is count_to_synapses\n");
  for_cell_targets (count_to_synapses);
      if (Debug)printf("call for_fiber_targets, fnc is count_to_synapses\n");
  for_fiber_targets (count_to_synapses);

   /* Allocate synapses */
  for (cpidx = 0; cpidx < S.net.cellpop_count; cpidx++) 
  {
    CellPop *cp = S.net.cellpop + cpidx;
    if (Debug)printf("cell count: %d\n",cp->cell_count);
    int cidx;
    {if (Debug) printf("cell pop %d\n",cpidx);}
    for (cidx = 0; cidx < cp->cell_count; cidx++) 
    {
      Cell *c = cp->cell + cidx;
      int stidx;
      Syn *syn;
      {if(Debug) printf("\nallocate %d slots in Syn array\n",c->syn_count);}
      TCALLOC (c->syn, c->syn_count);
      syn = c->syn;
      for (stidx = 0; stidx < S.net.syntype_count; stidx++) 
      {
        {if (Debug) printf("syn type array idx (stidx): %d\n",stidx);}
        SynType *stp = S.net.syntype + stidx;
        BOUNDS (cidx, S.net.cellpop[cpidx].cell_count);
        if (synapse[cpidx][cidx][stidx].ptr != 0) 
        {
          {if(Debug) printf("Cell pop %d cell %d\n",cpidx,cidx);}

          int n;
          BOUNDS (syn - c->syn, c->syn_count);
          syn->EQ = stp->EQ;
          syn->DCS = stp->DCS;
          syn->q_count = synapse[cpidx][cidx][stidx].maxqidx + 1;
          syn->cpidx = cpidx;
          syn->cidx = cidx;
          syn->stidx = stidx;
          syn->syntype = stp->SYN_TYPE;
          syn->synparent = stp->PARENT;

          {if (Debug) printf("add to synapse list:\n    EQ: %f\n    DCS:%f\n    q_count: %d\n    refers to synapse[%d][%d][%d]  type: %d parent: %d\n",
          syn->EQ,
          syn->DCS,
          syn->q_count,
          syn->cpidx,
          syn->cidx,
          syn->stidx,
          syn->syntype,
          syn->synparent);}

          TCALLOC (syn->q, syn->q_count);
          if (stp->SYN_TYPE == SYN_NOT_USED) // a bug
            fprintf(stderr,"Unexpected unused synapse in list\n");
          if (S.ispresynaptic && stp->SYN_TYPE != SYN_NORM)
          {
            if (stp->SYN_TYPE == SYN_PRE)
            {
              if (Debug) printf("add PRE to syn->q [%d][%d][%d]\n",cpidx,cidx,stidx);
            }
            else if (stp->SYN_TYPE == SYN_POST)
            {
              if (Debug) printf("add POST to syn->q [%d][%d][%d]\n",cpidx,cidx,stidx);
            }
            for (n = 0; n < syn->q_count; n++)
            {
              syn->q[n] = 1;             // initial conductance value (I think)
              if (Debug) printf(" syn[%d] = 1\n",n);
            }
          }
          synapse[cpidx][cidx][stidx].ptr = syn++;
        }
      }
      syn - c->syn == c->syn_count || DIE;
    }
  }

  if (Debug) printf("call for_cell_targets, fnc is attacth_to_synapses\n");
  for_cell_targets (attach_to_synapses);
  if (Debug) printf("call for_fiber_targets, fnc is attach_to_synapses\n");
  for_fiber_targets (attach_to_synapses);
  check_synapses ();
}
