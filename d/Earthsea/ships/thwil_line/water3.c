#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>

public void
create_earthsea_room()
{
    set_short("On the sea");
    set_long("The dark blue sea surrounds the ship. You see " +
        "the shore of the small town of Thwil ahead, welcoming " +
        "you to the Isle of Roke.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
