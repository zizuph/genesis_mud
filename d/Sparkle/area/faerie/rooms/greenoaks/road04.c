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
    set_long(short() + ". " + s_desc_sky_outside_sky() + "Trees line " +
        "the road. It veers southeast and runs west alongside a large " +
        "orchard north of here. A stone building stands south of the " +
        "road with a smaller building connected to the west. A sign " +
        "hangs above door.\n");
    
    add_item(({"south building", "southern building", }),
        "The stone building is carved with beautiful designs and is " +
        "south of the road. It is large with a sign hanging above the door.\n");

    add_item(({"southwest building", "southwestern building", 
            "small building", "smaller building"}),
        "The stone building is carved with beautiful designs and is " +
        "south of the road. It seems alive and is annexed to the " +
        "southeastern building. Soft, chittering sounds echo from within.\n");

    set_add_road();
    set_add_trees();
    set_add_orchard();
    set_add_plain_bldgs("There is a large building is to the south, " +
        "and a plain building to the southwest.");
    set_add_sign("Postal Service of Green Oaks");

    
    add_exit(ORCHARD_DIR + "orchard12", "north");
    add_exit(GO_DIR + "post", "south");
    add_exit(ORCHARD_DIR + "orchard16", "east");
    add_exit(GO_DIR + "road03", "west");
    add_exit(GO_DIR + "road07", "southeast");



}

/*
 * Function name:	init
 */
public void
init()
{
    ::init();

}
