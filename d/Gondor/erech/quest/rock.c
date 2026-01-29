/*
 * base_room
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit "/d/Gondor/common/lib/area_room";

inherit E_STD + "vale.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();

/*
 * Function name:    create_area_room()
 * Definition   :    Creates the room.
 */
public void
create_area_room()
{
    set_short("On a covenent rock in the vale of Erech.");
    set_areatype(AREATYPE_HILLS);
    set_area("northern");
    set_areadesc("covenent rock");
    set_areaname("Erech");
    set_extraline("The black rock under your feet looks strange and " +
        "seems to be magical.");

    vale_items();

    add_item( ({ "view", "landscape", "view over landscape" }),
	"You can see the whole vale from this point. The vale is narrower " +
	"to the north where it ends in the White Mountains, and to the " +
	"south the vale turns westwards. The vale is darkish green telling " +
	"you that there are large grass field with occational bushes here " +
	"there. To the southeast you notice a thin line of smoke coming " +
	"from a small group of houses.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "D4.c", "down", 0, 2, 1);
}
