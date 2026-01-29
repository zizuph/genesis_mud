inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-1", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-11-3", "south");
    set_extras("You can walk north to the corner or south toward " +
        "the southern edge of the city.  To your west you see the " +
        "back of a house.\n");
}
