/*******************************************************************\
| PERCH_4_2.C                                                       |
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
    4, 2,
    "carrying a relief of a dark grotto with worn floor, uneven with " +
    "depressions of varying sizes that dent the bare grey stone.",
    "carrying a relief of a dark grotto, home to a shimmering shape " +
    "of a dragon shackled by a massive iron chain.",
    "calia shackled dragon",
    "The shimmering shape of the shackled dragon seems to be comprised " +
    "entirely of scales, teeth and claws. Stretched across a heavily " +
    "muscled frame, the polished scales seem to ripple in the light in " +
    "an eerie complement to its burning red eyes.");
}

//-------------------------------------------------------------------

