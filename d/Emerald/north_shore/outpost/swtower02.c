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
    set_short("within the southwestern guard tower of the outpost");
    set_em_long("Though badly damaged, this guard tower still"
      + " provides a commanding view of the area. To the south,"
      + " the waters of the lake dominate the horizon, glittering"
      + " with light. A path winds below the outpost to the west"
      + " where it connects this fortress to a dock along the"
      + " shore. The courtyard is visible below and to the north."
      + " All around and above to the north are the dark colors"
      + " of the forest and eventual heights of the Blackwall"
      + " Mountains.\n");

    add_item( ({ "guard tower", "tower", "southwestern tower",
                 "southwestern guard tower", "southwest tower",
                 "southwest guard tower" }), long);
    add_item( ({ "view", "commanding view", "area" }),
        "Only from a guard tower such as this would you find"
      + " such a complete view of the surrounding area.\n");  

    add_courtyard_view();
    add_outpost_items();
    add_lakeview();

    add_exit("swtower01", "down");
} /* create_outpost_outside_room */


/*
 * Function name:        init()
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(climb_down_ladder, "climb");
} /* init */
