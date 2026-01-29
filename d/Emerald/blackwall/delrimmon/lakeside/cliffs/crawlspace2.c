/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/crawlspace2.c
 *
 *  This is a very deep corner of a crack in the high cliff walls
 *  of the western slopes of the Blackwall Mountains bordering Del Rimmon
 *  in the Gondor lands. A natural vent here leads to a nasty
 *  and damaging fall for the curious (or hapless) adventurer.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define    VENT_PROP        ("em_i_found_vent")
#define    WARNING_PROP     ("em_i_vent_warning")

/* prototypes */
public void    create_del_rimmon();
public int     do_crawl(string arg);
public void    init();
public string  exa_vent();
public string  exa_shadows();
public int     enter_vent(string arg);

public void    do_log(object ob, string logtxt);

/*
 * function name:        create_del_rimmon();
 * description  :        set up the room with domain presets
 */
public void
create_del_rimmon()
{
    set_short("a tight crawlspace deep within the recesses of a rock"
            + " wall");
    set_long(BSN(
        "The rock walls of this crawlspace narrow to the point"
      + " where it seems impossible to continue any farther. Shadows"
      + " are all that can pass deeper into the recesses"
      + " ahead."));

    add_item( ({ "shadow", "shadows", "cracks", "crannies",
                 "crack", "crannie", "cracks and crannies" }),
                 exa_shadows);
    add_item( ({ "vent", "hole", "dark vent", "corner",
                 "dark corner", "recess", "recesses",
                 "shadowy recess", "shadowy recesses",
                 "natural vent" }), exa_vent);
    add_item( ({ "rock", "rocks", "rock wall", "rock walls",
                 "wall", "walls" }), BSN(
        "The rock walls narrow to the point of making further"
      + " progress an impossibility here."));
    add_item( ({ "here", "crawlspace", "space", "area" }), BSN(
        "This crawlspace seems to be the result of some violent form"
      + " of seizmic activity in the region. It narrows dramatically"
      + " ahead."));
    add_item( ({ "recess", "recesses", "ahead", "forward" }), BSN(
        "The walls of the crawlspace narrow so dramatically that"
      + " it is impossible to crawl forward any farther here. Shadows"
      + " are all that are visible."));
    add_item( ({ "ground", "floor", "down" }), BSN(
        "The crawlspace is unlevel, so there is no ground or floor"
      + " here to speak of - only the walls of rock which surround"
      + " you."));
    add_item( ({ "roof", "ceiling", "up" }), BSN(
        "The roof of the crawlspace is just a few inches above"
      + " your head here."));
    add_item( ({ "sky", "sun", "moon" }), BSN(
        "The sky is not visible from this dark hole."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_S_DARK_LONG, "A tight, dark crawlspace.\n");

    add_prop(ROOM_M_NO_ATTACK,
        "There is not enough room to attempt such a feat in here.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,
        "There is not enough room to attempt such a feat in here.\n");

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest", "west", "northwest",
                        "up", "down" }), BSN(
        "It seems that the only way you can move is to crawl"
      + " backwards."));
} /* create_del_rimmon */


/*
 * function name:        do_crawl
 * description  :        allow the player to crawl around
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
do_crawl(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Crawl where?");
    }

    if (!parse_command(arg, ({}),
        "'back' / 'backward' / 'backwards' [the] [way] [i] [I]"
      + " [came]"))
    {
        NFN0("It seems as if you can only crawl backwards from here.");
    }

    WRITE("Struggling awkwardly, you crawl backwards along the"
        + " rock.");
    say("Struggling awkwardly, " + QCTNAME(TP) + " crawls backwards"
      + " along the rock, moving out of sight.\n");

    TP->move_living("M", DELRIMMON_DIR + "lakeside/cliffs/crawlspace1", 1);
    say(QCTNAME(TP) + " arrives, awkwardly struggling backward"
                    + " through the crawlspace.\n");
    return 1;
} /* do_crawl */


