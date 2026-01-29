/*
 * The Trade Road of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit FOREST_BASE;

string extra_line = "";

void
create_forest_room()
{
    FIXEUID;
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");
    set_short("A quiet glade off the Trade Road");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "A quiet peace " +
        "fills the glade and is surrounded by tall fir trees. The ground " +
        "is clean except for forest debris. A large, shimmering portal " +
        "sits in the center of the clearing.\n");
    add_std_herbs("forest");
    room_add_object(OBJ_DIR + "portal_solace");

    add_exit(FOREST_DIR + "ctroad16",   "west");
//    add_exit(FOREST_DIR + "clearing", "east");
}

public void
init()
{
    ::init();

}
void
reset_room()
{
    set_searched(0);
}

