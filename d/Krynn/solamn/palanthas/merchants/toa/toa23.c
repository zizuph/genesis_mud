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
    + "bootsteps echo from the corridors. An iron door is recessed into the "
    + "west wall.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");

    EXIT(TOA + "toa22", "north", 0, 0);
    EXIT(TOA + "toa24", "south", 0, 0);

    tdoor = clone_object(TOA + "doors/toa_lieutenant_door21");
    tdoor->move(TO);

    reset_palan_room();
}

void
auto_door()
{
    tdoor->reset_door();
}

void
defend_door(object picker)
{
    if (tguard1 != 0 && present(tguard1, TO))
    {
        if (random(6) == 1)
        {
            tguard1->command("asay annoy I hope no one tries to break in.");
        }
        tguard1->attack_func(picker);
    }

    if (tguard2 != 0 && present(tguard2, TO))
    { 
        if (random(6) == 1)
        {
            tguard1->command("asay annoy I hope no one tries to break in.");
        }
        tguard2->attack_func(picker);
    }
}