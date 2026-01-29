/*******************************************************************\
| RING_1.C                                                          |
\*******************************************************************/

/*
 * 06/09/24 Arandir     Created
 *
 */

#include "../defs.h"
#include "../../monastery/defs.h"

inherit CC_ROOM_RING_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  // This hint is related to the Dragon Within form.
  cc_create_ring (
    1,
    M_SKILL_FORMING_BLADE,
    "a blur of movements that come together in a beautiful and deadly dance",
    "Three more tall spires, probably of volcanic origin, are barely " +
    "visible to the north of where you are standing. The view of " +
    "the rest of the mountains is cut off by the spire you are " +
    "climbing, leaving only distant lowlands to the east.");
}

//-------------------------------------------------------------------

