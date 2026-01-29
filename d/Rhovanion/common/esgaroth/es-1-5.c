inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-1-4", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-5", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-6", "south");
    set_extras("A road leads east further into the city from here.\n");
}
