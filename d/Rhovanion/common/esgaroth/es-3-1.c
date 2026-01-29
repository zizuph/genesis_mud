inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-2", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-1", "west");
    set_extras("You can go further into the city to the south, or " +
    "continue along the edge of the city to the west and east.  To " +
    "your southwest and southeast you see the sides of houses.\n");
}
