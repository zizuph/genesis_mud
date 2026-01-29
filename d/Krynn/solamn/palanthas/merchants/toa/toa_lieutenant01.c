/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

object lieutenant, tdoor;

string
query_to_jail()
{
    return "west";
}

void
reset_palan_room()
{
    if (!lieutenant)
    {
        lieutenant = clone_object(TOA + "living/toa_lieutenant");
        lieutenant->move(TO);
    }

    lieutenant->command("close door");
    lieutenant->command("lock door with key");
}

void
create_palan_room()
{
    SHORT("An officer's room on the ground floor of the Tower of Arms");
    LONG("A desk, folders of papers, and stacks of scrolls occupy this room. "
    + "In the corner is a weapon rack, armour chest, a woven mat, and a "
    + "few hand weights. Archways open into corridors from here, and an "
    + "iron door is set into the west wall.\n");

    ITEM(({"desk", "folder", "folders", "paper", "papers", "stack", 
           "stacks", "scroll", "scrolls"}), "These are the working items of "
    + "what appears to be a Lieutenant of the Constabulary of Palanthas.\n");
    ITEM(({"corridor", "corridors"}), "Marble corridors extend from here.\n");
    ITEM(({"weapon rack", "rack", "armour chest", "chest", "woven mat", "mat",
           "hand weights", "weight", "weights"}), "These are the personal "
    + "effects of a Constabulary officer.\n");

    EXIT(TOA + "toa_lieutenant_n", "north", 0, 0);
    EXIT(TOA + "toa_lieutenant_e", "east", 0, 0);
    EXIT(TOA + "toa_lieutenant_s", "south", 0, 0);
    EXIT(TOA + "toa_lieutenant20", "up", 0, 0);

    tdoor = clone_object(TOA + "doors/toa_lieutenant_door2");
    tdoor->move(TO);

    reset_palan_room();
}

void
auto_door()
{
    tdoor->reset_door();
}
