inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
 
{
   set_short("In a garden");
   set_long("   A zesty expanse of zinnias stretches before you. "+
            "The gardener has taken much time to work the ground "+
            "here.  Perhaps he is going to put some flowers beside "+
            "the zinnias.  The path appears to continue south and west.\n\n");

   add_item(({"zinnias", "zinnia"}),"A round, many-petalled "+
            " flower.\n");
   add_item(({"ground"}), "The ground looks like it has been freshly "+
            "tilled.\n");

   add_exit(VILLAGE_DIR + "g4", "west", 0);
   add_exit(VILLAGE_DIR + "g8", "south", 0);
}
