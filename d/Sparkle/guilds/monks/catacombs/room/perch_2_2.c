/*******************************************************************\
| PERCH_2_2.C                                                       |
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
    2, 2,
    "carrying a relief of a large, barren and windowless room, " +
    "with a huge basin of water and a huge empty bucket.",
    "carrying a relief of a barren room, dominated by a shimmering " +
    "shape of a huge but old red dragon.",
    "krynn old dragon",
    "The shimmering shape of the red dragon is lined and wrinkled " +
    "with age, the brilliant red skin grayish and mottled. One of " +
    "its eyes is almost completely white, its sides are lined by " +
    "long scars and its wings are leathery and dry. Its talons, " +
    "though, are still sharp and destructive.");
}

//-------------------------------------------------------------------

