inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-5-4", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-5", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-6", "southwest");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-5", "west");
    set_extras("You are standing on the northwest edge of the market pool, where " +
        "people come to fill their buckets of water and to gossip.  " +
        "The road follows the pool to the east and the southwest, and " +
        "leads into the city in other directions.\n");
}
