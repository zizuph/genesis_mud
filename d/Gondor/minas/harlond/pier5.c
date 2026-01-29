inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#ifndef PELARGIR_OPEN
object  ship;
void
reset_room()
{
    if (objectp(ship))
        return;
    (ship = clone_object(SHIP_DIR + "ship5"))->start_ship();
}
#endif

void
create_room()
{
  set_short("the south pier of the harbour area of Minas Tirith");
  set_long(BSN("You are on a pier reaching out into the Anduin River. At " +
    "this pier ships from Pelargir land, loading goods and passengers. " +
#ifndef PELARGIR_OPEN
    "Now and then a large merchant vessel travelling to the " +
    "distant land of Kalad docks here as well. " +
#endif
    "The main harbour area, named Harlond, is to the northeast, with its " +
    "warehouses and bustling shipping-activity. "));
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit(MINAS_DIR+"harlond/pier","northeast",0);
  add_exit(MINAS_DIR + "harlond/warehouse1","north",0);
  add_item("pier","The pier is the southmost pier of the Harlond. The southbound\n"+
    "river-traffic uses this pier for loading and unloading.\n");
  add_item(({"wall","rammas","rammas echor"}), BSN(
    "To the north, you can see the great outer wall of Minas " +
    "Tirith, the Rammas Echor, surrounding the city and the Pelennor " +
    "fields. "));
  add_item(({"harlond", "harbour", "warehouses"}), BSN(
    "The main harbour area is to the northeast. You can see many " +
    "piers there, and warehouses close to them, full of cargoes " +
    "brought to the Harlond from the great sea-port Pelargir, from " +
    "Lebennin, Belfalas, and countries farther away. "));
  add_item(({"anduin","river","water"}), BSN(
    "The mighty river Anduin runs has a great bend here. It " +
    "flows down from the east, turning southwards to its mouths " +
    "in the Bay of Belfalas here. In this bend, there is the " +
    "Harlond, the harbour of Minas Tirith. The piers are built " +
    "far into the river, most of them running from west to east. "));

#ifndef PELARGIR_OPEN
    clone_object(SHIP_DIR + "kalad_sign")->move(TO);
#endif
}

