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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "simulator.h"
#include "util.h"
#include "inode.h"
#include "fileio.h"
#include "inode_hash.h"
#include "lung.h"
#if defined WIN32
#include <libloaderapi.h>
#include <fcntl.h>
#include "lin2ms.h"
#endif


inode_global D;

extern char *snd_ptr;
extern int snd_size;
extern char inPath[];
extern char outPath[];

struct StructInfo *(*struct_info_fn) (const char *str, unsigned int len);
struct StructMembers *(*struct_members_fn) (const char *str, unsigned int len);

static void
read_fileio_file (char *file_name)
{
  FILE *f = NULL;
  memset (D.inode, 0, sizeof D.inode);
  struct_info_fn = inode_struct_info;
  struct_members_fn = inode_struct_members;
#if defined __linux__
    if (snd_ptr)
       f = fmemopen(snd_ptr,snd_size,"r");
#else
    char namebuff[MAX_PATH];
    unsigned int randno;
    HANDLE hnd1, hnd2;

    rand_s(&randno);
    snprintf(&namebuff,sizeof(namebuff),"sndrun%x.tmp",randno);
    hnd1 = CreateFile(namebuff, GENERIC_READ | GENERIC_WRITE, 0, NULL, 
      CREATE_NEW, FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE, NULL);
    hnd2 = _open_osfhandle((intptr_t)hnd1,_O_RDONLY);
    f = _fdopen(hnd2,"r+");
    fwrite(snd_ptr,1, snd_size, f);
    rewind(f);
#endif

  if (load_struct_read_version(f)) 
  {
    load_struct (f, "inode_global", &D, 1);
    fclose (f);
  }
  else perror (file_name);
}

char *
read_any_link (char *path)
{
#ifdef __linux__
  static char *buf;
  static int bufsiz;

  if (bufsiz == 0) TMALLOC (buf, bufsiz = 64);
  while (1) {
    int val = readlink (path, buf, bufsiz);
    if (val < 0)
      return "";
    if (val < bufsiz) {
      buf[val] = 0;
      return buf;
    }
    TREALLOC (buf, bufsiz *= 2);
  }
#else
      return "";
#endif
}

void
print_coords (void)
{
  int pn, cn;

  for (pn = 0; pn < S.net.cellpop_count; pn++)
    for (cn = 0; cn < S.net.cellpop[pn].cell_count; cn++)
      printf ("print_coords: pop %d cell %d %g %g %g\n", pn, cn,
	      S.net.cellpop[pn].cell[cn].x,
	      S.net.cellpop[pn].cell[cn].y,
	      S.net.cellpop[pn].cell[cn].z);
}

// It is going to be tricky to do this in C in Windows, there are file system diffs
// Much easier in C++ using the Qt abstractions.
// For now, not avaible in windows
// But it has to be. Need the pop comments when using lung model.
// Passed: .snd filename for this .sim file.
void
get_cell_coords (char *filename)
{
  int n;
  FILE *g;

  char *tmp = asprintf("%s%s",outPath,"pop_names");
  (g = fopen (tmp, "w")) || DIE;
  free(tmp);
  read_fileio_file (filename);
  printf ("baby_lung_flag in %s: %d\n", filename, D.baby_lung_flag);
  
  baby_lung_flag = D.baby_lung_flag; /* baby_lung_flag in lung.h */
  for (n = 0; n < 100; n++) {
    if (D.inode[n].node_type == CELL) {
      static char *inbuf = 0;
      static size_t len = 0;
      int pn = D.inode[n].node_number - 1;
      double x, y, z;
      int cn, count;
      char *tmp = asprintf("%s%s",inPath,D.inode[n].comment1);
      FILE *f = fopen (tmp, "r");
      char *link_target = read_any_link (tmp);
      fprintf (g, "ln -sf \"%s\" \"%s\" # %d\n", link_target, tmp, pn + 1);
      S.net.cellpop[pn].name = strdup (tmp);
      
      if (f == 0) {
	fprintf (stdout, "can't open %s: %s\n", tmp, strerror (errno));
	continue;
      }
      if (getline (&inbuf, &len, f) == -1) {
	fprintf (stdout, "can't read %s: %s\n", tmp, strerror (errno));
	fclose (f);
	continue;
      }
      cn = 0;
      count = S.net.cellpop[pn].cell_count;
      while (cn < count && fscanf (f, " %lf %lf %lf ", &x, &y, &z) == 3) {
	Cell *c = &S.net.cellpop[pn].cell[cn++];
	c->x = x; c->y = y; c->z = z;
      }
      if (cn < count)
	fprintf (stdout, "error: only %d of %d read from %s\n", cn, count, tmp);
      fclose (f);
      free(tmp);
    }
    else if (D.inode[n].node_type == GLOBAL) {
      S.phrenic_equation = strdup (D.inode[n].unode.global_node.phrenic_equation);
      S.lumbar_equation = strdup (D.inode[n].unode.global_node.lumbar_equation);
    }
  }
  fclose (g);
}
