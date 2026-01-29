
// Bazaar Street13 (/d/Avenir/common/bazaar/extr/str13.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:


inherit "/d/Avenir/common/bazaar/extr/std_center.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

void
create_room()
{
   AE(EXTR + "str7", "north", 0);
   AE(EXTR + "centr", "west", 0);
   AE(EXTR + "str14", "east", 0);
   AE(EXTR + "str20", "south", 0);

   SHORT("East corner of Bazaar");
   make_the_room(" To the east the cobblestone square gives " +
      "way to a gravel path.\n");
}

