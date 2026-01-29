inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-10-10", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-11-11", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-11", "west");
    set_extras("To the north is a the small house of a fisherman.\n");
}
