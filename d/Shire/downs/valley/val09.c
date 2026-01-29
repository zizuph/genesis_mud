/*
 * The valley of the Barrow Downs
 * By Finwe, December 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit ROAD_BASE;
 
void
create_road_room()
{
    set_areadesc("valley");
    set_area("of");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("You stand at the base of a large barrow, The " +
        "land spreads out before you, covered in green grass and " +
        "bare of anything. Some stairs wind up around the barrow.");
    
    add_item("stairs",
        "The stairs are carved into the side of the barrow. They " +
        "wind around and lead up to the top of the hill.\n");
    add_item("steps",
        "The steps are made of packed earth. They look hard and " +
        "wind up around the side of the barrow.\n");
    set_add_valley_descrs();

    add_exit(ROAD_DIR + "road10", "up","@@climb_stairs@@");
    add_exit(VAL_DIR + "val10", "southwest");
}

void climb_stairs()
{
    write("\nYou climb up the stairs that circle around the barrow.\n\n");
}
