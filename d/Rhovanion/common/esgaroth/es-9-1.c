inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-10-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-2", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-1", "west");
    set_extras("There is an exit to a moderate house to the south.\n");
}
