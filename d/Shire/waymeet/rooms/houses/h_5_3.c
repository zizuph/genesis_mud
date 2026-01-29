/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A low-income hobbit hole
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

int is_flower = 1;

void
create_hobbit_room()
{
	set_short("The Kitchen");
	
	set_long("This is a small kitchen, big enough for just one hobbit "
		+ "to be in here at a time. A small table with a single chair "
		+ "occupies the center of the room. There is a tiny stove "
		+ "where dinner can be cooked, some simple wooden counters and "
		+ "a sink. It's a functional kitchen, but so, so tiny.\n");
	add_item("chair", "The chair a small and white. As you examine it, "
		+ "you notice that it could use some repair. The legs are loose "
		+ "and so if you sat on it, there's a good chance it would "
		+ "break.\n");
	add_item("table", "The table looks just big enough for one person "
		+ "to sit up to and eat her breakfast or second breakfast or "
		+ "any of the other meals hobbits so often eat. " + 
		"@@exa_flowers@@" + "\n");
	add_item( ({"vase", "clay vase"}), "@@exa_vase@@");
	add_item( ({"flower", "rose"}), "@@exa_rose@@");
	
	add_stove("tiny");
	add_kitchen("maple");
	add_floor_poor("clean but well-used");
	
	add_cmd_item( ({"on chair", "in chair"}), "sit", "You consider sitting on the chair, "
		+ "but it seems so rickety you decide not to. It might break!\n");
		
	add_exit(WAYM_HOUSE_DIR + "h_5_2", "north");

}

void
reset_shire_room()
{
	is_flower = 1;
}

void
init()
{
	::init();
	add_action("do_pick", "pick");
	add_action("do_pick", "get");
	add_action("do_pick", "take");

}

//A string to let us know if there are flowers in the vase.
string
exa_flowers()
{
	if(is_flower == 1)
	{
		return ("A clay vase sits on the table. In it you see a single "
			+ "red rose, perfectly open and fragrant.");
	
	}
	else
	{
		
		return("An empty clay vase sits on the table. There is water "
			+ "in the bottom of it, so you infer that until recently "
			+ "there were also flowers in it.");
		
	}
}

//you can get the flowers
int
do_pick(string str)
{
	if(parse_command(str, TO, "[the] [red] 'rose' / 'flower' 'from' [the] [clay] 'vase' ") )
        {
			if(is_flower == 0)
			{
				write("But there are no flowers in the vase!\n");
				return 1;
			}
			else
			{
				object rose;
				rose = clone_object(WAYM_OBJ_DIR + "kitchen_rose");
				rose->move(TP);
				write("You reach out and take the rose from the vase.\n");
				say(QCTNAME(TP) + " reaches out and takes the rose from the "
					+ "vase.\n");
				is_flower = 0;
				return 1;
			}
		}
	else
	{
		notify_fail("Take the rose from the vase maybe?\n");
		return 0;
	}
}
	
//returns the description of the vase
string
exa_vase()
{
	if(is_flower == 1)
	{
		return("The vase is made of clay and looks very inexpensive. A "
			+ "single red rose extends from the top of it, a touch of "
			+ "beauty and luxury in an otherwise very plain room.\n");
	}
	else
	{
		return("The vase is just inexpensive clay pottery, likely not even "
			+ "worth a copper coin. There is water in the bottom of the "
			+ "vase, so until recently it probably held flowers.\n");
	}
}

//returns the description of the rose
string
exa_rose()
{
	if(is_flower == 1)
	{
		return("This rose is perfect. It has a long, straight stem, and "
		+ "all the thorns have been shaved off with a sharp knife. The "
		+ "flower itself is a deep red and is fully open. Yesterday, the "
		+ "flower was likely closed, and tomorrow it may be wilted, but "
		+ "in this moment it is beautiful and perfect.\n");
	}
	else
	{
		return("Rose? What rose? The vase is empty.\n");
	}
}
	
	
