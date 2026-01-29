/* Outdoors in Waymeet
 * Raymundo, Jan 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "/d/Shire/waymeet/lib/hobbitmaker.h"

inherit WAYM_LIB_DIR + "base_waymeet.c";


int pick_apple = (1 + random(4));

void reset_shire_room();
void add_hobbit();
object hobbit;
void
create_waymeet_room()
{
	extraline = ("Past the gentle hill, under which a hobbit family "
		+ "has built their smial, you notice fields. There various "
		+ "vegetables are grown for the inhabitants of the village. A "
		+ "tall apple tree grows in front of the hobbit hole, providing "
		+ "shade, as well as a few tasty apples each year.\n");
		
	add_item( ({"tree", "apple tree"}), "The tree is quite tall, much "
		+ "taller than any of the hills here in Waymeet. " + "@@is_apple@@"
		+ "\n");
	add_cmd_item("tree", "climb", "You try to climb the tree but fall "
		+ "flat on your butt.\n");


	add_street(0);
	add_smial("h_3_1");
	add_hobbit();
	
	
	add_exit(WAYM_STREET_DIR + "street_6", "south", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_2", "west", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_4", "north", gravel_sound, 0, 0);
}
void
reset_shire_room()
{
	pick_apple = (1 + random(4));
	add_hobbit();
}

void
init()
{
	::init();
	add_action("get_apple", "pick");
	add_action("get_apple", "get");
	add_action("get_apple", "take");

}

string
is_apple()
{
	if(pick_apple != 0)
	{
		return("Large juicy-looking apples hang from its branches.");
	}
	else
	{
		return("The leaves look recently distrubed. It appears some hungry "
			+ "person picked all the apples!\n");
	}
}

//You can pick apples, if they're there.
int
get_apple(string arg)
{
	if(arg == "apple" | arg == "apple from tree")
	{
		if(pick_apple > 0)
		{
			pick_apple = (pick_apple - 1);
			write("You pick an apple from the tree.\n");
			say(QCTNAME(TP) + " picks an apple from the tree.\n");
			object apple;
			apple = clone_object(WAYM_OBJ_DIR + "apple");
			apple->move(TP);
			return 1;
		}
		else
		{
			write("There are no apples left to pick!\n");
			return 1;
		}
	}
	else
	{
		notify_fail("Did you want to pick an apple from the tree?\n");
		return 0;
	}
}

void
add_hobbit()
{
	   if (!present(hobbit))
	   {
		   int i;
		   for(i=0; i<3; i++)
		   {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CHILD);
	hobbit->set_gender();
	hobbit->move(TO);
		   }
	   return;
	   }
	   return ;
	
}