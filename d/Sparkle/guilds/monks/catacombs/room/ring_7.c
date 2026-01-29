/*******************************************************************\
| RING_7.C                                                          |
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
  // This hint is related to the Shields form.
  cc_create_ring (
    7,
    M_SKILL_FORMING_BLADE,
    "a sweeping low kick from under a pair of shields",
    "The majestic crests of the mountains stretch across the " +
    "entire horizon. Tearing your eyes off the peaks, you " +
    "can also see a narrow rope bridge swinging over a " +
    "deep valley to the west.");
}

//-------------------------------------------------------------------

