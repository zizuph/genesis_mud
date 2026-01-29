inherit "/d/Krynn/std/cabin";

#include <stdproperties.h>
#include "local.h"

void
create_cabin()
{
    set_short("A cabin inside the ship");
    set_long("This is a small cabin below the deck of the ship. " +
    "It is sparsely furnished, with just a hammock and a table.\n");

    add_item("table", "It is a sturdy wooden table.\n");

    add_item("hammock","A hammock hangs on the back wall. " +
      "It seems to you that some experience would be " +
      "needed to be able to use this contraption.\n");

    add_exit(SHIP_D + "deck","up",0);

    add_prop(ROOM_I_INSIDE, 1);

    set_cabin_sound("@@sounds");
}

sounds()
{
    if (random(2))
        return "The ship rocks gently over the sea.\n";

    return "The sound of water hitting the hull fills your ears.\n";
}

