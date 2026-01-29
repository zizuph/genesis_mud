inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-5", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-5", "northeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-7", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-6", "west");
    set_extras("You are standing on the west edge of the market pool--  " +
        "a center for gossip and fresh news.\n");
}
