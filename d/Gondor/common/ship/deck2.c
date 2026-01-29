/*
 * Modification log:
 * Gwyneth: ~Gondor/elessar/lib/time.c->~Gondor/common/lib/time.h
 */
#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Gondor/common/lib/time.h"

void
create_deck()
{
    set_short("On the ship");
    set_long(break_string("You're standing on a magnificent ship, your hair "+
             "rustling in the wind. The large sail above is filled by the wind, "+
             "the embroidered star shown fully. One great mast supports the sail. " + 
             "The prow of the ship is fashioned like a swan. A set of stairs lead down a hatch to the captain's cabin.\n",75));
    add_item(({"mast", "masts"}), break_string("There is one great mast "+
	     "supporting the enormous sail, made of timber felled in Nimbrethil. You can see people high up in the "+
	     "mast, climbing about.\n",76));
    add_item("prow","The prow is fashioned like a swan.\n");
    add_item(({"sail", "sails"}), break_string("The sail is made out of "+
	     "thick, incredibly strong canvas. On its center is embroidered "+
             "a single golden star. The sail is square shaped, and "+
	     "each time a gust of wind fills it, you feel a "+
             "shrug going through the ship and notice the mast swaying "+
             "slightly to the enormous pressure.\n",76));
    add_exit("/d/Gondor/common/ship/cabin2", "down", 0);

    add_prop(ROOM_I_HIDE, 50);
}
