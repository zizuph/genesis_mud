/*******************************************************************\
| PERCH_1_4.C                                                       |
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
    1, 4,
    "carrying a relief of a vast evergreen forest of ancient " +
    "oaks and dense underbrush.",
    "carrying a relief of an evergreen forest, roamed by a shimmering " +
    "shape of a tiny faery dragon with butterfly wings.",
    "flotsam faery dragon",
    "The shimmering shape of the faery dragon is surprisingly tiny, " +
    "just about twice the length of your arm. It has a large head " +
    "with a mischievous grin, and butterfly wings that sprout out " +
    "from tiny scales of all colors from deep purple to emerald " +
    "green.");
}

//-------------------------------------------------------------------

