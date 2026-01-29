inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-2", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-1", "west");
    set_extras("There is an opening for a small house to the south, " +
        "and the road continues west and east here.\n");
}
