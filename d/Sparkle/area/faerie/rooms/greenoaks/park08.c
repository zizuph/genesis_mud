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
    set_short("Southeast corner of the park in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "Large flower " +
        "boxes are spread around under the large oak trees in the park. " +
        "The park is quiet, with a calming feeling. Sweet fragrances " +
        "fill the air. A stone building is to the east, and another to " +
        "the northeast.\n");
        
    set_add_park();
    set_add_road();

    add_item(({"stone buildings", "stone building", "building", "buildings"}),
        "This buildings are square with domed roofs. They are beautifully " +
        "sculpted from white stone, revealing an inner beauty that " +
        "seems to make the buildings alive.\n");         
    add_item(({"northeast building", "northeastern building"}),
        "The northeast building is unusually larger. It has two stories " +
        "with windows set into the building. You can't see into the " +
        "building, but the sound of elves working out echoes from " +
        "the building.\n");
    add_item(({"east building", "eastern building"}),
        "This building is one story and seems very quiet. There are no " +
        "visible windows and no loud noises echo from it.\n");
    add_item(({"windows"}),
        "They are set into the northeast building. The windows are open, " +
        "allowing fresh air to blow in. Echos of elves working out " +
        "waft out from the windows.\n");
    
    add_exit(GO_DIR + "park05", "north");
    add_exit(GO_DIR + "park07", "west");
    add_exit(GO_DIR + "square", "northwest");
    add_exit(GO_DIR + "road16", "southeast");

 
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
