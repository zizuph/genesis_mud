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
    set_area("south of");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("An unusual hill stands north of you. It's " +
        "covered with grass with some exposed rocks. Rising from " +
        "the center of the hill is a tall stone.");
    add_item(({"hill", "unusual hill"}),
        "The hill looks greener then the rest and taller then the " +
        "other surrounding hills. A tall stone peeks out from the " +
        "center of the unusual hill.\n");
    add_item(({"tall rock", "rock", "tall stone", "stone"}),
        "The tall stone rises from the center of the hill, like " +
        "a dark finger.\n");
    set_add_valley_descrs();

    add_exit(VAL_DIR + "circle", "northeast");
    add_exit(VAL_DIR + "val04", "south");

}

