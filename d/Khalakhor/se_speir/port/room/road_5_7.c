/*
 * This is part of a road in Port Macdunn.
 *
 * Khail/Zima - July 25/97
 */
#pragma strict_types
 
#include "room.h"
#include "ktricircum.h"
 
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
        "To the south there is a long stone hall with a thatched "+
        "roof, while the walls of a tower rise high on the massive "+
        "stone structure to the north.\n");
 
    add_item("structure",
        "It is a large stone structure with walls that rise high "+
        "above you, casting a dim shadow on the road. There is a "+
        "a tower of the building here with a niche high on the wall "+
        "in which a statue stands gazing out over the street. You "+
        "can see the entrance to the structure further east.\n");
    add_item("tower",
        "Rising high above the rest of the structure, you see "+
        "open windows high at its top. A spire at the top seems "+
        "to reach almost to the clouds, and is topped with large "+
        "symbol made of gold.\n");
    add_item("spire",
        "It is a tall slender shaft which tapers to a point from "+
        "the top of the tower. It seems to reach into the clouds. "+
        "It is topped with a large symbol made of gold.\n");
    add_item("symbol",TRICIRCUM);
    add_item("niche",
        "It is an arched, hollowed out alcove in the face of the "+
        "wall, in which a statue looks out over the road.\n");
    add_item("statue",
        "It is a figure of a tall male elf dressed in a long robe "+
        "with a thick gold belt. He wears a cap on his head "+
        "with straps that fall down the sides of his face like long "+
        "sideburns. He holds aloft a large crystal which shimmers "+
        "with the colors of the rainbow.\n");
    add_item("hall",
        "It is a long stone hall, typical of the buildings of the "+
        "village, with stone walls and a thatched roof. It extends "+
        "along the road on its southern side.\n");
 
    add_exit(ROOM + "road_6_7", "east");
    add_exit(ROOM + "road_4_7", "west");
}
 
