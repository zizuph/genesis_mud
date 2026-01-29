
/* 
	*A yard, just outside farmer Maggot's house
	*Altrus, 
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define WEED_QUEST "_picking_weeds"

inherit BASE_YARD;
inherit AREA_ROOM;

public void
create_area_room()
{
	areadesc = "orderly yard";
	area = "of a quaint house in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "There is a small flower garden bordering the house, " +
	"filling the air with floral and herbal fragances. Small trees border " +
	"the fringes of the yard, and an old barn stands northeast of here. " +
	"There is a gate at the edge of the yard.";
	
	add_item(({"gate"}), "It is a wooden gate, just wide enough to " +
	"for two people to walk through at once. It is propped open by " +
	"a medium sized rock.\n");
	add_item(({"rock"}), "This rock is roughly the size of a human fist. " +
	"It is being used to prop open the gate.\n");
	
	set_add_yard();
	set_add_rtells_yard();
	
	add_std_herbs("meadow");
	
	add_exit(ROOM_DIR + "maggotyard03", "east");
	add_exit(ROOM_DIR + "maggotyard02", "west");
	add_exit(ROOM_DIR + "maggothall01", "north");
	add_exit(ROOM_DIR + "maggotlane03", "south");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

void init()
{
	::init();
	add_action("pull_weeds", "weed");
}

/*
* Function name: pull_weeds
* Description  : pulls weeds from the garden as part of a quest (no items generated, just action),
*adds a prop to player. This particular room does not have any weeds however, but the action
*remains to keep the rooms consistent.
*/
int pull_weeds(string str)
{
	if(str == "garden" || str == "flower garden")
	{
		if(TP->query_prop(WEED_QUEST))
		{
			TP->catch_msg("There are not any weeds in this part of the flower garden.\n");
		}
		
		else
			TP->catch_msg("Why would you want to weed the garden?\n");
			
		return 1;
	}
	
	else
		TP->catch_msg("Weed what? The garden?\n");
		
	return 1;
}