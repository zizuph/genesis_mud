/*******************************************************************\
| RING_4.C                                                          |
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
  // This hint is related to the Poised for Flight form.
  cc_create_ring (
    4,
    M_SKILL_FORMING_BLADE,
    "a jabbing motion of a taloned fist",
    "Staring directly to the south, you can see the narrow " +
    "winding path that leads up the mountains to the foot " +
    "of the spire you are climbing.");
}

//-------------------------------------------------------------------

