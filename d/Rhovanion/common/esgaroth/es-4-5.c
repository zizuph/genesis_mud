inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-4", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-5", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-6", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-5", "west");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-4", "northwest");
    set_extras("The owners of the house to the west would probably be " +
        "happier if you would continue to the north or the south and leave " +
        "their house alone.\n");
}
