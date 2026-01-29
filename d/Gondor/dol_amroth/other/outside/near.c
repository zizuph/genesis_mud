/* -*- Mode: C -*-
 *
 * near.c
 *
 * Skippern 20(c)01
 *
 */
inherit "/d/Gondor/common/lib/area_room";

#include "../../defs.h"

void
create_area_room()
{
    set_areatype(AREATYPE_ROAD);
    set_land("Belfalas");
    set_areadesc("small hill");
    set_area("western");
    set_areaname("Dor-en-Ernil");

    set_extraline("You see a city wall to the west.");

    add_item( ({ "wall", "city wall" }), "To the west you see a large " +
	      "city wall, surrounding the city of Dol Amroth.\n");
    add_item( ({ "town", "city", "dol amroth", "Dol Amroth" }),
	      "Behind the wall you see a large groupe of houses forming " +
	      "the city of Dol Amroth.\n");

    add_exit(DOL_OTHER + "gates/w-15", "west", 0, 1);
    add_exit(DOL_OTHER + "outside/close", "northeast", 0, 1);
}
