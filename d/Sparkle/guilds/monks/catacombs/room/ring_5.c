/*******************************************************************\
| RING_5.C                                                          |
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
  // This hint is related to the Serpentine form.
  cc_create_ring (
    5,
    M_SKILL_FORMING_CLUB,
    "a powerful kick at knee height",
    "Not very far below your vantage point, a rocky outcropping " +
    "extends over a motionless surface of a mountain lake, a " +
    "blue eye of a mystical creature whose bones were " +
    "turned to the very stone of the mountains.");
}

//-------------------------------------------------------------------

