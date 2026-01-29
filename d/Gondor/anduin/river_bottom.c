/*
 * anduin/river_bottom.c
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
#include <stdproperties.h>

void
create_room()
{
    set_short("On the bottom of the River Anduin");
    set_long("You are on the bottom of the Anduin River. This is just " +
        "a temporary room for use with objects sinking in the River.\n");
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
}

