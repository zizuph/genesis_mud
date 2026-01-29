/*******************************************************************\
| PERCH_2_0.C                                                       |
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
    2, 0,
    "carrying a relief of a giant cavern with a pool of molten lava, " +
    "spanned by a landbridge formed by molten rock deposits.",
    "carrying a relief of a landbridge in a lava cavern. The relief " +
    "is dominated by a shimmering shape of a huge red dragon.",
    "terel red dragon",
    "The shimmering shape of the red dragon radiates confidence " +
    "of many battles not only survived, but won overwhelmingly.");
}

//-------------------------------------------------------------------

