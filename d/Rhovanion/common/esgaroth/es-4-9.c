inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-8", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-10", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-10", "southwest");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-9", "west");
    set_extras("The doorway of the house to the west is wide open.\n");
}
