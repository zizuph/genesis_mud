/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tdoor;

string
query_to_jail()
{
  return "down";
}

void
create_palan_room()
{
    SHORT("A spartan bedroom in the Tower of Arms");
    LONG("This bedroom has simple furnishings and a small bed. It is little "
    + "more than a coat closet in size. The chink of armour and clump of "
    + "bootsteps echo from the corridors. An iron door is set against the "
    + "east wall.\n");

    ITEM(({"furnishing", "furnishings", "bed"}), "The furnishings of this "
    + "small room are plain and functional. You rifle through them and find "
    + "nothing worth taking.\n");
    ITEM(({"corridor", "corridors"}), "Marble corridors are outside the "
    + "door.\n");

    EXIT(TOA + "toa_lieutenant01", "down", 0, 0);

    tdoor = clone_object(TOA + "doors/toa_lieutenant_door22");
    tdoor->move(TO);
}

void
auto_door()
{
    tdoor->reset_door();
}
