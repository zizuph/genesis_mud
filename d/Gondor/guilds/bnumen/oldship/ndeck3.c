/*
 * Modification log:
 */
#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Gondor/common/lib/time.h"
#include "/d/Gondor/defs.h"

void
create_deck()
{
    set_short("The poop deck");
    set_long("Behind the mizzen mast, the poop deck extends to the back of the " +
         "stern. The deck is composed of intricately " +
        "laid strips of teak that gleam with oil. Ebony rails surround the edge " +
        "of the broad deck.  Ropes are neatly coiled, the silver " +
        "rigging gleams, and barrels and equipment are made fast so as not to " +
        "fly away in a storm. There is a cabin toward the stern, but the " +
        "door is locked. The deck extends forward to the mid deck of the ship. " +
        "There is an open door leading to a cabin aft, and a ladder leads " +
        "down through a hatch in the deck.\n");
    add_item(({"mast", "masts"}), "Three masts support the " +
         "midnight-black sails made of soft, resilient silk. " +
         "There are seamen high up working in the rigging.\n");
    add_item("seamen","The seamen climb about in the rigging,\n"+
             "typing ropes and securing sails. They look quite busy.\n");
    add_item("oars","You notice oars sticking out from each side of the ship,\n"+
             "and you guess there are rowers aboard maneuvering the vessel\n"+
             "up rivers and through shallows.\n");
    add_item(({"sail", "sails"}),"The sails are made out of "+
        "midnight-black silk emblazoned with a red emblem. " +
        "The sails are triangular, and each time a gust of wind " +
        "fills them, you feel a shrug going through the whole ship " +
        "and notice the masts swaying slightly under the enormous pressure.\n");
    add_item("emblem","The sails are midnight black with an emblem " +
        "of a blazing red star in the center.\n");

    add_exit(BNUMEN_DIR + "ship/ndeck2", "fore", 0);
    add_exit(BNUMEN_DIR + "rooms/join_room", "aft");
    add_exit(BNUMEN_DIR + "ship/ncabin_hall1", "down", 0);

    set_deck_sound("The great ship plows through the sea, and waves " +
        "splash upon the deck.\n");

}

