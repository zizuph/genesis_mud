/*
 * This is part of a road in Port Macdunn.
 *
 * Khail - May 16/97
 */
#pragma strict_types

#include "room.h"
#include <macros.h>

inherit ROADBASE;

public string
query_dir_to_jail()
{
    return "north";
}

public int
block_guild()
{
    write("A worker stops you and informs you the warrior's " +
        "crafthall is undergoing some repairs, and won't " +
        "be open again for some time.\n");
    return 1;
}

public void
create_road()
{
    set_short("wide dirt road");
    set_long("   You are on a wide dirt road leading " +
        "north and south through the middle of the " +
        "village. To the west is a small patch of " +
        "grass, to the east the entrance into what " +
        "appears to be the local chapterhouse of the " +
        "Warrior's Crafthall. The road empties out " +
        "south of here onto a larger road that leads " +
        "east and west.\n");

    add_item(({"chapterhouse","crafthall","Crafthall",
        "warrior's crafthall","Warrior's Crafthall"}),
        "The low stone building bears the crest of the Warrior's " +
        "Crafthall, a crossed sword and axe on a targe. " +
        "This chapterhouse, like most, is simply enough " +
        "constructed like the other buildings in the " +
        "village, despite the fact that the entirety of the " +
        "village militia was probably trained by them.\n");
    add_item(({"crest"}),
        "The crest upon the crafthall bears the symbol " +
        "of the Warrior's Crafthall, crossed sword and axe " +
        "above a targe.\n");
    add_item(({"grass","patch","patch of grass"}),
        "Between here and the next building to the west, " +
        "a small patch of green grass stretches out. " +
        "Well-matted, it appears to be a popular playground " +
        "for local children.\n");

    add_exit(ROOM + "road_12_5", "north");
    add_exit(ROOM + "w_craft_1", "east", VBFC_ME("block_guild"));
    add_exit(ROOM + "road_12_7", "south");
}
