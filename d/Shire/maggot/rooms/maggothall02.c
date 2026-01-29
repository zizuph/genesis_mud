
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
	"just right. To the west you can hear sounds of " +
	"pots clanging and loud muttering; it must be a " +
	"kitchen. East of here is what looks to be a " +
	"bathroom.\n");
	
	add_item(({"kitchen"}), "To the west is what looks like a kitchen. Something smells very appetizing coming from that direction.\n");
	add_item(({"bathroom"}), "To the east is a bathroom, but from where you are standing you can not see much in there.\n");
	add_item(({"hallway", "hall"}), "This is a short hallway inside a quaint farmhouse.\n");
	
	set_add_house();
	set_add_rtells_house();
	
	add_exit(ROOM_DIR + "maggotyard09", "north");
	add_exit(ROOM_DIR + "maggothall01", "south");
	add_exit(ROOM_DIR + "maggotkitchen", "west");
	add_exit(ROOM_DIR + "maggotbath", "east");

	reset_shire_room();
}

void reset_shire_room()
{
	
}


