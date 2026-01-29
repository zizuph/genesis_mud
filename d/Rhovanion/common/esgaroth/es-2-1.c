inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-3-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-1", "west");
    set_extras("This is the north edge of the city, and looking far " +
        "to the northeast you see the lonely mountain.  To your south " +
        "is the back of a house.\n");
}
