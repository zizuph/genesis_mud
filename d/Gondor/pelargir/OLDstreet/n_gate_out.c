inherit "/d/Gondor/pelargir/lib/out_gate.c";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("outside the north gate of Pelargir");
    set_long(BSN("The road that connects the Harlond and Minas Tirith "
      + "in the north with Pelargir reaches the northern city gate "
      + "of Pelargir here. To both sides of the gate are mighty towers "
      + "rising a little over the top of the walls, commanding the plain "
      + "north of the city."));

    add_item(({"plain", }), BSN(
        "North of the city walls lies a wide plain covered with fields "
      + "and green meadows. In the east, the plain ends on the west bank "
      + "of the mighty Anduin, while it looks as if it continues north "
      + "right up to the mountain chain that can be seen on the horizon."));

    add_anduin();

    add_item(({"mountain", "mountains", "mountain chain", "white mountains",
        "ered nimrais", }), BSN(
        "The mountains far north have white, snow covered peaks. These "
      + "must be the White Mountains of Gondor, the Ered Nimrais."));

    add_exit(LEB_DIR + "road/nr18", "north", 0);

    create_gate("north");
}

