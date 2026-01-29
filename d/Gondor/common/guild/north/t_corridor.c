#pragma save_binary

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/common/guild/north/northern_hq.h"

void
create_gondor()
{
    set_short("The temple corridor");
    set_long(BS("You're in the temple corridor. On the wall hangs a "+
      "tapestry. Burning torches are set in torch brackets at "+
      "regular intervals. To the west is an arched opening, and "+
      "east is an exit leading to the temple. A passage breaks off "+
      "from the corridor, leading south.\n"));

    add_item("tapestry",BS("The tapestry shows Tulkas, the "+
      "strongest of the people of Valar, "+
      "laughing joyfully as he fights bare-handed.\n"));
    add_item("opening","The opening leads into the great hall.\n");
    add_item("passage", "The passage has been added recently by the "
      + "signs you see.\n");
    TORCHES;
    SCONCES;
    WALLS;

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(RANGER_NORTH_DIR + "great_hall", "west", 0);
    add_exit(RANGER_NORTH_DIR + "temple", "east", 0);
    add_exit(RANGER_NORTH_DIR + "tunnel1", "south", 0);
}

