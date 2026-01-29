inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-1", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-3", "southeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-3", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-3", "southwest");
    set_extras("You can venture further into the city to the southwest " +
        "and southeast, while south will take you into one of the " +
        "citizen's homes, and north will lead you back to the edge of the " +
        "city.\n");
}
