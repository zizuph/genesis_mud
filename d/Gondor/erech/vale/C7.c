/*
 * C7.c
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
    set_short("In the vale of Erech.");
    set_areatype(AREATYPE_ROAD);
    set_area("central");
    set_areadesc("valley side");
    set_areaname("Erech");
    set_extraline("This is a road following the western side of the " +
        "vale of Erech. A bit to the east the sound of running water " +
        "can be heard. Through some bushes to the south there seems to " +
        "be a small field.");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    vale_items();
    path_items();
    add_item("bushes", "Through some bushes along the road you can see " +
	     "a small field.\n");

    add_exit(E_VALE + "D6.c", "northeast", 0, 2, 0);
    add_exit(E_VALE + "B8.c", "southwest", 0, 2, 0);
    add_exit(E_FIELD + "C8.c", "south", &to_field(), 2, 1);
}






