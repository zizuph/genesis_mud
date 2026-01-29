#include "defs.h"

object rat;

CONSTRUCT_ROOM
{
    set_short("Dirty hole");
    set_long(
	"You are in a dirty hole. A filthy passage leads to the south, while "+
	"in the west there is a slimy room. There is a round opening in the north "+
	"wall.\n");
    add_item(({"floor","dirt"}),
	"The floor is covered in thick dirt.");
    add_item("passage",
	"It leads south and looks rather filthy.");
    add_item("opening",
	"It is round and leads into what seems to be a corridor.");
    add_item(({"walls","wall","ceiling"}),
	"The walls and the ceiling are also filled with dirt.");
    NORTH("corr6");
    SOUTH("clampass");
    WEST("slime");
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
