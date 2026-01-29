inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-8", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-9", "southwest");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-8", "west");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-7", "northwest");
    set_extras("A house is to the west.\n");
}
