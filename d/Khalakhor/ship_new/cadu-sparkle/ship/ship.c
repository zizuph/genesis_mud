/*
 * ship.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Ported to the new ship system by Tapakah, 10/2008.
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  set_ship_line(
		MASTER_OB(TO),
		SHIP_CREW_DIR + "/captain",
		SHIP_OBJS_DIR + "/ticket",
		({
		  "/d/Genesis/start/human/town/pier12",
		  "/d/Khalakhor/inisi/roke/nyreese/cadu_b2",
		}),
		);
  if (!IS_CLONE)
    return;
  
  ::create_ship();
  seteuid(getuid());
  set_cabin(SHIP_ROOM_DIR + "/cabin");
  set_deck( SHIP_ROOM_DIR + "/deck");
  set_name("ship");
  add_name("boat");
  add_name("warship");
  add_adj("huge");
  set_long("A huge warship that travels between Sparkle and Cadu to " +
           "protect the waters from fierce warriors.\n");
}
