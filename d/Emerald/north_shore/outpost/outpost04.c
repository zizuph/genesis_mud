/*
 *  /d/Emerald/north_shore/outpost/outpost04.c
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
    set_short("in the mess hall of the outpost");
    set_em_long("This room is rather crowded, filled with the tables"
      + " and chairs typical of a military mess hall. A few plates"
      + " and drinking vessels are littered around the room, and the"
      + " aroma of food lingers. A corridor leads west toward a"
      + " central chamber.\n");

    add_item( ({ "table", "tables" }),
        "The tables are oval in shape, and made of thick polished"
      + " wood. A few plates and cups have been left around.\n");
    add_item( ({ "plate", "plates", "cup", "cups", "vessel",
                 "vessels", "drinking vessels", 
                 "plates and cups", "plates and drinking vessels" }),
        "Plates and cups have been left around the room on the various"
      + " tables. Some look to have been used recently - others, less"
      + " recently.\n");
    add_item( ({ "chair", "chairs" }),
        "Chairs are gathered around each table. They look sturdy and"
      + " are solid wood.\n");
    add_item( ({ "central chamber", "chamber" }),
        "A central chamber is visible at the end of a short corridor"
      + " leading west out of this room.\n");
    add_item( ({ "hall", "mess hall", "military mess hall" }), long);

    add_indoor_items();

    add_exit("outpost02" , "west");
} /* create_outpost_inside_room */


/*
 * Function name:        do_sit
 * Description  :        allow the player to sit at the table
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_sit(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Sit where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [at] [in] [on] [upon] [the] 'table' / 'tables'"
      + " / 'chair' / 'chairs'"))
    {
        return 0; /* can't parse player syntax */
    }

    write("You sit down at one of the tables and relax a bit. These"
      + " chairs are quite well-made, and offer a comfortable moment"
      + " of repose. After a bit, you stand up again.\n");

    return 1;
} /* do_sit */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_sit, "sit");
} /* init */

