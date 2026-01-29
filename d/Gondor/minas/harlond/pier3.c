inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    object  sign;

  set_short("the south pier of the harbour area of Minas Tirith");
  set_long("You are on a pier reaching out into the Anduin River. " +
//    "At this pier, a ship from the distant land of Grey Havens lands here. " +
    "The main harbour area, named " +
    "Harlond, is to the northwest, with its warehouses and bustling " +
    "shipping activity. The pier extends east and west.\n");
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit(MINAS_DIR + "harlond/pier2", "east");
  add_exit(MINAS_DIR + "harlond/pier", "west");
  add_item("pier","The pier is the southmost pier of the Harlond.\n" +
    "It is for loading and unloading ships.\n");


//    sign = clone_object(SHIP_DIR + "grey_havens_sign");
//    sign->set_file(SHIP_DIR + "grey_havens.txt");
//    sign->move(TO);

}
