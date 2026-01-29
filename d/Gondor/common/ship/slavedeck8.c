#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/slavedeck.c";
#include "/d/Gondor/common/lib/time.h"

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("the slavedeck");
    set_long(BSN("This is the oar deck of the ship. There are "+
	     "a number of benches on each side where the rowers sit when they "+
	     "are rowing, and there is a large beating drum at the far end of "+
	     "the deck, used to keep the rowers in pace, thus enforcing "+
	     "fair speeds. A rugged brass lantern hangs in the ceiling, "+
	     "shedding a dim light so that you can barely see the room."));
    add_item("drum", "This is a large drum giving a deep booming sound.\n");
    add_item("benches", "The old, wooden benches look really uncomfortable.\n");
    add_item("lantern", "It's an old brass lantern, secured in the ceiling.\n");
    add_exit(SHIP_DIR + "cabin8", "up", 0);
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
