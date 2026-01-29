inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()

{
   set_short("In a garden");
   set_long("   A blaze of morning glories assault your eyes as you "+
            "travel through this conflagration of colourful charm. As in "+
            "other parts of the garden you can smell roses as well as "+
            "morning glories.\n\n");

   add_item(({"morning glories", "morning glory"}),"A pretty bell-shaped flower.\n");

   add_exit(VILLAGE_DIR + "g5", "south",);
   add_exit(VILLAGE_DIR + "g3", "west",);
   add_exit(VILLAGE_DIR + "g9", "east",);
}
