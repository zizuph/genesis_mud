/*
 *  /d/Emerald/north_shore/outpost/netower01.c
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
    set_short("beneath the northeastern tower of the outpost");
    set_em_long("This corner of the outpost has almost certainly"
      + " taken the most severe damage from the recent raids."
      + " The walls have been charred black by fire, and where"
      + " once a guard tower stood, above you is a loose"
      + " collection of charred and ruined timbers. A ladder"
      + " still stands here, itself rather black, leading"
      + " up into the ruined tower.\n");

    add_item( ({ "ladder", "narrow ladder" }),
        "This ladder has tasted fire recently. Its wood is still"
      + " servicable for climbing, but no amount of sanding will"
      + " ever be able to remove the blackened sheen it now"
      + " carries.\n");

    add_courtyard_view();
    add_outpost_items();
    add_cant_see_items();

    add_exit("gate03", "west");
    add_exit("netower02", "up");
    add_exit("setower01", "south");
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
