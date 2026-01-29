inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in a ship-building area");
    set_long(BSN("This is a dry dock in a huge shipbuilding area. It "
      + "appears they are in the middle of building a ship of a size "
      + "to rival any of those in port. But perhaps impressions are "
      + "deceiving because the ship is entirely out of water. The mass "
      + "of planks gives the impression of a beached whale. Tar and "
      + "pitch are strewn about and it would be hard to tell just how "
      + "much work has been done on it lately."));
    add_item(({"whale","ship"}), BSN("The unfinished ship is propped "
      + "upon a mass of planks and pulleys, revealing a few gaps in "
      + "the hull. Parts of it have already been sealed with tar and "
      + "pitch, but overall it seems the ship is far from complete."));
    add_item(({"tar","pitch","tar and pitch"}), BSN("The small pools "
      + "and piles of this sticky black goo have almost turned this "
      + "area into an obstacle course, It seems that they have gotten "
      + "just about as much tar on the ground as on the ship."));
    add_item(({"plank", "planks", "mass", "mass of planks"}), "The "
      + "mass of planks gives the impression of a beached whale.\n");

    add_exit(PELAR_DIR + "streets/shipwright05", "east", 0);
}
