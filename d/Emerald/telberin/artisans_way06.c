/*
 *  /d/Emerald/telberin/artisans_way06.c
 *
 *  This section of Artisans Way houses the jewelery Store.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 *
 *  Note: I would have liked to have used the building code which
 *        is used throughout telberin for the jewelery store. However,
 *        due to the problem of dual inheritance, I've had to do it
 *        using my own add_actions here. (gorboth)
 */
#pragma strict_types
#include "defs.h"

inherit TELBERIN_ARTISANS_WAY;

/* prototypes */
public void        create_artisans_way();
public void        init();
public int         do_enter(string arg);


public void
create_artisans_way()
{
    set_em_long("The long stretch of Artisans Way makes a gentle arc"
      + " through the Mercantile Quarter of Telberin, passing countless"
      + " business offices, shops, and outdoor markets along its southern"
      + " edge. North, a sprawling green extends the entire length of"
      + " the quarter, from the western gates of the city to gates of the"
      + " towering royal palace at the city's center. Directly to the"
      + " south, a narrow, elegantly-framed building looks onto the"
      + " street, a fine oval plaque resting above its entrance.\n"); 

    add_item( ({ "green", "sprawling green" }),
        "The grass of the lawn is exquisitely green, adding a fresh"
      + " color for backdrop behind the business of the quarter.\n");
    add_item( ({ "building", "elegant building", "narrow building",
                 "elegantly-framed building",
                 "narrow, elegantly-framed building",
                 "narrow elegantly-framed building",
                 "jeweler", "jewelers", "store", "jewelers store",
                 "shop", "jewelers shop", "jeweler shop",
                 "jewelry shop", "gem shop", "south",
                 "jewel store", "jewelry store" }),
        "The building directly to the south is discernably more"
      + " elegant than those around it. It has a look of wealth and"
      + " affluance, having spared no expense in the exquisite detailing"
      + " of its exterior. A fine oval plaque rests above its"
      + " entrance.\n");
    add_item( ({ "plaque", "oval plaque", "sign", "fine plaque",
                 "fine oval plaque" }),
        "The plaque reads: 'Master Jeweler - Amshal Fendant.'"
      + " The elegant black letters have been artfully engraved"
      + " into polished alabaster which has been gracefully beveled"
      + " along its oval edges.\n");
    add_item( ({ "entrance", "door", "doors", "doorway" }),
        "The doors to the south are made of a rich dark wood which"
      + " has been coated in a fine oil finish.\n");
    add_item( ({ "office", "offices", "business", "businesses",
                 "business office", "business offices", "buildings" }),
        "Many of the buildings in this quarter have the look of"
      + " some form of business or another. You see suppliers travelling"
      + " to and fro, coming and going in their various deliveries to"
      + " the various establishments.\n");
    add_item( ({ "suppliers" }),
        "These people are everywhere, bringing their varied goods and"
      + " services to the businesses of the quarter.\n");
    add_item( ({ "market", "markets", "outdoor market",
                 "outdoor markets" }),
        "A number of merchants have set up outdoor markets to offer"
      + " their goods to the public. Their many colored awnings run"
      + " the length of the boulevard to the east and west.\n");
    add_item( ({ "awning", "awnings", "colored awning",
                 "colored awnings", "merchant", "merchants" }),
        "The awnings of the merchants add a distinct flavor to the"
      + " boulevard, their many colors waving in the occasional"
      + " breeze.\n");

    add_cmd_item( ({ "plaque", "oval plaque", "sign", "fine plaque",
                     "fine oval plaque", "letters", "words" }),
                  ({ "read" }),
        "The plaque reads: 'Master Jeweler - Amshal Fendant.'\n");

    add_exit("artisans_way07", "east");
    add_exit("artisans_way05", "west");
    add_exit("/d/Emerald/telberin/mercantile/jeweler_shop",
        "south", 0, 1, 1);

}


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_enter, "enter");
} /* init */


/*
 * Function name:        do_enter
 * Description  :        allow players to enter the jewelery store
 *                       in a way similar to that handled by the building
 *                       code in Telberin
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
//      notify_fail("Enter what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [narrow] [narrow,] [elegant] [elegantly]"
      + " [elegantly-framed] [framed] [jeweler] [jewelers]"
      + " [jewelery] [jewelry]"
      + " [gem] 'shop' / 'store' / 'building' / 'jewelers'"
      + " / 'jeweler' [shop] [store]"))
    {
        return 0; /* can't parse the player's syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'south' here, using"
          + " 'command.' Since you are a wizard, that won't work. Simply"
          + " go south yourself.\n");
        return 1;
    }

    this_player()->command("south");
    return 1;
} /* do_enter */
