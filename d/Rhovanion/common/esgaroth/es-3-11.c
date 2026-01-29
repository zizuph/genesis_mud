inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-3-10", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-11", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-12", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-11", "west");
    set_extras("There is a sign over the building to the south which " +
        "is painted with the words: \"Town Hall\".\n");
}
