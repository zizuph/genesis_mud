/*
 * /d/Gondor/rhovanion/mirkwood/oldroad/base.c
 *
 * Base room for the old road in Mirkwood.
 *
 * Created by Eowul, Juni 2008
 * Modified by Varian, Nov 2012
 */
 
#include "../defs.h"

inherit MIRKWOOD_STD_DIR + "room";
inherit MIRKWOOD_LIB_DIR + "movement";

#include <macros.h>
#include "descriptions.c"
#include "items.c"

void create_mirkwood_road_room()
{
    // Generic randomized long descriptions
    add_location_long();
    add_tree_long(); 
    add_emo_long();   
    setup_mirkwood_herbs();
    
    set_add_all_rooms();
    set_movement_difficulty(30);   
}

void create_mirkwood_room()
{
    create_mirkwood_road_room();
}