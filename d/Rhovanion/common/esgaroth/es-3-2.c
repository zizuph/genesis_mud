inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-3-1", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-3", "south");
    set_extras("The road continues to the north and the south, and " +
        "the sides of houses stand to your east and west.\n");
}
