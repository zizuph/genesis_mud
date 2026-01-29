/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/crawlspace1.c
 *
 *  This is a crawlspace deep within the recesses of a crack in the
 *  rock walls, high above the lake of Del Rimmon in the western
 *  slopes of the Blackwall Mountains. One can crawl around a bit.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_del_rimmon();
public void    crawl(string where, object tp);
public int     do_crawl(string arg);
public void    init();



/*
 * function name:        create_del_rimmon
 * description  :        set up the room
 */
public void
create_del_rimmon()
{
    set_short("a tight crawlspace surrounded by jagged rock");
    set_long(BSN("Jagged rock walls close in on all sides of this"
           + " tight crawlspace. There is hardly enough room in"
           + " here to breathe, let alone stand up. It looks as"
           + " if it might be possible to crawl forward, or through"
           + " a hole to the north."));

    add_item( ({ "rock", "rock wall", "rock walls", "jagged rock",
                 "jagged rock wall", "jagged rock walls",
                 "rocks", "wall", "walls" }), BSN(
        "The rock has separated here, forming a crawlspace in which"
      + " you are barely able to maneuver."));
    add_item( ({ "here", "crawlspace", "space",
                 "tight crawlspace" }), BSN(
        "This crawlspace seems to have been formed by some violent"
      + " activity in the area which separated the rock walls from"
      + " one another. An opening to the north seems to move into"
      + " a larger chamber, while one might crawl forward to move"
      + " farther into the crawlspace."));
    add_item( ({ "opening", "north", "chamber", "large chamber",
                 "larger chamber", "hole" }), BSN(
        "To the north, an opening leads to what appears to be a much"
      + " larger chamber."));
    add_item( ({ "forward", "depths", "depth" }), BSN(
        "The crawlspace continues into unknown depths, as one"
      + " crawls forward from here."));
    add_item( ({ "sky", "sun", "moon", "stars" }), BSN(
        "The sky is quite impossible to view from here."));
    add_item( ({ "ground", "floor" }), BSN(
        "There is really no ground here to speak of. Rather, the"
      + " rock walls are all about you, above and below, forming"
      + " the confines of this crawlspace."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_DARK_LONG, "A tight, dark crawlspace.\n");

    add_prop(ROOM_M_NO_ATTACK,
        "There is not enough room to attempt such a feat in here.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,
        "There is not enough room to attempt such a feat in here.\n");


    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest", "west", "northwest" }),
        "There is no real way to move in this tight space, except"
      + " perhaps by crawling. You could also go back through"
      + " the hole to the north.\n");
} /* create_del_rimmon */


/*
 * function name:        crawl
 * descrption   :        provide a message about where the player
 *                       is crawling, and move them there
 * arguments    :        string where -- which way did they go?
 *                       object tp    -- the player object
 */
public void
crawl(string where, object tp)
{
    if (where == "north")
    {
        WRITE("With some difficulty, you crawl through the opening"
            + " to the north.");
        say("With some difficulty, " + QCTNAME(TP) + " crawls through"
          + " an opening to the north.\n");

        tp->move_living("M", DELRIMMON_DIR + "lakeside/cliffs/plateau_crack",
                        1);
        say(QCTNAME(TP) + " arrives from the south, crawling through"
                        + " an opening in the rock.\n");
        return;
    }

    WRITE("With some difficulty, you crawl forward, farther into the"
        + " depths of the crawlspace.");
    say("With some difficulty, " + QCTNAME(TP) + " crawls forward,"
      + " farther into the depths of the crawlspace.\n");

    tp->move_living("M", DELRIMMON_DIR + "lakeside/cliffs/crawlspace2", 1);
    say(QCTNAME(TP) + " arrives, crawling awkwardly along the"
                    + " crawlspace.\n");
    return;
} /* crawl_message */


/*
 * function name:        do_crawl
 * description  :        allow the player to crawl in different
 *                       directions here
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
do_crawl(string arg)
{
    string *dir = ({ "hole", "opening", "north", "forward" });

    if (!strlen(arg))
    {
        NFN0("Crawl where?");
    }

    if (!parse_command(arg, ({}),
        "[through] [the] %p [to] [the] [north]", dir))
    {
        NFN0("You cannot " + QVB + " there.");
    }

    if (dir[0] == "hole" || dir[0] == "opening" || dir[0] == "north")
    {
        crawl("north", TP);
        return 1;
    }

    crawl("forward", TP);
    return 1;
} /* do_crawl */


/*
 * function name:        init
 * description  :        add some actions for the player
 */
public void
init()
{
    ::init();

    add_action(do_crawl, "crawl");
    add_action(do_crawl, "enter");
} /* init */
