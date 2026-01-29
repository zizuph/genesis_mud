inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-7-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-2", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-1", "west");
    set_extras("This is a junction in the center of the north edge of " +
        "town.  You can go south into the wooden streets of Esgaroth, " +
        "or continue west and east along the planked road.\n");
}
