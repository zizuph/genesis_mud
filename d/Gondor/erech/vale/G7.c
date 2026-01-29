/*
 * G7.c
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
        "leads northeast and west.");

    path_items();
    vale_items();
    add_item_field();
    add_item( ({"farm","building","buildings","house","houses","barn"}), 
	"Out on the field you see " +
        "a small group of buildings. One large red building looks abit " +
        "a barn, and by this a white house whith tiled roof stands.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "H6.c", "northeast", 0, 2, 0);
    add_exit(E_VALE + "F7.c", "west", 0, 2, 0);
    add_exit(E_FIELD + "G6.c", "north", &to_field(), 2, 1);
}
