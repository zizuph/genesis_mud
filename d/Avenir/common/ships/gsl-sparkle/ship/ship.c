// -*-C++-*-
// name: Melancholy /d/Avenir/common/ships/sparkle/ship.c
// creator(s):    Tepisch   Oct 1994
// last update:   Boriska, Mar 23 1995
// purpose:       To bring people to Avenir from Sparkle   
// note:
// bug(s):
// to-do:   
// Ported by Tapakah to the new ship system, 05/2009

#pragma save_binary

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  ::create_ship();
  set_name("ship");
  add_name("Melancholy");
  add_name(({"bark", "barque"}));
  add_adj("ghostly");
  set_long("A ghostly-looking sailing ship with square-rigged masts. " +
	   "A decaying bust of indeterminate gender decorates the prow. " +
	   "On either side of the prow the letters 'G.S. MELANCHOLY' " +
	   "are printed in fading gold paint.\n");
  
  set_cabin(CABIN);
  set_deck(DECK);
  seteuid(getuid());

  set_ship_line(MASTER_OB(TO), CAPTAIN, TICKET,
                ({ SYBARUS_PIER, SPARKLE_PIER }));
}

