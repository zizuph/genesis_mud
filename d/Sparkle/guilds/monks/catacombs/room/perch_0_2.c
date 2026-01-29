/*******************************************************************\
| PERCH_0_2.C                                                       |
\*******************************************************************/

/*
 * 03/07/22 Arandir     Created
 *
 */

#include "../defs.h"

inherit CC_ROOM_PERCH_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  cc_create_perch (
    0, 2,
    "carrying a relief of a large cavern, its walls covered with sulphur " +
    "and calcite deposits, with the floor hidden under a litter of leaves " +
    "and bones.",
    "carrying a relief of a large sulphur and calcite cavern, dominated " +
    "by a shimmering shape of an ancient black dragon.",
    "mithas black dragon",
    "The shimmering shape of the ancient black dragon almost completely " +
    "fills the dark cave of the relief. Its entire body is covered with " +
    "thick dark scales and its long tail and immense wings look extremely " +
    "dangerous.");
}

//-------------------------------------------------------------------

