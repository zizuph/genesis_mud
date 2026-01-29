inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("at a crossing near a bridge");
    set_long(BSN("You are at an intersection of roads. The main city "+
       "road continues north to the city gates and southwest across a "+
       "stone bridge. Another road branches off to the east where in the "+
       "distance you can see the lighthouse. There are several "+
       "buildings around, though most are just houses built for the "+
       "people of Pelargir. The cobblestones give the streets an air of "+
       "security."));
    add_cobble();
    add_admiral("north");
    add_item("bridge", "The aged bridge spans the "
      +	"Sirith River, and heads deeper into the city.\n");
    add_northside();
    add_item("lighthouse", "From this distance all you "
      + "can make out is that it is tall.");
    add_exit(PELAR_DIR + "street/mroad1",    "north",     0);
    add_exit(PELAR_DIR + "street/nroad1",    "east",      0);
    add_exit(PELAR_DIR + "street/bridstone", "southwest", 0);
}
