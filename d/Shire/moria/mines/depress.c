#include "defs.h"

object rat;

CONSTRUCT_ROOM
{
    set_short("Deep depression");
    set_long(
	"You are in a deep depression in front of a clammy passage. "+
	"The depression is filled with mire and pebbles.\n");
    add_item(({"mire","mud"}),
	"Filth and water probably created this mud, and now the depression "+
	"has collected enough mire to make this place slippery and miry.");
    add_item("pebbles",
	"Pebbles and small rocks lies in between the mud.\n");
    add_item("depression",
	"This is a hollow, or depression rather, in the mountain.");
    add_item("passage",
	"The clammy passage leads north.");
    NORTH("clampass");
    WEST("lowroom");
    reset();
}

RESET_ROOM
{
    if (!rat || !present(rat))
	{
	    rat = clone_object(MORIA_NPC + "rat");
	    rat -> move(TO);
	}
}
