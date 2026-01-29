/*
 *      
 */
#pragma strict_types

#include "arnor_defs.h"
inherit NEW_ARNOR_ROOM;

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"


void
reset_room()
{
    set_searched(0);
}

public void
create_arnor()
{
    string road_dirs;
   
    set_short("An ancient road through the North Downs of Arnor.");
    road_dirs = " The road climbs uphill to the " +
        "north and descends to the southeast.\n";
    set_long(&set_road_downs_long(road_dirs));
    add_road_downs_tells();
    add_road_downs_items();
    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs(HERB_LOC1)),
                    ONE_OF_LIST(HERB_MASTER->query_herbs(HERB_LOC2))}),
                    ({ "ridge", "hills", "hill", "grass", }), 5);
    add_exit(ND_ROAD + "nd_road9", "north", 0, 1);
    add_exit(ND_ROAD + "nd_road7", "southeast", 0, 1);
    set_grass_wandering_msg();
    reset_room();
}



void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }   
}

