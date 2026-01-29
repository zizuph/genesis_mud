inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-9-6", "southeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-6", "south");
}

create_room()
{
    set_short("great hall");
    set_long("This is normally the great hall, where affairs of " +
        "state, and those events demanding formality are held.  " +
        "Due to a recent rat infestation though, the building is " +
        "temporarily abandoned.\n");
    add_prop(ROOM_I_INSIDE, 1);
    create_exits();
}
