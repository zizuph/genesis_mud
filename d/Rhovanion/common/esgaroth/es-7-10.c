inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-9", "northeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-10", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-11", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-10", "west");
    set_extras("Market pool is to the north, and to the east is a house.  " +
        "The lady of the house is probably a gossip monger, as this house " +
        "is the closest in all the city to the market pool.\n");
}
