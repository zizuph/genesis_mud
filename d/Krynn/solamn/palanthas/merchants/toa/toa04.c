/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tguard1, tguard2;

string
query_to_jail()
{
    return "south";
}

void
reset_palan_room()
{
    if (!objectp(tguard1))
    {
        tguard1 = clone_object(TOA + "living/toa_guard");
        tguard1->move(TO);
    }
    if (!objectp(tguard2))
    {
        tguard2 = clone_object(TOA + "living/toa_guard");
        tguard2->move(TO);
    }
}

void
create_palan_room()
{
    SHORT("A corridor on the ground floor of the Tower of Arms");
    LONG("Marble corridors extend through the tower from here. An archway "
    + "opens north onto the fields of the Tower of Arms. The chink of "
    + "armour and clump of bootsteps echo about.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");

    EXIT(TOA + "toa_field01", "north", 0, 0);
    EXIT(TOA + "toa05", "east", 0, 0);
    EXIT(TOA + "toa02", "south", 0, 0);
    EXIT(TOA + "toa03", "southwest", 0, 0);
    EXIT(TOA + "toa21", "up", 0, 0);
    EXIT(TOA + "toaL02", "down", 0, 0);

    reset_palan_room();
}
