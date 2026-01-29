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
    set_short("within the central chamber of the outpost complex");
    set_em_long("You stand within a very large octagonal room which"
      + " is at the heart of this complex. Each of the walls here"
      + " opens onto a passageway which leads to the various rooms"
      + " within the building. The floor here is paved with stone,"
      + " at the center of which, a large emblem has been carved"
      + " directly beneath a ladder which leads up through a hatch"
      + " in the ceiling.\n");

    add_item( ({ "octagonal room", "octagon", "large octagonal room",
                 "very large octagonal room" }), long);
    add_item( ({ "wall", "walls", "passage", "passageway",
                 "corridor", "corridors" }),
        "Each of the walls which frame this room opens onto a"
      + " corridor which runs toward the various rooms within the"
      + " complex.\n");
    add_item( ({ "stone", "floor", "ground", "down" }),
        "This room is paved with stone which has been carefully set"
      + " to form a sturdy floor. In the center of the room, an"
      + " emblem has been carved into the stone.\n");
    add_item( ({ "ladder", "wide ladder" }),
        "A wide ladder leads from the center of the floor up"
      + " through a hatch in the ceiling to a chamber above.\n");
    add_item( ({ "chamber above", "upper chamber", "hatch",
                 "hatch in the ceiling" }),
        "The hatch in the ceiling leads to some upper chamber,"
      + " which is not easily viewed from here.\n");
    add_item( ({ "ceiling", "up", "roof" }),
        "The ceiling of this room is interrupted by a hatch which"
      + " leads to some chamber above. A ladder leads through the"
      + " hatch.\n");

    add_indoor_items();

    add_exit("outpost09.c" , "north");
    add_exit("outpost03.c" , "northeast");
    add_exit("outpost04.c" , "east");
    add_exit("outpost05.c" , "southeast");
    add_exit("outpost01.c" , "south");
    add_exit("outpost06.c" , "southwest");
    add_exit("outpost07.c" , "west");
    add_exit("outpost08.c" , "northwest");
    add_exit("outpost10.c" , "up");

    reset_room();
} /* create_outpost_inside_room */


/*
 * Function name:        reset_room
 * Description  :        clone the emblem into the room
 */
public void
reset_room()
{
    object  emblem;

    if (!present("kot_emblem"))
    {
        emblem = clone_object(
            "/d/Emerald/blackwall/delrimmon/obj/normal_emblem");
        emblem->set_emblem(
            "The emblem is great in size, spanning a large portion of"
          + " the floor at the center of the room. It depicts the"
          + " symbol of Telberin - a four-pointed star within a"
          + " circular band.");
        emblem->move(this_object());
    }
} /* reset_room */


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
