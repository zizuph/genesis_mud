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
#include "/d/Shire/waymeet/lib/hobbitmaker.h"

inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

//is there a nut to be searched for?
int is_nut = 1;

void add_hobbit();
object hobbit;

void
create_hobbit_room()
{
	set_short("In the Kitchen");
	
	set_long("The kitchen is clean and warm, but otherwise unremarkable. "
		+ "It has a counter and a sink, a stove and a pantry, and even "
		+ "an icebox. But it is not very decorated. There is a pot of food "
		+ "cooking on the stove top, and from what you can smell you think "
		+ "it's probably a pot of beans. The room isn't big enough for a "
		+ "table or chairs. Everyone must eat on the furniture in the "
		+ "living room to the west.\n");
		

	
	add_prop(OBJ_S_SEARCH_FUN, "search_counter");

	add_kitchen("weathered stone");
	add_stove("small");
	add_floor_poor("stained");
	
	add_exit(WAYM_HOUSE_DIR + "h_2_1", "west"); 
	
	add_hobbit();
}



void
reset_shire_room()
{
	is_nut = 1;
   add_hobbit();
   
}

void
init()
{
	::init();
	
}

public string
search_counter(object me, string arg)
{
	if(arg == "counter" | arg == "counter top" | arg == "counters" | arg == "counter tops")
	{
	
	if (is_nut == 1)
	{
		object nut;
		nut = clone_object(WAYM_OBJ_DIR + "nutshell");
		
		say(QCTNAME(TP) + " finds a " + nut->query_short() 
			+ " on the counter! How anticlimactic!\n");
		nut->move(TP);
		is_nut = 0;
		return ("You found a " + nut->query_short() + " on the counter! "
			+ "How anticlimatctic!\n");
		
	}
	else
	{
		return("This is one clean looking counter. Impressive!\n");
		
	}
	}
	else
	{
		return "";
	}
}

void
add_hobbit()
{
	   if (!present(hobbit))
	   {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CITIZEN);
	hobbit->set_gender(1);
	hobbit->move(TO);
	   }
	   return ;
	
}