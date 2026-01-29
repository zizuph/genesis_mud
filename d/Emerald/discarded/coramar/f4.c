#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");


    add_fexit(CORAMAR+"f6", "northwest", 0);
    set_long("    The path here widens slightly as it continues into the "+
             "shadows to the northwest. A pair of young trees leans are "+
             "bent over the path in an arch-like shape, creating the " +
             "illusion that this section of the path is a tunnel of some "+
             "kind. Beyond the young trees, the dark outlines of "+
             "what must be the thickest trees currently alive. Some of them "+
             "have trunks that could be ten men wide. The path narrows "+
             "to the southeast.\n\n");

    add_item(({"young trees", "arch", "arch-shape", "tunnel", "arch-like shape"}),
        "The young trees here have somehow been bent to grow in an arch-"+
        "like shape over the gradually widening path to the northwest. "+
        "Although it is not unheard of for trees to bend naturally while "+
        "growing, you think there is something more to this arch-like shape "+
        "than what is readily apparent.\n");

    add_fexit(CORAMAR+"f3", "southeast", 0);
}
