inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-1-3", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-5", "south");
    set_extras("The road continues to the north and south here.\n");
}
