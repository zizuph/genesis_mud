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
    set_short("A southwestern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It runs along " +
        "the edge of the forest and the town. The road runs north and " +
        "south. Another road meets here and runs east. A wide building " +
        "stands in the trees north of the road.\n");
        
    set_add_road();
    set_add_park();
    set_add_trees();
    set_add_forest();

    set_add_plain_bldg("It stands hidden in the trees to north of the road.\n");
    add_item(({"northern building", "wide building", "north building"}),
        "It is perfectly square and is set between the trees. The building " +
        "is one story tall.\n");

    add_exit(GO_DIR + "road19", "east");    
    add_exit(GO_DIR + "road14", "northwest");    
    add_exit(GO_DIR + "road22", "southeast");    
    add_exit(GO_DIR + "house03", "southwest"); 


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
