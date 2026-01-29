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
    set_short("A southern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It runs " +
        "northwest towards the park and south, passing between trees " +
        "that line the road. Numerous buildings are scattered everywhere " +
        "and hidden the trees.\n");

    set_add_road();
    set_add_park();
    set_add_trees();
    set_add_plain_bldgs("There is a large building to the north, a wide " +
        "building to the northeast, a tall building to the east, and " +
        "a square building to the southwest.\n");

    add_item(({"northern building", "large building", "north building"}),
        "It is perfectly square and iis one story tall. The building is " +
        "hidden in the trees and hard to make out.\n");

    add_item(({"northeastern building", "wide building", "northeast building"}),
        "It is wide and hidden in the trees. The building is one story " +
        "tall and appears to be important.\n");

    add_item(({"eastern building", "tall building", "east building"}),
        "The building is taller than the others around it. Groans echo " +
        "from it.\n");

    add_item(({"southwestern building", "square building", "southwest building"}),
        "The building is large and square. Unlike most other buildings, " +
        "there aren't to many trees around it.\n");


    add_exit(GO_DIR + "road20", "south");
    add_exit(GO_DIR + "road15", "west");
    add_exit(GO_DIR + "park08", "northwest");


}

/*
 * Function name: init
 * Description:
 */
public void
init()
{
    ::init();

}
