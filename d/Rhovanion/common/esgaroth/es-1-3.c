inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-1-2", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-3", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-4", "south");
    set_extras("The road continues to the north and the south, and " +
        "leads into the city from the south.\n");
}
