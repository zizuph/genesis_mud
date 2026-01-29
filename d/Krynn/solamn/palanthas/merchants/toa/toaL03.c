/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object tguard1, tguard2;

string
query_to_jail()
{
    return "up";
}

void
create_palan_room()
{
    SHORT("A corridor in the dungeon of the Tower of Arms");
    LONG("Marble corridors extend through the tower from here. Shadows "
    + "flicker, and the sound of water dripping can be heard nearby.\n");

    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");

    EXIT(TOA + "toaL01", "north", 0, 0);
    EXIT(TOA + "toa08", "up", 0, 0);

}
