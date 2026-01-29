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
   
    set_short("A sea of grass.");
    set_long(&set_grass_room_long());
    add_road_downs_tells();
    add_item("tracks", &can_see_path("south"));
    set_up_herbs(({ ONE_OF_LIST(HERB_MASTER->query_herbs(HERB_LOC1)),
                    HERB_DIR + "suranie",
                    ONE_OF_LIST(HERB_MASTER->query_herbs(HERB_LOC2))}),
                    ({ "ridge", "hills", "hill", "grass", }), 5);
    add_exit(ND_OFFROAD + "offw1_1", "east", &off_road(), 0, 1);
    add_exit(ND_OFFROAD + "offw1_3", "south", &off_road(), 0, 1);
    set_grass_wandering_msg();
    add_grass_room_items();
    set_tracks("south", "orc");
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

