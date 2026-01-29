/*
 *  /d/Emerald/north_shore/outpost/outpost05.c
 *
 *  This area was originally created by Mhyrkhaan in November of
 *  1998 and then put on hold. That wizard has since left the
 *  Emerald domain, and so I have decided to put his work to some
 *  use as a small killing area to give some small satisfaction
 *  to players who value that sort of thing. The descriptions
 *  and items have been updated by Gorboth.
 *
 *  Update August 2003 (Gorboth)
 */
#pragma strict_types

#include "defs.h"
inherit OUTPOST_OUTSIDE_ROOM;


/* prototypes */
public int         check_exit();


/*
 * Function name:    create_outpost_outside_room
 * Description  :    set up the room with annoying noises
 */
public void
create_outpost_outside_room()
{
    set_short("a large open room above the outpost complex");
    set_em_long("Though indoors, the four large open windows of"
      + " this chamber offer as good a view as any of the"
      + " four guard towers which rise from the corners of the"
      + " fortress. A large desk sits just in front of the"
      + " ladder which rises out of the hatch in the floor. It"
      + " appears as if hasty changes have been made to this"
      + " place. Tables have been overturned before the windows,"
      + " and many unspent arrows litter the floor where archers"
      + " might once have knelt. Stains of blood are upon the"
      + " floor.\n");

    add_name("_north_shore_outpost_hq");


    add_item( ({ "room", "chamber", "hall", "here" }), long);
    add_item( ({ "window", "windows", "large window",
                 "large windows", "four windows",
                 "large open window", "large open windows" }),
        "The windows overlook the grounds, facing north, south,"
      + " east, and west. They command a view not unlike those"
      + " of the guard towers, and give the commanders of this"
      + " outpost a central base of operations to conduct defences.\n");
    add_item( ({ "desk", "large desk", "paper", "papers",
                 "letter", "letters", "scroll", "scrolls",
                 "map", "maps", "report", "reports",
                 "document", "documents" }),
        "The desk is littered with letters, scrolls, and maps of"
      + " all sorts. A few of the documents have been sealed and"
      + " look rather official.\n");
    add_item( ({ "table", "tables" }),
        "The tables which are overturned in front of the"
      + " windows have many black arrows stuck in their outward-"
      + "facing surfaces. They appear to have been used as cover"
      + " for archers in some recent defence of the outpost.\n");
    add_item( ({ "arrow", "arrows" }),
        "Unspent arrows litter the ground beside the overturned"
      + " tables. Black arrows have pierced the tables themselves.\n");
    add_item( ({ "black arrow", "black arrows" }),
        "These arrows have a cruel look. They have obviously been"
      + " shot through the windows from the courtyard, where it"
      + " seems there has been a recent raid on the outpost.\n");
    add_item( ({ "floor", "ground", "down", "stain", "stains",
                 "blood", "blood stains", "stains of blood" }),
        "Dark stains of blood mark the floor which is littered"
      + " with unspent arrows. The top of a ladder protrudes"
      + " from a hatch in the center of the floor.\n");
    add_item( ({ "unspent arrows" }),
        "These arrows were perhaps used by archers who knelt"
      + " behind the upturned tables in the defence of this outpost."
      + " It seems clear that at some point they were no longer"
      + " needed, as a number remain unfired.\n");
    add_item( ({ "ladder", "wide ladder", "hatch", "top of a ladder",
                 "hatch in the floor" }),
        "A wide ladder protrudes from a hatch in the floor which"
      + " leads down to a room below this one.\n");

    add_courtyard_view();
    add_outpost_items();
    add_lakeview();

    add_exit("outpost02", "down", check_exit, 0, 1);
} /* create_outpost_outside_room */


/*
 * Function name:        check_exit
 * Description  :        Only allow players to use the ladder
 * Returns      :        0 - allow the passage, 1 - don't allow
 */
public int
check_exit()
{
    if (interactive(this_player()))
    {
        return 0;
    }

    return 1;
} /* check_exit */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_down_ladder, "climb");
} /* init */


/*
 * Function name:        captain_escape
 * Description  :        show the players what the captain does
 *                       after he escapes
 */
public void
captain_escape()
{
    tell_room(this_object(),
        "From below, you see the captain sprint out of the southern"
      + " gates, limping as he runs. He pauses only briefly to peer"
      + " hatefully up at this tower before heading down the path"
      + " toward the docks where he catches the ferry back to"
      + " Telberin.\n");

    return;
} /* captain_escape */


/*
 * Function name:        trigger_escape
 * Description  :        do the captain escape, with a delay
 */
public void
trigger_escape()
{
    set_alarm(5.0, 0.0, captain_escape);
    return;
} /* trigger_escape */
