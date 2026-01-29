inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-2", "northeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-4", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-2", "northwest");
    set_extras("The plankwalk leads northeast, northwest, and south from " +
        "here, and you see houses in many directions.\n");
}
