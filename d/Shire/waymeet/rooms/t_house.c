/* 
 *Farmhouse for Waymeet
 *
 * --Raymundo, Mar 2020
 */
 
inherit "/d/Shire/std/room";


#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

#define OUTSIDE "_i_can_go_out_back"

void reset_shire_room();

//You can only go outside if you're working on the quest from Cair Andros
int
block_people()
{
	if(TP->query_prop(OUTSIDE))
	{
		write("The farmer gives you an approving nod as you head out back.\n");
		return 0;
	}
	else
	{
		write("You're going to need the farmer to open the door for you if "
			+ "you're going to get into the back yard.\n");
		return 1;
	}
}


void
create_shire_room()
{
	set_long("You stand inside a well-appointed farmhouse. The floor is "
		+ "made of cherry wood with thick rugs covering it. The walls are "
		+ "covered in tapestries depicting daily life in the Shire. Windows "
		+ "overlook the fields, making the room feel bright and airy. "
		+ "But over everything you notice the lingering smell of Pipeweed "
		+ "around the room.\n");
	set_short("Inside a Farmhouse");
	add_item( ({"window", "windows"}), "The windows are quite large and give "
		+ "a nice view outside. You could probably look out of them if you "
		+ "wanted. They are closed.\n");
	add_item("farmhouse", "You're inside the farmhouse.\n");
	add_item( ({"floor", "cherry wood"}), "The floor is made of rich cherry "
		+ "wood. You notice rugs on the floor.\n");
	add_item( ({"rug", "rugs"}), "The rugs are brown and green, and remind "
		+ "you of tobacco plants. They look expensive, and like they would "
		+ "feel soft if you touched them.\n");
	add_item("ceiling", "The ceiling is actually quite high for a hobbit "
		+ "farmhouse.\n");
	add_item( ({"wall", "walls"}), "The walls are solid and clean. They have "
		+ "tapestries hanging on them. You notice a door on the south wall. "
		+ "It's closed.\n");
	add_item( ({"tapestry", "tapestries"}), "@@exa_tapestry@@");
	add_item( ({"wall", "south wall"}), "The south wall has tapestries on "
		+ "it like the rest of the house. You also see a closed door that "
		+ "leads, you guess, toward the curing shed.\n");
	add_item( ({"door", "doors"}), "There is a door on the south wall, leading "
		+ "toward the curing shed. It's made of sturdy oak and closed tight. "
		+ "You'll need the farmer's permisson before you exit to the south.\n");
	add_room_tell("Wolves howl from the direction of the fields.");
	add_room_tell("Light from the windows flickers across the floor.");
	
	add_cmd_item( ({"room", "pipeweed", "tobacco"}), 
		"smell", "You smell the sweet scent of pipeweed.\n");
	add_cmd_item( ({"rug", "rugs"}), ({"touch", "feel"}), "As you touch the rug, "
		+ "your hand disappears into the soft fibers. This is a thick, expensive "
		+ "rug!\n");
	add_cmd_item( ({"window", "windows"}), ({"open", "unlock"}), 
		"The windows are shut tight. You cannot open them.\n");
	add_cmd_item( ({"door"}), "open", "You try to open the door, but the farmer "
		+ "stands between you and it. You don't feel welcome to open the door "
		+ "on your own.\n");
	add_prop(ROOM_I_INSIDE, 1);
	set_room_tell_time(200);
	add_npc(WAYM_NPC_DIR + "farmer");
	add_exit(WAYM_FIELD_DIR + "s_field12", "out");
	add_exit(WAYM_FIELD_DIR + "s_field12", "northeast", 0, 0, 1);
	add_exit(WAYM_ROOM_DIR + "back_yard", "south", block_people, 0, 1);
	add_exit(WAYM_ROOM_DIR + "back_yard", "exit", block_people, 0, 1);
	
		
}

void
reset_shire_room()
{

}

void
init()
{
	::init();
	add_action("do_window", "look");
	add_action("do_window", "l");
	
}

//what you see out of the window
string
window_string()
{
	return((WAYM_FIELD_DIR + "s_field12")->long_desc());
}

//lets you look out of the window
int
do_window(string str)
{
	if(str == "window" | str == "out window" | str == "out of window" | str == "windows" | str == "out windows" | str == "out of windows")
	{
		write("You look out of the window and see:\n" + window_string());
		say(QCTNAME(TP) + " looks out of the window.\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

//what you see when you look at tapestries.
string
exa_tapestry()
{
	write("On the tapestry you see ");
	int x = random(4);
	switch(x)
	{
		case 0:
		return("a hobbit digging through his larder, looking for something "
			+ "to eat for his second breakfast.\n");
		break;
		
		case 1:
		return("a hobbit mother holding her darling baby girl in a field "
			+ "of flowers.\n");
		break;
		
		case 2:
		return("hobbit children lighting off fireworks from Waymeet in "
			+ "celebration of a birthday!\n");
		break;
		
		case 3:
		return("thirteen dwarves sitting in a hobbit burrow, drinking ale "
			+ "and playing music.\n");
		break;	
		
		default:
		return("thirteen dwarves sitting in a hobbit burrow, drinking ale "
			+ "and playing music.\n");
		break;
	}
}