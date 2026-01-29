#include "defs.h"

object uruk1, uruk2;

CONSTRUCT_ROOM
{
    set_short("In the forechamber of the Uruk trolls!");
    set_long(
	"You are in the forechamber of the Uruk trolls!!\n"+
	"This is a round space or hollow with exits in the "+
	"south. In the north there is an opened door and in "+
	"the east a closed door.\n");
    add_item("door", "Which door, the open or the closed?");
    add_item(({"open","opened", "open door", "opened door"}),
	"It leads into a room.");
    add_item(({"closed","closed door"}),
	"It seems closed and locked, and you wouldn't try to "+
	"open it when the uruks are here!");
    SOUTH("uruks");
    EAST("prison");
    NORTH("ringroom");
    if (!uruk1 || !uruk2)
	make_uruks();
}

make_uruks()
{
    if (!uruk1)
	uruk1 = clone_object(MORIA_NPC+"uruk");
    if (!uruk2)
	uruk2 = clone_object(MORIA_NPC+"uruk");
    if (!present(uruk1, TO))
	uruk1->move(TO);
    if (!present(uruk2, TO))
	uruk2->move(TO);
}

get_back()
{
    uruk1->move(TO);
    uruk2->move(TO);
}

init()
{
    ::init();
    make_uruks();
}
