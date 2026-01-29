/*******************************************************************\
| HALL_UPPER_SOUTH.C                                                |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/03/29 Arandir     Some polishing up
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("southern end of the upper hall");
  set_long  ("High above is the domed stone ceiling that makes " +
             "the roof of the monastery. Near the top of the " +
             "dome is a narrow stone ledge, on which stand " +
             "many small statues of past monks, evenly spaced " +
             "out between each other. Large iron lamps hanging " +
             "from iron brackets in the wall provide light for " +
             "this part of the hall. Opening onto a small balcony " +
             "to the south is a wooden lattice door.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_upper_north", "north");
  add_exit ("meeting", "east");
  add_exit ("balcony_south", "south");
  add_exit ("balcony_temple", "west");

  dg_add_entrance ("south", "You walk back inside.");

  m_item_statues_former (50, 100);

    add_item(({"lattice","wooden lattice","door","lattice door","wooden lattice door"}),
        " It is a door is simplicity and elegance, made "
        + "with strips of fine, hand-polished wood.\n");
    add_item(({"lamp","lamps","iron lamps","wrought iron lamps"}),
        "These lamps are made of wrought iron. They resemble "
        + "fiery orbs clasped in a dragon's claw.\n");
    add_item(({"light","sunlight"}),
        "The sunlight is warm, it seems to cling to the "
        + "walls with a tenacious hold.\n");
    add_item(({"ceiling","roof"}),
        "The ceiling here is the northern half of a great, "
        + "shallow dome that extends to the southern end of "
        + "the hall. The dome is smooth, made from some "
        + "white stone, and unadorned. It is beautiful in "
        + "its simplicity.\n"
        + dg_embed_action ("stares up at the dome above."));
    add_item(({"shelf","ledge"}),
        "Ringing the base of the dome high above, and "
        + "continuing to the south, is a very thin ledge of "
        + "stone, supported by short, thick beams of wood "
        + "that angle out from the walls. Sitting atop the "
        + "ledge are many small wooden statues.\n"
        + dg_embed_action ("looks up at the ledge ringing the dome."));
    add_cmd_item(({"down","floor",""}), ({"kneel"}),
        "You kneel down on the uncomfortable grille.\n");
    add_cmd_item(({"silence","to silence"}), ({"hear","listen"}),
        "Silence makes no noise.\n"
        + dg_embed_action ("tries futily to hear something."));
    add_cmd_item(({"wall","dome","ledge","up"}), ({"climb","scale"}),
        "There is no way you could climb the wall, making "
        + "you wonder how they got the statues to the ledge "
        + "in the first place.\n"
        + dg_embed_action ("scratches and scrambles against the wall in a vain attempt to climb up."));
}

//-------------------------------------------------------------------

