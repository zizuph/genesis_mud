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
    SHORT("A corridor in the Tower of Arms");
    LONG("A corridor in the Tower of Arms, the chink of armour and clump of "
    + "bootsteps echo from the corridors. Stairs spiral up to the west.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");
    ITEM(({"stair", "stairs"}), "A spiral staircase of marble rises "
    + "from the corridor west.\n");

    EXIT(TOA + "toa42", "north", 0, 0);
    EXIT(TOA + "toa44", "south", 0, 0);
    EXIT(TOA + "toa55", "west", 0, 0);

    reset_palan_room();
}
