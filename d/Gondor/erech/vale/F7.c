/*
 * F7.c
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
    set_extraline("Almost the entire field can be seen from this point. " +
        "It is possible to see a farm not far away on the field. A road " +
        "leads east and south.");

    path_items();
    vale_items();

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "G7.c", "east", 0, 2, 0);
    add_exit(E_VALE + "F8.c", "south", 0, 2, 0);
    add_exit(E_FIELD + "E7.c", "west", &to_field(), 2, 1);
}
