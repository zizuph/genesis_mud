inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("a poor section of Pelargir");
    set_long(BSN("You are standing in front of a small orphanage in "
      + "the southern part of Pelargir. There is an unfavorable scent "
      + "in the air, which may come from the refuse in the street, or "
      + "from the shack to the south. Though there are many homes "
      + "around here, it does not seem that any of them are too "
      + "receptive to visitors."));
    add_item("orphanage", BSN("The orphanage looks rather gloomy and "
      + "boring. It surely cannot be an interesting place to live."));
    add_item("refuse",BSN("The refuse here in the street seems to "
      + "attract a lot of attention.... from the flies at least."));
    add_item("shack", BSN("The shack looks like a strong wind is all "
      + "it would take to blow it right over. It would seem to be safer "
      + "just to live in the street."));

    add_exit(PELAR_DIR + "homes/orphanage", "north",0);
    add_exit(PELAR_DIR + "street/proad2",   "east",0);
    add_exit(PELAR_DIR + "homes/shack1",    "south",0);
    add_exit(PELAR_DIR + "street/proad",    "west",0);
}

