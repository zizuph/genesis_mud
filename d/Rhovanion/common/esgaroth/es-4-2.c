inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-1", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-3", "south");
    set_extras("The back door of the house is to the north while the " +
        "front door leads south into the city.\n");
}
