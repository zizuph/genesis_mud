/*
 *  /d/Emerald/north_shore/outpost/gate03.c
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
    set_short("Inside the northern gates of a large outpost");
    set_em_long("Here, within the northern gate of the outpost,"
      + " a courtyard spreads out beneath the dark forms of"
      + " the walls which form the outer defences. Access to"
      + " the two northern guard towers can be found via ladders"
      + " which are visible a short distance to the east and"
      + " west along the wall. Just to the south, the central"
      + " complex of the outpost overlooks the yard.\n");

    add_courtyard_view();
    add_outpost_items();
    add_cant_see_items();

    add_exit("gate04", "north", 0, 1, 1);
    add_exit("netower01","east");
    add_exit("nwtower01","west");
    add_exit("outpost09","south");
    add_exit("gate04", "out");
} /* create_outpost_outside_room */
