// Bazaar Street15 (/d/Avenir/common/bazaar/extr/str15.c)
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
   ADD("do_crunch","west");
   ADD("do_nogo", "north");
   ADD("do_nogo", "south");
}

void
create_room()
{

   AE(EXTR + "str16", "east", 0);
   AE(EXTR + "str14", "west", 0);

   AI(({"building","north building"}), "It seems to be one "+
     "of the few entertainment centers in the area. Going "+
     "west and then north will bring you to the entrance.\n");

   AI(({"wall", "mud-brick wall"}), "The wall is part of a "+
     "hut with a thatched roof. If you go west and then turn "+
     "south you will find the entrance.\n");

   SHORT("East side, near Icky Bods and the guard room");
   make_the_room(" West the gravel path continues toward the "+
      "market. Sounds alternating between violence and merry"+
      "making come from the building north of you. A mud-brick "+
      "wall is to the south. The path continues along to the east.\n");
}

do_crunch()
   {
   write("Gravel crunches under your feet.\n");
   }

do_nogo()
   {
   write("The entrance to that building is further west.\n");
   }

do_gono()
{
   write("That way is not yet open.\n");
}


