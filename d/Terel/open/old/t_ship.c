inherit "/d/Genesis/ship/ship";

#include "/d/Terel/common/terel_defs.h"

#define BSN(xx)  break_string(xx+"\n", 70)
#define SPARKLE  "/d/Genesis/start/human/town/pier5"
#define NAME     "Calathin Commoner"

void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(SHIP + "t_cab");
    set_deck(SHIP +  "t_deck");
    cap=clone_object(SHIP + "t_cap");
    set_captain(cap);
    set_places_to_go(({PORT + "p1_2",
		       PORT + "bay",
		       PORT + "sea1",
		       PORT + "sea2",
		       SPARKLE,
		       PORT + "sea2",
		       PORT + "sea1",
                 PORT + "bay"}));
    set_time_between_stops(({25,
			      3,
			     12,
			      5,
			     25,
			      5,
			     12,
                      3}));
    set_ticket_id("the terel-sparkle line");
    set_name("ship");
    add_name("boat");
    set_adj(({"large", "sailing"}));
    set_short("large sailing ship");
    set_long(BSN(
	"It's a large sailing ship. On the side of the ship you " +
	"read the name: "+NAME+"."
    ));
}
