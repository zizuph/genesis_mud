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

void reset_shire_room();

//This int will keep track of whether the door is open or closed.
int door = 0;

//Returns the status of the door.
string
open_close_door()
{
	if (door == 0)
	{
		return "closed";
	}
	else
	{
		return "open";
	}
}
	
string 
item_height()
{
	if(TP->query_race_name() == "ogre")
	{
		return("ankle");
	}
	else if(TP->query_race() == "human")
	{
		return("waist");
	}
	else if(TP->query_race() == "elf")
	{
		return("waist");
	}
	else if(TP->query_race() == ("hobbit", "gnome", "dwarf", "goblin"))
	{
		return("shoulder");
	}
	else
	{
		return("knee");
	}
}

/* 
 * This will prevent exit if the door is closed.
 */
 
 int
 block_people()
 {
	 if (door == 0)
	 {
		 write("But the door is closed!\n");
		 return 1;
	 }
	 else
	 {
		 return 0;
	 }
 }
string door_status();
void
create_shire_room()
{
	set_short("The entryway");
	
	set_long("You stand in the entry way of a hobbit's home. It looks clean, "
		+ "and warm, and comfortable. Along the east "
		+ "wall are some " + "@@item_height@@" 
		+ "-high hooks for hanging cloaks "
		+ "and jackets and the like. A doorway leads out, whilst a hallway "
		+ "leads deeper into the hobbit hole.\n");
		
	add_item( ({"hook", "hooks", "coat hook", "coat hooks"}), 
		"These hooks are about " + "@@item_height@@" 
		+ "-high on you. They look like "
		+ "a good place for a guest to hang a jacket or cloak.\n");
	add_item( ({"entry", "entryway", "entry way", "way"}), "There is a "
		+ "beautiful round door leading out of the hobbit hole. Quite a nice "
		+ "door, really, and well-cared for. It is " + "@@open_close_door@@" 
		+ ".\n");
	add_item( ({"door", "doors", "round door"}), door_status());
	add_item( ({"wall", "walls", "west wall",}), 
		"The walls clean and welcoming. They "
		+ "are covered with wood paneling.\n");
	add_item( ({"panel", "wood panel", "wood paneling", "paneling"}),
		"The wood panels are fitted together nicely and stained a deep, rich "
		+ "brown.\n");
	add_item( ({"east wall", "east walls"}), "The east wall looks like all "
		+ "the other walls, except that it has some coat hooks on it.\n");
	add_item( "ceiling", "The ceiling is gently rounded to distribute the "
		+ "weight of the ground above.\n");
	add_item( "floor", "The floor is spotless. Whoever lives here takes the "
		+ "time to clean!\n");
	add_item( ({"hole", "hobbit hole"}), "This is a hobbit hole, and it "
		+ "looks comfortable!\n");
	add_item( "north wall", "There is no north wall. That's the hallway that "
		+ "leads further into the dwelling.\n");
	add_item( "south wall", "Covered in paneling, the south wall looks like "
		+ "all the other walls, except that it has a large round door in the "
		+ "middle of it.\n");
		
		
	add_cmd_item( ({"door", "on door"}), "knock", "Why would you knock on the "
		+ "door from the inside of the home? That's just daft!\n");
	add_cmd_item( "floor", "clean", "There is no need to clean the floor. "
		+ "It's spotless!\n");
	add_prop(ROOM_I_INSIDE, 1);
	
	add_exit(WAYM_HOUSE_DIR + "h_1_2", "north");
	add_exit(WAYM_STREET_DIR + "street_3", "out", block_people, 0,0); 
		
}

void
reset_shire_room()
{
	door = 0;
}

void
init()
{
	::init();
	add_action("hang_jacket", "hang");
	add_action("close_door", "close");
	add_action("open_door", "open");

}

/*
 * This is just a fun bit to let people interact with the hooks
 * without actually interacting with them.
 */
 
int
hang_jacket(string str)
{
	if(!strlen(str))
        {
            notify_fail("Hang what? Where?\n");
            return 0;
        }
	if (parse_command(str, TO, " 'jacket' / 'cloak' / 'coat' / 'cape' [on] [the] 'hook' ") )
        {
			write("You wouldn't feel right just hanging something up without "
				+ "being invited!\n");
			return 1;
		}
	if (parse_command(str, TO, " 'jacket' / 'cloak' / 'coat' / 'cape' [on] [the] 'hooks' ") )
        {	
			write("Why on earth would you need more than one hook?\n");
			return 1;
		}
	else
		{	
			return 0;
		}
}

/*
 * Here we can close the door.
 */
int
close_door(string str)
{
	 if(!strlen(str))
        {
            return 0;
        }
	if( str == "door" | str == "round door" | str =="the door" | str =="the round door" )
	{
		if (door == 0)
		{
			write("But the door is already closed!\n");
			say(QCTNAME(TP) + " tries to close the already closed door!\n");
			return 1;
		}
		else
		{
			door = 0;
			write("You close the door.\n");
			say(QCTNAME(TP) + " closes the door.\n");
			
			return 1;
		}
	}
	else
	{
		return 0;
	}
}

/*
 * And this will open the door.
 */
int
open_door(string str)
{
	 if(!strlen(str))
        {
            return 0;
        }
	if( str == "door" | str == "round door" | str =="the door" | str =="the round door" )
	{
		if (door == 0)
		{
			door = 1;
			write("You open the door.\n");
			say(QCTNAME(TP) + " opens the door.\n");
			
			return 1;
		}
		else
		{
			write("You try to open the door, but it was already open!\n");
			say(QCTNAME(TP) + " tries to open the door, but it was already "
				+ "open!\n");
			return 1;
		}
	}
	else
	{
		return 0;
	}
}

/*
 * Lets you know if the door is open or closed.
 */
 
string
door_status()
{
	return("The door is round and made "
		+ "of wood. You don't see any scratches or scuffs on it. The door is "
		+ "currently " + "@@open_close_door@@" + ".\n");
}