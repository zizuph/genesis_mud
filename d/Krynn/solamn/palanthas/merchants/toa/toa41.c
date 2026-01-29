/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tguard1, tguard2;

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
    SHORT("A room with stairs in the Tower of Arms");
    LONG("A corridor with a stairway descending from here. The "
    + "chink of armour and clump of bootsteps echo from the corridors.\n");

    ITEM(({"stair", "stairs", "flight", "flights", "flight of stairs",
      "stairway"}), "A stairway descends from here. The steps "
    + "are worn but still nearly perfect and smooth. They have recently "
    + "been polished and gleam beautifully.\n");
    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");

    EXIT(TOA + "toa42", "east", 0, 0);
    EXIT(TOA + "toa48", "west", 0, 0);
    EXIT(TOA + "toa21", "down", 0, 0);

    reset_palan_room();
}
