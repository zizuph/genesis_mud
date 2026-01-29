/*******************************************************************\
| RING_0.C                                                          |
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
  // This hint is related to the Birth form.
  cc_create_ring (
    0,
    M_SKILL_FORMING_STICK,
    "a powerful uppercut from a kneeling position",
    "Three spires, tall even though not as tall as the one you " +
    "are climbing, are visible from this vantage point. Behind " +
    "them, a wide crest cuts across the northern horizon like " +
    "a monstrous wing.");

  cc_item_crevice ();
}

//-------------------------------------------------------------------

