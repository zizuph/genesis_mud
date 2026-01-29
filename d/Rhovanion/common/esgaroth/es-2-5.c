inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-3-4", "northeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-6", "southeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-5", "west");
    set_extras("The road branches out to the northeast and southeast here, " +
        "circling the house that lies to the east.\n");
}
