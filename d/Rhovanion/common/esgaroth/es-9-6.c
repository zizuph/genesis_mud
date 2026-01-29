inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-6", "west");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-5", "northwest");
}

create_room()
{
    set_short("great hall");
    set_long("This is the great hall of Esgaroth, but you can't " +
        "really see what is so great about it at the moment.  " +
        "Apparently it is under renovation.\n");
    add_prop(ROOM_I_INSIDE, 1);
    create_exits();
}
