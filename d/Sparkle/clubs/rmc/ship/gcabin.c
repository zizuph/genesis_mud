/*
 * Conan Jun -96
 * Ported to the new ship system
 * Tapakah, 10/2008
 */
 
#include "defs.h"
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

#pragma save_binary

inherit STDSHIPROOM;

void
create_room()
{
	::create_shiproom();
  set_short("Golden ship cabin");
  set_long(break_string(
    "You're standing in a richly decorated cabin on the golden "+
    "ship. Everything here shimmers of gold and gemstones. Diamonds "+
    "big as eggs are fastened on the walls. You're truly impressed!\n",60));

  OUTSIDE;

  add_exit("gdeck","fore");
}
