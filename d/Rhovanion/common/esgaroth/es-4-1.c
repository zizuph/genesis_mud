inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-5-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-2", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-1", "west");
    set_extras("The road continues to the west and east, and there is " +
    "an entrance into a small house to the south.\n");
}
