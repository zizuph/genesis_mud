inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-7-1", "north");
    set_extras("The entrance is to the north.  You can leave back to " +
        "the edge of the city that direction.\n");
}
