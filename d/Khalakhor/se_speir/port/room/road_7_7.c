/*
 * This is part of a road in Port Macdunn.
 *
 * Khail/Zima - July 25/97
 */
#pragma strict_types
 
#include "room.h"
 
inherit ROADBASE;
 
public string
query_dir_to_jail()
{
    return "east";
}
 
public void
create_road()
{
    set_short("wide dirt road");
    set_long("   You are on a wide dirt road leading east " +
        "and west through the village of Port Macdunn. " +
        "The high walls of a massive stone structure rise along "+
        "the north side of the road, while the side of a long stone "+
        "hall stretches along the south side.\n");

    add_item("structure",
        "It is a large stone structure with walls that rise high "+
        "above you, casting a dim shadow on the road. There is a "+
        "niche high on the wall with a statue standing in it. You "+
        "can see the entrance to the structure further west.\n");
    add_item("niche",
        "It is an arched, hollowed out alcove in the face of the "+
        "wall, in which a statue looks out over the road.\n");
    add_item("statue",
        "It is a figure of an angel with his wings spread high, "+
        "holding a long trumpet to his lips with one hand and "+
        "a scroll in the other.\n");
    add_item("hall",
        "It is a long stone hall, typical of the buildings of the "+
        "village, with stone walls and a thatched roof. It extends "+
        "along the road on its southern side.\n");
 
 
    add_exit(ROOM + "road_8_7", "east");
    add_exit(ROOM + "road_7_8", "south");
    add_exit(ROOM + "road_6_7", "west");
}

