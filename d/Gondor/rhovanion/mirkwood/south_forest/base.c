#include "../defs.h"

inherit MIRKWOOD_STD_DIR + "room";
inherit MIRKWOOD_LIB_DIR + "movement";

#include <macros.h>
#include "/d/Gondor/rhovanion/mirkwood/south_forest/descriptions.c"
#include "/d/Gondor/rhovanion/mirkwood/south_forest/items.c"

void create_mirkwood_south_forest_room() 
{

}

nomask void create_mirkwood_room() 
{
    set_add_all_rooms();
    create_mirkwood_south_forest_room();
    set_movement_base_directory(MIRKWOOD_SOUTH_FOREST_DIR);
}