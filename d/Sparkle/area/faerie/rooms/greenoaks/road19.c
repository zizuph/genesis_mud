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
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It is quiet, " +
        "and passes beneath tree branches from many oak trees, leading " +
        "west and veering northwest. A square building is hidden in " +
        "the trees east of the road.\n");

    set_add_road();
    set_add_trees();

    set_add_plain_bldg("It is square and sits east of the road. A " +
        "sign hangs above the door.\n");

    add_item(({"eastern building", "square building", "east building"}),
        "The building is large and square. Unlike other buildings, " +
        "there aren't to many trees around it.\n");


    add_exit(GO_DIR + "road18", "west");
    add_exit(GO_DIR + "road15", "northeast");


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
