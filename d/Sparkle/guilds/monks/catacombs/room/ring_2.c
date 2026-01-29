/*******************************************************************\
| RING_2.C                                                          |
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
  // This hint is related to the Dragon Strike form.
  cc_create_ring (
    2,
    M_SKILL_FORMING_CLUB,
    "a flying crescent kick",
    "The view of the mountains is pretty much cut off by the spire " +
    "you are climbing, leaving only distant lowlands to the east " +
    "to provide what is still a lovely view.");
}

//-------------------------------------------------------------------

