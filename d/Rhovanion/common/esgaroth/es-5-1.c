inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-6-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-1", "west");
    set_extras("The road continues west and east, and far to the " +
        "northeast you see the lonely mountain.\n");
}
