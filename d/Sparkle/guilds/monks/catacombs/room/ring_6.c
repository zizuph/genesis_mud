/*******************************************************************\
| RING_6.C                                                          |
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
  // This hint is related to the Shadow of Wings form.
  cc_create_ring (
    6,
    M_SKILL_FORMING_CLUB,
    "a powerful forward slash of both hands",
    "The view of the distant mountain peaks is dominated by a single " +
    "tall peak, a tail of a serpent poised to strike. A bit more to " +
    "the north, a closed off forest valley is visible in the very " +
    "heart of the mountains.");
}

//-------------------------------------------------------------------

