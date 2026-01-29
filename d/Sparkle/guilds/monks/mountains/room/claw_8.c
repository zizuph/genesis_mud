/*******************************************************************\
| CLAW_8.C                                                          |
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

A sharp edge of a rocky cliff is right at your feet, angling
down with an uncompromising vehemence as if it were a giant
claw set into the lowlands below. The rock of the cliff is
mostly white, bleached by the sun except for a few veins
shaded red.

  add_exit ("claw_9", "northeast");

  dg_item_sky_outside ();
}

//-------------------------------------------------------------------

