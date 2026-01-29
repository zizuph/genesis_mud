
// Ledge path 9 (/d/Avenir/common/ledge/ledge9.c)
// creator(s): Ilyian
// last update:  
// purpose:
//
// note: this is where the ledge area goes into the tunnels by the outpost
// bug(s):
// to-do:

inherit "/d/Avenir/common/ledge/std_ledge";
#include "ledge.h"

void
create_room()
{
     AE(LEDGE+"ledge8", "northwest", 0, 6);
     AE(OUTPOST+"path1", "southeast", 0, 0);

   SHORT("On the steep path");
   make_the_room("  There is a dark tunnel leading into the cavern "
      +"wall to the southeast. The open view here is marvelous. You "
      +"can see almost all of the great cavern in all of its "
      +"glory. The gentle sound of the dark sea far below you "
      +"can be heard faintly from here.\n");

   AI(({"tunnel","opening","wall"}),"The tunnel opening is wide, but "
      +"you cannot make anything out in the thick darkness that "
      +"encloses it.\n");
}

