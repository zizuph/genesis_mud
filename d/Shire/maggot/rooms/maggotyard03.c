
/* 
	*A yard, just outside farmer Maggot's house
	*Altrus, 
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define WEED_QUEST "_picking_weeds"
#define WEED_ONE "_weed_garden_one"
#define WEED_TWO "_weed_garden_two"
#define WEED_THREE "_weed_garden_three"
#define WEED_FOUR "_weed_garden_four"

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
	"the fringe of the yard. There is an old barn northeast of here. " +
	"There is a round window set into the front of the house here.";
	
	add_item(({"window"}), "As you look inside the window, you " +
	"can make out a clean room, with what looks like a bed and " +
	"and a nightstand, although you can not see them very well.\n");
	add_item(({"furniture", "bed", "nightstand"}), "You can not see " +
	"it very well from outside.\n");
	
	set_add_yard();
	set_add_rtells_yard();
	
	add_std_herbs("meadow");
	
	add_exit(ROOM_DIR + "maggotyard04", "east");
	add_exit(ROOM_DIR + "maggotyard01", "west");
		
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
*adds a prop to player.
*/
int pull_weeds(string str)
{
	if(str == "garden" || str == "flower garden")
	{
		if(TP->query_prop(WEED_QUEST))
		{
			if(!TP->query_prop(WEED_TWO))
			{
				TP->add_prop(WEED_TWO, 1);
				TP->catch_msg("You pull some weeds from among the flowers.\n");
				say(QCTNAME(TP) + " pulls some weeds from the flower garden.\n");
				if(TP->query_prop(WEED_ONE) && TP->query_prop(WEED_TWO) && TP->query_prop(WEED_THREE) && TP->query_prop(WEED_FOUR))
				TP->catch_msg("The garden looks fairly weed-free now!\n");
			}
			
			else
				TP->catch_msg("There aren't any more weeds for you to pull here.\n");
				
			return 1;
		}
		
		else
			TP->catch_msg("Why would you want to weed the garden?\n");
			
		return 1;
	}
	
	else
		TP->catch_msg("Weed what? The garden?\n");
		
	return 1;
}