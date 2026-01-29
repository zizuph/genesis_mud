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
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It runs north " +
        "and south on the edge of the town. Long branches reach over the " +
        "road shading it. A quiet park is on the eastern side of the road. " +
        "A tall building rises north of here, hidden in the oak trees " +
        "surrounding the road.\n");
        
    set_add_road();
    set_add_park();
    set_add_trees();
    set_add_forest();
    set_add_sign("Winery of Green Oaks");

    set_add_plain_bldg("There is a tall building hidden between the " +
        "trees to the north. A sign hangs over the door.");
    add_item(({"tall building", "northern building", "north building"}),
        "It is difficult to see what kind of a building it is, but " +
        "the building is tall and hidden in the trees. A sign hangs " +
        "above the door.\n");
    
    add_exit(GO_DIR + "winery", "north");    
    add_exit(GO_DIR + "road12", "south");    
    add_exit(GO_DIR + "park01", "northeast");


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
