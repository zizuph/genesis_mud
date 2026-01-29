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
    set_short("Western side of the park in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "This part of " +
        "the park is quiet and relaxing. A sweet fragrance blows in the " +
        "breeze from the many flowers growing in boxes around the park. " +
        "Tall oak trees shade the park.\n");
        
    set_add_park();
    set_add_road();
    
    add_exit(GO_DIR + "park01", "north");
    add_exit(GO_DIR + "park06", "south");
    add_exit(GO_DIR + "square", "east");

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
