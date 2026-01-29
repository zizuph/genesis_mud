
/* 
	*A bathroom in the house of farmer Maggot
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit BASE_HOUSE;
inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("In a bathroom inside a small house");

	set_long(short() + ". There are two hobbit-sized " +
	"wash basins in the middle of the room. A mirror is " +
	"standing near the eastern wall, and a wooden rack " +
	"is placed next to the basins. The floor looks wet.\n");
	
	add_item(({"bathroom"}), "This is a modest-sized hobbit bathroom.\n");
	add_item(({"mirror"}), "It is nearly floor to ceiling in " +
	"length, which is not saying much considering the walls " +
	"barely reach six feet. It is set in a stand.\n");
	add_item(({"ceiling"}), "It is very low, barely six feet " +
	"from the floor.\n");
	add_item(({"floor"}), "The floor is damp here, evidence " +
	"of a recent bath.\n");
	add_item(({"walls", "wall"}), "Like the rest of the " +
	"house, the walls in here bulge outward, and are " +
	"white-washed. There is a large mirror near the " +
	"east wall.\n");
	add_item(({"east wall", "eastern wall"}), "There is a " +
	"mirror propped in a stand near the east wall. There " +
	"is also a small window set into the wall.\n");
	add_item(({"window", "slit"}), "This window is pretty small,  " +
	"nothing more than a mere horizontal slit in the wall " +
	"near the ceiling. Most likely it is a vent for steam " +
	"that eminates from basins during a bath.\n");
	add_item(({"stand", "wood"}), "It is a stand made of wood. " +
	"It is holding a long mirror, which is near the east " +
	"wall.\n");
	add_item(({"basin", "basins", "wash basin", "wash basins"}), "The " +
	"basins are sitting in the middle of the room. They look like " +
	"they are made from polished copper.\n");
	add_item(({"rack", "wooden rack"}), "The rack looks like it is used for holding towels or linen, but it is empty right now.\n");
	add_item(({"copper", "dents"}), "The copper on the basins are polished to a shine, but there are small dents in the metal.\n");
	
	set_add_rtells_house();
	
	add_exit(ROOM_DIR + "maggothall02", "west");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}
