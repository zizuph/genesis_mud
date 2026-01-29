inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-1-10", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-11", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-12", "south");
    add_exit("/d/Rhovanion/common/esgaroth/westbridge1", "west");
    set_extras("There is a bridge which leads out of town here to the west, " +
        "toward Mirkwood Forest.\n");
}
