#pragma save_binary

inherit "/d/Genesis/ship/deck";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_deck()
{
    set_short("On the ship");
    set_long(break_string(
	  "This is an old and not very well kept ship. "
	+ "The deck is in poor shape as are the two "
	+ "masts that support the sails. There is "
	+ "a small hole in the deck leading down to "
	+ "the cabin below. The smartest thing to "
	+ "do right now would probably be to leave "
	+ "this ship before it reaches open water.\n",75));

    add_item(({"mast", "masts"}), break_string("There are two small masts "
	+ "supporting the torn rags acting as sails.\n",76));

    add_item(({"rags", "torn rags"}), break_string("The torn rags looks "
	+ "like they act as sails, but you doubt their effectiveness.\n",76));

    add_item("ship", break_string("Well, if you can call this a ship, it "
	+ "looks like this poor boat is in poor shape.\n",76));

    add_item(({"sail", "sails"}), break_string("The sails are spotted and "
	+ "moldy, barely holding together.\n",76));

    add_item(({"hole", "small hole"}), break_string("You would probably "
	+ "get below deck and into a cabin if you went down.\n",76));

    add_exit("/d/Shire/common/ship/oldship/cabin","down",0);

}