inherit "/std/room";

#include "default.h"

void
create_room()
{
    set_short("Wild road");
    set_long("This road is in the wilderness of the elven forests. To the " +
             "north, looming up on the horizon, is a white castle - faint " +
             "plumes of smoke trailing up from its chimneys. There is a " +
             "small hamlet to the south.\n");
    add_exit(OUT_DIR + "v2", "south");
    add_exit(OUT_DIR + "p6", "west");
    add_exit(OUT_DIR + "p4", "northeast");
    add_item("castle","The castle is within thirty miles now; its "+
             "walls are clearly visible to you.\n");
    add_item(({"plumes","smoke"}), "The smoke is probably from the "+
    "cooking fires.\n");
    add_item("forests", "There are trees all around you, all of different "+
             "sizes. The forests stretch\nfor miles in every direction.\n");
    add_item("trees","The trees have a serene beauty all of their own.\n"+
             "They might have even been shaped by magic.\n");
    add_item("hamlet","The hamlet really only consists of a few huts.\n");
}

