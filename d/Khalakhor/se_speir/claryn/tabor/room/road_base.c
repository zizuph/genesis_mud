/*
 * road_base.c
 *
 * This is a baseroom for the road throughout Tabor Sogh.
 * Mainly here just for a few common add_items.
 *
 * Khail - July 22, 1997
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
        "/d/Khalakhor/se_speir/port/room/road_%d_%d", G_x, G_y);
}

public int *
query_local_coords()
{
    return ({G_x, G_y});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

public int
is_tabor_sogh_road()
{
    return 1;
}

public void
create_khalakhor_room()
{
    string temp;

    this_object()->create_road();
    setup_local_coords();

    add_item(({"town","village","tabor sogh","Tabor Sogh"}),
        "Tabor Sogh is an old fishing village, but has never " +
        "grown much beyond a handful of homes and a few " +
        "necessities for fishing. The village consists of " +
        "a single road upon which all buildings are built " +
        "of dark grey stone.\n");
    add_item(({"sky"}),
        "Looking up, you see the sky is partially overcast, " +
        "with thick grey clouds drifting through an " +
        "otherwise blue sky.\n");
    add_item(({"clouds","thick clouds", "grey clouds",
        "thick grey clouds"}),
        "Thick clouds drift lazily across the sky high above " +
        "your head.\n");
    add_item(({"ground","earth","dirt","road"}),
        "The ground here is firmly packed earth on the road, " +
        "with thick strips of grass filling in anything that " +
        "isn't road nor building.\n");
    add_item(({"grass"}),
        "Thick patches of green grass cover the ground in " +
        "many places which see little traffic, which is most " +
        "of the roads.\n");
    add_item(({"buildings","stone buildings","low buildings"}),
        "A number of buildings occupy the village, most " +
        "look pretty much identical with stone walls and " +
        "thatched roofs.\n");
    add_item(({"wall","walls"}),
        "The walls of all the buildings are are made " +
        "in a similar fashion, of thin plates of dark " +
        "grey stone which have been neatly stacked together. " +
        "No mortar or packing is evident, but the walls " +
        "appear quite sturdily built regardless.\n");
    add_item(({"stones","blocks"}),
        "The stones which make up the walls of most of " +
        "the buildings here are thin plates of dark grey " +
        "stone, carefully stacked to form walls for the " +
        "buildings.\n");

    add_item(({"shore","shoreline"}),
        "The road here follows the shoreline of the great " +
        "southern sea, Lear Min, north and south. The shore, " +
        "to the west, disappears into the distance in both " +
        "directions, broken only by a small pier jutting out " +
        "into the water near the center of the village.\n");
    add_item(({"water","sea","Lear Min","lear min"}),
        "The waters of Lear Min are are slate grey in colour, " +
        "with white caps topping the larger of the waves in " +
        "the choppy waters as far as the eye can see.\n");

    if (G_y == 5)
        add_item(({"pier","piers"}),
            "Immediately west from here, the small pier of " +
            "Tabor Sogh juts out westwards into the " +
            "waters of Lear Min.\n");
    else if (G_y < 5)
        add_item(({"pier","piers"}),
            "To the south, the small wooden pier of Tabor " +
            "Sogh juts out westwads into the waters of " +
            "Lear Min.\n");
    else 
        add_item(({"pier","piers"}),
            "To the north, the small wooden pier of Tabor " +
            "Sogh juts out westwads into the waters of " +
            "Lear Min.\n");
} 
    
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        (ROAD_MESSAGES)->start_messages();
}
