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
#define _GNU_SOURCE

#include <QtGlobal>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <regex.h>
#include <assert.h>
#include <time.h>
#if defined __linux__
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif
#include "simulator.h"
#include "fileio.h"
#include "simulator_hash.h"
#include "lung.h"
#include "expr.h"
#include "inode.h"
#include "lin2ms.h"
#include "wavemarkers.h"
#include "simrun_wrap.h"

#ifdef __linux__
extern int sock_fd;
extern int sock_fdout;
#elif defined WIN32
extern SOCKET sock_fd;
extern SOCKET sock_fdout;
#else
#pragma message("WARNING: Unknown environment configuration, not Linux or Windows")
#endif
extern bool Debug;
extern int use_socket;
extern int write_waves;
extern int write_bdt;
extern int write_analog;
extern int write_smr;
extern int write_smr_wave;
extern int isedt;
extern char *fmt;
extern double dt_step;
extern char simmsg[];
extern char inPath[];
extern char outPath[];

time_t global_last_time;
extern void destroy_cmd_socket();
extern void destroy_view_socket();

struct StructInfo *(*struct_info_fn) (const char *str, unsigned int len) = simulator_struct_info;
struct StructMembers *(*struct_members_fn) (const char *str, unsigned int len) = simulator_struct_members;

/*
; exp(-.5/2)
        0.77880078307140486825
; exp(-.5/1.5)
        0.71653131057378925043
*/

extern int st (float eq, float dcs);

static const double g_L = 2.8;
static const double E_Na = 50;
static const double E_L = -65;

char wave_buf[1024*64];

bool have_cmd_socket()
{
#ifdef __linux__
  if (sock_fd)
#else
  if (sock_fd != INVALID_SOCKET)
#endif
    return 1;
  else
    return 0;
}

bool have_data_socket()
{
#ifdef __linux__
  if (sock_fdout)
#else
  if (sock_fdout != INVALID_SOCKET)
#endif
    return 1;
  else
    return 0;
}

// this was for initial testing on ways to use afferent inputs 
#if 0
typedef struct { double x;  // bp or other value
                double y;  // probabilty for this value
               } Points;

static const double bpl = 120;
static const double bp0 = 140;
static const double bph = 160;

//static const double pl = 0.0;
//static const double p0 = 0.5;
//static const double ph = 0.9;

static const double pl = 0.00;
static const double p0 = 0.05;
static const double ph = 0.08;

static double Hz = 3.0;

Points pts[] = {{bpl,pl},{bp0,p0},{bph,ph}};

// function to interpolate the given data points using linear interpolation.
// xi corresponds to the new data point whose value is to be obtained
// n represents the number of known data points
// Data is the array with the points
static double interpolate(Points f[], double xi, int n)
{
   double result = 0; 
   for (int i=0; i<n; i++)
   {
      // Compute individual terms of above formula
      double term = f[i].y; 
      for (int j=0 ; j<n; j++) 
      {
         if (j!=i) 
            term = term * (xi - f[j].x) / (f[i].x - f[j].x);
      }
      result += term; 
   }
   return result;
}

static Points *Prob;
static size_t ProbLen;

// figure out # of ticks for Hz seconds, then calculate sine values from 0 to
// 2pi for that many slots
static void makeProb()
{
   unsigned int ticks_in_sec = ceil(1000.0/S.step);
   ProbLen = ticks_in_sec * Hz;
   int len = sizeof(pts)/sizeof(Points);
   printf("ts: %u steps: %lu len: %d\n",ticks_in_sec, ProbLen,len);
   Prob = (Points*) malloc(ProbLen*sizeof(Points));
   Points *prob = Prob;
   double val, res;
   double stepsize = (2*M_PI)/ProbLen;
   int slots = 0;
   for (double i = 0.0;  slots < ProbLen ; i+= stepsize, ++slots)
   {
      val = sin(i) * ((bph-bpl)/2.0)+bp0; // scale to 120 - 160
      res = interpolate(pts,val,len);
      printf("%lf %lf %lf\n",i,val,res);
      prob->x = val;
      prob->y = res;
      ++prob;
   }
}
#endif

// Given current afferent input value for a fiber pop, return
// the corresponding probabilty using linear interpolation
// on the value to probability lookup table for this population.
// Values outside the range return 0.
static double interpolate(FiberPop *fp, double curr_val)
{
   int num = fp->num_aff - 1;
   int idx;
   double result = 0.0; 
   for (idx = 0; idx < num; ++idx)
   {
      if (curr_val >= fp->aff_val[idx] && curr_val < fp->aff_val[idx+1])
      {   
         result = (fp->aff_prob[idx+1]  - fp->aff_prob[idx]) 
                  / (fp->aff_val[idx+1] - fp->aff_val[idx])
                  * (curr_val - fp->aff_val[idx]) + fp->aff_prob[idx];
         break;
      }
   }
   return result;
}


// Send the simulation plot results directly to simviewer.
static void send_wave()
{
  size_t to_send;
  size_t sent = 0, total_sent = 0;
  char* ptr = wave_buf;

  if (have_data_socket())
  {
    to_send = strlen(wave_buf);
    while (total_sent != to_send)
    {
#ifdef __linux__
      sent = send(sock_fdout, (void*)ptr,to_send,0); // blocking i/o
      if (sent == -1 && errno == EPIPE) // lost connection
      {
         fprintf(stderr,"SIMRUN: Connection to simviewer lost.\n");
         fflush(stderr);
         destroy_view_socket();
         return;
      }
      else if (sent == -1)
      {
         perror("SIMRUN");
         continue;
      }
      else
      {
         total_sent += sent;
         ptr += sent;
      }
#else
      sent = send(sock_fdout, (void*)ptr,to_send,0);
      if (sent == SOCKET_ERROR)
      {
         int sockerr = WSAGetLastError();
         if (sockerr == WSAECONNRESET || sockerr == WSAECONNABORTED)
            fprintf(stderr,"Connection to simviewer lost.\n");
         else
            fprintf(stderr,"Socket error is %d\n",sockerr);
         fflush(stderr);
         destroy_view_socket(); // most errors are fatal
         return;
      }
      else
      {
         total_sent += sent;
         ptr += sent;
      }
#endif
    }
    total_sent += sent;
    ptr += sent;
  }
  fflush(stdout);
}