/*
 * function name:        init
 * description  :        add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(do_crawl, "crawl");
    add_action(do_crawl, "move");
    add_action(enter_vent, "enter");
    add_action(enter_vent, "slide");
} /* init */


/*
 * function name:        exa_vent
 * description  :        you have to know where the vent is before you
 *                       can examine it, so we don't let people see it
 *                       unless they have found its location
 * returns      :        string -- the chute description
 */
public string
exa_vent()
{
    if (TP->query_prop(VENT_PROP))
    {
        return BSN("A natural vent of some sort opens in the shadowy"
                 + " recesses of the crawlspace just ahead.");
    }

    return BSN("You find no " + Exa_arg + ".");
} /* exa_chute */


/*
 * function name:        exa_shadows
 * description  :        if a player examines the shadows, they might
 *                       notice a vent going down. If they do, then
 *                       we add a prop.
 * returns      :        string -- the shadows description
 */
public string
exa_shadows()
{
    string  shadow_txt = "Ahead the shadows are impenetrably deep"
                       + " where they fill the smallest cracks and"
                       + " crannies of the fragmented rock walls. ";

    if (TP->query_skill(SS_AWARENESS) > 25)
    {
        shadow_txt += "You notice what appears to be some sort of"
                    + " dark vent leading downward within a dark"
                    + " corner of the crawlspace.";

        if (!TP->query_prop(VENT_PROP))
        {
            TP->add_prop(VENT_PROP, 1);
        }
    }

    return BSN(shadow_txt);
} /* exa_shadows */


/*
 * function name:        enter_vent
 * description  :        allow the player to try to enter the vent
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
enter_vent(string arg)
{
    int     falldamage;

    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (!parse_command(arg, ({}),
        "[into] [down] [the] 'vent' / 'hole' / 'opening'"))
    {
        return 0;
    }

    if (!TP->query_prop(VENT_PROP))
    {
        return 0;
    }

    if (!TP->query_prop(WARNING_PROP))
    {
        WRITE("As you approach the vent, you notice that it drops nearly"
      + " vertically downward, with no real handholds. You guess"
      + " that there is a good chance you might get hurt if you"
      + " try it, and hesitate.");

        TP->add_prop(WARNING_PROP, 1);
        return 1;
    }

    write("You find that the only way down the vent is head first,"
        + " and so you carefully ... whoops!\n\n"
        + "You find yourself falling out of control down a slippery"
        + " chute. Suddenly, you are falling through open air to land"
        + " painfully on your neck and shoulders!\n");
    say(QCTNAME(TP) + " crawls over to a dark corner of the"
      + " crawlspace ahead, yells suddenly and then disappears.\n");

    tell_room(DELRIMMON_DIR + "lakeside/caves/large_room",
              "A scream sounds out suddenly from above, only to"
            + " be followed by a body which falls to land at the"
            + " base of the southern niche with a sickening crunch.\n");

    TP->move_living("M", DELRIMMON_DIR + "lakeside/caves/large_room",
                    1, 1);

    falldamage = 600 + (random(TP->query_encumberance_weight() *5));
    TP->reduce_hit_point(falldamage);
    do_log(TP, " fell down vent.  Damage: " + falldamage);

/*
 * I think we'll have this be non-lethal for now. I simply detest
 * death-traps. (Gorboth)
 */
//  if (TP->query_hp() <= 0)
//  {
//      TP->do_die(TO);
//      do_log(TP, " DIED FROM FALLING DOWN THE VENT");

//  }
    return 1;
} /* enter_vent */


/*
 * function name:        do_log
 * description  :        helps us log unpleasantries that happen
 *                       players here
 * arguments    :        object ob -- the player
 *                       string logtxt -- what happened
 */
public void
do_log(object ob, string logtxt)
{
    log_file(LOG_FILE + "cliff_vent", ctime(time())
           + " -- " + ob->query_name() + " ("
           + ob->query_average_stat() + ")"
           + logtxt + ".\n");

    return;
} /* do_log */
