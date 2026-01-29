inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-2", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-11-4", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-3", "west");
    set_extras("The road leads north and south along the east edge of " +
        "Esgaroth, and intersects with another road leading west.\n");
}
