/*
 *  /d/Emerald/north_shore/outpost/outpost02.c
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
inherit OUTPOST_INSIDE_ROOM;


/*
 * Function name:    create_outpost_inside_room
 * Description  :    set up the room with annoying noises
 */
public void
create_outpost_inside_room()
{
    set_short("in the sleeping quarters of the outpost");
    set_em_long("This room appears to be designated as sleeping"
      + " quarters for the guards of the outpost. There are a number"
      + " of shabby cots around the room, and the air is thick with"
      + " the musk of unbathed bodies. A corridor leads southeast"
      + " toward a larger chamber.\n");

    add_item( ({ "cot", "cots", "bed", "beds", "matress",
                 "mattresses", "straw", "shabby cot",
                 "shabby cots" }),
        "A few of the cots are furnished with crude matresses which"
      + " look to be little other than straw which has been shoved"
      + " into a bundle of fabric. Otherwise, they look completely"
      + " uncomfortable.\n");
    add_item( ({ "larger chamber", "large chamber" }),
        "A larger chamber is visible at the far end of a corridor"
      + " which leads to the southeast.\n");

    add_cmd_item( ({ "cot", "cots", "bed", "beds",
                     "on cot", "on cots", "on bed", "on beds",
                     "in cot", "in cots", "in bed", "in beds" }),
                  ({ "sleep", "rest", "lie" }),
        "You lie down upon one of the cots, but immediately decide"
      + " that it is too uncomfortable to achieve any meaningful rest."
      + " You rise back to your feet and stretch out your back.\n");

    add_indoor_items();

    add_exit("outpost02" , "southeast");
} /* create_outpost_inside_room */
