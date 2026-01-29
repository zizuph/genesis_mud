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
    set_short("Northwest corner of the park in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "Boxes of " +
        "flowers are scattered around the park. Elves often come here " +
        "to relax and enjoy a moment of peace. Wisteria grow over a " +
        "trellis around the park.\n");
        
    set_add_park();
    set_add_road();
    
    
    add_exit(GO_DIR + "road05", "north");
    add_exit(GO_DIR + "park04", "south");
    add_exit(GO_DIR + "park02", "east");
    add_exit(GO_DIR + "square", "southeast");
    add_exit(GO_DIR + "road10", "southwest");


 
}

/*
 * Function name:	init
 * Description	:	add the drinking and river verbs
 */
public void
init()
{
    ::init();

}
