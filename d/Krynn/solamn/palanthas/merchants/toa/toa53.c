/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tguard1, tguard2;

string
query_to_jail()
{
    return "southwest";
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
    + "bootsteps echo from the corridors. A long corridor of barracks extends "
    + "southwest.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here. "
    + "To the east and west, rows of barracks extend as far as you can "
    + "see.\n");

    EXIT(TOA + "toa52", "southwest", 0, 0);

    reset_palan_room();
}
