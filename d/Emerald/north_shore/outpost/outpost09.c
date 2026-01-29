/*
 *  /d/Emerald/north_shore/outpost/outpost09.c
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
    set_short("within the north entrance of the outpost complex");
    set_em_long("Standing within the northern entrance to this central"
      + " complex within the outpost, it is evident that this building"
      + " has not yet been breached by the raids which have ravaged"
      + " the rest of the fortress. This corridor runs to the south,"
      + " where it appears to open onto a much larger chamber. The"
      + " walls here are lined with racks which at one time probably"
      + " held weapons. Great steel doors stand open on the doorway"
      + " to the south which leads out into the courtyard.\n");

    add_item( ({ "chamber", "larger chamber", "much larger chamber",
                 "large chamber", "central chamber", "central room" }),
        "The large chamber visible at the end of the corridor appears"
      + " to be at the heart of the complex. Little is visible from"
      + " here.\n");
    add_item( ({ "rack", "racks", "weapon rack", "weapon racks" }),
        "As is common in such outposts, weapon racks have been"
      + " placed at the entrance to this complex to allow any"
      + " soldiers garrisoned within to grab them on their way into"
      + " the courtard to man their stations. They currently stand"
      + " empty.\n");
    add_item( ({ "door", "doors", "steel door", "steel doors",
                 "great door", "great doors", "great steel door",
                 "great steel doors" }),
        "Great steel doors stand open at this entrance to the"
      + " building. It appears as if these doors have held fast in"
      + " the recent calamities which have all but ruined this once"
      + " formidable outpost. It is likely that these have been all"
      + " that has stood between the destruction in the courtyard"
      + " and the undisturbed innards of the complex.\n");

    add_indoor_items();

    add_exit("gate03" , "north");
    add_exit("outpost02" , "south");
} /* create_outpost_inside_room */
