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


#include "simwin.h"
#include <QApplication>

bool Debug = false;

int main(int argc, char *argv[])
{
   if (argc > 1)
      if (strcmp(argv[1],"-d") == 0)
         Debug = true;

   QApplication a(argc, argv);
   SimWin w;
   if (Debug)
      w.printMsg("Debug output turned on");
   w.show();
   return a.exec();
}
