/*
 * road_base.c
 *
 * This is a baseroom for the roads throughout Meidh.
 * Mainly here just for a few common add_items.
 *
 * Khail - February 22, 2002
 */
#pragma strict_types

#include "room.h"
#include "/d/Khalakhor/sys/defs.h"
inherit "/d/Khalakhor/std/room";
int G_x,
    G_y;

public void
setup_local_coords()
{
    sscanf(file_name(TO),
        ROOM + "/road_%d_%d", G_x, G_y);
}

public int *
query_local_coords()
{
    return ({G_x, G_y});
}

public int *
query_global_coords()
{
    return GLOBAL_COORDS;
}

public int
is_meidh_road()
{
    return 1;
}

public void
create_khalakhor_room()
{
    string temp;

    this_object()->create_road();
    setup_local_coords();

    add_item(({"town","village","meidh","Meidh"}),
        "Meidh is the centre of the human population in " +
        "Khalakhor, and the largest town in Ruighe Cuideal, " +
        "the southeastern region of Khalakhor.  Most of " +
        "the buildings are built in the typical fasion with " +
        "walls made of stacked grey stone slabs topped with a " +
        "roof, however some of the wealthier citizens and " +
        "businesses are made from heavier granite blocks and " +
        "wood.\n");

    add_item(({"sky"}),
        "Looking up, you see the sky is partially overcast, " +
        "with thick white clouds drifting through an " +
        "otherwise blue sky.\n");
    add_item(({"clouds","thick clouds", "white clouds",
        "thick white clouds"}),
        "Thick clouds drift lazily across the sky high above " +
        "your head.\n");
    add_item(({"ground","earth","dirt","road"}),
        "The ground around the town is almost entirely " +
        "hard-packed dirt, with a few grassy patches here and " +
        "there between buildings in the places where neither " +
        "people nor animals have chosen to invent a shortcut " +
        "to somewhere.\n");
    add_item(({"grass"}),
        "Thick patches of green grass cover the ground in " +
        "many places which see little traffic.\n");
    add_item(({"buildings","stone buildings","low buildings"}),
        "Dozens of buildings jut up out of the dirt roads " +
        "throughout the town of Meidh, most look pretty " +
        "much identical with stone walls and " +
        "thatched roofs.\n");
    add_item(({"wall","walls"}),
        "The walls of most the buildings are are made " +
        "in a similar fashion, of large stone blocks " +
        "which have been squared and mortared together " +
        "with clay.\n");
    add_item(({"stones","blocks"}),
        "The stones which make up the walls of most of " +
        "the buildings here are odd-sized blocks of grey " +
        "stone, though moderately well dressed and squared.\n");
    add_item(({"clay"}),
        "The chinks between the stones in the walls are " +
        "packed tightly with river clay to make a more " +
        "secure seal.\n");
    add_item(({"keep"}),
        "On the north edge of the city, tucked up against " +
        "the cliff face, rises the keep around which the " +
        "town of Meidh grew.  It stands atop a small plateau " +
        "overlooking the town.\n");
}
    
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

//    if (interactive(ob))
//        (ROAD_MESSAGES)->start_messages();
}
