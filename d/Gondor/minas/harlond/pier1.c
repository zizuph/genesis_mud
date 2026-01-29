inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
inherit "/d/Genesis/gsl_ships/lib/pier";

object  ship;
int     ir;

void
reset_room()
{
    if (objectp(ship))
        return;

#ifndef PELARGIR_OPEN
    ship = clone_object(SHIP_DIR + "ship");
    ship->start_ship();
#endif
}

void
create_room()
{
    object  sign;

  set_short("a pier in the Harlond, the harbour of Minas Tirith");
  set_long(BSN("You are on a pier reaching out into the Anduin River. At "
    + "this pier ships from Pelargir land, loading and unloading goods "
    + "and passengers. "
#ifndef PELARGIR_OPEN
    + "Now and then ships from the distant town Sparkle dock here as well. "
#endif
    + "The main harbour area with its warehouses and "
    + "bustling shipping-activity continues to the north, to the south "
    + "there is one more pier. To the northwest, you can see the Rammas "
    + "Echor, the outer wall of Minas Tirith. "));
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit(MINAS_DIR + "harlond/pier4",      "northeast",0);
  add_exit(MINAS_DIR + "harlond/pier",       "southwest");
  add_exit(MINAS_DIR + "harlond/warehouse3", "north",0);
  add_item("pier",BSN("This is a pier in the central parts of the "
    + "Harlond. The southbound river-traffic and the ship from "
    + "Sparkle use this pier for loading and unloading. "));
  add_item(({"wall","rammas","rammas echor"}), BSN(
    "To the northwest, you can see the great outer wall of Minas " +
    "Tirith, the Rammas Echor, surrounding the city and the Pelennor " +
    "fields. ")); 
  add_item(({"harlond", "harbour", "warehouses"}), BSN(
    "The main harbour area extends to the north. You can see many " +
    "piers there, and warehouses close to them, full of cargoes " +
    "brought to the harlond from the great sea-port Pelargir, from " +
    "Lebennin, Belfalas, and countries farther away. "));
  add_item(({"anduin","river","water"}), BSN(
    "The mighty river Anduin runs has a great bend here. It " +
    "flows down from the east, turning southwards to its mouths " +
    "in the Bay of Belfalas here. In this bend, there is the " +
    "Harlond, the harbour of Minas Tirith. The piers are built " +
    "far into the river, most of them running from west to east. "));

  /*
    sign = clone_object(SHIP_DIR + "sparkle_sign");
    sign->set_file(SHIP_DIR + "pelargir.txt");
    sign->move(TO);
    clone_object(SHIP_DIR + "sparkle_sign")->move(TO);
  */
    add_pier_entry(MASTER_OB(TO), "Harlond", "Connection to Pelargir");
    initialize_pier();
    reset_room();
}

