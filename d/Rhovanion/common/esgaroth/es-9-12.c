inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-9-11", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-12", "east");
    set_extras("The kitchen lies to the east from here.\n");
}
