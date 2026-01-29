
/* 
	*A yard, just outside farmer Maggot's house
	*Altrus, 
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define WEED_ONE 		"_weed_garden_one"
#define WEED_TWO		"_weed_garden_two"
#define WEED_THREE		"_weed_garden_three"
#define WEED_FOUR 		"_weed_garden_four"
#define WEED_QUEST 		"_picking_weeds"
#define BRACE_PROP 		"_finding_bracelets_beads"
#define LOOK_ONE		"_checked_garden_once"
#define PROP_M			"_found_m_bead"

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
	extraline = "There is a small flower garden bordering the house, filling the air with floral and herbal fragances. Small trees border the fringes of the yard while an old barn stands northeast of here. There is a round window set into the front of the house here.";
	
	add_item(({"window"}), "As you look inside the window, you can make out a clean room, with some comfortable looking furniture.\n");
	add_item(({"furniture"}), "You can not see it very well from outside.\n");
	add_item(({"flower garden", "garden"}), "@@look_garden");
	add_item(({"flower", "flowers", "plants"}), "There are too many different kinds of flowers to count, creating a blanket of colors around the outside of the house.\n");
	add_item(({"house"}), "The house is only a single story and very short, reminiscent of hobbit holes one might see in other areas of the Shire.\n");
	add_item(({"barn", "old barn"}), "It is slightly higher than the house, faded red in color. Sounds of animals can be heard coming from within.\n");
	add_item(({"yard"}), "The grass is kept very short, trimmed at the edges near the garden. Trees line the yard.\n");
	add_item(({"trees", "small trees"}), "They are small, almost shrubs. Their foliage is very green.\n");
	add_item(({"foliage", "leaves"}), "The leaves are a healthy shade of green.\n");
	
	set_add_rtells_yard();
	
	add_std_herbs("meadow");
	
	add_exit(ROOM_DIR + "maggotyard01", "east");
	
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
			if(!TP->query_prop(WEED_ONE))
			{
				TP->add_prop(WEED_ONE, 1);
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

string look_garden()
{
	if(!TP->query_prop(BRACE_PROP))
	{
		return "The flower garden is quite orderly, with a variety of plants, in a variety of colors. Fragrances from the garden fill the air.\n";
	}
	
	if(TP->query_prop(PROP_M))
	{
		return "The flower garden is quite orderly, with a variety of plants, in a variety of colors. Fragrances from the garden fill the air.\n";
	}
	
	if(!TP->query_prop(LOOK_ONE))
	{
		TP->add_prop(LOOK_ONE, 1);
		return "The flower garden is quite orderly, with a variety of plants, in a variety of colors. Something in the garden catches your eye. Maybe you should get a closer look.\n";
	}
	
	if(TP->query_prop(LOOK_ONE))
	{
		TP->remove_prop(LOOK_ONE);
		TP->add_prop(PROP_M, 1);
		clone_object("/d/Shire/maggot/obj/bead_m.c")->move(TP);
		return "Yes! There was something, hidden amongst the flowers. You find a small bead and pick it up.\n";
	}
}
	