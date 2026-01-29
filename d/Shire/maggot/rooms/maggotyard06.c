
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
	area = "beside a quaint house in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "There is a small flower garden bordering the house, " +
	"filling the air with floral and herbal fragances. Small trees border " +
	"the fringes of the yard, and an old barn stands east of here.";
	
	add_item(({"flower garden", "garden"}), "The flower garden is " +
	"quite orderly, with a variety of plants, in a variety of colors. " +
	"Fragrances from the garden fill the air.\n");
	add_item(({"flower", "flowers", "plants"}), "There are too many different "+
	"kinds of flowers to count, creating a blanket of colors around the " +
	"outside of the house.\n");
	add_item(({"house"}), "The house is only a single story and very short, " +
	"reminiscent of hobbit holes one might see in other areas of the Shire.\n");
	add_item(({"barn", "old barn"}), "It is slightly higher than the house, faded red in " +
	"color. Sounds of animals can be heard coming from within.\n");
	add_item(({"yard"}), "The grass is kept very short, trimmed at the edges " +
	"near the garden. Trees line the yard.\n");
	add_item(({"trees", "small trees"}), "They are small, almost shrubs. Their foliage is very " +
	"green.\n");
	add_item(({"foliage", "leaves"}), "The leaves are a healthy shade of green\n");
	/*add_item(({"wall"}), "Upon closer inspection, there appears to be a loose " +
	"board in the wall. It hangs out from the wall a little.\n");
	add_item(({"board"}), "It is sticking out from the wall a little, but still " +
	"quite firmly attached to the house. It looks climbable.\n");*/
	
	set_add_rtells_yard();
	
	add_std_herbs("meadow");
	
	add_exit(ROOM_DIR + "maggotyard07", "north");
	add_exit(ROOM_DIR + "maggotyard05", "south");
		
	reset_shire_room();
}

void reset_shire_room()
{
	
}

void init()
{
	::init();
	//add_action("climb_board", "climb");
	add_action("pull_weeds", "weed");
}

/*Function name: climb_board
*Description: Allows a player to go from the yard to the roof. Blocks if the 
*player is mounted.
*/
/*int climb_board(string str)
{
	if (this_player()->query_prop(LIVE_O_STEED))
        {
            write("You must dismount your steed before climbing the tree.\n");
            return 1;
        }

        if(str == "board")
        {
		this_player()->catch_msg("You put your foot on the board and " +
		"scamper up onto the roof.\n");
		say(QCTNAME(this_player()) + " puts " + HIS_HER(this_player()) + " foot " +
		"on a loose board on the wall of the house and scampers up onto the roof.\n");
		this_player()->move_living("M", ROOM_DIR + "maggotroof01", 1);
		tell_room(ENV(this_player()), QCTNAME(this_player()) + " arrives from below.\n",this_player());
		return 1;
        }
        else 
        {
            write("Climb what?\n");
            return 1;
        }
    
}*/

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