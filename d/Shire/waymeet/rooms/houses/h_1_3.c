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
#include "/d/Shire/waymeet/lib/hobbitmaker.h"

inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

void reset_shire_room();
void add_hobbit();
object hobbit;
//Determines whether or not there are dolls in the room.
int doll = 1;
//Are the covers made on the bed?
int covers = 1;

//Did you make the bed?
string
made_unmade()
{
	if(covers == 1)
	{
		return("unmade in a pile at the foot of the bed. ");
	}
	else
	{
		return("neatly made, and smoothed, as if a maid has just "
			+ "visited the room. ");
	}
}

void
create_shire_room()
{
	set_short("In the Bedroom");
	
	set_long("This bedroom belongs to a small child. " + "@@is_doll@@" 
		+ "A bed sits against the north wall, its covers " + "@@made_unmade@@"
		+ "The closet door is securely shut. A round window lets some light "
		+ "into the room, and through it you can hear birds chirping.\n");
	
	add_item( "bed", "This bed is quite small, being built for a hobbit "
		+ "child. There are covers " + "@@made_unmade@@" + "It looks like "
		+ "a comfortable place to lie down for a nap.\n");
		
	add_item( ({"door", "closet", "closet door"}), "The closet door is closed "
		+ "and seems to be quite stuck. You're not sure you could open it.\n");
		
	add_item( ({"cover", "covers", "blanket", "blankets"}), "@@exa_covers@@");
		
		
	add_cmd_item( ({"in bed", "down in bed", "bed"}), "lie", "You are too "
		+ "tall to lie down in the bed. It's made for a child!\n");
	add_cmd_item( ({"closet", "door"}), "unlock", 
		"The closet door isn't locked.\n");
	add_cmd_item( ({"closet", "door"}), "open", 
		"The door is stuck. You cannot open it.\n");

	add_walls();
	add_window("yellow");
	
	
	add_prop(ROOM_I_INSIDE, 1);
	
	add_exit(WAYM_HOUSE_DIR + "h_1_2", "east");
	
	add_hobbit();
		
}

void
reset_shire_room()
{
	doll = 1;
	covers = 1;
	if(!hobbit)
	{
		add_hobbit();
	}
}

void
init()
{
	::init();
	add_action("make_bed", "make");
	add_action("exa_doll", "exa");
	add_action("exa_doll", "examine");
	add_action("exa_doll", "l");
	add_action("exa_doll", "look at");
	add_action("exa_doll", "look");
	add_action("get_doll", "snatch");
	add_action("get_doll", "get");
	add_action("get_doll", "take");


}

// Is there a doll or did someone take it?
string
is_doll()
{
	if(doll == 1)
	{
		return("A doll lies strewn about on the floor. ");
	}
	else
	{
		return("");
	}
}

//Be a good boy and make the bed!
int
make_bed(string str)
{
	if(str == "bed")
	{
		if (covers == 1)
		{
			write("You gently take the covers and pull them up to the "
				+ "head of the bed. Then you smooth them out so that the bed "
				+ "is perfectly made.\n");
			say(QCTNAME(TP) + " gently takes the covers and pulls them up to "
				+ "the head of the bed. Then " + HE_SHE(TP) + " smoothes them "
				+ "out so that the bed is perfectly made.\n");
	
			covers = 0;
			return 1;
		}
		else
		{
			write("But the bed is already made!\n");
			say(QCTNAME(TP) + " tries to make the bed, but the bed has already "
				+ "been made.\n");
			return 1;
		}
	}
	else
	{
		notify_fail("Make what, the bed?\n");
		return 0;
	}
}

//Let's you look at the doll, if it's there.
int
exa_doll(string str)
{
	if(str == "doll")
	{
		if(doll == 1)
		{
			write("The doll looks like a cute little bunny rabbit holding "
			+ "a carrot. There are a few bare spots on it, so likely it "
			+ "has been played with quite a lot.\n");
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

//You can take the doll, if you want to be a mean bastard.
int
get_doll(string str)
{
	 if(!strlen(str))
        {
            return 0;
        }
	if(parse_command(str, TO, " [the] [well-worn] [grey] 'doll' / 'rabbit' ") )
        {
		if(doll == 1)
		{
			object rabbit;
			rabbit = clone_object(WAYM_OBJ_DIR + "rabbit_doll.c");
			write("You reach down and pick up the " + 
				rabbit->query_short() + "!\n");
			say(QCTNAME(TP) + " reaches down and picks up the "
				+ rabbit->query_short() + "!\n");

		
			rabbit->move(TP);
			doll = 0;
			return 1;
		}
		else
		{
			return 0;
		}

		}
				else
		{
			return 0;
		}
}

//Description of the covers

string
exa_covers()
{
	if(covers == 1)
	{
		return("The covers look warm. They would be inviting if only the "
			+ "child who lives here had bothered to make the bed.\n");
	}
	else
	{
		return("The covers look warm and inviting. This is the kind of bed "
			+ "a person like you might like to lie down in.\n");
	}
}




void
add_hobbit()
{
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CHILD);
	hobbit->set_power(20);
	hobbit->move(TO);
	hobbit->set_chat_time(30);
	hobbit->add_chat("I miss my mom!");
	hobbit->add_chat("Where's mother?");
	hobbit->add_chat("Father says she went on a trip, but mother has been gone a long time.");
	hobbit->add_chat("I want my mommy!");
	hobbit->set_default_answer("The hobbit looks worried "
		+ "about " + HIS_HER(hobbit) + " mother.\n");
	object diaper;
	diaper = clone_object(WAYM_ARM_DIR + "diaper");
	diaper->move(hobbit);
	hobbit->command("wear diaper");
}
