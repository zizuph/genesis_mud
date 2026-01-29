/*******************************************************************\
| PERCH_0_4.C                                                       |
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
    0, 4,
    "carrying a relief of a grassy forest clearing, with a large " +
    "oak tree overshadowing most of the grass.",
    "carrying a relief of a grassy forest clearing with an oak tree, " +
    "is dominated by a shimmering shape of a green dragon, fearsome " +
    "and graceful creature of legends.",
    "flotsam green dragon",
    "The shimmering shape of the green dragon is huge and ancient, " +
    "eighty feet in length from snout to tail tip. Darkly beautiful " +
    "and exceedingly graceful, it is far from the hulking and ponderous " +
    "monster often envisioned. Most frightening of all are its eyes, orbs " +
    "of golden green slashed by vertical pupils and bright with a cold, " +
    "alien intelligence.");
}

//-------------------------------------------------------------------

