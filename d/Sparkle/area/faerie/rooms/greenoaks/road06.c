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
    set_long(short() + ". " + s_desc_sky_outside_sky() +  "A large orchard " +
        "lines the road to the north. It is a favorite place for travellers " +
        "who visit Green Oaks for it is often full of abundant fruit. " +
        "The road is paved with white flagstones. A serene park is south " +
        "of the road. A stone building is east of the road.\n");
        
    set_add_road();
    set_add_park();
    set_add_orchard();
    set_add_trees();

    set_add_plain_bldg("It appears sturdier than most other buildings. It " +
        "lies east of the road hidden in the trees.");
    add_item(({"east building", "eastern building", "sturdy building"}),
        "The exquisite building is made of stone. It is one story tall " +
        "and sturdy looking. Periodically, travellers stream in and out of it.\n");
    
    add_exit(ORCHARD_DIR + "orchard15", "north");
    add_exit(GO_DIR + "road05", "west");
    add_exit(GO_DIR + "road02", "northeast");


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
