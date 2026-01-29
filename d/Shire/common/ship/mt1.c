/*
 * 
 */
#include "/d/Gondor/defs.h"
inherit (COMMON_DIR + "room");
#include <stdproperties.h>

void
create_room()
{
    set_short("Near the docks and piers of Mithlond");
    set_long("The docks and piers line the western side of Mithlond.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
