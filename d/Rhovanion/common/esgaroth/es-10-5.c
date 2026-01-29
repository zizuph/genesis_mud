inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-5", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-5", "west");
    set_extras("You can walk to the west of the east here, and from the " +
        "north you hear the quiet sounds of a small bar.\n");
}
