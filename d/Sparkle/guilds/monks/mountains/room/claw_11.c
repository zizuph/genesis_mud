/*******************************************************************\
| CLAW_11.C                                                         |
\*******************************************************************/

/*
 * 03/10/21 Arandir	Created
 *
 */

#include <tasks.h>
#include <ss_types.h>

#include "../defs.h"

inherit MT_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

/*
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("niche between rocks");
  set_long  ("...");

A niche between two groups of larger rocks creates a welcome shelter
from the incessant wind, shared by an alder and a pine tree twisted
around each other in search of more space. With some of the rocks
only waist high, the rocky plateau to your north is well visible.
To the south, however, progress is blocked by more rocks, and
only a small opening to the east looks passable.

  add_exit ("claw_14", "north");
  add_exit ("claw_10", "east");

  dg_item_sky_outside ();
}

//-------------------------------------------------------------------