// If simviewer (or other program) is getting wave info from a socket, wait
// until that side tells us it has got all of the packets. We do this by
// sending an EOF msg, then wait for the other side to tell us it got it
// on the same socket we are sending to.
// This can hang here forever in some cases.
void waitForDone()
{
  int got;
  char in[1];

  if (have_data_socket())
  {
    wave_buf[0] = MSG_EOF;
    wave_buf[1] = 0;
    send_wave();
    if (have_data_socket())
    {
      got = recv(sock_fdout,in,sizeof(in),0); // block until it shows up
      if (got > 0 && (unsigned char) in[0] != MSG_EOF)
        printf("got unexpected msg from simviewer, still done\n");
    }
  }
  fflush(stdout);
}

// send via network or write results to the next wave file
static void
simoutsned (void)
{
  static int recctr, flctr, nrecs;
  static FILE *wfile = 0;
  int n;
  static char *wfile_name=0;
  static char *wfile_name_tmp=0;
  static char *buffptr=wave_buf;
  char line[80];
  int time = (int)((S.stepnum + 1) * S.step / dt_step);

  if (!have_data_socket() && !write_waves) // if using socket and other side died, nothing to do
    return;
  if (recctr == 0)  // new wave block set up
  {
    nrecs = S.step_count - S.stepnum >= 100 ? 100 : S.step_count - S.stepnum;
 
    if (have_data_socket())
    {
      sprintf(line,"%c%d\n%d\n", MSG_START, S.spawn_number,flctr);
      memcpy(buffptr,line,strlen(line)); // don't want null
      buffptr += strlen(line);
      sprintf (line, "%12d %f\n", nrecs, S.step);
      memcpy(buffptr,line,strlen(line));
      buffptr += strlen(line);
      sprintf (line, "%12d\n", S.plot_count);
      memcpy(buffptr,line,strlen(line));
        buffptr += strlen(line);
      for (n = 0; n < S.plot_count; n++)
      {
        sprintf(line, "%3d %3d %3d %d %s\n", S.plot[n].pop, S.plot[n].cell, S.plot[n].var, S.plot[n].type, S.plot[n].lbl);
        memcpy(buffptr,line,strlen(line));
        buffptr += strlen(line);
      }
      for (n = 0; n < S.plot_count; n++)
      {
        sprintf (line, "%12.8f %d\n", S.plot[n].val, S.plot[n].spike);
        memcpy(buffptr,line,strlen(line));
        buffptr += strlen(line);
        if (write_smr_wave)
        {
           if (S.plot[n].var != -17) // no waveforms for events
              writeWaveForm(n,time,S.plot[n].val);
           if (S.plot[n].spike)
              writeWaveSpike(n, time);
        }
      }
    }
    else // writing files
    {
       // don't let simviewer see file until it is complete
       // write header and first block of wave values
      if (asprintf (&wfile_name, "%swave.%02d.%04d", outPath, S.spawn_number, flctr) == -1) exit (1);
      if (asprintf (&wfile_name_tmp, "%swave.%02d.%04d.tmp", outPath, S.spawn_number, flctr) == -1) exit (1);
      (wfile = fopen (wfile_name_tmp, "w")) || DIE;
      fprintf (wfile, "%12d %f\n", nrecs, S.step);
      fprintf (wfile, "%12d\n", S.plot_count);
      for (n = 0; n < S.plot_count; n++)
        fprintf (wfile, "%3d %3d %3d %d %s\n", S.plot[n].pop, S.plot[n].cell, S.plot[n].var, S.plot[n].type, S.plot[n].lbl);
      for (n = 0; n < S.plot_count; n++)
      {
        fprintf (wfile, "%12.8f %d\n", S.plot[n].val, S.plot[n].spike);
        if (write_smr_wave)
        {
           if (S.plot[n].var != -17)
              writeWaveForm(n,time,S.plot[n].val);
           if (S.plot[n].spike)
              writeWaveSpike(n, time);
        }
      }
    }
    ++recctr;
    return;
  }
     // set up done if here, accumlate results
  for (n = 0; n < S.plot_count; n++)  
  {
    sprintf (line, "%12.8f %d\n", S.plot[n].val, S.plot[n].spike);
    if (have_data_socket())
    {
      memcpy(buffptr,line,strlen(line));
      buffptr += strlen(line);
    }
    else
    {
      fprintf (wfile, "%12.8f %d\n", S.plot[n].val, S.plot[n].spike);
    }
    if (write_smr_wave)
    {
       if (S.plot[n].var != -17)
          writeWaveForm(n,time,S.plot[n].val);
       if (S.plot[n].spike)
         writeWaveSpike(n, time);
    }
  }
  if (++recctr == nrecs) 
  {
    if (use_socket)
    {
       sprintf(line,"%c", MSG_END);
       memcpy(buffptr,line,strlen(line));
       buffptr += strlen(line);
       send_wave();
       buffptr = wave_buf;
       memset (wave_buf, 0, sizeof(wave_buf));
    }
    else
    {
       // Note: when testing this with Win10 in a VM from time to time, closing
       // the file does not actually result in a file with anything in it.
       // When simviewer tries to read it, it sees an empty file after we rename it.
       // This has not been reported native Win10, so I guess it is a VM problem.
       // Flushing seems to make this not happen.
       fflush(wfile); 
       fclose (wfile); 
       rename(wfile_name_tmp,wfile_name);
       free (wfile_name);
       free (wfile_name_tmp);
    }
    recctr = 0;
    if (++flctr == 10000)  // wrap 9999+1 back to 0.
      flctr = 0;
  }
}

