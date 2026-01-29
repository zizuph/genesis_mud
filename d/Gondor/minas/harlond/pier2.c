inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  ship;

#ifndef PELARGIR_OPEN
void
reset_room()
{
    if (objectp(ship))
        return;

    ship = clone_object(SHIP_DIR + "ship2");
    ship->start_ship();
}
#endif

void
create_room()
{
  set_short("the southeast pier of the harbour area of Minas Tirith");
  set_long("You are on a pier reaching out into the Anduin River. At this pier\n"+
    "ships from Pelargir land, loading and unloading goods and passengers.\n"+
#ifndef PELARGIR_OPEN
    "Occasionally you spot strange slim ships arriving from Faerie.\n"+
#endif
    "The main harbour area, named Harlond, is to the northwest, with its\n"+
    "warehouses and bustling shipping-activity. The pier continues \n" + 
    "to the west.\n");
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit(MINAS_DIR + "harlond/pier3", "west");
  add_item("pier",BSN("You are on the southmost pier of the Harlond. The southbound "+
    "river-traffic uses this pier for loading and unloading. "));
  add_item(({"anduin","river","water"}), BSN(
    "The mighty river Anduin runs has a great bend here. It " +
    "flows down from the east, turning southwards to its mouths " +
    "in the Bay of Belfalas here. In this bend, there is the " +
    "Harlond, the harbour of Minas Tirith. The piers are built " +
    "far into the river, most of them running from west to east. "));
  add_item(({"wall","rammas","rammas echor"}), BSN(
    "To the northwest, you can see the great outer wall of Minas " +
    "Tirith, the Rammas Echor, surrounding the city and the Pelennor " +
    "fields. "));
  add_item(({"harlond", "harbour", "warehouses"}), BSN(
    "The main harbour area is farther to the northwest. You can see many " +
    "piers there, and warehouses close to them, full of cargoes " +
    "brought to the harlond from the great sea-port Pelargir, from " +
    "Lebennin, Belfalas, and countries farther away. "));

#ifndef PELARGIR_OPEN
    clone_object(SHIP_DIR + "faerie_sign")->move(TO);
    reset_room();
#endif
}


