inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-9", "northeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-11", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-10", "west");
    set_extras("To the west is a house, and to the east you see a " +
        "small bridge arching over the gap in part of the planking.\n");
}
