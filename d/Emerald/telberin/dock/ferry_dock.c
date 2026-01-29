/*
 *  /d/Emerald/telberin/dock/ferry_dock.c
 *
 *  This is the dock where one can catch the ferry to the
 *  north shore of Lake Telberin from the city.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 *
 *  Revision history: Aug 2021 - Added fishing (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#undef CHAPEL_CHARRIAGE

/* prototypes */
public void        create_emerald_room();
public void        reset_room();
public string      read_sign();
public void        init();
public int         do_dive(string arg);


/* global variables */
static object      Ship;

#ifdef CHAPEL_CARRIAGE
static object carriage;
#endif

/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("a wide pier before the walls of Telberin");
    set_em_long("A wide pier extends from the main docks of Telberin"
      + " which are visible just to the south. Numerous crates"
      + " and barrels line the edge of the planks here, which hang"
      + " over the fresh and bobbing waters of Lake Telberin. A"
      + " small sign has been fastened to one of the wooden"
      + " pillars which supports the pier.\n");

    add_item( ({ "island", "telberin island" }),
        "The island which the city is build upon is hard and rocky,"
      + " offering few sandy beaches, but excellent fortification.\n");
    add_item( ({ "pier", "wide pier" }),
        "This pier is not very long, but looks wide enough to"
      + " accomodate large numbers of people and cargo passing"
      + " along its stretch.\n");
    add_item( ({ "telberin", "city", "city of telberin" }),
        "The city of Telberin rises south of these docks, taking"
      + " up most of the landmass that this island provides. Its"
      + " nearest walls rise above the docks to the south.\n");
    add_item( ({ "wall", "walls", "walls of the city", "city walls",
                 "nearest wall", "nearest walls", "city wall",
                 "wall of the city" }),
        "The walls of the city are visible rising above the docks"
      + " to the south. Every so often, a guard is visible walking"
      + " along the battlements.\n");
    add_item( ({ "guard", "guards", "battlements", "battlement" }),
        "Guards patrol the city walls constantly, peering out to"
      + " be sure that no invaders are in sight.\n");
    add_item( ({ "dock", "docks", "south", "docks of telberin",
                 "telberin docks", "main dock", "main docks",
                 "main docks of telberin" }),
        "This pier runs out from the main docks of Telberin, which"
      + " are visible to the south. From there, many larger ships"
      + " come and go bringing visitors from far lands.\n");
    add_item( ({ "plank", "planks", "edge", "edge of the planks" }),
        "The planks of this peer are warped and water-worn. They are"
      + " crowded with numerous barrels and crates.\n");
    add_item( ({ "crates", "barrels", "crate", "barrel",
                 "crates and barrels", "barrels and crates", "cargo" }),
        "This looks to be cargo either waiting to be loaded onto the"
      + " ferry, or waiting to be taken back into the city.\n");
    add_item( ({ "lake", "water", "waves", "water of the lake",
                 "lake telberin", "telberin lake", "clear waters",
                 "waters", "bobbing waters", "fresh waters",
                 "bobbing water", "fresh water",
                 "fresh and bobbing water",
                 "fresh and bobbing waters" }),
        "Lake Telberin surrounds this island for many miles. Its"
      + " clear waters bob and splash around this pier, relaxing"
      + " the mind with their constant din.\n");
    add_item( ({ "shore", "north shore", "distant shore" }),
        "Far in the distance the north shore of the lake is visible,"
      + " nestled beneath the dark forms of the Blackwall Mountains.\n");
    add_item( ({ "mountains", "blackwall mountains", "mountain" }),
        "The Blackwall Mountains rise far to the north,"
      + " looming above the distant shore like a dark and brooding"
      + " storm.\n");
    add_item( ({ "sky", "up" }),
        "The sky is clear and bright, sending blue down upon blue"
      + " here before the vibrant color of the lake.\n");    
    add_item( ({ "sign", "small sign" }), read_sign);

    add_cmd_item( ({ "sign", "small sign" }),
                  ({ "read" }), read_sign);

    add_exit("telberin_dock", "south");

    set_no_exit_msg( ({ "southwest", "west", "northwest", "north",
                        "northeast", "east", "southeast" }),
        "You pause at the edge of the dock and peer into the water."
      + " Using your better judgement, you return to the center"
      + " of the pier.\n");

    add_prop("_live_i_can_fish", "freshwater");
    add_prop(ROOM_I_NO_CLEANUP, 1); /* must not be unloaded */
    add_prop(ROOM_I_LIGHT, 9);

    reset_room();
} /* create_emerald_room */


