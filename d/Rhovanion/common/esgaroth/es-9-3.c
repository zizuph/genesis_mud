inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-10-3", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-4", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-3", "west");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-2", "northwest");
    set_extras("A side entrance leads into a house to the west.\n");
}
