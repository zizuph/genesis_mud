/*******************************************************************\
| PERCH_2_4.C                                                       |
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
    2, 4,
    "carrying a relief of a large cave, looking decidedly " +
    "dark and damp and altogether unpleasant.",
    "carrying a relief of a damp cave, dominated by a shimmering " +
    "shape of a blue dragon.",
    "cadu blue dragon",
    "The shimmering shape of the blue dragon is quite unremarkable, " +
    "except for its disquietingly human expression of evil " +
    "contempt.");
}

//-------------------------------------------------------------------

