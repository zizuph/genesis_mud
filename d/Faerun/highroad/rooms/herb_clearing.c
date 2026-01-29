/*
 * Trail in the Grasslands near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("a clearing off the stone road");
    set_extraline("Brush and debris have been cleared away, leaving the area neat and tidy. Some small gardens encircle a cottage, which is set in the center. A tendril of smoke rises from the roof.");

    reset_faerun_room();

    add_item(({"clearing"}),
        "This is set off the road to the southwest. It is neat and tidy, with a cottage set in the center.\n");
    add_item(({"cottage", "house"}),
        "This is a small house. It is made of stone and looks rustic, but is neat and tidy. Herb gardens surround the house. A small door leads into the cottage, and a tendril of smoke curls up from the chimney.\n");
    add_item(({"gardens", "herb gardens"}),
        "The gardens are full of herbs of all kinds and surround the cottage. The plants are well tended and look healthy.\n");
    add_item(({"chimney"}),
        "The chimney is made of stone. The base is wide and then becomes narrow about halfway up the cottage.\n");
    add_item(({"roof"}),
        "It is rounded, covered with thatching. It looks weathered with some mosses and lichens growing on it.\n");
    add_item(({"thatching"}),
        "It is layered bundles of grasses and branches. They make up the roof and are weathered looking. Various mosses and lichens appear to be growing in it.\n");
    add_item(({"mosses", "lichens"}),
        "They grow on the roof, making the thatching look rustic. The mosses and lichens look healthy and are shapes and sizes.\n");
    add_item(({"door"}),
        "The door is small and made of boards. It is weathered and looks sturdy.\n");
    add_item(({"smoke"}),
        "It is gray and curls out of the chimney.\n");

    add_exit(HR_DIR + "herb_cottage", "in");
    add_exit(HR_DIR + "srd02", "southwest");

}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
}


int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("You cannot go there yet.\n");
    return 1;
}