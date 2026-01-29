inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-5", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-11-7", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-6", "west");
    set_extras("A small house lies to the west.\n");
}