#define SQR(a) ((a)*(a))

static bool
check_lung_used (void)
{
  for (int pn = 0; pn < S.net.cellpop_count; pn++)
    if (S.net.cellpop[pn].ic_expression)
      return true;
  return false;
}

typedef struct
{
  int count;
  char *name;
  char *var;
  int *num;
  double *rate;
} PopList;

typedef struct
{
  PopList phrenic;
  PopList abdominal;
  PopList pca;
  PopList ta;
  PopList expic;
  PopList inspic;
} MotorPops;

static void
mup_error (muParserHandle_t hParser)
{
  char *msg, *cmd;
  if (asprintf (&msg,
                "\"Fatal error parsing the equation \"%s\"\n"
                "Message:  \"%s\"\n"
                "Token:    \"%s\"\n"
                "Position: %d\n"
                "Errc:     %d\n\"",
                mupGetExpr (hParser),
                mupGetErrorMsg(hParser),
                mupGetErrorToken(hParser),
                mupGetErrorPos(hParser),
                mupGetErrorCode(hParser)) == -1) exit (1);
    if (asprintf (&cmd, "%s %s %s", simmsg, "\"SIMRUN ERROR\"", msg) == -1) exit (1);
  if (system (cmd))
  {}
  free(msg);
  free(cmd);
  error (1, 0, "%s", msg);
}

static double
spikes_per_s_per_cell (int pn)
{
  CellPop *p = S.net.cellpop + pn;
  int spike_count = 0;
  for (int cn = 0; cn < p->cell_count; cn++)
    spike_count += p->cell[cn].spike;
  if (0) {
    static FILE *f;
    if (f == NULL) f = fopen ("phrenic_spike_counts", "w");
    if (pn == 24) fprintf (f, "%d", spike_count);
    if (pn == 43) fprintf (f, " %d\n", spike_count);
  }
  
  return (double)spike_count / p->cell_count / (S.step / 1000);
}

double
mup_eval (PopList pops, char *eqn, void **parser)
{
  if (eqn == NULL) {            /* PCA or TA */
    if (pops.num[0] < 0) 
      error_at_line (1, 0, __FILE__, __LINE__, "No %s0 pop found", pops.name);
    return spikes_per_s_per_cell (pops.num[0]);
  }
  if (*parser == NULL) {
    *parser = mupCreate (muBASETYPE_FLOAT);
    mupSetErrorHandler (*parser, mup_error);
    for (int i = 0; i < pops.count; i++)
      if (pops.num[i] >= 0) {
        char *varname;
        if (asprintf (&varname, "%s%d", pops.var, i) == -1) exit (1);
        mupDefineVar(*parser, varname, &pops.rate[i]);  
        free (varname);
      }
    mupSetExpr (*parser, eqn);
  }
  
  for (int i = 0; i < pops.count; i++)
    if (pops.num[i] >= 0)
      pops.rate[i] = spikes_per_s_per_cell (pops.num[i]);

  return mupEval (*parser);
}

PopList
get_poplist_by_name (char *name, char *n2, char *var)
{
  char *regex;
  regex_t re, re_pre;
  char *pattern = "(^|[^[:alnum:]])%s([0-9]+)?($|[^[:alnum:]])";
  if (asprintf (&regex, pattern, name) == -1) 
    exit (1);

  if (regcomp (&re, regex, REG_EXTENDED | REG_ICASE)) 
    error (1, 0, "%s", "poplist regcomp failed");
  free (regex);

  if (asprintf (&regex, pattern, "pre") == -1)
     exit (1);
  if (regcomp (&re_pre, regex, REG_NOSUB | REG_EXTENDED | REG_ICASE)) 
    error (1, 0, "%s", "poplist regcomp pre failed");
  free (regex);

  PopList pl = {0};
  pl.name = name;
  pl.var = var;

  int count = 0;
  for (int pn = 0; pn < S.net.cellpop_count; pn++) 
  {
    regmatch_t pmatch[3];
    if (S.net.cellpop[pn].name
        && regexec (&re, S.net.cellpop[pn].name, 3, pmatch, 0) == 0
        && regexec (&re_pre, S.net.cellpop[pn].name, 0, 0, 0) != 0) 
    {
      int pli = 0;
      if (pmatch[2].rm_eo > pmatch[2].rm_so)
        pli = atoi (S.net.cellpop[pn].name + pmatch[2].rm_so);
      if (pli >= pl.count) {
        int newcount = pli + 1;
        pl.num = realloc (pl.num, newcount * sizeof *pl.num);
        pl.rate = realloc (pl.rate, newcount * sizeof *pl.rate);
        for (int i = pl.count; i < newcount; i++)
          pl.num[i] = -1;
        pl.count = newcount;
      }
      if (pl.num[pli] != -1) 
      {
        char *msg, *cmd;
        if (asprintf (&msg,
                      "\"%d %d %d\n"
                      "There is more than one population with the word %s in its name\n"
                      "numbered %d and without the word \"pre\"\n"
                      "There must be exactly one.  Aborting sim...\n\"",
                      pn, pl.num[pli], pli,
                      n2 ? n2 : name, pli) == -1) exit (1);
        if (asprintf (&cmd, "%s %s %s", simmsg, "\"SIMRUN ERROR\"", msg) == -1) exit (1);
        if (system (cmd)) {}
        error (1, 0, "%s", msg);
      }
      pl.num[pli] = pn;
      count++;
    }
  }
  if (count == 0) 
  {
    char *msg, *cmd;
    if (asprintf (&msg,
                  "\"There are no populations with the word %s in their names\n"
                  "and without the word \"pre\"\n"
                  "There must be exactly one.  Aborting sim...\n\"", n2 ? n2 : name) == -1) exit (1);
    if (asprintf (&cmd, "%s %s %s", simmsg, "\"SIMRUN ERROR\"", msg) == -1) exit (1);
    if (system (cmd)) {}
    error (1, 0, "%s", msg);
    free(msg);
    free(cmd);
  }
  regfree (&re);
  regfree (&re_pre);
  return pl;
}

