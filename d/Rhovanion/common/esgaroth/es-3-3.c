inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-3-2", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-3", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-4", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-3", "west");
    set_extras("Roads lead in all the cardinal directions here.\n");
}
