#pragma save_binary

#include "/d/Krynn/solamn/palan/local.h"

inherit STREET_BASE

#include <stdproperties.h>
#include <macros.h>
#include RND_MEET


void
reset_palan_room()
{
    return;
}

void
create_palan_room()
{
    set_short("A bare pier in the harbour of Palanthas");
    set_long("You are on a wooden pier in the harbour of Palanthas, one of "
      + "the largest sea ports in Ansalon. Ships from all over the "
      + "continent arrive at this seafaring hub. This pier is " 
      + "relatively bare of cargo, and only a small sign nailed to a " 
      + "wooden post reminds you that sometimes a ship docks here.\n");

    add_item("post", "A sturdy wooden post is attached to the pier. "
      + "A small sign has been nailed to it.\n");
    add_item("sign","The sign reads: Palanthas - Icewall, no winter runs.\n");

    add_cmd_item("sign","read","The sign reads: Palanthas - Icewall, "
      + "no winter runs.\n");

    add_exit("/d/Krynn/solamn/palan/shipX/flotsam_pier", "south", 0, 0);
}
