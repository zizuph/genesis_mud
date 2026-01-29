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
    set_long("   You are at the entrance of the long stone hall which "+
        "runs along the south side of the road. A wooden door with "+
        "a plaque bars the entrance to the hall. To the north is "+
        "a lush garden behind a high iron fence. The tower of the "+
        "massive stone structure rises into the sky to the northeast.\n");
 
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
        "along the road on its southern side. The entrance of the "+
        "hall is to the south.\n");
    add_item("door",
        "The door of the hall is made of wood and bears a plaque. "+
        "It is closed.\n");
    add_cmd_item("door",({"open","close","lock","unlock"}),
        "The door is closed and locked.\n");
    add_item("plaque",
        "The plaque bears an emblem consisting of a silver shield "+
        "split diagonally by green band. Above the band is the image "+
        "of a tree, while a footprint adorns the shield below the "+
        "band.\n");
    add_item("garden",
        "It is a lush green garden growing on the west side of the "+
        "large stone building. It is guarded by a high iron fence.\n");
    add_item("fence",
        "Made of tall iron spikes set into the ground and joined by "+
        "thick horizontal bars, it runs along the north side of the "+
        "road here, protecting the garden on the other side.\n");
 
    add_exit(ROOM + "road_5_7", "east");
    add_exit(ROOM + "road_3_7", "west");
}
