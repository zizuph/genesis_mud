/*
 * anduin/sriver1.c
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
#include <stdproperties.h>

void
create_room()
{
    set_short("Somewhere on the River Anduin");
    set_long("The Anduin River runs southwest towards the ocean.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
