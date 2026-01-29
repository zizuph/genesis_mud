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
    return "down";
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
    LONG("A landing atop a spiral staircase in the Tower of Arms, the "
    + "chink of armour and clump of bootsteps echo from the corridors. "
    + "The stairs descend from here, and an iron door is set into the "
    + "east wall.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here. "
    + "To the west, rows of barracks extend.\n");
    ITEM(({"stair", "stairs"}), "A spiral staircase of marble rises "
    + "and descends from here.\n");

    EXIT(TOA + "toa61", "northwest", 0, 0);
    EXIT(TOA + "toa63", "southwest", 0, 0);
    EXIT(TOA + "toa65", "west", 0, 0);
    EXIT(TOA + "toa70", "up", 0, 0);
    EXIT(TOA + "toa55", "down", 0, 0);

    tdoor = clone_object(TOA + "doors/toa_confis_door41");
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
    if (tguard1 != 0)
    {
        if (random(6) == 1)
        { tguard1->command("asay annoy I hope no one tries to break in."); }
        tguard1->attack_func(picker);
    }

    if (tguard2 != 0)
    { 
        if (random(6) == 1)
        { tguard1->command("asay annoy I hope no one tries to break in."); }
        tguard2->attack_func(picker);
    }
}