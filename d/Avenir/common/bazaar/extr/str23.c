// Bazaar Street23 (/d/Avenir/common/bazaar/extr/str23.c)
// creator(s):   Triana 1994
// last update:  Tepisch Sept 94, Ilyian May 95
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

init()
{
   ::init();

   ADD("do_crunch", "north");
   ADD("do_crunch", "south");
   ADD("do_nogo", "east");
}

void
create_room()
{
   AE(EXTR + "str22", "north", 0);
//   AE(EXTR + "str25", "east", 0);
   AE(EXTR + "str24", "south", 0);

   SHORT("Gravel path in southern bazaar");
   make_the_room(" The gravel path continues in a north-"+
      "south direction.\n");
}

do_crunch()
   {
   write("You stumble as you trudge through the gravel.\n");
   }

do_nogo()
{
   write("That way is not yet open.\n");
}


