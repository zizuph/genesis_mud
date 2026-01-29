inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-9-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-2", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-1", "west");
    set_extras("A small path branches off to the south, into the city.\n");
}
