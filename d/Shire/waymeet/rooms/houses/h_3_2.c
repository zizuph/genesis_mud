/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A medium-income hobbit hole
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>


inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

int is_lamp = 1;

void reset_shire_room();

void
is_light()
{
	add_prop(ROOM_I_LIGHT, 1);
}

void
create_hobbit_room()
{
	set_short("In the Hallway");
	
	set_long("This hallway leads from the foyer to the kitchen, which makes "
		+ "it quite an important hallway indeed, given a hobbit's love for "
		+ "food! All types of delicious smells eminate from the south, and "
		+ "if you were to take the time to smell them, your mouth would "
		+ "likely start to water. There are no windows here. "
		+ "@@lamp_status@@" + "\n");
	
	add_item( ({"oil", "puddle", "oil puddle", "puddle of oil"}),
		"@@oil_puddle@@");
	add_item( "food", "You should go south into the kitchen if you want to "
		+ "see what's cookin'\n");
	add_item( "kitchen", "The kitchen is south.\n");
	add_item( ({"window", "windows"}), "There are no windows here.\n");
	add_item( ({"sconce", "lamp"}), "@@exa_sconce@@");
	
	add_walls();

	add_exit(WAYM_HOUSE_DIR + "h_3_1", "west"); 	//Foyer	
	add_exit(WAYM_HOUSE_DIR + "h_3_3", "south");	//Kitchen
	add_exit(WAYM_HOUSE_DIR + "h_3_4", "north");	//Dining room
	add_exit(WAYM_HOUSE_DIR + "h_3_5", "east"); 	// Hallway
}

void
reset_shire_room()
{
	is_lamp = 1;
	is_light();
}

void
init()
{
	::init();
	add_action("smell_smells", "smell");
	add_action("grasp_lamp", "grasp");
	add_action("grasp_lamp", "grab");
	add_action("grasp_lamp", "take");
	add_action("grasp_lamp", "break");
	add_action("grasp_lamp", "get");
	
	
}

//You can break the lamp off the walk and use it.
int
grasp_lamp(string str)
{
	if(is_lamp == 0)
	{
		write("There is no lamp in the sconce!\n");
		return 1;
	}
	if(str == "lamp" | str == "lamp from wall" | str == "lamp from sconce")
	{
		write("You reach up and grasp the lamp. Too late, you realize that "
			+ "it wasn't affixed very well to the sonce. The lamp breaks "
			+ "off in your hand! You fumble the lamp and spill oil all over "
			+ "the floor.\n");
		say(QCTNAME(TP) + " reaches up and grabs the lamp. It breaks off "
			+ "in " + HIS_HER(TP) + " hand! " + CAP(HE_SHE(TP)) 
			+ " fumbles the lamp and spills oil all over the floor.\n");
		object obj;
		obj = clone_object("/d/Gondor/common/obj/oil_lamp.c");
		obj->move(TP);
		add_prop(ROOM_I_LIGHT, -1);
		is_lamp = 0;
		write("\nYou get an " + obj->query_short() + " from the sconce.\n");
		return 1;
	}
	else
	{
		return 0;
	}
}
		

//a silly emote allowing you to smell what the kitchen is cooking
int
smell_smells(string str)
{
	if(!strlen(str))
	{
		write("You inhale through your nose and cannot help but notice how "
			+ "wonderful the food cooking in the kitchen smells! You start "
			+ "salivating at the thought of such a yummy, yummy meal.\n");
		say(QCTNAME(TP) + " inhales through " + HIS_HER(TP) + " nose and "
			+ "immediately begins salivating--no, salivating isn't quite "
			+ "the right word--" + HE_SHE(TP) + "begins drooling. The food "
			+ "from the kitchen must smell really good!\n");
		return 1;
	}
	if(str == "smells" | str == "delicious smells")
	{
		write("You inhale through your nose and cannot help but notice how "
			+ "wonderful the food cooking in the kitchen smells! You start "
			+ "salivating at the thought of such a yummy, yummy meal.\n");
		say(QCTNAME(TP) + " inhales through " + HIS_HER(TP) + " nose and "
			+ "immediately begins salivating--no, salivating isn't quite "
			+ "the right word--" + HE_SHE(TP) + "begins drooling. The food "
			+ "from the kitchen must smell really good!\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

//additional description for the long description.
string
lamp_status()
{
	if(is_lamp == 1)
	{
		return("However a lamp is attached to a sconce on the wall, casting "
			+ "light about the room.\n");
	}
	else
	{
		return("However, there is a sconce on the wall. "
			+ "Unfortunately, the sconce is empty, its lamp having been "
			+ "broken off. You see a puddle of lamp oil on the floor.\n");
	}
}

//gives the description of the puddle of oil on the floor.
string
oil_puddle()
{
	if(is_lamp == 1)
	{
		return("You find no puddle.\n");
	}
	else
	{
		return("This is a puddle of lamp oil. Someone must have spilled it "
			+ "all over the floor when they stole the lamp from the "
			+ "sconce!\n");
	}
}

//You can examine the sconce!
string
exa_sconce()
{
	if(is_lamp == 1)
	{
		return("You see a sconce attached to the wall. It gently holds a "
			+ "lamp. The lamp sheds light along the hallway, keeping "
			+ "everything bright and cheerful.\n");
	}
	else
	{
		return("You see a sconce attached to the wall. Looking closely "
			+ "you see a broken bolt that likely used to hold a lamp "
			+ "in place. It's a shame, really, because a lamp here "
			+ "would illuminate the entire hallway.\n");
	}
}