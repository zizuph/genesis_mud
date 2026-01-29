/*******************************************************************\
| PERCH_4_4.C                                                       |
\*******************************************************************/

/*
 * 03/07/23 Arandir     Created
 *
 */

#include "../defs.h"

inherit CC_ROOM_PERCH_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  cc_create_perch (
    4, 4,
    "carrying a relief of an immense underground cavern with " +
    "strangely smooth walls and a large chest.",
    "carrying a relief of an immense cavern, guarded by a shimmering " +
    "shape of an aged black dragon with fierce eyes.",
    "krynn black dragon",
    "The shimmering shape of the black dragon appraises its surroundings " +
    "with fierce lustrous-black eyes. Its muscular body is plated with " +
    "dragon scales. Sharp claws erupt from its forearms, and the talons " +
    "look like they could rip anything to shreds in no time.");
}

//-------------------------------------------------------------------

