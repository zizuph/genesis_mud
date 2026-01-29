inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-2-2", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-3", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-3", "west");
    set_extras("There is an entrance to a house to the north, and to " +
        "the south is another home, but the entrance must be on one of " +
        "its other sides.\n");
}
