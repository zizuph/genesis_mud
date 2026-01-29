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


void reset_shire_room();

//A little flavor while walking down the hall.
int
block_people()
{
	if(TP->query_race_name() == "ogre")
	{
		write("\n\nYou start down the hallway but get stuck. This is "
		 + "a very small hallway, and you are a very wide " +
		 TP->query_nonment_name() + ".\n\n");
		say(QCTNAME(TP) + " tries to walk down the hallway, but "
			+ "quickly realizes that " + HE_SHE(TP) + " is far too "
			+ "wide to fit!\n");
		return 1;
	}
	if(TP->query_race() == "human" || TP->query_race() == "elf")
	{
		write("\n\nYou bang and bump your way down the hall, bouncing "
			+ "from one wall to another because it is all entirely too "
			+ "tight for you.\n\n");
		say(QCTNAME(TP) + " bangs and bumps " + HIS_HER(TP) 
			+ " way down the hallway, bumping from one wall to another. "
			+ "The hallway is obviously too small for " + HIM_HER(TP)
			+ ".\n");
		return 0;
	}
	else
	{
		write("As you walk down the hallway, it feels a little tight, "
			+ "but given your size, you have no problems here.\n");
		return 0;
	}
}

//The description of the reflection in the mirror
string 
adj()
{
    return("You gaze into the mirror and see a " +
        this_player()->query_nonmet_name() + " staring back at you.\n");
}

void
create_hobbit_room()
{
	set_short("In the Hallway");
	
	set_long("The hallway is surprisingly narrow, as if the architect of this "
		+ "smial wanted to save as much room as possible for the rooms "
		+ "themselves and thought hallways superfluous. A large mirror hangs "
		+ "on the wall, giving hobbits a chance to see how they look before "
		+ "they go out in public. Otherwise, this is just a way to move from "
		+ "one place to another, and is not at all fancy.\n");
	
	add_item( ({"mirror", "mirrors"}), "This is a very large mirror, taking "
		+ "up a goodly portion of the wall. It is of high quality, you "
		+ "notice, giving almost no distortion whatsoever for those who gaze "
		+ "into it.\n");
	add_cmd_item( ({"mirror", "mirrors", "into mirror", "in mirror", "into mirrors", "in mirrors"}), 
		({"gaze", "stare", "look", "glance", "ogle"}),
		"@@adj@@");
	add_cmd_item( ({"mirror", "mirrors"}), ({"polish", "clean"}), 
		"You polish the mirror, making it shine even more brightly.\n");
		
	add_walls();


	add_exit(WAYM_HOUSE_DIR + "h_4_1", "east"); //Foyer
	add_exit(WAYM_HOUSE_DIR + "h_4_5", "west", block_people,0,0); //Hallway
	add_exit(WAYM_HOUSE_DIR + "h_4_3", "north"); //study
	add_exit(WAYM_HOUSE_DIR + "h_4_4", "south"); //kitchen

}

void
reset_shire_room()
{
	
}

void
init()
{
	::init();

}
