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

    set_extraline("The ground slowly rises to the north and west " +
        "as it falls from the Barrow Downs. The land is covered " +
        "in green grass. To the south is an unusual hill. To the " +
        "north and east is a dark line, marking the edge of the " +
        "barrows.");
    add_item(({"hill", "unusual hill"}),
        "The hill looks greener then the rest and taller then the " +
        "other surrounding hills. A tall stone peeks out from the " +
        "center of the unusual hill.\n");
    add_item(({"tall rock", "rock", "tall stone", "stone"}),
        "The tall stone rises from the center of the hill, like " +
        "a dark finger.\n");
    set_add_valley_descrs();

    add_exit(VAL_DIR + "val07", "north");
    add_exit(VAL_DIR + "circle", "south");

}

