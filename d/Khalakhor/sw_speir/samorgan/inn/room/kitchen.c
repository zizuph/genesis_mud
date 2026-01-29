/**********************************************************************
 * - kitchen.c                                                      - *
 * -                                                                - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types
inherit "/d/Khalakhor/std/room";
#include "pit.c"

public void
create_khalakhor_room()
{
	set_short("A large kitchen");
	set_long("\n   This is a fairly large kitchen, which has a "+
	"roaring fire pit. There are a few servants rushing around "+
	"tending to the roasting meats that bask over the pit. There "+
	"are large shelves placed in the walls and you can see a cold "+
	"storage room off to the side.\n");
	add_item(({"room", "area", "kitchen"}), query_long);
	add_cmd_item("door", "open", "The door is locked "+
	"and you should be ashamed for trying to open it!\n");
	add_item(({"pit", "fire pit"}),
	"The fire pit has a fairly large fire in it. There is a "+
	"large metal skewer that houses meats on it. Which are "+
	"turned by servants so the meat is roasted evenly.\n");
	add_item(({"fire", "roaring fire", "flame", "flames"}),
	"The flames burn hot and dance majestically in the fire pit.\n");
	add_item(({"skewer", "metal skewer"}),
	"The skewer is large and made from a metal you are not "+
	"familiar with. It has large amount of meat on it.\n");
	add_item(({"meat", "skewered meat", "dragon", "red dragon", "red meat", "roasting meat", "roasting meats"}),
	"The meat on the skewer is quite large and red.\n");
	add_item(({"shelves", "shelf"}),
	"The shelves are filled with dry goods, spices, dishes, glasses "+
	"and mugs.\n");
	add_item(({"dry goods", "goods"}),
	"There various dry goods ranging from flour, sugar and salt.\n");
	add_item(({"spices", "spice", "jar", "jars"}),
	"There are way too many different spices for you examine, "+
	"but there is one large jar with a clearly written label, "+
	"'spice for dragon'.\n");
	add_item(({"torch", "torches"}),
	"The torches are placed securely in the walls and "+
	"cannot be removed.\n");
	add_item(({"wall", "walls"}),
	"The walls are made from a smooth dark stone.\n");
	add_item(({"cold room", "storage", "cold storage", "storage room", "cold storage  room"}),
	"The cold storage room is off to the side with the door firmly "+
	"closed.\n");
	add_item(({"door"}),
	"The door to the cold storage room is closed firmly. "+
	"You may not open it.\n");
	add_item(({"mug", "mugs"}),
	"The mugs are obviously for holding ale.\n");
	add_item(({"glass", "glasses"}),
	"The glasses are obviously for the wine.\n");
	add_item(({"plate", "plates"}),
	"These plates are obviously used for the food to be placed on.\n");
	add_item(({"salt", "sugar", "flour"}),
	"You see it sitting on the shelves.\n");
	add_item(({"servant", "servants"}),
	"The servants are busily working trying to prepare meals for guests.\n");
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 2);
	
	add_exit("inn", "south");
	add_exit("hall4", "up");
	add_fail(({"north", "west", "east", "northeast", "northwest", "southeast", "southwest"}),
	"You walked into a wall!\n"+
	"Ouch! That's gotta hurt!\n");
}

public void
init()
{
	::init();
	init_pit();
}
 