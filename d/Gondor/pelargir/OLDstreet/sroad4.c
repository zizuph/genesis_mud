inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("south of Pelargir square");
    set_long(BSN("You are just south of a bulky statue in the "
      + "city square of Pelargir. To the west is a smaller square "
      + "with an inn and the post office. The main street continues "
      + "southeast to the southern city gates, staying to the left "
      + "of a large stone building."));

    add_cobble();
    add_admiral();

    add_item("statue",BSN("The statue is rather tall and bulky but "+
       "other than that you cannot see details without getting "+
       "closer."));
    add_item(({"post office","inn"}),BSN("You would have to be "+
       "closer to get a better look."));
    add_item(({"gates", "gate", "city gates", "southern city gates", }),
        BSN("The gates cannot be seen from here as the street makes a "
      + "turn between here and the gates."));
    add_item(({"building", "stone building", }), BSN(
        "This large stone building is the Adventurers' Guild of "
      + "Pelargir. The building was constructed from grey stone blocks "
      + "hewn from rock and polished. Time and weather have left their "
      + "impact on the stones, but the expert workmanship is still "
      + "clearly visible. A large archway without doors is leading "
      + "into the building."));
    add_item(({"arch", "archway", "entrance", "doors", "door", }), BSN(
        "A large archway is leading into the building of the "
      + "Adventurers' Guild. The arch itself was made from larger "
      + "stone slabs than the walls, fitted together to form half "
      + "a circle over the entrance. There are no doors blocking the "
      + "passage through the archway."));

    add_exit(PELAR_DIR + "street/statue",   "north",0);
    add_exit(PELAR_DIR + "street/sroad5",   "southeast",0);
    add_exit(PELAR_DIR + "misc/pelguild",   "south",0);
    add_exit(PELAR_DIR + "street/plaza",    "west",0);
}
