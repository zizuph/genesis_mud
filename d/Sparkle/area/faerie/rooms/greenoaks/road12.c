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
    set_short("A western road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "A park " +
        "surrounds it to the east. Tall trees surround and enclose the " +
        "road, and is thicker to the west.\n");
        
    set_add_road();
    set_add_park();
    set_add_trees();
    set_add_forest();
    
    add_exit(GO_DIR + "road10", "north");    
    add_exit(GO_DIR + "road14", "south");    


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
