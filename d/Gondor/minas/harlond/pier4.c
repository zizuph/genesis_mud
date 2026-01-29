inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
  set_short("a pier in the Harlond, the harbour of Minas Tirith");
  set_long(BSN("You are on a pier reaching out into the Anduin River. At "
    + "this pier ships from Pelargir land, loading and unloading goods "
    + "and passengers. The main harbour area with its warehouses and "
    + "bustling shipping-activity continues to the north and the south. "
    + "To the north, you can enter an empty warehouse, to the northwest there "
    + "is an office building, probably accommodating the harbour master. " 
    + "Behind it, you can see the Rammas Echor, the outer wall of Minas Tirith. "));
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit(MINAS_DIR + "harlond/pier1","southwest",0);
  add_exit(MINAS_DIR + "harlond/warehouse2","north",0);
  add_exit(MINAS_DIR + "harlond/hoffice","northwest","@@check_rat");
  add_item("pier",BSN("This is a pier in the central parts of the "
    + "Harlond. The southbound river-traffic uses this pier for loading and unloading. "));
  add_item(({"wall","rammas","rammas echor"}), BSN(
    "To the northwest, you can see the great outer wall of Minas " +
    "Tirith, the Rammas Echor, surrounding the city and the Pelennor " +
    "fields. ")); 
  add_item(({"harlond", "harbour", "warehouses"}), BSN(
    "The main harbour area extends to the north and the south. You can see many " +
    "piers there, and warehouses close to them, full of cargoes " +
    "brought to the harlond from the great sea-port Pelargir, from " +
    "Lebennin, Belfalas, and countries farther away. "));
  add_item(({"warehouse"}), BSN(
    "It is an old and empty warehouse. Probably the traffic on the " +
    "river isn't as much any more as it once must have been. "));
  add_item(({"office","building","office building"}), BSN(
    "Over the entrance to the building to the northeast you can see "
    + "the words 'Harbour Master' written in black paint. "
    + "The building seems to contain offices. "));
  add_item(({"anduin","river","water"}), BSN(
    "The mighty river Anduin runs has a great bend here. It " +
    "flows down from the east, turning southwards to its mouths " +
    "in the Bay of Belfalas here. In this bend, there is the " +
    "Harlond, the harbour of Minas Tirith. The piers are built " +
    "far into the river, most of them running from west to east. "));
}

int
check_rat()
{
  return !(interactive(TP));
}

