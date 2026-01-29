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
      "regular intervals. To the north the passage enters a corridor "+
      "going east and west. In the other direction the passageway looks "+
      "darker and more narrow.\n"));

    add_item("opening","The opening to the north leads into an "
      + "east-west corridor.\n");
    add_item("passage", "The passage has been reopened recently by the "
      + "signs you see.\n");
    TORCHES;
    SCONCES;
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR + "t_corridor", "north", 0);
    add_exit(RANGER_NORTH_DIR + "tunnel2", "south", 0);
}

