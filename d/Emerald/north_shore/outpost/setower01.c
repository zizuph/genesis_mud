/*
 *  /d/Emerald/north_shore/outpost/setower01.c
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
    set_short("beneath the southeastern tower of the outpost");
    set_em_long("Above you here, a guard tower rises to overlook the wall"
      + " of this southeastern corner of the outpost. A narrow"
      + " ladder is set in the ground leading up to an opening"
      + " in the base of the tower. To the north, a ruined tower"
      + " barely rises over the wall. West of here are the southern"
      + " gates of the outpost.\n");

    add_item( ({ "ladder", "narrow ladder" }),
        "A ladder travels up into the guard tower above.\n");

    add_courtyard_view();
    add_outpost_items();
    add_cant_see_items();

    add_exit("netower01", "north");
    add_exit("gate02","west");
    add_exit("setower02","up");
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

