/* 
 * A hobbit dwelling in Waymeet
 *
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

void reset_shire_room();
// an adjective for my_reflection() down below
string 
adj()
{
    return(this_player()->query_nonmet_name());
}

void
create_shire_room()
{
	set_short("In the Hallway");
	
	set_long("The hallway is more spacious than one would think. Even "
		+ "very fat dwarves could walk through here without bumping into "
		+ "the walls. A soft rug sits on the floor, and a painting hangs "
		+ "next to the doorway on the east wall.\n");
	

	add_walls();
	add_item( ({"doorway", "door way", "doorways", "door ways"}), 
		"There are two doorways, one to the east and one to the west.\n");
	add_item( ({"east doorway", "east door way"}), "To the east an open "
		+ "doorway leads into the kitchen. The food in there smells "
		+ "delicious.\n");
	add_item( ({"west doorway", "west door way"}), "To the west, an open "
		+ "doorway leads into a bedroom.\n");
	add_item( "east wall", "The east wall is covered in the same wood "
		+ "paneling as the other walls, and like the other walls it's clean. "
		+ "You notice a painting on the wall.\n");
	add_item("painting", "The painting has a gold-leaf covered frame and "
		+ "is covered with glass to protect it from dust. The subject of the "
		+ "painting is a young hobbit woman, wearing what must be her best "
		+ "dress. Her smile is both innocent and alluring, and it brings "
		+ "forth strong feelings in you.\nYou notice a reflection on the "
		+ "glass.\n");
	add_item("frame", "The frame is covered in gold-leaf. It must have been "
		+ "expensive!\n");
	add_item( ({"gold-leaf", "gold leaf"}), "Gold leaf that has been hammered "
		+ "until it's very thin. It can be used to cover anything--in this "
		+ "case, a picture frame.\n");
	add_item( "reflection", "@@my_reflection@@");
	add_item("rug", "This is a red and black rug. It sits in the middle of the "
		+ "hall, right in front of the painting. The rug looks like a very "
		+ "soft place to stand while you look at the painting.\n");
	
		
	add_cmd_item( ({"rug", "on rug"}), "stand", "You stand on the rug. It "
		+ "does seem like a nice place to stand indeed!\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	
	add_exit(WAYM_HOUSE_DIR + "h_1_1", "south");
	add_exit(WAYM_HOUSE_DIR + "h_1_3", "west");
	add_exit(WAYM_HOUSE_DIR + "h_1_4", "east");
	add_exit(WAYM_HOUSE_DIR + "h_1_5", "north");
		
}

void
reset_shire_room()
{
	
}

void
init()
{
	::init();
	add_action("smell_food", "smell");
	add_action("feel_rug", "feel");
	add_action("feel_rug", "touch");
	add_action("feel_rug", "fondle");

}

// Allows you to feel the rug. Also allows others to see you feeling the rug
int
feel_rug(string str)
{
	if(!strlen(str))
	{
		return 0;
	}
	if(str == "rug")
	{
		write("You bend down and touch the rug. Yes, it's a very soft "
			+ "rug indeed!\n");
		say(QCTNAME(TP) + " bends down and touches the rug with " +
			HIS_HER(TP) + " hand. Hmm....\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

// allows you to smell what's being cooked in the kitchen.
int
smell_food(string str)
{
	if(!strlen(str) | str == "food" | str == "kitchen")
	{
		write("You breathe deeply through your nose. You can smell delicious "
			+ "food cooking to the east. You sigh hungrily.\n");
		say(QCTNAME(TP) + " breathes deeply through " + HIS_HER(TP) 
			+ " nose. " + CAP(HE_SHE(TP)) + " sighs hungrily.\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

//You can see yourself staring back at yourself.
string
my_reflection()
{
	return("As you examine the reflection closely, you see a " + adj()
		+ " looking back at you.\n");
}