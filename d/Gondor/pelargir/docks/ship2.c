inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("on a Royal Gondorian Ship");
    set_long(BSN("You are on a Royal Gondorian ship. This must be the "
      + "ship of an important personage because you see the Royal "
      + "Standard of Gondor painted in several places. The sails are "
      + "all furled so it does not look like this ship will be going "
      + "anywhere soon, but it has the look of war about it. There are "
      + "a few harpoon-spears in a rack next to the captain's cabin."));
     add_item(({"harpoons","spears","harpoon-spears","rack"}),
        BSN("This is a large rack of barbed spears mostly used "+
        "to fend off odd sea creatures and occasionally "+
        "used to pick off pirates from other ships. "+
        "The captain would be very upset if you took one."));
     add_item("deck",BSN("The deck is spotless,  you could not "+
        "have done a better job yourself."));
     add_exit(PELAR_DIR + "docks/cabin2.c","cabin",0);
     add_exit(PELAR_DIR + "docks/dock6","disembark",0);
}
