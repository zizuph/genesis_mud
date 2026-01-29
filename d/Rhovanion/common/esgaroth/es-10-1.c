inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-1", "west");
    set_extras("The road continues west, and reaches the edge of the " +
        "town to the east.\n");
}
