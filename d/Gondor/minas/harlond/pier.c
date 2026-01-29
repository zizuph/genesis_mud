inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
  set_short("The south pier of the harbour area of Minas Tirith");
  set_long(BSN("You are on a pier reaching out into the Anduin River. At " +
    "this pier ships from Pelargir land, loading goods and passengers. " +
#ifndef PELARGIR_OPEN
    "Now and then a transport galleon travelling to the " +
    "Greyhavens, to the island of Gont, and to the distant town " +
    "of Sparkle docks here as well. " +
#endif
    "The main harbour area, named Harlond, is to the north, with its " +
    "warehouses and bustling shipping-activity. "));
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit(MINAS_DIR + "harlond/harlond2","north",0);
  add_exit(MINAS_DIR + "harlond/pier1","northeast",0);
  add_exit(MINAS_DIR + "harlond/pier3", "east");
  add_exit(MINAS_DIR + "harlond/pier5","southwest",0);
  add_item("pier","This pier is the southmost pier of the Harlond, save for the\n"+
    "pier southwest of here. The southbound river-traffic uses this pier\n"+
    "for loading and unloading.\n");
  add_item(({"wall","rammas","rammas echor"}), BSN(
    "To the north, you can see the great outer wall of Minas " +
    "Tirith, the Rammas Echor, surrounding the city and the Pelennor " +
    "fields. "));
  add_item(({"harlond", "harbour", "warehouses"}), BSN(
    "The main harbour area is to the north. You can see many " +
    "piers there, and warehouses close to them, full of cargoes " +
    "brought to the Harlond from the great sea-port Pelargir, from " +
    "Lebennin, Belfalas, and countries farther away. "));
  add_item(({"anduin","river","water"}), BSN(
    "The mighty river Anduin runs has a great bend here. It " +
    "flows down from the east, turning southwards to its mouths " +
    "in the Bay of Belfalas here. In this bend, there is the " +
    "Harlond, the harbour of Minas Tirith. The piers are built " +
    "far into the river, most of them running from west to east. "));

/*
    clone_object(SHIP_DIR + "circle_sign")->move(TO);
*/
}

