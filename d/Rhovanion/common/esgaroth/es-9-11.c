inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-9-10", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-11", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-12", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-11", "west");
    set_extras("To the south is a home which is slightly larger than " +
        "most of the other homes in the area.\n");
}
