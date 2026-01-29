/* This was updated to include an item for a quest.
 * To that end, a closet was added, and a search 
 * feature, and the functionality of opening and 
 * closing doors.
 *
 * Raymundo, Jan 2020
 */


inherit "/d/Shire/eastroad/village/whit/whithouse";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/waymeet/defs.h"
#include <macros.h>

int closet_door = 0;
int pipe = 1; //for the quest in /d/Shire/eastroad/western/foam_mug_up

create_house()
{
   set_short("Hobbit house");
   set_long("This is the home of a family of hobbits. It is a single " +
      "room, as the family is quite poor, but it is nice and cheerful. " +
      "The room has a number of beds, a closet, "
	  + "and some chairs set around " +
      "the large table in the centre of the room. There is a large " +
      "cupboard against the wall, beside the window that lets light " +
      "into this house.\n");
   
   add_item( "closet", "The closet is set up against the west wall. "
		+ "It looks big enough to hold quite a bit of clothing. The "
		+ "door is currently " + "@@door_closed@@" + ".\n");
		
	add_item(({"door", "closet door"}), "@@exa_door@@");
	add_cmd_item( ({"door", "closet door"}), "open", "@@do_open@@");
	add_cmd_item( ({"door", "closet door"}), "close", "@@do_close@@");
	add_cmd_item( ({ "inside", "inside closet", "closet", "inside the closet"}), 
        ({"peer"}), 
		"@@do_look@@");
	add_cmd_item( ({"a closer look"}), "take", "Well... that didn't work. "
		+ "Have you thought about searching? The closet maybe?\n");
		
	add_prop(OBJ_S_SEARCH_FUN, "search_closet");
	
add_exit("/d/Shire/eastroad/village/whit/whitlane1","out");
	
   
/*  Four hobbits from the hobbitmaker */
}

void
reset_shire_room()
{
	closet_door = 0;
	pipe = 1;

}

public string
search_closet(object me, string arg)
{
	if(arg == "closet" | arg == "inside closet")
	{
		if(closet_door == 0)
		{
			write("You search the closed closet door.\n");
			return "";
		}
		if(pipe == 0)
		{
			return("Your search reveals nothing special, this time.\n");
		}
		else
		{
			
			object copper_pipe;
			copper_pipe = clone_object(WAYM_OBJ_DIR + "still_pipe_1");
			copper_pipe->move(TP);
			pipe = 0;
			return("You search through the closet and find an onion shaped "
				+ "piece of copper pipe.\n");
		}
	}
	else
	{
		return "";
	}
}

string
door_closed()
{
	if(closet_door == 0)
	{
		return("closed");
	}
	else
	{
		return("open. You could probably peer inside the closet now");
	}
}

string
exa_door()
{
	if(closet_door == 0)
	{
		return("The door looks well-constructed, but old. Honestly, it "
			+ "needs a coat of paint as it's a faded-yellow, not a bright "
			+ "cheerful yellow. But paint costs money. Right now, the "
			+ "door is closed tight.\n");
	}
	else
	{
		return("The door looks well-constructed, but old. Honestly, it "
			+ "needs a coat of paint as it's a faded-yellow, not a bright "
			+ "cheerful yellow. But paint costs money. Right now, the "
			+ "door is open wide.\n");
	}
}

//Open the closet door
int
do_open()
{
	if(closet_door == 0)
	{
		write("You open the closet door. Now you can look inside.\n");
		closet_door = 1;
		return 1;
	}
	else
	{
		write("The door is already open!\n");
		return 1;
	}
}

//close the door
int
do_close()
{
	if(closet_door == 0)
	{
		write("The door is already closed.\n");
		return 1;
	}
	else
	{
		write("You close the closet door. It's shut tight.\n");
		closet_door = 0;
		return 1;
	}
}

int
do_look()
{
	if(closet_door == 1)
	{
	write("You look inside the closet. You see clothes (although not very "
		+ "nice ones, but at least they're clean) and some extra bedding. "
		+ "and way in the back, you think you might see something metal. "
		+ "Weird. But you'd really need to take a closer look to be "
		+ "sure.\n");
		
	return 1;
	}
	else
	{
		write("You try to look inside the closet, but the door is closed "
			+ "and now you feel stupid.\n");
		return 1;
	}
}