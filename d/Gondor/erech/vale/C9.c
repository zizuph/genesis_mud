/*
 * C9.c
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
    set_area("southern");
    set_areadesc("field");
    set_areaname("Erech");
    set_extraline("This is a road following the eastern side of the vale " +
        "of Erech. A bit to the north the sound of running water can be " +
        "heard.");

    path_items();
    vale_items();

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "D9.c", "east", 0, 2, 0);
    add_exit(E_VALE + "C10.c", "south", 0, 2, 0);
    add_exit(E_FIELD + "B9.c", "west", &to_field(), 3, 1);
    add_exit(E_FIELD + "D8.c", "northeast", &to_field(), 3, 1);
}
