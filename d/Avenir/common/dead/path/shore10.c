// file name: shore10
// creator: Ilyian, September 21, 1995
// last update: room along the Shore path around the
//              Isle of the Dead
// purpose:
// note: Most of the code for this room is contained
//       in the inherited file /d/Avenir/common/dead/dead.c
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"

void
create_room()
{
   shore_long("The path bends inwards here, leading "
             +"north and southwest. The water to the "
             +"west is calm, and the rocky shore "
             +"forms a small inlet here."); 
   set_short("path along an inlet");
   AI(({"inlet","cove"}),"The shore bends inward here, "
             +"forming a natural inlet where the water "
             +"is calm.\n");

   shore_exit("north","11");
   shore_exit("southwest","9");
   shore_marsh("south","18");
   shore_marsh("east","22");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
