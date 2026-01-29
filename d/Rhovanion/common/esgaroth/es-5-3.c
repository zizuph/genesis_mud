inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-5-2", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-2", "northeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-3", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-4", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-3", "west");
    set_extras("You can enter houses to the north and the east.\n");
}
