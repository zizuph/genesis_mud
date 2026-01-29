/*******************************************************************\
| RING_3.C                                                          |
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
  // This hint is related to the Memories form.
  cc_create_ring (
    3,
    M_SKILL_FORMING_STICK,
    "a blur of strikes in many directions",
    "The lowlands to the southeast of here seem almost uninhabited, " +
    "except for a small village near the blue ribbon of the sea that " +
    "lines the horizon.");
}

//-------------------------------------------------------------------

