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
    SHORT("A spiral stair in the Tower of Arms");
    LONG("A spiral staircase in the Tower of Arms, the chink of armour and "
    + "clump of bootsteps echo from the corridors. The stairs rise and "
    + "descend from here.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here. "
    + "To the east and west, rows of barracks extend as far as you can "
    + "see.\n");
    ITEM(({"stair", "stairs"}), "A spiral staircase of marble rises "
    + "and descends from here.\n");

    EXIT(TOA + "toa43", "east", 0, 0);
    EXIT(TOA + "toa62", "up", 0, 0);

    reset_palan_room();
}
