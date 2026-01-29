/*
 * Outdoor room in Green Oaks
 * By Finwe, August 2004
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit TOWN_BASE;
 
void
create_town_room()
{
    set_short("A road in northern Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The road is " +
        "lined with tall oaks, from which the town got its name. The " +
        "road is made of flagstones and leads south into the town, " +
        "northwest into a forest, and north and into an orchard.\n");
        
    set_add_road();
    set_add_orchard();
    set_add_forest();
    set_add_trees();
    
    room_add_object(OBJ_DIR + "cbox");

    add_exit(ORCHARD_DIR + "orchard08", "north");
    add_exit(GO_DIR + "road05", "south");
    add_exit(ORCHARD_DIR + "orchard15", "east");
    add_exit(FOREST_DIR + "mtroad25", "northwest");

}

/*
 * Function name:	init
 * Description	:	
 */
public void
init()
{
    ::init();

}
