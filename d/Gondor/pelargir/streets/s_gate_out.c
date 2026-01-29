inherit "/d/Gondor/pelargir/lib/out_gate.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("outside the south gate of Pelargir");
    set_long(BSN("The road from Linhir upon Gilrain and Dol Amroth "
      + "enters Pelargir here through the city's southern gate. "
      + "To both sides of the gate are mighty towers rising a "
      + "little over the top of the walls, commanding the plain "
      + "south of the city."));

    add_item(({"plain", }), BSN(
        "Southwest of the city walls lies a wide plain covered with "
      + "fields and green meadows. In the south and the east, the "
      + "plain ends on the bank of the mighty Anduin."));

    add_item(({"river", "rivers", }), BSN("There are two rivers "
      + "here: the mighty Anduin to the east and the south branch "
      + "of the Sirith that joins the Anduin here."));
    add_item(({"river anduin", "anduin", }), BSN(
        "The Anduin, mightiest of rivers of Middle Earth, languidly flows "
      + "towards its mouths just east of city and plains. So far south, "
      + "the stream has become so wide that the opposite bank is just "
      + "a green line beyond a wide band of water."));

    add_item(({"road", }), BSN("The road to Linhir upon Gilrain and Dol "
      + "Amroth crosses the Sirith over an old stone bridge and runs "
      + "southwest on the other bank of the river."));

    add_item(({"sirith", "river", "river sirith", "branch", 
        "southern branch", }), BSN(
        "The city of Pelargir lies in between the two arms into "
      + "which the Sirith river splits just before joining the "
      + "Anduin. The larger and southern branch is just south "
      + "of here, while to the west, the city walls have been "
      + "built right onto the northern bank of the river."));
    add_item(({"bridge", "stone bridge", "old bridge", "old stone bridge", }),
        BSN("The road crosses the Sirith on an old stone bridge "
      + "just outside the city walls. The bridge is wide enough "
      + "for ox carts to use it. It spans the river in three arches "
      + "that rest on the banks on both sides of the river and on "
      + "two mighty stone pillars built into the river."));

    add_exit(LEB_DIR + "sroad/sirithb", "southwest", 0, 2);

    create_gate("south");
}

