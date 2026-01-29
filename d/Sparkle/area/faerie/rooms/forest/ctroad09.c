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
    set_short("Along the Southern Trade Road");
    set_long(forest_desc1(extra_line));
    add_std_herbs("forest");

    add_exit(FOREST_DIR + "ctroad10", "northwest");
    add_exit(FOREST_DIR + "ctroad08", "south");

    reset_room();
}

public void
init()
{
    ::init();
}

void
reset_room()
{
    object cart;

    if (!present("cart",TO))
    {
        cart = clone_object(OBJ_DIR + "cart");
        cart->move(TO);
    }

    set_searched(0);
}
