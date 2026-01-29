/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tguard1, tguard2;

string
query_to_jail()
{
    return "east";
}

void
reset_palan_room()
{
    if (!objectp(tguard1))
    {
        tguard1 = clone_object(TOA + "living/toa_guard_nude");
        tguard1->move(TO);
    }
    if (!objectp(tguard2))
    {
        tguard2 = clone_object(TOA + "living/toa_guard_nude");
        tguard2->move(TO);
    }
}

void
create_palan_room()
{
    SHORT("A barracks in the Tower of Arms");
    LONG("A barracks in the Tower of Arms, the chink of armour and clump of "
    + "bootsteps echo from the corridors. A few of barracks are located "
    + "here.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here. "
    + "There are a few barracks in this area.\n");

    EXIT(TOA + "toa65n", "north", 0, 0);
    EXIT(TOA + "toa62", "east", 0, 0);
    EXIT(TOA + "toa65s", "south", 0, 0);
    EXIT(TOA + "toa65w", "west", 0, 0);

    reset_palan_room();
}
