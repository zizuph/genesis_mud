inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in the captain's cabin");
    set_long(BSN("You are in the captain's cabin. The captain's cabin "
      + "is nearly as spotless and orderly as the deck was. A neat "
      + "stack of papers is pinned to the desk awaiting the captain's "
      + "attention. There is a small porthole in the side, but other "
      + "than some sea charts pinned on the wall the cabin is pretty "
      + "bare."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"charts","maps"}),BSN("These are mostly odd maps and "
      + "charts of stars and sea. How these sailors ever get anywhere "
      + "using these is beyond you."));
    add_item("deck",BSN("The deck is spotless, you could not have "
      + "done a better job yourself."));
    add_item(({"papers","stack of papers","stack"}), 
        "These are for the Captain's eyes only, but you take a quick "
      + "peek anyway..\n"
      + "Awww.. it is just the boring ship's log.\n");
    add_item(({"porthole","window"}),
        "Through this you can glance the vast river.\n");

    add_exit(PELAR_DIR + "docks/ship1", "deck", 0);
}

