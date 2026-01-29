inherit "/d/Rhovanion/lib/room";
#include <stdproperties.h>

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-3-11", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-12", "west");
}

create_room()
{
    set_short("Town hall");
    set_long("You stand in the town hall of Esgaroth, the wooden " +
        "planking of the floor echoes beneath you as you walk.  To " +
        "the west, there is a meeting room, and you can go back " +
        "outside to the north.\n");
    add_prop(ROOM_I_INSIDE, 1);
    create_exits();
}
