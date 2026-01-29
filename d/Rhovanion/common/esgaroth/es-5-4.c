inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-5-3", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-4", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-5", "south");
    set_extras("To the west is the back of a pub, and to the east lies " +
        "a house.\n");
}
