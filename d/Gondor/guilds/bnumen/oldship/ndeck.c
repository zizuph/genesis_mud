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
    set_short("On the ship");
    set_long("Three tall masts support the rigging and sails " +
        "on the deck of this ship. The deck is composed of intricately " +
        "laid strips of teak that are oiled. Ebony rails surround the edge " +
        "of the deck A set of stairs leads down "+
        "below deck.\n");
    add_item(({"mast", "masts"}), "Three masts support the " +
         "midnight-black sails made of soft, resilient silk. " +
         "You can see seamen high up " +
         "working at the sails at the captain's command.\n");
    add_item("seamen","The seamen climb about in the rigging,\n"+
             "typing ropes and securing sails. They look quite busy.\n");
    add_item("oars","You notice oars sticking out from each side of the ship,\n"+
             "and you guess there are rowers aboard maneuvering the vessel\n"+
             "up rivers and through shallows.\n");
    add_item(({"sail", "sails"}),"The sails are made out of "+
        "midnight-black silk emblazoned with a red emblem. " +
        "The sails are triangular, and "+
        "each time a gust of wind fills them, you feel a "+
        "shrug going through the ship and notice the masts swaying "+
        "slightly to the enormous pressure.\n");
    add_item("emblem","The sails are midnight black with an emblem " +
        "of a blazing red star in the center.\n");
    add_exit(BNUMEN_DIR + "ship/ncabin", "down", 0);

}
