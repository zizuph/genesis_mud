/*
 * C2.c
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
    set_area("northern");
    set_areadesc("valley side");
    set_areaname("Erech");
    set_extraline("This is a road following the western side of the " +
        "vale of Erech. A path goes south along a ridge leading to " +
	"a strange hill.");

    vale_items();
    path_items();
    hill_items();

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "D1.c", "northeast", 0, 2, 0);
    add_exit(E_VALE + "C3.c", "south", 0, 2, 0);
    add_exit(E_VALE + "B3.c", "southwest", 0, 2, 0);
}
