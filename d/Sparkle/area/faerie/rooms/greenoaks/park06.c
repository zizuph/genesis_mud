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
    set_short("Southwestern corner of the park in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "Leaves " +
        "flutter in the breeze of the oak trees. They shade the flower " +
        "boxes and wisteria growing on the trellis along the outside " +
        "of the park.\n");
        
    set_add_park();
    set_add_road();
    
    add_exit(GO_DIR + "park04", "north");
    add_exit(GO_DIR + "park07", "east");
    add_exit(GO_DIR + "square", "northeast");
    add_exit(GO_DIR + "road14", "southwest");

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
