/*
 *  /d/Emerald/north_shore/outpost/swtower02.c
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


/*
 * Function name:    create_outpost_outside_room
 * Description  :    set up the room with annoying noises
 */
public void
create_outpost_outside_room()
{
    set_short("beneath the soutwestern tower of the outpost.");
    set_em_long("A guard tower looms above you here, standing tall"
      + " above this southwestern corner of the walls which border"
      + " the courtyard of this outpost. East lie the southern"
      + " gates of the fortress. To the north, another guard tower"
      + " stands above the wall. A ladder is set in the ground"
      + " here.\n");

    add_item( ({ "ladder", "narrow ladder" }),
        "A narrow ladder provides access to the outpost above.\n");

    add_cant_see_items();
    add_outpost_items();
    add_courtyard_view();

    add_exit("nwtower01", "north");
    add_exit("gate02", "east");
    add_exit("swtower02", "up");
} /* create_outpost_outside_room */


/*
 * Function name:        init()
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_up_ladder, "climb");
} /* init */
