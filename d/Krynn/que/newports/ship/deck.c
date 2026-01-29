inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("On the Newports-Sparkle ship");
    set_long("This is the magnificent ship, Fairview. " +
        "Wind rolls around you, only to be impeded by the sails. " +
        "A cabin resides in the aft portion of the ship, while a " +
        "ladder leads down to the rowing deck. From anywhere on " +
        "main deck, you are able to get an excellent view of " +
        "your surroundings.\n");

    add_item("wind", "The wind softly buffets around you.\n");
    add_item("sails", "The cloth sails are in impeccable condition. " +
        "They are filled by the wind whether the boat is in motion " +
        "or on shore. Perhaps it is a magical wind that only allows " +
        "the boat to move when appropriate.\n");
    add_item("cabin", "The cabin is small in appearance, but it " +
        "is perhaps worth an investigation.\n");
    add_item("ladder", "The ladder looks sturdy, able to hold " +
        "a minotaur's weight.\n");
    add_item("sky", "The sky has a few clouds but is otherwise " + 
	"featureless.\n");
    
    add_item("oars", "@@oars");

    add_exit(TDIR + "cabin", "aft", 0);
    add_exit(TDIR + "rowingdeck", "down", 0);
    add_exit(TDIR + "for", "forward", 0);

    set_deck_sound("@@sounds");
}

sounds()
{
    if(random(3))
    return "The ship splashes into a high wave, causing water to " +
        "spray onto the deck.\n";

	return "The ship sways slightly in the wind.\n";

    return "The ship is rocking gently with the waves.\n";
}

public int
query_no_time() { return 1; }

