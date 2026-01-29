/*******************************************************************\
| PERCH_3_0.C                                                       |
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
    3, 0,
    "carrying a relief of an open moorland, with short pale grass " +
    "covering shallow hollows and small hillocks.",
    "carrying a relief of a pale moorland. The relief is dominated " +
    "by a shimmering shape of a monstrous ice dragon with a frosty " +
    "stare.",
    "calia ice demon",
    "The shimmering shape of the ice dragon is almost mountainous " +
    "in size, with white scales like mithril shields and great " +
    "outspread wings the size of galleon sails.");
}

//-------------------------------------------------------------------

