/*
 * Modification log:
 * Gwyneth: ~Gondor/elessar/lib/time.c->~Gondor/common/lib/time.h
 */
#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;

#include "/d/Gondor/common/lib/time.h"

void
create_room()
{
  ::create_shiproom();
    set_short("On the ship");
    set_long("You're standing on a magnificent ship, your hair "+
             "rustling in the wind. The large sail above is filled by the wind, "+
             "the embroidered star shown fully. One great mast supports the sail. " + 
             "The prow of the ship is fashioned like a swan. A set of stairs lead down a hatch to the captain's cabin.\n");
    add_item(({"mast", "masts"}), "There is one great mast "+
	     "supporting the enormous sail, made of timber felled in Nimbrethil. You can see people high up in the "+
	     "mast, climbing about.\n");
    add_item("prow","The prow is fashioned like a swan.\n");
    add_item(({"sail", "sails"}), "The sail is made out of "+
	     "thick, incredibly strong canvas. On its center is embroidered "+
             "a single golden star. The sail is square shaped, and "+
	     "each time a gust of wind fills it, you feel a "+
             "shrug going through the ship and notice the mast swaying "+
             "slightly to the enormous pressure.\n");
    add_exit(CABIN, "down", 0);

    add_prop(ROOM_I_HIDE, 50);
	set_is_deck(1);
}
