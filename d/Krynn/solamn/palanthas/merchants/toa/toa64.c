/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tdoor, tguard1, tguard2;

void defend_door(object picker);

string
query_to_jail()
{
    return "southeast";
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
    SHORT("A corner corridor in the Tower of Arms");
    LONG("A corner corridor within the tower, the chink of armour and clump "
    + "of bootsteps echo from the corridors. An iron door is recessed into "
    + "the west wall.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");

    EXIT(TOA + "toa61", "northeast", 0, 0);
    EXIT(TOA + "toa63", "southeast", 0, 0);

    tdoor = clone_object(TOA + "doors/toa_constable_door43");
    tdoor->move(TO);

    reset_palan_room();
}

void
defend_door(object picker)
{
    if (tguard1 != 0)
    {
        if (random(6) == 1)
        {
            tguard1->command("asay annoy I hope no one tries to break in.");
        }
        tguard1->attack_func(picker);
    }

    if (tguard2 != 0)
    { 
        if (random(6) == 1)
        { 
            tguard1->command("asay annoy I hope no one tries to break in.");
        }
        tguard2->attack_func(picker);
    }
}