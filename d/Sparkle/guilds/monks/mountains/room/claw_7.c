/*******************************************************************\
| CLAW_7.C                                                          |
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
  set_short ("rocky cliff");
  set_long  ("...");

A steep cliff stops your way here. A quick look below reveals
a mass of stone tearing into the green mass of a forest, in
places overhung so that the foot of the cliff is not visible.
A similar but smaller cliff rises further east, with sparse
vegetation covering its top.

  add_exit ("claw_9", "north");

  dg_item_sky_outside ();
}

//-------------------------------------------------------------------

