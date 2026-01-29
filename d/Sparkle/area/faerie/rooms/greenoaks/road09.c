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
    set_short("An eastern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It cuts " +
        "through the center of Green Oaks and meets another road leading " +
        "south. Trees line the road, and branches cast long shadows " +
        "everywhere. Hidden in the trees are various buildings. A sign " +
        "hangs over the door of a wide building to the east.\n");
        
    set_add_road();
    set_add_trees();
    set_add_forest();
    set_add_sign("Herbal Shop of Green Oaks");

    set_add_plain_bldgs("There is a wide building to the east, a large " +
        "building to the north, a sturdy building to the northwest, and " +
        "a square building southwest.");
    add_item(({"sturdy building", "northwestern building", "northwest building"}),
        "The building is hidden in the trees to the northwest. It appears " +
        "rectangular shaped and strong looking.\n");
    add_item(({"large building", "northern building", "north building"}),
        "It is difficult to see what this building is, but it is square " +
        "shaped and two stories tall.\n");
    add_item(({"square building", "southwest building", "southwest building"}),
        "It stands in the trees to the southwest. Faint groans and " +
        "shouts echo from it.\n");
    add_item(({"wide building", "eastern building", "east building"}),
        "It is difficult to see what this building is, but it is long " +
        "and has a sign hanging above its door.\n");
    
    add_exit(GO_DIR + "road11", "south");    
    add_exit(GO_DIR + "herb_shop", "east");    
    add_exit(GO_DIR + "road08", "west");
    add_exit(GO_DIR + "road07", "northeast");


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
