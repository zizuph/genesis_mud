#pragma save_binary

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/common/guild/north/northern_hq.h"

void
create_gondor()
{
    set_short("the southern passageway");
    set_long(BS("You are in the southern passageway. The walls are "+
      "smooth and even, yet obviously ancient. "+
      "Burning torches are set in torch brackets at "+
      "regular intervals. The passage curves slightly westwards "+
      "here, leading north in one direction, and disappearing into "+
      "darkness to the southwest.\n"));

    add_item("passage", "The passage has been reopened recently by the "
      + "signs you see.\n");
    TORCHES;
    SCONCES;
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR + "tunnel1", "north", 0);
    add_exit(RANGER_NORTH_DIR + "tunnel3", "southwest", 0);
}

