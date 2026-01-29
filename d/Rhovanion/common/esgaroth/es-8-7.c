inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-6", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-7", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-8", "south");
    set_extras("The local post office is to the east of here.\n");
}
