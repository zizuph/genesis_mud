inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()

{
   set_short("In a garden");
   set_long("   You step onto a carefully-laid stone walkway travelling neatly "+
            "through a multitude of meticulously-kept flower beds and are suddenly "+
            "surrounded by tall-standing tulips.  You smile at their waxen beauty. "+
            "The smell of roses is faint here. Perhaps a walk through the garden "+
            "will show you where the roses are.\n\n");

   add_item(({"tulips", "tulip"}),"An erect, cup-shaped flower.\n");

   add_exit(VILLAGE_DIR + "g3", "north");
   add_exit(VILLAGE_DIR + "g1", "south");
}
