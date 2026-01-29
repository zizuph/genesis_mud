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
    set_short("A pier in the harbour of Palanthas");
    set_long("You are on a pier in the harbour of Palanthas, one of "
      + "the largest sea ports in Ansalon. Ships from all over the "
      + "continent arrive at this seafaring hub. Barrels and crates "
      + "are stacked along the pier. A large freshly painted sign "
      + "hangs from a post, swinging gently in the wind.\n");

    add_item(({"barrel" , "barrels"}), "These are large wooden "
      + "barrels, normally used as containers for salt-cured foods.\n");
    add_item(({"crate", "crates"}), "These are large solid crates "
      + "probably filled with some kind of merchandise.\n");
    add_item("post", "A sturdy wooden post is attached to the pier. "
      + "A freshly painted sign hangs from the post.\n");
    add_item("sign","The sign reads: Palanthas - Kalaman, no regular "
      + "schedule.\n");

    add_cmd_item("sign","read","The sign reads: Palanthas - Kalaman, "
      + "no regular schedule.\n");

    add_exit("/d/Krynn/solamn/palan/ship/pier", "south", 0, 0);
  add_exit("/d/Krynn/solamn/palan/city/icewall_pier", "north", 0, 0);


    /* add_exit(PIER5, "northwest", 0, 0); */
}
