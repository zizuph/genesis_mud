inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("on a Royal Gondorian Ship");
    set_long(BSN("You are on a Royal Gondorian ship. Though it does "
      + "not seem that this one leaves port very often, someone must "
      + "keep it very tidy.  There isn't a single thing out of place. "
      + "There is a weapons rack here with a full compliment of "
      + "harpoon-spears near the entrance to the captains cabin, and "
      + "the deck looks freshly swabbed with clean mop water. The "
      + "sails have all been furled so you do not imagine that this "
      + "ship will be leaving port soon."));
    add_item(({"harpoons","spears","harpoon-spears","rack"}), BSN(
        "This is a large rack of barbed spears mostly used to fend off "
      + "odd sea creatures and occasionally used to pick off pirates "
      + "from other ships. The captain would be very upset if you took "
      + "one."));
    add_item("deck",BSN("The deck is spotless,  you could not have "
      + "done a better job yourself."));
    add_exit(PELAR_DIR + "docks/cabin1", "cabin",0);
    add_exit(PELAR_DIR + "docks/dock4",  "disembark",0);
}
