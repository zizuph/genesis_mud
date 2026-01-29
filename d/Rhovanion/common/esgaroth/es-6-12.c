inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-6-11", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-12", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-12", "west");
}

create_room()
{
    set_short("Welcome center");
    set_long("This is the visitor's center in Esgaroth, where " +
        "there are facilities set up that visitors often need.  There " +
        "is an adventurer's guild to the east, and a shop to the west.\n");
    add_prop(ROOM_I_INSIDE, 1);
    create_exits();
}
