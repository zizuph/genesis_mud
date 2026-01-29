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

    set_extraline("Two large stones stand on either side of the " +
        "path at the base of the barrow. They are bone white and " +
        "rounded, standing as sentinels surveying the Downs.");

    add_item(({"sentinals", "large stones", "white stones", 
            "bone white stones"}),
        "The large stones are bone white and sun bleached. They are " +
        "cracked and jagged, like teeth rising up from the ground.\n");

    set_add_valley_descrs();

    add_exit(VAL_DIR + "val09", "northeast");
    add_exit(VAL_DIR + "val11", "southeast");
}