/*
 * Function name:        reset_room
 * Description  :        load the ship and start 'er up.
 */
public void
reset_room()
{
#ifdef CHAPEL_CARRIAGE
    if (!carriage)
    {
        setuid();
        seteuid(getuid());
        carriage = clone_object("/d/Emerald/telberin/mainland/chapel_carriage/carriage");
        carriage->start_carriage();
    }
#endif

    if (objectp(Ship))
    {
        return;
    }

    Ship = clone_object("/d/Emerald/telberin/dock/ferry");
    Ship->start_ship();
} /* reset_room */

#ifdef CHAPEL_CARRIAGE
public int
query_carriage_stop(object carriage)
{
    return 1;
}
#endif

/*
 * Function name:        read sign
 * Description  :        show the sign, in fun text graphics
 * Returns      :        string - the sign text
 */
public string
read_sign()
{
    string desc;

    desc = "\n\n"
     + "          _____________________________\n"
     + "        .'                             `.\n"
     + "        |   Ferry to the North Shore    |\n"
     + "        |       Price: 10 copper        |\n"
     + "        |                               |\n"
     + "        |    The Wedding Carriage is    |\n"
     + "        | undergoing repairs and should |\n"
     + "        |   be back in service soon.    |\n"
     + "        `._____________________________.'\n\n";

    return desc;
} /* read_sign */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_dive, "swim");
    add_action(do_dive, "dive");
} /* init */


/*
 * Function name:        do_dive
 * Description  :        allow the player to try to dive off the pier,
 *                       but inform him/her that that won't be possible
 * Arguments    :        string arg - what the player typed
 * Return       :        int 1 - success, 0 - failure
 */
public int
do_dive(string arg)
{
    string  swim_room;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[off] [in] [to] [into] [across] [the] 'lake' / 'water' / 'pier'"))
    {
        return 0; /* couldn't parse the player syntax */
    }

    swim_room = "/d/Emerald/north_shore/dock";

    if (this_player()->query_skill(SS_SWIM) < 50)
    {
        notify_fail("Peering into the often turbulent waters of"
          + " Lake Telberin, you feel sure you lack the necessary"
          + " skill to traverse the waters on your own.\n");
        return 0;
    }

    if (this_player()->query_fatigue() < 30)
    {
        notify_fail("You are too tired to try that right now.\n");
        return 0;
    }

    this_player()->add_fatigue(-50);
    this_player()->reveal_me();
    this_player()->catch_tell("You dive off the pier and swim"
      + " with powerful strokes across the water. Reaching the"
      + " north shore of the lake, you climb out of the"
      + " water to stand dripping on the dock.\n");
    tell_room(swim_room, QCTNAME(this_player()) + " suddenly"
      + " appears in the distance to the south, swimming across"
      + " the lake with powerful strokes. Presently, "
      + this_player()->query_pronoun() + " reaches the dock and"
      + " clambers up over the side to stand dripping beside"
      + " you.\n");
    this_player()->move_living("M", swim_room, 1, 0);
    tell_room(this_object(), QCTNAME(this_player()) + " dives off"
      + " the pier and swims with powerful strokes toward the"
      + " north shore. " + capitalize(this_player()->query_pronoun())
      + " soon disappears into the distance and is lost from"
      + " sight.\n");

    return 1;
} /* do_dive */

