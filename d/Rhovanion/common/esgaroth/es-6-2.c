inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-6-1", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-3", "southeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-3", "southwest");
    set_extras("Houses stand to your east, west and south, but there " +
        "entrances must be on different sides, since you see no way to " +
        "enter any of them.\n");
}
