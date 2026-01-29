/*******************************************************************\
| PERCH_1_0.C                                                       |
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
    1, 0,
    "carrying a relief of a twisty path winding its way through a " +
    "rugged icy plain.",
    "carrying a relief of a twisty path on an icy plain. The relief " +
    "is dominated by a shimmering shape of an adult white dragon, " +
    "by all appearances slim and vicious.",
    "icewall white dragon",
    "The shimmering shape of the white dragon looks slim and vicious. " +
    "The dragon has a menacing look of someone who would not back down " +
    "from a fight. Its entire body is covered with white scales.");
}

//-------------------------------------------------------------------