static MotorPops
get_motor_pops (void)
{
  MotorPops m;
  m.phrenic = get_poplist_by_name ("phrenic", "\"phrenic\"", "P");
  m.abdominal = get_poplist_by_name ("lumbar", "\"lumbar\"", "L");
  m.pca = get_poplist_by_name ("(PCA|ILM)", "\"PCA\" or \"ILM\"", "");
  m.ta = get_poplist_by_name ("(TA|ELM)", "\"TA\" or \"ELM\"", "");
#ifdef INTERCOSTALS
  m.expic = get_poplist_by_name ("int", "\"int\"", "");
  m.inspic = get_poplist_by_name ("ext", "\"ext\"", "");
#endif
  return m;
}

static State state;

static inline double
get_GE0 (CellPop *p)
{
  if (!p->ic_expression)
    return p->GE0;
  if (!p->ic_evaluator)
    assert ((p->ic_evaluator = (char *) xp_set (p->ic_expression)));
  return xp_eval ((Expr *)p->ic_evaluator, state.volume);
}

static double
limit (double x, double lo, double hi)
{
  if (x > hi)
    return hi;
  else if (x < lo)
    return lo;
  return x;
}


/*
This gets called a once per simulation loop. I benchmarked it an on my
laptop it takes about 700 microseconds to run, so, not a lot of overhead.
If a paused msg, we stay here until we get a resume or terminate.

*/

