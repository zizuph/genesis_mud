inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

void
create_deck()
{
    set_short("On the ferry");
    set_long("You're standing on an old croaking ferry, feeling " +
	     "water directly underneath your feet. " +
	     "From here you get a splendid view of your surroundings.\n");

    set_deck_sound("@@sounds");
}

string
sounds()
{
    if (random(3))
      return "The ferryman pushes the ferry with effort through the water " +
	"using a long pole.\n";

    return "The ferryman lets the ferry glide along with the current.\n";
}

