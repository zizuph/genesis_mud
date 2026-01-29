/*******************************************************************\
| PERCH_4_0.C                                                       |
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
    4, 0,
    "carrying a relief of an enormous oval chamber with smooth " +
    "and reflective walls and a geyser near a treasure pile.",
    "carrying a relief of an enormous treasure chamber, guarded " +
    "by a shimmering shape of a deep dragon with iridescent scales.",
    "kalad deep dragon",
    "The shimmering shape of the deep dragon is horrible and magnificent. " +
    "Its iridescent maroon scales make it appear as if it were covered " +
    "not in scales, but in red gems of the finest quality. The size " +
    "of the creature is over a hundred feet in length and there is a " +
    "particularly large triangular scale on its chest.");
}

//-------------------------------------------------------------------

