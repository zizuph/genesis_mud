inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-3", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-11-5", "south");
    set_extras("The road continues north and south from here, and to " +
        "the west lies the back of one of the local pubs.\n");
}
