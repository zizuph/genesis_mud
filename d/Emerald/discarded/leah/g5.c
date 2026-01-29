inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
 
{
   set_short("In a garden");
   set_long("   An abundance of asters greet your eyes as you "+
            "meander through this lush garden.  To the south you "+
            "see a small cottage. The smell of roses is strong here. "+
            "You must be getting closer to them.\n\n");

   add_item(({"asters", "aster"}),"A collection of purple,"+
           " white, pink, and yellow flowers.\n");
   add_item(({"cottage"}),"This seems to be the north wall of"+
           " a small, tidy cottage.\n");

   add_exit(VILLAGE_DIR + "g8", "east", 0);
   add_exit(VILLAGE_DIR + "g4", "north", 0);
}