void chk_for_cmd()
{
  int got;
  char msg[1];
  bool pause;

  if (!have_cmd_socket()) // check for commands if started up by simbuild
    return;
  pause = false;

  do
  {
    msg[0] = 0;
#ifdef __linux__
    got = recv(sock_fd,msg,sizeof(msg),MSG_DONTWAIT);
    if (got == 0 && errno == EPIPE)
    {
      fprintf(stderr,"Connection to simbuild lost.\n");
      fflush(stderr);
      destroy_cmd_socket();
      return;
    }
    else if (got == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
    {
     fprintf(stderr,"SIMRUN: Error getting msg from simbuild, error is: %d\n",errno);
      fflush(stderr);
    }
#else
    got = recv(sock_fd,msg,sizeof(msg),0); // was set to nonblocking in setup
    if (got == SOCKET_ERROR)
    {
      int err = WSAGetLastError();
      if (err != WSAEWOULDBLOCK)
      {
        if (err != WSAECONNRESET)  // simviewer went away
        {
          fprintf (stderr,"Error getting msg from simbuild, error is: %d\n",WSAGetLastError());
        }
        else
          fprintf(stderr,"Connection to simbuild lost.\n");
        fflush(stderr);
        destroy_cmd_socket();
        return;
      }
    }
#endif
    if (msg[0] == 'P') // pause
    {
      pause = true;
      fprintf(stderr,"Pausing\n");
      fflush(stderr);
    }
    else if (msg[0] == 'R')  // resume
    {
      pause = false;
      fprintf(stderr,"Starting back up\n");
      fflush(stderr);
    }
    else if (msg[0] == 'U') // update
    {
      update ();
    }
    else if (msg[0] == 'T') // terminate
    {
      sigterm = true;
      pause = false;
      fprintf(stderr,"simrun got terminate command\n");
      fflush(stderr);
    }
    else if (msg[0] != 0) // unknown msg
    {
      fprintf(stderr,"Got unknown command %c\n",msg[0]);
      fflush(stderr);
    }
    if (pause) // .5 sec
    {
      usleep(500000); // We can hang here forever if simbuild goes away
                      // without unpausing us, but we could also be
    }                 // paused over the weekend, so there is no "too long"
  } while (pause);
}

/* This is the simulation calculation engine.
*/
void simloop ()
{
  int nf;
  double noise_decay = exp (-S.step / 1.5);
  S.seed = 314159;
  double ticks_in_sec = ceil(1000.0/S.step);
  char msg[2048];
  bool lung_is_used = check_lung_used ();
  bool doFibCalc, skipFib;
  MotorPops m;
  if (Debug)
    fprintf (stderr, "\n%s line %d, cellpop_count %d\n", __FILE__, __LINE__,
             S.net.cellpop_count);

  if (lung_is_used) 
  {
    if (!S.phrenic_equation || S.phrenic_equation[0] == 0)
      S.phrenic_equation = strdup ("P0/100");
    if (!S.lumbar_equation || S.lumbar_equation[0] == 0)
      S.lumbar_equation = strdup ("L0/20");
    m = get_motor_pops ();

    fprintf(stderr,"motor pops are: phrenic");
    for (int i = 0; i < m.phrenic.count; i++)
      if (m.phrenic.num[i] >= 0)
        fprintf(stderr," %d", m.phrenic.num[i] + 1);
    fprintf(stderr,", abdominal");
    for (int i = 0; i < m.abdominal.count; i++)
      if (m.abdominal.num[i] >= 0)
        fprintf(stderr," %d", m.abdominal.num[i] + 1);
    fprintf (stderr,", elm/ta %d, ilm/pca %d", m.ta.num[0] + 1, m.pca.num[0] + 1);
#ifdef INTERCOSTALS
    fprintf(stderr,", ext %d, int %d", m.ta.num[0] + 1, m.pca.num[0] + 1, m.inspic.num[0] + 1, m.expic.num[0] + 1);
#endif
    fprintf(stderr,"\n");
    
    state = lung ((Motor) {0,0,0,0}, S.step);
  }
  else 
     fprintf(stderr,"Lung model is not used\n");
  if (Debug)
  {
     fprintf (stderr, "\n%s line %d, cellpop_count %d\n", __FILE__, __LINE__,
               S.net.cellpop_count);
     fprintf (stderr, "\n%s line %d\n", __FILE__, __LINE__);
  }

   // MAIN LOOP, work until done or get a TERM signal or get a quit command
  for ( ; S.stepnum < S.step_count && !sigterm; S.stepnum++) 
  {
    double GEsum0;
    int pn;
    static time_t now, last_time = 0;

    Motor mr;
    State next_state = {0};

    if (lung_is_used) 
    {
      mr.phrenic = mup_eval (m.phrenic, S.phrenic_equation, &S.pe_evaluator);
      mr.abdominal = mup_eval (m.abdominal, S.lumbar_equation, &S.le_evaluator);
      mr.pca = mup_eval (m.pca, 0, 0);
      mr.ta = mup_eval (m.ta, 0, 0);
#ifdef INTERCOSTALS
      mr.expic = mup_eval (m.expic, 0, 0);
      mr.inspic = mup_eval (m.inspic, 0, 0);
#endif
      next_state   = lung (mr, S.step);
    }

    if (have_cmd_socket() && (S.stepnum % (int) ticks_in_sec) == 0)
    {
        snprintf(msg,sizeof(msg)-1,"TIME\n%d\n", (int)(S.stepnum/ticks_in_sec));
        send(sock_fd,&msg,strlen(msg),0); // progress rpt for simbuild 
    }
    if ((now = time (0)) > last_time)
	    global_last_time = last_time = now;

    nf = 0;
    for (pn = 0; pn < S.net.cellpop_count; pn++)  // cells
    {
      CellPop *p = S.net.cellpop + pn;
      int cn;
      for (cn = 0; cn < p->cell_count; cn++) 
      {
        Cell *c = p->cell + cn;
        double Gsum = 0, GEsum = 0, Prob = 0, Vm, Gk;
        int sidx, tidx, pp_idx;

        for (sidx = 0; sidx < c->syn_count; sidx++) 
        {
          Syn *s = c->syn + sidx;
          if (S.ispresynaptic) 
          {
            int type_of_syn = S.net.syntype[s->stidx].SYN_TYPE;
            if (type_of_syn == SYN_NOT_USED) // you've got a bug
              fprintf(stderr,"Unexpected unused synapse in simloop\n");
            if (type_of_syn == SYN_NORM)
            {
               Syn *chk = c->syn;
               double post = 1;
                  // do we have a post item associated with us?
               for (pp_idx = 0; pp_idx < c->syn_count; ++pp_idx, ++chk) 
               {
                  if (chk->synparent && chk->synparent == s->stidx+1)
                  {
                     if (chk->syntype == SYN_POST)
                     {
                       post = chk->G;
                       break; // at most one of these
                     }
                  }
               }
               Gsum += s->G * post;
               GEsum += s->G * post * (s->EQ - (p->pop_subtype  == BURSTER_POP ? 65. : 0));
               if (p->pop_subtype == PSR_POP) 
                  Prob += s->G * post * (1. - s->DCS); /* PSR or other external object */
            }
          }
          else 
          {
            Gsum += s->G;
            GEsum += (double)s->G * (s->EQ - (p->pop_subtype == BURSTER_POP ? 65. : 0));
            if (p->pop_subtype == PSR_POP) 
               Prob += s->G * (1. - s->DCS); /* PSR or other external object */
           }
        }
#define NOISE_FIRING_PROBABILITY .05
#define NOISE_EQ 70

        if (p->noise_amp)
        {
          double ranval;
          double gnoise_e = c->gnoise_e;
          double gnoise_i = c->gnoise_i;
          
          gnoise_e *= noise_decay;
          gnoise_i *= noise_decay;
          if ((ranval = ran (&p->noise_seed)) < NOISE_FIRING_PROBABILITY)
            gnoise_e += p->noise_amp;
          if ((ranval = ran (&p->noise_seed)) < NOISE_FIRING_PROBABILITY)
            gnoise_i += p->noise_amp;
          Gsum += gnoise_e + gnoise_i;
          GEsum += gnoise_e * ( NOISE_EQ - (p->pop_subtype == BURSTER_POP ? 65. : 0));
          GEsum += gnoise_i * (-NOISE_EQ - (p->pop_subtype == BURSTER_POP ? 65. : 0));
          c->gnoise_e = gnoise_e;
          c->gnoise_i = gnoise_i;
        }
        GEsum0 = GEsum;

        Vm = c->Vm_prev = c->Vm;
        Gk = c->Gk;
        if (p->pop_subtype == PSR_POP)  /* PSR or other external object */
        {
          double DC = Vm < Prob ? p->DCTH : p->DCG;
          if (S.stepnum == 0)
            Vm = 0;
          Vm = (Vm - Prob) * DC + Prob;
             // spike is 1 (fired) or 0 (not)
          c->spike = (Vm > c->Thr) ? (ran (&S.seed) <= (Vm - c->Thr)) : 0;
        }
        else 
        {
          if (p->pop_subtype == BURSTER_POP)     /* hybrid IF cell */
          {
            double G_NaP;
            double m_inf = 1 / (1 + exp ((Vm - p->theta_m) / p->sigma_m));
            double h_inf = 1 / (1 + exp ((Vm - p->theta_h) / p->sigma_h));
            double tau_h = p->taubar_h / cosh ((Vm - p->theta_h) / (2 * p->sigma_h));
            if (S.stepnum == 0) 
               Gk = /*.28*/ .43, Vm = -52;
            Gk = h_inf + (Gk - h_inf) * exp (-S.step / tau_h);
            G_NaP = p->g_NaP_h * m_inf * Gk;
            Gsum += G_NaP + g_L;
            GEsum += G_NaP * E_Na + g_L * E_L + get_GE0 (p);
          }
          else 
          {
            Gk = c->spike ? p->B + (Gk - p->B) * p->DCG : Gk * p->DCG;
            Gsum += Gk + S.Gm0;
            double GE0 = get_GE0 (p);

            if(Debug)
            {
               static char done[100];
               if (!done[pn]) 
               {
                 // printf ("pn = %d, GE0: %g\n", pn, GE0);
                 done[pn] = 1;
              }

              static double last_volume = -1;
              if (p->ic_expression && state.volume != last_volume) 
              {
                //  printf ("pn = %d, GE0: %.17e, volume: %.17e\n", pn, GE0, state.volume);
                last_volume = state.volume;
              }
            }

            GEsum += GE0 + Gk * S.Ek;
          }

          Vm = GEsum/Gsum + (Vm - GEsum/Gsum) * exp(Gsum * p->R0);

         if (0) // debug stuff, 0 -> 1 to turn it on
         {
           static FILE *f;
           if (f == NULL)
             f = fopen ("simloop.dbg", "w");
           if (pn == 37)
           fprintf (f, "step: %d, cn: %d, Vm: %g %g %g %g %g %g %g %g %g %d %g %g | %g %g %g %g %g\n",
                    S.stepnum, cn, Vm, GEsum, Gsum, c->Vm, p->R0, GEsum0, p->GE0, Gk, S.Ek, c->spike, p->B, p->DCG,
                    c->Thr, p->Th0, p->MGC, S.Vm0, p->DCTH);
            if (S.stepnum == 6) 
            {
              fclose (f);
              exit (0);
            }
         }
       
         if (p->pop_subtype == BURSTER_POP)
           c->Thr = p->Vthresh;
         else 
         {
           double Vt = p->Th0 + p->MGC * (Vm - S.Vm0);
           c->Thr = Vt + (c->Thr - Vt) * p->DCTH;
         }
         c->spike = Vm >= c->Thr;
       }

       if (c->spike)  // fired?
       {
// printf("FIRE\n");
         int widx;
         if (write_bdt)
         {
           for (widx = 0; widx < S.cwrit_count; widx++)
           {
             if (S.cwrit[widx].pop == pn + 1) 
             {
               if  (S.cwrit[widx].cell == cn + 1)
               {
                 fprintf (S.ofile, fmt, 100 + widx + 1, (int)((S.stepnum + 1) * S.step / dt_step));
                 fprintf (S.ofile, "%c",0x0a);
               }
               else 
                  if (S.cwrit[widx].cell == 999999999) /* Thu Feb  1 08:42:27 EST 2007: what is this? ROC */
                  {
                    fprintf (S.ofile, fmt, 21 + cn, (int)((S.stepnum + 1) * S.step / dt_step));
             // if running in DOS, no way now to view bdt, so make this linux text format
                    fprintf (S.ofile, "%c",0x0a);
                  }
             }
           }
         }
         if (write_smr)
         {
           for (widx = 0; widx < S.cwrit_count; widx++)
           {
             if (S.cwrit[widx].pop == pn + 1) 
             {
               if  (S.cwrit[widx].cell == cn + 1)
               {
                 writeSpike(100 + widx + 1, (int)((S.stepnum + 1) * S.step / dt_step));
               }
               else 
                  if (S.cwrit[widx].cell == 999999999) /* Thu Feb  1 08:42:27 EST 2007: what is this? ROC */
                  {
                    fprintf (S.ofile, fmt, 21 + cn, (int)((S.stepnum + 1) * S.step / dt_step));
                    fprintf (S.ofile, "%c",0x0a); // if running in DOS, no way now to view 
                                                  // bdt, so make this linux text format
                  }
             }
           }
         }
         if (pn + 1 == S.nanlgpop) 
           nf++;
         for (tidx = 0; tidx < c->target_count; tidx++) 
         {
           Target *target = c->target + tidx;
           Syn *syn = target->syn;
           if (target->disabled)
             continue;
           int type_of_syn=S.net.syntype[syn->stidx].SYN_TYPE;
           if (!S.ispresynaptic || type_of_syn == SYN_NORM) 
             syn->q[(S.stepnum + target->delay) % syn->q_count] += target->strength;
           else if (target->strength < 1)
             syn->q[(S.stepnum + target->delay) % syn->q_count] *= target->strength;
           else
             syn->q[(S.stepnum + target->delay) % syn->q_count] += target->strength - 1.;
         }
         if (p->pop_subtype == BURSTER_POP) 
         {
           Vm = ((11.085 * Gk) - 6.5825) * Gk + p->Vreset;
           Gk += p->delta_h - .5 * 0.0037 * Gk;
         }
       }
       c->Vm = Vm;
       c->Gk = Gk;
      }
    }

    for (pn = 0; pn < S.net.fiberpop_count; pn++)      // fibers
    {
      FiberPop *p = S.net.fiberpop + pn;
      skipFib = false;
      doFibCalc = false;
      int fn;
      int widx;
      if (S.stepnum >= p->start - 1 && S.stepnum < p->stop - 1)
      {
        if (p->pop_subtype == ELECTRIC_STIM)
        {
          skipFib = true; // don't do this unless hit the next tick
          if (p->next_stim == S.stepnum) // time to apply stim
          {
             doFibCalc = true;
             skipFib = false;
             switch(p->freq_type)
             {
                case STIM_FIXED:
                   p->next_stim += ticks_in_sec / p->frequency;
                   break;

                case STIM_FUZZY:
                   p->next_fixed += ticks_in_sec / p->frequency;
                   int fuzz_min = -(((p->fuzzy_range/2)/S.step));
                   int fuzz = (int)(ran(&p->infsed) * (p->fuzzy_range/S.step));
                   int next_targ = fuzz_min + fuzz;
                   p->next_stim = p->next_fixed + next_targ;
                   break;
                default:
                   fprintf(stderr,"Unknown type of electric stim frequency\n");
                   break;
             }
           }
        }
        else if (p->pop_subtype == AFFERENT)
        {
           double prob;
           doFibCalc = true;
           skipFib = false;
           nextExternalVal(p,&prob);
           printf("Got %lf\n",prob);
           p->probability = interpolate(p,prob);
           printf("Prob for %lf is %lf\n",prob,p->probability);

           // here will go code to determine the current probablity for this pop/source
        }
        else if (p->pop_subtype == 0)
           fprintf(stderr,"Unknown fiber subtype\n");

        for (fn = 0; fn < p->fiber_count; fn++) 
        {
          int tidx;
          Fiber *f = p->fiber + fn;
          float ranval;
          f->state = 0;
// dale bp test, use prob from fake bp prob array
//          if (doFibCalc || (!skipFib && (ranval = ran(&p->infsed)) <= curr_prob))
// end daletest

// real code
          if (doFibCalc || (!skipFib && (ranval = ran(&p->infsed)) <= p->probability))
          {
            f->state = 1; // an event occurred
            doFibCalc = false;
            if (write_bdt)
            {
              for (widx = 0; widx < S.fwrit_count; widx++)
                if (S.fwrit[widx].pop == pn + 1 && S.fwrit[widx].cell == fn + 1)
                {
                  fprintf (S.ofile, fmt, 100+ S.cwrit_count + widx + 1, (int)((S.stepnum + 1) * S.step / dt_step));
                  fprintf (S.ofile, "%c",0x0a);
                }
            }
            if (write_smr)
            {
              for (widx = 0; widx < S.fwrit_count; widx++)
                if (S.fwrit[widx].pop == pn + 1 && S.fwrit[widx].cell == fn + 1)
                {
                  writeSpike(100+ S.cwrit_count + widx + 1, (int)((S.stepnum + 1) * S.step / dt_step));
                }
            }
            for (tidx = 0; tidx < f->target_count; tidx++)
            {
              Target *target = f->target + tidx;
              Syn *syn = target->syn;
               int type_of_syn = S.net.syntype[syn->stidx].SYN_TYPE;
                  // if NORM, one calc, both pre and post get same calc, depending on sign
               if (!S.ispresynaptic || type_of_syn == SYN_NORM) 
                 syn->q[(S.stepnum + target->delay) % syn->q_count] += target->strength;
               else if (target->strength < 1)
                 syn->q[(S.stepnum + target->delay) % syn->q_count] *= target->strength;
               else
                 syn->q[(S.stepnum + target->delay) % syn->q_count] += target->strength - 1.;
// printf("%d %lf\n",S.stepnum % syn->q_count,syn->q[S.stepnum % syn->q_count]);
              }
           }
         }
       }
    }

    for (pn = 0; pn < S.net.cellpop_count; pn++) 
    {
      CellPop *p = S.net.cellpop + pn;
      int cn;
      for (cn = 0; cn < p->cell_count; cn++) 
      {
        Cell *c = p->cell + cn;
        int sidx;
        if (!S.ispresynaptic) 
        {
          for (sidx = 0; sidx < c->syn_count; sidx++) 
          {
            Syn *s = c->syn + sidx;
// printf("%d %lf\n",S.stepnum % s->q_count,s->q[S.stepnum % s->q_count]);
            s->G = (double)s->G * s->DCS + s->q[S.stepnum % s->q_count];
            s->q[S.stepnum % s->q_count] = 0;
          }
        }
        else 
        {
          int pp_idx;

            // Walk through the syn list. For normal type, if using pre/post synaptic
            // modifiers, look for any that belong to current normal syn
          for (sidx = 0; sidx < c->syn_count; ++sidx) 
          {
            Syn *norm, *pre = 0, *post = 0;
            float *norm_q;
            int stidx = c->syn[sidx].stidx;
            int type_of_syn=S.net.syntype[stidx].SYN_TYPE;
            if (type_of_syn != SYN_NORM) // skip any pre/post
              continue;
            norm = c->syn + sidx;
            norm_q = norm->q + S.stepnum % norm->q_count;
            Syn *chk = c->syn;
              // do we have a pre and/or post item associated with current normal?
            for (pp_idx = 0; pp_idx < c->syn_count; ++pp_idx, ++chk) 
            {
               if (chk->synparent && chk->synparent == norm->stidx+1)
               {
                  if (chk->syntype == SYN_PRE)
                     pre = chk;
                  else if (chk->syntype == SYN_POST)
                     post = chk;
               }
            }
            if (pre) 
            {
              float *pre_q = pre->q + S.stepnum % pre->q_count;
              double G = pre->G;
              norm_q[0] *= G;
              G = (G - 1) * pre->DCS + 1;
              if (pre_q[0]  < 1) 
                 G *= (double)pre_q[0];
              else
                 G += (double)pre_q[0] - 1;
              pre_q[0] = 1;
              pre->G = G;
            }
            norm->G = (double)norm->G * norm->DCS + norm_q[0];
            norm_q[0] = 0;
            if (post) 
            {
              float *post_q = post->q + S.stepnum % post->q_count;
              double G = post->G;
              G = (G - 1) * post->DCS + 1;
              if (post_q[0] < 1)
                G *= (double)post_q[0];
              else
                G += (double)post_q[0] - 1;
              post_q[0] = 1;
              post->G = G;
            }
          }
        }
      }
    }

    if (S.outsned == 'e')   // save waveforms?
    {
       int n, i, spike_count;
       for (n = 0; n < S.plot_count; n++) 
       {
         int p = S.plot[n].pop - 1;
         int c = S.plot[n].cell - 1;
         if (S.plot[n].var > 0 && (p < 0 || p >= S.net.cellpop_count))
           continue;
         S.plot[n].spike = 0;
         S.plot[n].type = S.plot[n].var >= 0 && S.net.cellpop[p].pop_subtype == BURSTER_POP;
            // what kind of plot do we save?
         switch (S.plot[n].var) 
         {
           case 1:
             S.plot[n].val    = S.net.cellpop[p].cell[c].Vm_prev;
             if (S.net.cellpop[p].pop_subtype == BURSTER_POP)   /* hybrid IF population */
               S.plot[n].val += 50;
             S.plot[n].spike = S.net.cellpop[p].cell[c].spike;
             break;
           case 2:
             if (S.net.cellpop[p].pop_subtype == BURSTER_POP)
               S.plot[n].val    = S.net.cellpop[p].cell[c].Gk * 60;
             else
               S.plot[n].val    = -20 + S.net.cellpop[p].cell[c].Gk * 10;
             break;
           case 3:
             S.plot[n].val    = S.net.cellpop[p].cell[c].Thr;
             if (S.net.cellpop[p].pop_subtype == BURSTER_POP)
               S.plot[n].val += 50;
             break;
           case -1:
             S.plot[n].val    = (state.volume - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -2:
             S.plot[n].val    = (state.flow - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -3:
             S.plot[n].val    = (state.pressure - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -4:
             S.plot[n].val    = (state.Phr_d - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -5:
             S.plot[n].val    = (state.u - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -6:
             S.plot[n].val    = (state.lma - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -7:
             S.plot[n].val    = (state.Vdi - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -8:
             S.plot[n].val    = (state.Vab - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -9:
             S.plot[n].val    = (state.Vdi_t - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -10:
             S.plot[n].val    = (state.Vab_t - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -11:
             S.plot[n].val    = (state.Pdi - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -12:
             S.plot[n].val    = (state.Pab - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -13:
             S.plot[n].val    = (state.PL - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -14:
             S.plot[n].val    = (limit (state.Phr_d, 0, 1) - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -15:
             S.plot[n].val    = (limit (state.u, 0, 1) - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -16:
             S.plot[n].val    = (limit (state.lma, -1, 1) - (p + 1) / 10000.) / ((c + 1) / 10000.);
             break;
           case -17:
             // S.plot[n].val    = S.net.fiberpop[p].fiber[c].state;
             S.plot[n].val    = 0;
             S.plot[n].spike  = S.net.fiberpop[p].fiber[c].state;
             break;

           default:
             if (S.plot[n].var < -17) // how does this case happen, just insurance?
               break;
             //if (S.plot[n].var >= 4)
             {  // this is case 4 or greater, If 4, inst. pop activity.
                // if > 4, var is is binwidth in ms. can't have a case 4 or greater. . .
               static struct {int spkcntcnt; int sum; int *spkcntlst;} *cdat;
               static int cdat_size;
               int mult = c + 1;
               double binwidth_in_ms = S.plot[n].var;
               int spkcntcnt = S.plot[n].var == 4 ? 1 : floor (binwidth_in_ms / S.step + .5);
               int sclidx = S.stepnum % spkcntcnt;
               double spikes_per_second_per_cell;
               if (cdat_size < S.net.cellpop_count) {
                 TREALLOC (cdat, S.net.cellpop_count);
                 memset (cdat + cdat_size, 0, (S.net.cellpop_count - cdat_size) * sizeof *cdat);
                 cdat_size = S.net.cellpop_count;
               }
               if (cdat[p].spkcntcnt != spkcntcnt) {
                 free (cdat[p].spkcntlst);
                 TCALLOC (cdat[p].spkcntlst, spkcntcnt);
                 cdat[p].spkcntcnt = spkcntcnt;
               }
               spike_count = 0;
               for (i = 0; i < S.net.cellpop[p].cell_count; i++)
                 spike_count += S.net.cellpop[p].cell[i].spike;
               cdat[p].sum += spike_count - cdat[p].spkcntlst[sclidx];
               cdat[p].spkcntlst[sclidx] = spike_count;
               spikes_per_second_per_cell = (cdat[p].sum / (spkcntcnt * S.step / 1000.0)
                         / (S.net.cellpop[p].cell_count ? S.net.cellpop[p].cell_count : 1));
               S.plot[n].val = spikes_per_second_per_cell / mult;
             }
             //else
             //   printf("Unhandled default plot type in simloop\n");
             break;
           }
       }
       simoutsned ();
     }

     if (write_analog)
     {
       static int nanlgtot, nanlgcnt, nanlglst;
       nanlgtot += nf;
       nanlgcnt++;
       if (nanlgcnt == 1 / S.step * S.nanlgrate)
       {
         int nval;
         nanlgtot *= S.sclfct;
         nanlglst = nanlglst * S.dcgint + nanlgtot;
         nval = nanlglst + 2048;
         if (nval > 4095) 
           nval = 4095;
         if (nval < 0) 
           nval = 0;
         int aval = S.nanlgid * 4096 + nval;
         int time = (int)((S.stepnum + 1) * S.step / dt_step);
         if (write_bdt)
         {
           fprintf (S.ofile, fmt, aval, time);
           fprintf (S.ofile, "%c",0x0a);
         }
         if (write_smr)
           writeWave(aval, time); 
         nanlgtot = 0;
         nanlgcnt = 0;
       }
     }
     chk_for_cmd();
     state = next_state;
  } // END OF MAIN LOOP

  snprintf(msg,sizeof(msg)-1,"TIME\n%.2f\n", S.stepnum/ticks_in_sec);
  if (have_cmd_socket())
    send(sock_fd,&msg,strlen(msg),0); // progress rpt for simbuild 
  fprintf(stderr,"simloop exited\n");
  fflush(stdout);

  if (write_bdt)
    fclose (S.ofile);

  if (have_data_socket())
    waitForDone();

#if __linux__
  /* TODO no shell for windows, create a function that does what .sh file does. */
  if (write_analog && access("/usr/local/bin/simpower_spectrum.sh", X_OK) == 0)
  {
     char *cmd;
     if (isedt)
     {
        if (asprintf (&cmd, "simpower_spectrum.sh %d %d edt&", S.spawn_number, S.nanlgrate) == -1)
           exit (1);
     }
     else
     {
        if (asprintf (&cmd, "simpower_spectrum.sh %d %d bdt&", S.spawn_number, S.nanlgrate) == -1)
        exit (1);
     }
     fprintf(stderr,"%s\n", cmd);
     if (system (cmd)){} 
        free(cmd);
  }
#endif
  fprintf(stderr,"simloop function returning\n");
  fflush(stderr);
}


