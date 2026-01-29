/*
 * other/gates/w-15.c
 *
 * Skippern 20(c)01
 *
 * Outside Dol Amroth, by the outher gate.
 */
#include "../../defs.h"

inherit "/d/Gondor/common/lib/area_room";
inherit DOL_LIB + "gates";

public void
create_area_room()
{
    set_areatype(AREATYPE_ROAD);
    set_land("Belfalas");
    set_areadesc("small hill");
    set_area("western");
    set_areaname("Dor-en-Ernil");

    set_extraline("To the west a large wall with a gate towers up.");

    add_item( ({ "wall", "large wall" }), "A large wall surrounds the city " +
	      "of Dol Amroth. The wall is tall, and made from granite " +
	      "stone. Ontop the wall is an armament, where soldiers can " +
	      "keep a sharp lookout.\n");

    add_exit(DOL_OTHER + "gates/v-15", "west", &outher_gate(), 1, 
	     &outher_visible());
    add_exit(DOL_OTHER + "outside/near", "east", 0, 1);
}
