/*
 * /d/Gondor/mordor/ungol/tower/east01.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define PLAYER_I_FOUND_HATCH_EAST01 "_player_i_found_hatch_east01"
#define PLAYER_I_FOUND_HATCH_EAST11 "_player_i_found_hatch_east11"

#define MINIMUM_LOC_SENSE_NEEDED 30
#define MINIMUM_AWARENESS_NEEDED 30

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* get rid of the add_item torch   */
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, ground level");
    add_name( ({ "room", "hall", "hallway", "passage" }) );

    set_short("The tower at Cirith ungol, ground level, prison hallway");
    set_long(BSN("You are at ground level in the tower at Cirith Ungol. " +
        "This room is probaly hewn out of the rocks of the mountain. You " +
        "are in a prison hall. To the north are several small cells where " +
        "prisoners, captured here, are held until they are send further " +
        "for questioning or punishment. Several torches shed a little light " +
        "on the walls. To the south you see something that might look like " +
        "the guards quarters."));

    add_item( ({ "quarters", "guards quarters" }),
        BSN("South of here, you see a room that looks like a guards " +
        "quarters. The orcs that are on guard probably sit there while " +
        "trey try to kill the time."));
    add_item( ({ "cell", "cells", "prison", "prisons" }),
        BSN("To the north you see several doors, leading to small cells " +
        "where prisoner of the orcs might be locked up. In the doors are " +
        "small spy-holes to look at the prisoners in the cells. To the " +
        "east and west this hall continues with more cells."));
    add_item( ({ "hole", "holes", "spy-hole", "spy-holes", "spy hole",
        "spy holes" }),
        BSN("They are small holes in the doors to the prison cells. When " +
        "you look though the holes, you cannot see whether there are " +
        "prisoners in the cells, for they are too dark and when you move " +
        "your head for the hole, you block the little light from the toches " +
        "in this dark passage."));
    add_item( ({ "wood_worm", "wood-worms", "worm", "worms" }),
        BSN("Just as you think you have spotted a wood-worm, it eats its " +
        "way into some wood."));
    add_item("ceiling", "@@ceiling_description");
    add_item( ({ "hatch", "trap-door" }), "@@hatch_description");

    add_prop(OBJ_S_SEARCH_FUN, "search_in_this_room");
    add_prop(OBJ_I_SEARCH_TIME, 10);

    make_door(CIRITH_DIR + "east00",  "north", 2);

    add_exit(CIRITH_DIR + "centre01", "west");
    add_exit(CIRITH_DIR + "east04",   "east");
    add_exit(CIRITH_DIR + "east02",   "south");
}

/*
 * Give a nice description of the ceiling if the player searched it.
 */
string
ceiling_description()
{
    if (TP->query_prop(PLAYER_I_FOUND_HATCH_EAST01))
    {
        return BSN("The ceiling is made of stone and supported by several " +
            "girders. Among the stone plates, there is a hatch, leading to " +
            "a room higher up in this tower.");
    }

    if ((TP->query_prop(PLAYER_I_FOUND_HATCH_EAST11)) &&
        (TP->query_skill(SS_LOC_SENSE) >= MINIMUM_LOC_SENSE_NEEDED))
    {
        return BSN("The ceiling is made of stone and supported by several " +
            "girders. You cannot see anything particular at it, but you " +
            "remember that somewhere in the room above this room or one of " +
            "the adjecent rooms is a hatch in the floor, probably leading " +
            "to this floor.");
    }

    return BSN("Glancing at the ceiling, you discover that the ceiling is " +
        "made of stone. There are several wooden girders supporting the " +
        "ceiling.");
}

/*
 * Give a nice description of the hatch if the player searched it.
 */
string
hatch_description()
{
    if (TP->query_prop(PLAYER_I_FOUND_HATCH_EAST01))
    {
        return BSN("In the ceiling you see a hatch that is carefully hidden " +
            "by the builders. The hatch is not that big, but being about " +
            "three feet in length and width it is large enough for a you to " +
            "fit through. You do not see any way to open the hatch meaning " +
            "that you have to find another way to get up to the first floor.");
    }

    if ((TP->query_prop(PLAYER_I_FOUND_HATCH_EAST11)) &&
        (TP->query_skill(SS_LOC_SENSE) >= MINIMUM_LOC_SENSE_NEEDED))
    {
         return BSN("You remember that somewhere in the room above this " +
             "room or one of the adjecent rooms is a hatch in the floor, " +
             "probably leading to this floor, but you cannot locate it " +
             "briefly looking at the ceiling.");
    }

    return BSN("You find no hatch.");
}

string
search_in_this_room(object searcher, string str)
{
    if (str == "ceiling")
    {
        if (searcher->query_skill(SS_AWARENESS) >= MINIMUM_AWARENESS_NEEDED)
        {
            return BSN("Thorough inspection of the ceiling reveals a hatch " +
                "that is carefully hidden by the builders of this great " +
                "tower.");
        }
        else
        {
            return BSN("You search the ceiling, but your eyes are not " +
                "skilled enough to discover anything except a lost " +
                "wood-worm.");
        }
    }

    if (((str == "hatch") || (str == "trap-door")) &&
        (searcher->query_prop(PLAYER_I_FOUND_HATCH_EAST01)))
    {
        return BSN("Though you cannot reach the ceiling, you try to examine " +
            "it as good as possible. However, you cannot see a way to get " +
            "the hatch to open. Maybe it is a trap-door in the room " +
            "upstairs or maybe there is another way to open it.");
    }

    return 0;
}
