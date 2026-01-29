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
    set_short("A southeastern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It runs along " +
        "the southern perimeter of the town to the west and bends to " +
        "the northeast. Buildings line the northern side of the road, " +
        "with a tall building rising above them.\n");
        
    set_add_road();
    set_add_trees();
    set_add_forest();

    set_add_plain_bldg("It stands north of the road hidden in the trees.");
    add_item(({"tall building", "northern building", "north building"}),
        "The building is tall and stands north of you. The sounds of " +
        "groans and shouts echo from it.\n");
    
    add_exit(GO_DIR + "road20", "west");    
    add_exit(GO_DIR + "road17", "northeast");    

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
