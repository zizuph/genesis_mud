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
    set_long(short() + ". " + s_desc_sky_outside_sky() + "The forest " +
        "surrounds the village with tall branches growing over the road. " +
        "The road turns southwest as it goes around a tall building. Other " +
        "buildings are nestled in between the trees.\n");
        
    set_add_road();
    set_add_trees();
    set_add_forest();

    set_add_plain_bldgs("There is a tall building to the west and a " +
        "wide building to the northwest.");
    add_item(({"tall building", "western building", "west building"}),
        "The building is hidden in the trees to the west. It is tall. " +
        "The sounds of groans and shouts echo from it.\n");
    add_item(({"wide building", "northwestern building", "northwest building",}),
        "It is hidden in the trees west of the road. The building is " +
        "one story and appears to be important.\n");
    
    add_exit(GO_DIR + "road13", "north");    
    add_exit(GO_DIR + "road21", "southwest");    

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
