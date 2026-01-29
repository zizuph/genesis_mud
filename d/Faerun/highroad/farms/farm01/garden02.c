/*
 * Farm flower garden
 * By Finwe, October 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "/d/Faerun/flowers/flowers.h"
#include "defs.h"

inherit BASE_GARDEN;
inherit BASE_COMMON;

void
create_garden_room()
{
    add_prop(ROOM_S_MAP_FILE, "farm_e_map.txt");

    set_short("A large flower garden");

    set_extraline("A gravel path runs through the gardens. Tall flowers " +
        "hide the path which runs northwest. A stone wall surrounds " +
        "the garden, keeping out animals and protecting you.\n");

    add_item(({"farmhouse", "house"}),
        "The farmhouse is large and surrounded flowerbeds. It is whitewashed " +
        "and sits at the southern edge of the garden.\n");      

    reset_room();    
    set_flowers(FARM1_FLOWERS);
    add_exit(FARM1_DIR + "garden01", "northwest");
    add_exit(FARM1_DIR + "kitchen", "west");
    
}

void reset_room()
{
    ::reset_room();
}
