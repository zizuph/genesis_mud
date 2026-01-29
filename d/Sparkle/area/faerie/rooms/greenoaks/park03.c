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
 
    set_short("Northeast corner of the park in Green Oaks");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "Colorful " +
        "flower boxes are scattered around the park. A trellis surrounds " +
        "the outside of the park, filling the air with sweet perfume, " +
        "and creating a quiet, relaxing atmosphere. To the north and " +
        "northeast stand two buildings.\n");
        
    set_add_park();
    set_add_road();

    add_item(({"stone buildings", "stone building", "building", "buildings"}),
        "This buildings are square with domed roofs. They are beautifully" +
        "sculpted from white stone, revealing an inner beauty that " +
        "seems to make the buildings alive.\n");    
    
    add_exit(GO_DIR + "park05", "south");
    add_exit(GO_DIR + "road08", "east");
    add_exit(GO_DIR + "park02", "west");
    add_exit(GO_DIR + "square", "southwest");

 
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
