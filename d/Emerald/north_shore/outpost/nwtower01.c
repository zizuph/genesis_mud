/*
 *  /d/Emerald/north_shore/outpost/nwtower01.c
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
    set_short("beneath the northwestern tower of the outpost");
    set_em_long("A great deal of damage has been done to this"
      + " northwestern corner of the courtyard, where a guard tower"
      + " rises above the walls which frame the outpost. To the"
      + " south, another guard tower is visible. East of here are"
      + " the northern gates of the outpost. A ladder is set in"
      + " the ground beneath the tower.\n");

    add_item( ({ "ladder", "narrow ladder" }),
        "The ladder is narrow and made of wood. It rises up to"
      + " grant access to the guard tower above.\n");

    add_courtyard_view();
    add_outpost_items();
    add_cant_see_items();

    add_exit("gate03", "east");
    add_exit("nwtower02", "up");
    add_exit("swtower01", "south");
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
