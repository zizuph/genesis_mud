/*
 *  /d/Gondor/guilds/rangers/hq/herb_shop.c
 *
 *  Herb shop of Ranger Central Headquarters
 *
 *  Coded by Alto
 *    Original theme of Druedain hideout by Elessar.
 *
 *  Modification log:
 *    Gwyneth, 3 May 2004
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
#include "/d/Gondor/defs.h"

#include <macros.h>
#include <std.h>
#include <stdproperties.h>

inherit RANGERS_HQ_DIR + "ch_funcs.c";

public string long_func();
public void   reset_room();

static object Herbalist;

public void
create_gondor()
{
    set_short("the office of the Master Herbalist");
    set_long(long_func);

    hideout_add_items();

    add_item(({"container", "containers"}), "There are many kinds of "
        + "containers stacked around the room, including shelves, boxes, "
        + "bottles, baskets, drawers and cabinets. All of them seem to "
        + "be filled with botanicals of one sort or another.\n");
    add_item(({"shelf", "shelves"}), "There are shelves filling almost "
        + "every open space on the walls here! Upon them are more boxes, "
        + "bottles and baskets than you can count.\n");
    add_item(({"box", "boxes"}), "Boxes of every shape, size and colour "
        + "can be seen on the shelves, in the corners of the room, and "
        + "even hanging from the massive oak beams supporting the ceiling!\n");
    add_item(({"bottle", "bottles"}), "Bottles of all sizes can be seen "
        + "resting on the shelves. They appear to be used for storing "
        + "herbs.\n");
    add_item(({"basket", "baskets", "wicker basket", "wicker baskets"}),
        "Wicker baskets can be seen stacked upon the various shelves and upon "
        + "the floor. These are undoubtedly used by the Master Herbalist to "
        + "store those herbs which he stocks in abundance.\n");
    add_item(({"drawer", "drawers"}), "The cabinets contain numerous drawers, "
        + "all of which appear to be stuffed with packets of herbs.\n");
    add_item(({"cabinet", "cabinets"}), "Difficult to see beneath the stacks "
        + "of baskets and bottles, there are several cabinets placed about "
        + "the room. Each cabinet has numerous drawers used for the storage "
        + "of botanical inventory.\n");
    add_item(({"room"}), &long_func());
    add_item(({"south wall"}), "There is a small window built into the "
        + "south wall.\n");
    add_item(({"window", "small window"}), "In the south wall there is built a "
        + "small window. Without the fresh breeze blowing in from the window, "
        + "the scent of herbs in the room might become too overpowering.\n");
    add_item(({"botanical", "botanicals"}), "You will need to speak with the "
        + "Master Herbalist to examine them more closely. He will probably "
        + "require that you pay for them first.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(RANGERS_HQ_DIR + "boardhall",   "north",  0, 0);

    reset_room();
}

public string
long_func()
{
    object clock = find_object(CLOCK);
    string time = clock->query_time_of_day(),
            longtxt = "You are standing in a small room cramped with "
                + "numerous shelves, boxes, bottles, baskets and drawers. "
                + "A pungent herbal scent hangs heavy in the air, and you "
                + "suspect that the various containers about the room must "
                + "be stuffed to the brim with local and exotic botanicals. "
                + "If the Master Herbalist is about, he may be willing to "
                + "answer questions about his inventory. He might also "
                + "purchase or sell herbs, depending on his available stock.";

    switch (time)
    {
    case "night":
        longtxt += " A cool night breeze blows in through a small window "
            + "in the south wall.";
        break;
    case "early morning":
        longtxt += " The rising sun peeks in through a small window in the "
            + "south wall.";
        break;
    case "morning":
    case "noon":
    case "afternoon":
        longtxt += " Daylight shines through a small window in the south wall.";
        break;
    case "evening":
        longtxt += " The setting sun sends a few last rays through a small "
            + "window in the south wall.";
        break;
    }

    return (longtxt + "\n");
}

public void
reset_room()
{
    if (!objectp(Herbalist))
    {
        Herbalist = clone_object(RANGERS_NPC + "herbalist");
        Herbalist->arm_me();
        Herbalist->move(TO);
    }
}

