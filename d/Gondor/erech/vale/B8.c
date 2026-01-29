/*
 * B8.c
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
    set_extraline("This is a road following the western side of the " +
        "vale of Erech. A bit to the south the sound of running water " +
        "can be heard. Through some bushes to the east there seems to " +
	"be a small field.");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    vale_items();
    path_items();
    add_item( ({"bush","bushes"}), "Some bushes grows along the road, " +
        "and behind some of the bushes on the eastern side of the " +
        "road there seems to be a small field.\n");
    add_item( ({"field","small field"}), "Behind some bushes to the " +
        "east there seems to be a small field.\n");

    add_exit(E_VALE + "C7.c", "northeast", 0, 2, 0);
    add_exit(E_VALE + "A9.c", "southwest", 0, 2, 0);
    add_exit(E_FIELD + "C8.c", "east", &to_field(), 2, 1);
}
