/*
 * /d/Emerald/blackwall/delrimmon/cliff_room.c
 *
 *  Rooms which run below the cliffs of the Blackwall Mountains inherit this
 *  file. Support for attempting to climb cliffs is included.
 *
 *  Copyright (c) April 1998, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/legacy/delay_room";

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_cliff_room();
public void    create_del_rimmon();
public int     em_climbing_hook(string str);


/*
 * Function name: create_cliff_room
 * Description  : Inheriting rooms should use this in place of
 *                create_room
 */
public void
create_cliff_room()
{
} /* create_cliff_room */


/*
 * Function name: create_del_rimmon
 * Description  : allows us to create a room
 */
public void
create_del_rimmon()
{
    create_cliff_room();

    set_short(del_rimmon_short);
    set_long(del_rimmon_long);

    add_view();
} /* create_del_rimmon */


/*
 * Function name: em_climbing_hook
 * Description  : Support for the verb 'climb' which players are likely
 *                to attempt in these rooms. Redefine this function to
 *                allow climbing in any of the inheriting rooms.
 * Arguments    : string str - what the player typed after 'climb'
 * Returns      : 0 ( we don't let them climb in most rooms )
 */
public int
em_climbing_hook(string str)
{
    if (!strlen(str))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        "[up] [down] [the] 'cliff' / 'cliffs'"))
    {
        return 0; /* can't parse it */
    }

    if (parse_command(str, ({}),
        "[up] [the] 'tree' / 'trees'"))
    {
        notify_fail("The trees do not grow near enough to these cliffs"
          + " for you to reach them. You'd have to travel a bit to the"
          + " east.\n");
        return 0;
    }

    notify_fail("The cliffs here look far too perilous to attempt"
      + " any climbing.\n");
    return 0;
} /* em_climbing_hook */
