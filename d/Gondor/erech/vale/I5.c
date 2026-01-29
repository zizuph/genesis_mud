/*
 * I5.c
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
    set_areadesc("vally side");
    set_areaname("Erech");
    set_extraline("A bit to the north the bouldering sound of water can be " +
        "heard. Allmost the entire field can be seen from this point. A " +
        "road leads north and southwest.");

    path_items();
    vale_items();

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "I4.c", "north", 0, 2, 0);
    add_exit(E_VALE + "H6.c", "southwest", 0, 2, 0);
}
