inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-7-3", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-5", "south");
    set_extras("To the south lies the edge of the market pool, and " +
        "going north will lead you toward the edge of the city.\n");
}
