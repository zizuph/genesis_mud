#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/time.h"

void
create_deck()
{
    set_short("on the deck of a corsair");
    set_long(BSN("You are standing on the deck of a small, run-down corsair. " +
        "Above you, the wind is swelling a grey sail supported by " +
        "a single mast. From both sides you can see oars sticking " +
        "out, probably used for maneuvering in the shallows and up rivers. " +
        "A set of stairs leads down a hatch to a cabin."));
    add_item(({"mast", "masts"}), BSN(
        "There is one great mast supporting the sail. You can see " +
        "sailors high up in the mast, climbing about."));
    add_item("oars",BSN("You notice oars sticking out from each side of the ship, "+
        "and you guess there are rowers aboard maneuvering the vessel " +
         "up rivers and through shallows."));
    add_item(({"sail", "sails"}), BSN("The sail is made out of "+
        "thick, strong canvas. Once it must have been white, now it is grey, " +
        "and it has been patched many times. The sail is square shaped, and "+
        "each time a gust of wind fills it, you feel a "+
        "shrug going through the ship and notice the mast swaying "+
        "slightly to the enormous pressure."));
    add_exit(SHIP_DIR + "cabin6","down", 0);

    add_prop(ROOM_I_HIDE, 60);
}
