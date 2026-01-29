inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-5-3", "south");
    set_extras("There is only one door in this house, and it leads " +
        "south to the city.\n");
}
