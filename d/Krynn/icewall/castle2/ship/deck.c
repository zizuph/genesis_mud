inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("On the middle deck of the schooner");
    set_long("This two-mast schooner is an old vessel, but kept in" +
        "good condition. Two sturdily rigged masts bear white canvas " +
        "and the hull has been heavily reinforced with thick wooden " +
        "beams. A cabin opens in the aft portion of the ship, while a " +
        "ladder leads down below decks. From anywhere on " +
        "main deck, you are able to get an excellent view of " +
        "your surroundings.\n");
    add_item(({"sails", "canvas"}), "The canvas sails are patched and " +
        "have a rugged look.\n");
    add_item("cabin", "This is the captain's cabin.\n");
    add_item("ladder", "The ladder looks sturdy, able to hold " +
        "a minotaur's weight.\n");

    add_exit(TDIR + "cabin", "aft", 0);
    add_exit(TDIR + "belowdeck", "down", 0);
    add_exit(TDIR + "for", "forward", 0);

    set_deck_sound("@@sounds");
}

sounds()
{
    if(random(3))
    return "The ship splashes into a high wave, causing water to " +
        "spray onto the deck.\n";

    return "The ship sways slightly in the wind.\n";

    return "Using favourable currents, the ship streams ahead.\n";
}

public int
query_no_time() { return 1; }

