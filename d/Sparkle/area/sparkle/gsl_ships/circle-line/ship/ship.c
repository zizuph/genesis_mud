#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIP;

void
create_ship()
{
  ::create_ship();
  set_deck(DECK);
  set_cabin(CABIN);
    set_name("galleon");
    add_name("ship");
    add_adj("large");
    add_adj("transport");
    set_long(break_string("This is a large ocean-going transport galleon. " +
	"It's put here by the officials in Genesis to go between " +
	"the many harbours around the world. It's a well built ship, and " +
	"looks quite strong, but slow. You see the words: Circle Line, " +
	"written in the front of the ship." +
        "\n", 70));
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, "", 
                ({ PELARGIR_PIER, GELAN_PIER,
		   TELBERIN_PIER, LAST_PIER,
		   MACDUNN_PIER, RAUMDOR_PIER,
		   KABAL_PIER, GONT_PIER,
		   CADU_PIER, SYBARUS_PIER,
		   PALANTHAS_PIER, FAERUN_PIER, FAERIE_PIER }) );
}
