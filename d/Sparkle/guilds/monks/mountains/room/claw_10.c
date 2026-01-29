/*******************************************************************\
| CLAW_10.C                                                         |
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
  set_short ("cascade of rocks");
  set_long  ("...");

You stand on a cascade of rocks that slants down towards west,
where a group of trees splits the rocks into smaller groups
Eastwards, the cascade provides access to yet another
rocky plane. Little else is visible from here, save for
a strangely pointed end of a ridge (the Tail Ridge) to your
southwest.

  add_exit ("claw_9", "east");
  add_exit ("claw_11", "west");

  dg_item_sky_outside ();
}

//-------------------------------------------------------------------

