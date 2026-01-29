
/* 
	*A yard, just outside farmer Maggot's house
	*Altrus, 
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define WEED_QUEST "_picking_weeds"

inherit BASE_YARD;
inherit AREA_ROOM;

void make_npcs();

object maghob;

public void
create_area_room()
{
	areadesc = "orderly yard";
	area = "behind a quaint house in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "There is a small flower garden bordering the house, filling the air with floral and herbal fragances. Small trees border the fringes of the yard, hiding an old barn east of here. ";
	
	set_add_yard();
	set_add_rtells_yard();
	
	add_std_herbs("meadow");
	
	add_exit(ROOM_DIR + "maggotyard06", "south");
	add_exit(ROOM_DIR + "maggotyard08", "west");
		
	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

void make_npcs()
{
	if(!maghob)
	{
		maghob = clone_object(NPC_DIR + "rosemary");
		maghob->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(maghob->query_nonmet_name()))+ " walks around the yard, looking very worried.\n");
	}
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