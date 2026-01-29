/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/pathway1.c
 *
 *  The path leading up into the hills reaches its height
 *  here, cresting to fall finally down into the valley
 *  of Del Rimmon to the north.
 *
 *  Copyright (c) January 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>      /* for QCTNAME, etc */
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* global variables */

/* prototypes */
public void        create_del_rimmon();


/*
 * Function name:       create_del_rimmon
 * Description :        set up the room with area presets
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_cliffs");
    set_short("on a pathway in the Blackwall Mountains");
    set_long(del_rimmon_long);
    Extraline =
             "Massive formations of rock rise forbodingly to the north,"
           + " framing a narrow corridor through which this pathway"
           + " leads as it begins its trek downward into what appears"
           + " to be a valley of some kind in that direction. To the"
           + " west, the pathway travels downwards along some"
           + " switchbacks as it leads down out of the mountains. A"
           + " waterfall is visible to the east.";

    add_item( ({ "mountain", "mountains", "blackwall mountains",
                 "cliff", "cliffs" }),
        "The Blackwall Mountains spread out in all directions north"
      + " of here, their tall peaks meeting with the sky as far"
      + " as the eye can see.\n");
    add_item( ({ "rock", "formations", "formation", "rock formation",
                 "rock formations", "formation of rock",
                 "formations of rock",
                 "massive formations of rock" }),
        "Just to the north, rock formations rise to meet with the"
      + " bright sky. The path travels between two rises, the"
      + " easternmost of which rises to a great peak - one of three"
      + " which are visible.\n");
    add_item( ({ "rise", "rises", "two rises", "rise of rock", 
                 "rises of rock", "two rises of rock" }),
        "The path travels through two rises of rock to the north,"
      + " A high ridge of rock on the left, and a great peak on"
      + " the right.\n");
    add_item( ({ "ridge", "high ridge", "ridge of rock",
                 "high ridge of rock" }),
        "The ridge of rock rises above the pathway to the north, to"
      + " run westward as far as the eye can see.\n");
    add_item( ({ "peak", "great peak", "eastern peak", "east peak",
                 "easternmost peak", "melan rath" }),
        "This is the peak of Melan Rath, one of three great peaks"
      + " which rise at the southern end of these mountains. It rises"
      + " high into the sky just to the northeast. The pathway seems"
      + " to run just to the left of its base ahead to the north.\n");
    add_item( ({ "peaks", "three peaks", "three great peaks",
                 "great peaks" }),
        "Three great peaks are visible from here. Directly ahead is"
      + " Melan Rath, rising majestically into the sky above the"
      + " path. Just behind it the uppermost reaches of"
      + " Ael Rannath are visible. A ways to the east Melan Earl"
      + " can also be seen, rising above a massive waterfall which"
      + " empties its waters at the feet of the peak.\n");
    add_item( ({ "ael rannath", "uppermost reaches" }),
        "Ael Rannath is mostly obscured by Melan Rath, which rises"
      + " directly to the north. Its uppermost reaches peek above"
      + " the closer peak, however, glimmering in the distance.\n");
    add_item( ({ "melan earl" }),
        "Melan Earl rises majestically a ways to the east, towering"
      + " over a great waterfall which empties its sluice over the"
      + " cliffs to fall deep into the lowlands below.\n");
    add_item( ({ "waterfall", "rimmon falls" }),
        "These are Rimmon Falls, which endlessly empty the mighty"
      + " waters of the Lake of Del Rimmon over the cliffs to fall"
      + " far below to become the Telberin River. The sound of the"
      + " waterfall is faint, but ever-present from this distance.\n");
    add_item( ({ "lake", "del rimmon", "lake of del rimmon" }),
        "The lake is not visible from here, though Rimmon Falls"
      + " bear its waters over the cliffs.\n");
    add_item( ({ "lowlands", "below" }),
        "Far below, and stretching away to the south, the lowlands"
      + " of Emerald stretch away into the distance.\n");
    add_item( ({ "river", "telberin river", "river telberin" }),
        "The River Telberin winds away to the south, a silvery"
      + " ribbon winding away into the lowlands to eventually"
      + " feed Lake Telberin at the edge of sight.\n");
    add_item( ({ "lake telberin", "telberin lake" }),
        "Lake Telberin is just barely visible at the edge of sight"
      + " far to the south, its waters glimmering in the distance.\n");
    add_item( ({ "telberin", "city", "great city" }),
        "Though you know it is there, the great city is simply too"
      + " distant to view from this vantage point.\n");
    add_item( ({ "corridor", "narrow corridor" }),
        "The pathway runs between two rises of rock ahead, narrowly"
      + " crowding together to form a corridor of sorts.\n");
    add_item( ({ "path", "pathway", "road" }),
        "The pathway travels to the north here, winding its way between"
      + " two rises of rock. To the west, it travels down out of the"
      + " mountains via switchbacks.\n");
    add_item( ({ "switchback", "switchbacks" }),
        "The switchbacks can be seen zigzagging their way down to"
      + " the lowlands west of here.\n");
    add_item( ({ "valley" }),
        "The valley to the north is not visible from here. It is"
      + " probable that the valley contains the Lake of Del Rimmon,"
      + " which empties its waters over the waterfall to the east.\n");

    add_cmd_item( ({ "cliff", "cliffs", "mountain", "mountains",
                     "rock", "rocks", "rise", "rises", "formation",
                     "formations", "rock formation", "rock formations",
                     "peak", "peaks", "melan rath" }),
                  ({ "climb" }),
        "Such feats are beyond your ability.\n");

    add_exit(DELRIMMON_DIR + "lakeside/pathway2", "north");
    add_exit(DELRIMMON_DIR + "trail/switchback4", "west", 0, 5, 0);

    set_no_exit_msg( ({ "east", "southeast", "south", "southwest" }),
        "A few short paces from the trail, you are halted by a"
      + " sheer dropoff.\n");
    set_no_exit_msg( ({ "northeast", "northwest" }),
        "Rock formations rise to block your movement in that"
      + " direction.\n");

    add_view();
} /* create_del_rimmon */
