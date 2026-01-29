/*
 *      
 */
#pragma strict_types

#include "arnor_defs.h"
inherit NEW_ARNOR_ROOM;

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Wolf = allocate(1);

public void
create_arnor()
{
    string road_dirs;
   
    set_short("An ancient road through the North Downs of Arnor.");
    road_dirs = " The road continues steadily downhill around " +
        "a bend in the rock ridge that turns sharply to the northeast " +
        "and climbs uphill to the southeast.\n";
    set_long(&set_road_downs_long(road_dirs));
    add_item("tracks", &can_see_path("west"));
    add_road_downs_tells();
    add_road_downs_items();
    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs(HERB_LOC1)),
                    ONE_OF_LIST(HERB_MASTER->query_herbs(HERB_LOC2)),
                    HERB_DIR + "suranie"}),
                    ({ "ridge", "hills", "hill", "grass", }), 5);
    add_exit(ND_ROAD + "nd_road5", "northeast", 0, 0);
    add_exit(ND_ROAD + "nd_road3", "southeast", 0, 0);
    add_exit(ND_OFFROAD + "offw1_1", "west", &off_road(), 0, 1);
    set_grass_wandering_msg();
    set_tracks("west", "orc");
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

public void
reset_room()
{
    clone_npcs(Wolf, NPC_DIR + "wolf", -1.0);
    set_searched(0);
}