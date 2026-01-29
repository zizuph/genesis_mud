/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tguard1, tguard2;

string
query_to_jail()
{
    return "west";
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
    + "east.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here. "
    + "To the east, rows of barracks extend as far as you can see.\n");

    EXIT(TOA + "toa29n", "north", 0, 0);
    EXIT(TOA + "toa30", "east", 0, 0);
    EXIT(TOA + "toa29s", "south", 0, 0);
    EXIT(TOA + "toa27", "west", 0, 0);

    reset_palan_room();
}
