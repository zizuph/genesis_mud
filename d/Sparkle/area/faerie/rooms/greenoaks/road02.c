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
    set_short("A northern road in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "A sturdy, stone " +
        "building sits south of the road. A sign hangs above the door " +
        "which swings in a light breeze. To the southeast stands another " +
        "building. A large orchard spreads out to the north.\n");

    set_add_sign("Green Oaks Shop");
    set_add_road();
    set_add_park();
    set_add_orchard();
    set_add_trees();
    set_add_plain_bldg("It appears sturdier than most other buildings. It " +
        "is southeast of the road hidden in the trees.");
    add_item(({"southeast building", "southeastern building", "sturdy building"}),
        "The exquisite building is made of stone. It is one story tall " +
        "and sturdy looking. Periodically, travellers stream in and out of it.\n");
        
    add_exit(ORCHARD_DIR + "orchard10", "north");
    add_exit(GO_DIR + "shop", "south");
    add_exit(GO_DIR + "road03", "east");
    add_exit(ORCHARD_DIR + "orchard15", "west");
    add_exit(GO_DIR + "road06", "southwest");

}

/*
 * Function name:	init
 */
public void
init()
{
    ::init();
}
