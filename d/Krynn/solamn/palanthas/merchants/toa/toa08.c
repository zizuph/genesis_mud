/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tguard1, tguard2;

string
query_to_jail()
{
    return "north";
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
    LONG("Marble corridors extend through the tower from here. The chink of "
    + "armour and clump of bootsteps echo about.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");

    EXIT(TOA + "toa02", "north", 0, 0);
    EXIT(TOA + "toa07", "east", 0, 0);
    EXIT(TOA + "toa09", "northwest", 0, 0);
    EXIT(TOA + "toa25", "up", 0, 0);
    EXIT(TOA + "toaL03", "down", 0, 0);

    reset_palan_room();
}
