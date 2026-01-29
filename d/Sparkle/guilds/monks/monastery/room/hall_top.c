/*******************************************************************\
| HALL_TOP.C                                                        |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/03/29 Arandir     Polished up
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("central hall");
  set_long  ("Hanging from the four corners of this " +
             "square hall are wrought iron lamps whose " +
             "flickering fires cast about a warm glow. Running " +
             "along the top of the walls are four wide, red glass " +
             "windows which provide little additional " +
             "illumination to the room. To the east is a " +
             "dark stairwell, and a small chapel lies to " +
             "the west. A wooden archway in the south wall " +
             "leads into a comfortable chamber.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("stair_top", "east");
  add_exit ("dormitory", "south");
  add_exit ("chapel", "west");

    add_item(({"lamp","lamps","iron lamps","wrought iron lamps"}),
        "These lamps are made of wroght iron. They resemble "
        + "fiery orbs clasped in a dragon's claw.\n");
    add_item(({"window","windows","red windows","red glass"}),
        "An understated display of wealth, these red glass "
        + "windows extend the length of the four walls of "
        + "the great hall. They glow a glorious, rich red "
        + "when the sun strikes them, casting little light, "
        + "but instead a great deal of awe into the hearts "
        + "of those who witness it.\n");
    add_item(({"walls","wall","top of walls"}),
        "They are made of the same stone as the rest of the "
        + "monastery.\n");
    add_item(({"stairs","stairwell","dark stairwell"}),
        " It is a dark stairwell, only faintly illuminated "
        + "by the lamps. It spirals down into the great "
        + "hall, below.\n");
    add_item(({"arch","archway"}),
        "It is a simple archway leading into a comfortable "
        + "room.\n");
}

//-------------------------------------------------------------------

