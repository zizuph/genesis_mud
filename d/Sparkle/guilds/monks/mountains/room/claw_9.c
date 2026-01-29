/*******************************************************************\
| CLAW_9.C                                                          |
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
  set_short ("rocky plane");
  set_long  ("...");

You are at a bare rocky plane, leveling off towards the west
in a cascade of rocks that make the passage tricky. The plane
extends to the south, where it ends in a steep cliff. Further
to the south, treetops hide what must be lowland meadows. An
end of a ridge (the Tail Ridge) is visible to your southwest,
pointing up towards the sky in a marvelous feat of natural
creation.

  add_exit ("claw_7", "south");
  add_exit ("claw_8", "southwest");
  add_exit ("claw_10", "west");

  dg_item_sky_outside ();
}

//-------------------------------------------------------------------

