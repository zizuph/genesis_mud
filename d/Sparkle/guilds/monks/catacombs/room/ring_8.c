/*******************************************************************\
| RING_8.C                                                          |
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
  // This hint is related to the Victorious form.
  cc_create_ring (
    8,
    M_SKILL_FORMING_STICK,
    "a quick shoulder roll under the guard of the enemy",
    "Three more spikes, similar to the one you are climbing, " +
    "frame your view towards north. A green valley, walled " +
    "off from all sides by the steep mountain sides, opens " +
    "to the northwest.");

  cc_item_crevice ();
}

//-------------------------------------------------------------------

