inherit "/d/Emerald/std/room";

#include "../guild.h"
#include <stdproperties.h>

void create_vamp_room() {}

nomask void create_emerald_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_FREE_VAMP_DVIS, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    create_vamp_room();
}
