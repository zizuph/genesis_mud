/* A waterskin made by Glinda, may-95.
 * Thanks to Grace for making it recoverable, dec-95 
 *
 * Adapted for sale in general EQ store of Aesthetics
 * quarter of Palanthas.
 *
 * Mortis 05.2006
 *
 * 13.12.2007 Milan, added str check in do_drink() and changed ADDs to functions in init()
 * 2018-12-22: Cotillion - Fixed weight updates
 */

inherit "/std/object";
inherit "/lib/keep";

#include "../../local.h"
#include <macros.h>
#include <cmdparse.h>


int level;

create_object()
{
	set_name("waterskin");
	add_name("skin");
	add_adj("suede");
	set_short("suede waterskin");
	set_pshort("suede waterskins");
	set_long("A soft yet sturdy waterskin made from suede.  You may drink "
	+ "from it, fill it, refill it, or empty it.  The waterskin is "
	+ "@@query_level_desc@@" + "\n");

	level = 6500;
	add_prop(OBJ_I_VALUE,    72);
	add_prop(OBJ_I_VOLUME, 6000);
	add_prop(OBJ_I_WEIGHT, "@@query_weight");
	add_prop(OBJ_I_CONTAIN_WATER, "@@query_water");

	set_keep(1);
}

query_recover()
{
	return MASTER + ":";
}
         
query_water()
{
	if(!level)
		return 0;
	else
		return 1;
}



int
ob_weight()
{
	return(200 + level / 3);
}




int
query_weight()
{
	return(200 + level / 3);
}



string
query_level_desc()
{
	switch(level)
	{
		case 1..500:
			return "almost empty.";
		case 501..2000:
			return "less than half full of water.";
		case 2001..3000:
			return "half full of water.";
		case 3001..4500:
			return "more than half full of water.";
		case 4501..6500:
			return "full of water.";
	}

	return "empty.";
}

do_empty(string str)
{
	object *obs;
	object obj;


	NF("Empty what?\n");

	if (!stringp(str))
		return 0;

	if((!parse_command(str, TP,"[the] %i",obs)) ||
		(!sizeof(obs = NORMAL_ACCESS(obs, 0, 0))))
		return 0;

	if (sizeof(obs) != 1)
		write("Please try with one at a time.\n");

	else
		obj = obs[0];

	if (obj != TO)
		return 0;

	else
	{
		if(!(TP==environment()))
			write("But you don't have the suede waterskin!\n");

		if(!level)
			write("The suede waterskin is already empty.\n");

		else
		{
			write("You empty your suede waterskin. The water rapidly soaks "
			+ "into the ground.\n");
			say(QCTNAME(TP) + " empties " + HIS(TP) + " suede waterskin.  "
			+ "The water rapidly soaks into the ground.\n");
            mark_state();
			level = 0;
            update_state();
		}

		return 1;
	}

	return 0;
}

do_refill(string str)
{
	object *obs;
	object obj;

	NF("Refill what?\n");

	if (!stringp(str))
		return 0;

	if((!parse_command(str, TP,"[the] %i",obs)) ||
		(!sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))   )
		return 0;

	if (sizeof(obs) != 1)
		write("Please try with one at a time.\n");

	else
		obj = obs[0];

	if (obj != TO)
		return 0;

	else
	{
		if(!(TP==environment()))
			write("But you don't have the suede waterskin!\n");
		
		else if (environment(TP)->query_prop(OBJ_I_CONTAIN_WATER) ||
			environment(TP)->query_prop(ROOM_I_TYPE == ROOM_BEACH) ||
			environment(TP)->query_prop(ROOM_I_TYPE == ROOM_IN_WATER))
		{
			write("You refill your suede waterskin.\n");
			say(QCTNAME(TP) + " refills " + HIS(TP) + " suede waterskin.\n");
            mark_state();
			level = 6500;
            update_state();
		}

		else
			write("You cannot refill your suede waterskin here.\n");

		return 1;
	}

	return 0;
}



do_drink(string str)
{
	int max;
	int capacity;
	object *obs;
	object obj;

	NF("Drink from what?\n");

	if(!stringp(str))
	     return 0;

	max = TP->query_prop(LIVE_I_MAX_DRINK);
	capacity = max-TP->query_soaked();      /* How much more can u drink? */

	if((!parse_command(str, TP,"'from' [the] %i",obs)) ||
		(!sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))   )
		return 0;

	if (sizeof(obs) != 1)
		write("Please try with one at a time.\n");

	else
		obj = obs[0];

	if (obj != TO)
		return 0;

	else
	{
        mark_state();

		if(!(TP==environment()))
			write("But you don't have the suede waterskin!\n");

		else if(!level)
			write("But the suede waterskin is empty!\n");

		else if(TP->query_soaked()==max)
		{
			say(QCTNAME(TP) + " tried to drink from " + HIS(TP) + " suede "
			+ "waterskin, but failed.\n");
			write("You cannot drink anymore water!\n");
		}

		else if( capacity < 500 )
		{
			level = level - capacity;
			TP->drink_soft(capacity);
			say(QCTNAME(TP) + " drinks from a suede waterskin.\n");
			write("You drink from the suede waterskin until you are "
			+ "completely soaked.\n");
		}

		else if( level < 500 )
		{
			TP->drink_soft(level);
			level = 0;
			say(QCTNAME(TP) + " drinks from a suede waterskin.\n");
			write("You drink from the suede waterskin until its empty.\n");
		}

		else
		{
			TP->drink_soft(500);
			level = level - 500;
			say(QCTNAME(TP) + " drinks from a suede waterskin.\n");
			write("You drink some water from your suede waterskin.\n");
		}

        update_state();

		return 1;
	}

	return 0;
}

int
query_level()
{
	return level;
}

init()
{
	::init();
	ADD(do_drink, "drink");
	ADD(do_refill, "refill");
	ADD(do_refill, "fill");
	ADD(do_empty,"empty");
}
