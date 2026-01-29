/*
 * F8.c
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
    set_areadesc("valley side");
    set_areaname("Erech");
    set_extraline("This is a road following the eastern part of the vale " +
        "of Erech.");

    path_items();
    vale_items();

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "F7.c", "north", 0, 2, 0);
    add_exit(E_VALE + "E8.c", "west", 0, 2, 0);
}
