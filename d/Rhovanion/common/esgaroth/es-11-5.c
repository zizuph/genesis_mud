inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-4", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-11-6", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-5", "west");
    set_extras("To the east lies the lake.  Roads lead in all other " +
        "cardinal directions.\n");
}
