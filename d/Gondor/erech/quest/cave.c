/*
 * base_room
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

//inherit "/d/Gondor/common/lib/area_room";

inherit E_STD + "path.c";

//inherit E_LIB + "vale.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_gondor();

/*
 * Function name:    create_gondor()
 * Definition   :    Creates the room.
 */
public void
create_gondor()
{
    set_short("Inside a small cave.");
    set_long("This is the inside of a small cave. The cave " +
	"is narrow and the walls are rough. It looks like somebody " +
	"have used it as a cave lately.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_CAVE);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);

    add_exit(E_FIELD + "G4.c", "out", 0, 0, 1);
}
