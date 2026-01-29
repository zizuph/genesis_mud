/* created by Aridor, 05/03/94
    the temporary room for the pigeon high up in the air */

inherit "/std/room";

#include "/d/Krynn/common/defs.h"

void
create_room()
{
    set_short("In the air");
    set_long("You are high up in the air.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
}
