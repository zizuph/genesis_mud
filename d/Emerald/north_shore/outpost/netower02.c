/*
 *  /d/Emerald/north_shore/outpost/netower02.c
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
    set_short("within the burned out remains of a guard tower");
    set_em_long("Charred and ruined timbers surround you as you"
      + " stand in open air within what was once a sturdy guard"
      + " tower. This shell of a chamber is now little more than"
      + " a burned out landing which, though utterly indefensible,"
      + " yet provides a commanding view of the area.\n");

    add_item( ({ "guard tower", "tower", "northeastern tower",
                 "northeastern guard tower", "northeast tower",
                 "northeast guard tower", "shell", "ruined tower",
                 "destroyed tower" }), long);
    add_item( ({ "view", "commanding view", "area" }),
        "Only from a guard tower such as this would you find"
      + " such a complete view of the surrounding area.\n");  
    add_item( ({ "timbers", "timber", "charred timber",
                 "charred timbers", "ruined timber",
                 "ruined timbers", "charred and ruined timber",
                 "charred and ruined timbers" }),
        "This tower has been utterly devastated by fire. It seems"
      + " as if the few guards who struggle to maintain this"
      + " fort have given it up as a total loss.\n");

    add_courtyard_view();
    add_outpost_items();
    add_lakeview();

    add_exit("netower01", "down");
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
