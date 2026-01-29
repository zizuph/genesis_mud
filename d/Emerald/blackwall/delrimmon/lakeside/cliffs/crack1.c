/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/crack1.c
 *
 *  A narrow crawlspace which can be found near the edge of
 *  a ledge along the western slopes of the Blackwall Mountains.
 *
 *  Copyright (c) February 1999, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: December 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_del_rimmon();
public void    init();
public int     climb_tree(string arg);
public int     enter_hole(string arg);

/*
 * function name:        create_del_rimmon
 * descripiton  :        set up the room
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_cliffs");
    set_short("a narrow crawlspace set within the western cliff"
            + " faces of the Blackwall Mountains in Emerald");
    set_long(del_rimmon_long);

    set_extraline("Fragmented rock surrounds this crawlspace, set"
               + " within the western cliff faces of the Blackwall"
               + " Mountains. An opening to the east looks out over the lake"
               + " far beneath these heights. Above, the"
               + " space opens somewhat, traveling farther within"
               + " the side of the cliff.");

    add_item( ({ "opening", "opening to the east", "crack", "east",
                 "cliff" }), BSN(
        "To the east, an opening in the cliff looks out over the lake"
      + " which lies far below. A gnarled tree trunk grows at an odd"
      + " angle from a precipice a short distance away from the"
      + " opening."));
    add_item( ({ "tree", "gnarled tree", "tree trunk", "trunk",
                 "gnarled tree trunk", "gnarled trunk" }), BSN(
        "The tree trunk grows nearly sideways out from the edge"
      + " of a nearby precipice."));
    add_item( ({ "angle", "odd angle" }), BSN(
        "The angle at which the tree grows looks as if it might"
      + " serve as a good anchor if you wanted to try to climb"
      + " onto the precipice."));
    add_item( ({ "precipice", "nearby precipice", "edge" }), BSN(
        "A precipice extends from the side of the cliffs just a" 
      + " few feet from the opening to the east. A tree trunk"
      + " grows at an odd angle from its edge."));
    add_item( ({ "rock", "fragmented rock", "rocks",
                 "fragmented rocks" }), BSN(
        "The fragmented rocks which form the sides of this"
      + " crawlspace suggest that it was formed by violent forces"
      + " of nature, such as an earthquake."));
    add_item( ({ "sides", "crawlspace", "sides of this crawlspace",
                 "sides of the crawlspace" }), BSN(
        "This crawlspace makes its way in and upwards from the"
      + " side of the cliff to the east."));
    add_item( ({ "side of the cliff", "cliff side", "cliffside",
                 "western cliff face", "western cliff faces",
                 "western cliff", "western cliffs" }), BSN(
        "The sides of the cliff to the east travel a dizzying"
      + " distance downward towards the trees far below."));
    add_item( ({ "space", "above", "up", "upwards", "upward" }), BSN(
        "The crawlspace continues to make its way into the cliff"
      + " above, where a dark hole is visible."));
    add_item( ({ "hole", "dark hole" }), BSN(
        "The hole is extremely dark. It is impossible to tell from"
      + " here what might be beyond it."));

    add_lakeview();
    add_view();

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/outpost1", "up", 0, 4, 1);

    set_no_exit_msg( ({ "north", "northeast", "southeast", "south",
                        "southwest", "west", "northwest" }),
        "The walls of rock which surround you prevent any movement"
      + " in that direction.\n");
    set_no_exit_msg( ({ "east" }),
        "East lies a drop which would certainly prove fatal. You might"
      + " be able to climb back up to the precipice using the tree"
      + " to balance yourself, however.\n");
} /* create_del_rimmon */

/*
 * function name:        init
 * description  :        add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(climb_tree, "climb");
    add_action(enter_hole, "enter");
} /* init */

/*
 * function name:        climb_tree
 * description  :        let the player climb onto the precipice
 *                       using the tree trunk as an anchor
 * arguments    :        arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
climb_tree(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Where do you want to " + query_verb() + "?");
    }

    if (!parse_command(arg, ({}),
        "[up] [on] [onto] [the] 'tree' / 'trunk' / 'precipice'"))
    {
        return 0;
    }

    WRITE("You grasp the tree trunk, and swing yourself carefully"
        + " onto the precipice.");
    say(QCTNAME(TP) + " grasps the tree trunk, and swings "
        + TP->query_objective() + "self onto the precipice.\n");

    TP->move_living("M", DELRIMMON_DIR + "lakeside/cliffs/ledge11");
    say(QCTNAME(TP) + " arrives, grasping the trunk of the tree as "
      + TP->query_pronoun() + " climbs up over the side of the"
      + " precipice.\n");
    return 1;
} /* climb_tree */

/*
 * function name:    enter_hole
 * description  :    move the player up if they try to enter the
 *                   hole more verbosely
 * arguments    :    arg -- what the player typed
 * returns      :    1 -- success, 0 -- failure
 */
public int
enter_hole(string arg)
{
    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [dark] 'hole'"))
    {
        return 0;
    }

    if (TP->query_wiz_level())
    {
        WRITE("Normally, we would move the player 'up' here using"
            + " command(). Since you are a wiz, that won't work.");
    }

    TP->command("up");
    return 1;
} /* enter_hole */
