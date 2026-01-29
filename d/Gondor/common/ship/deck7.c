#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Gondor/common/lib/time.h"
#include "/d/Gondor/defs.h"

void
create_deck()
{
    set_short("aboard the river boat");

    set_long(BSN("The deck of the river boat is very wide. Further towards "
      + "the bow, the deck gives way for a large open cargo hold. The sail "
      + "on the single mast is filled by a strong wind, but the oars are "
      + "also in use to move the heavy boat to its destination. A set of "
      + "stairs leads down a hatch to the captain's cabin."));
    add_item(({"mast", "masts"}), BSN("There is one great mast "
      + "supporting the large sail, made of the strongest "
      + "Gondorian lebethron wood. You can see people high up in the "
      + "mast, climbing about. On top of the mast there flies a banner."));
    add_item("people","These people climb about in the rigging,\n"+
             "typing ropes and securing sails. They look quite busy.\n");
    add_item("oars", BSN("You notice oars sticking out from each side of "
      + "the boat. They are moved by the rowers on the slave deck."));
    add_item(({"sail", "sails"}), BSN("The sail is made out of "
      + "thick grey canvas. The sail is square shaped and the "
      + "strong wind is filling it."));
    add_item(({"banner", }), BSN("From top of the mast, the ship flies "
      + "the banner of Pelargir: Three golden ships in a blue field, "
      + "surmounted by a silver crown."));

    add_exit(SHIP_DIR + "cabin7", "down", 0);

    add_prop(ROOM_I_HIDE, 50);
}