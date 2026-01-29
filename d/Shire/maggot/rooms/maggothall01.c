
/* 
	*A hallway in the house of farmer Maggot
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit BASE_HOUSE;
inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("In a hallway inside a small house");

	set_long(short() + ". The walls bow outward, in the same " +
	"style that might be seen in a hobbit hole. The " +
	"ceiling is very low, although, to a hobbit it is " +
	"just right. West of here there is a room that " +
	"appears to be a parlor of some sort. East leads " +
	"to a bedroom. There are hooks on the wall for " +
	"visiting hobbits to hang their overcoats.\n");
	
	add_item(({"bedroom"}), "Although from here you can not see much, there appears to be a bedroom through the door to the east.\n");
	add_item(({"parlor"}), "To the west of here is a parlor.\n");
	add_item(({"hallway", "hall"}), "This is a short hallway inside a quaint farmhouse.\n");
	add_item(({"hooks", "coat hooks"}),"The hooks are made of brass and stylishly cast in floral patterns.\n");
	add_item(({"brass"}), "The brass hooks are cast in floral patterns.\n");
	add_item(({"patterns", "floral patterns"}), "Although the patterns are rather crudely cast, the hooks are still a tasteful addition to the walls.\n");
	
	set_add_house();
	set_add_rtells_house();
	
	add_exit(ROOM_DIR + "maggotyard01", "south");
	add_exit(ROOM_DIR + "maggothall02", "north");
	add_exit(ROOM_DIR + "maggotparlor", "west");
	add_exit(ROOM_DIR + "maggotbed", "east");

	reset_shire_room();
}

void reset_shire_room()
{
	
}


