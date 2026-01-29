inherit "/std/room";

#include "default.h"

void
create_room()
{
    set_short("Village road");
    set_long("You are on a small tree-lined road.  The village centre and " +
             "its buildings are to the east where this small road ends.\n");
    add_exit(OUT_DIR + "p3", "southeast");
    add_exit(OUT_DIR + "v2", "east");
    add_item("buildings", "The buildings are very well built, with a "+
             "sense of direction and art of their own.\n");
    add_item("trees", "The trees have a serene beauty all of their own. " +
                "They might have even been shaped by magic.\n");

}

