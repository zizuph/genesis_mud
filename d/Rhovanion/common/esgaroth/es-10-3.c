inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-3", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-3", "west");
    set_extras("The plankwalk continues to the west and east, " +
        "to the south you hear subdued sounds of drunken shouting.\n");
}
