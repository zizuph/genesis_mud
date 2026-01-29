inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-9-4", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-5", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-6", "southeast");
    set_extras("To the west is the back of the great hall, while a " +
        "house has a back entrance to the southeast.\n");
}
