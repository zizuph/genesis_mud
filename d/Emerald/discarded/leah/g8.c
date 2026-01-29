inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
 
{
   set_short("In a garden");
   set_long("   A bright blue carpet seems to spread before you "+
            "as you step into this bed of bouncy bluebonnets.  Step "+
            "carefully so as not to crush their soft beauty! The smell "+
            "of roses and bluebonnets is sweet and enticing.\n\n");

   add_item(({"bluebonnets", "bluebonnet"}),"A small blue "+
     "flower set close to the ground.\n");

   add_exit(VILLAGE_DIR + "g9", "north",);
   add_exit(VILLAGE_DIR + "g7", "south",);
   add_exit(VILLAGE_DIR + "g5", "west",);
}
