#include "../sforest.h"
#include "../basic.h"

#include <macros.h>
#include <stdproperties.h>
inherit SFOREST + "trail";

#define LIVE_I_DIRTY   "_live_i_dirty"   /* how dirty is the player? */

public void
create_trail_room()
{
	set_short("a small stone bridge");
	set_long("   A small stone bridge marks this passage through "+
	"an over-grown trail. Soft strands of light sparkle in from "+
	"high above the canopy of converging pine and maple trees "+
	"along a small stream.\n");

	add_item(({"up"}),
	"The canopy is in that direction.\n");
	add_item(({"down"}),
	"The stone bridge is firm with dark soil and stones.\n");
	add_item(({"west", "southwest"}),
	"The trail continues in the direction.\n");
	add_item(({"south", "northeast", "east", "southeast", "north", "northwest"}),
	"The wilderness is in that direction.\n");
	add_item(({"water", "stream"}),
	"The stream has cystal clear water, pure enough to drink.\n");
	
	
	add_prop(OBJ_I_CONTAIN_WATER, 1);
	
	add_exit("trail4", "west");
	add_exit("trail2", "southwest");

}

int
wash_it(string str)
{
	object *ob;
	int i;
	if((str == "face"))
	{
		write("You lean over the small stone bridge dipping "+
		"your hands into the stream washing your face "+
		"with some of the water.\n"+
		"It feels cool on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" leans over the small stone bridge "+
		"dipping "+HIS(TP)+" hands into the stream washing "+
		""+HIS(TP)+" face with some of the water.\n");
		return 1;
	}
	if((str == "hands"))
	{
		write("You lean over the small stone bridge dipping "+
		"your hands into the stream washing your hands "+
		"with some of the water.\n"+
		"It feels cool on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" leans over the small stone bridge "+
		"dipping "+HIS(TP)+" hands into the stream washing "+
		""+HIS(TP)+" hands with some of the water.\n");
		return 1;
	}
	if((str == "neck"))
	{
		write("You lean over the small stone bridge dipping "+
		"your hands into the stream washing your neck "+
		"with some of the water.\n"+
		"It feels cool on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" leans over the small stone bridge "+
		"dipping "+HIS(TP)+" hands into the stream washing "+
		""+HIS(TP)+" neck with some of the water.\n");
		return 1;
	}
	if((str == "ears"))
	{
		write("You lean over the small stone bridge dipping "+
		"your hands into the stream washing your ears "+
		"with some of the water.\n"+
		"It feels cool on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" leans over the small stone bridge "+
		"dipping "+HIS(TP)+" hands into the stream washing "+
		""+HIS(TP)+" ears with some of the water.\n");
		return 1;
	}
	if((str == "feet"))
	{
		write("You lean over the small stone bridge dipping "+
		"your hands into the stream washing your feet "+
		"with some of the water.\n"+
		"It feels cool on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" leans over the small stone bridge "+
		"dipping "+HIS(TP)+" hands into the stream washing "+
		""+HIS(TP)+" feet with some of the water.\n");
		return 1;
	}
	if((str == "body"))
	{
		write("You lean over the small stone bridge dipping "+
		"your hands into the stream washing your body "+
		"with some of the water.\n"+
		"It feels cool on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" leans over the small stone bridge "+
		"dipping "+HIS(TP)+" hands into the stream washing "+
		""+HIS(TP)+" body with some of the water.\n");
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
		return 1;
	}
	else
	{
		notify_fail("Wash what? Your face perhaps?\n");
		return 0;
	}

}

int
drink_it(string str)
{
	string what, where;
	int i;
	if (!strlen(str))
	{
		notify_fail("Drink what?\n");
		return 0;
	}
	
	/* See if syntax is "drink <something> from <something>" */
	if (sscanf(str, "%s from %s", what, where) != 2)
	{
		/* See if syntax is "drink from <something>" */
		if (!sscanf(str, "from %s", where))
		{
			/* Syntax must simply be "drink <something>" */
			what = str;
		}
	}
	if (what && !parse_command(what, ({}), "[the] / [some] 'water'"))
	{
		notify_fail("Drink what?\n");
		return 0;
	}
	if (where && !parse_command(where, ({}), "[the] 'stream' "))
	{
		/* Technically, this isn't going to show because 
		 * of the standard 'drink' command.  Really, there's 
		 * not much choice, though, since we don't want to 
		 * return 1.
		 */
		 notify_fail("Drink from where?\n");
		 return 0;
	}
	
	/* Drink small amounts up to 500 soft */
	for (i = 0; i < 10; i++)
	{
		if (!this_player()->drink_soft(50))
		{
			/* Can't drink any more */
			break;
		}
	}
	if (i == 0)
	{
		write("You are too full to drink any water.\n");
		return 1;
	}
	if (!this_player()->drink_soft(50, 1))
	{
		write("You take a drink of the cool water.  Having "+
		"drunk your fill, you feel refreshed.\n");
	}
	else
	{
		write("You take a drink of the cool water.\n");
	}
	say(QCTNAME(this_player()) +" drinks some water from the "+
	"stream.\n");
	return 1;
}

void
init()
{
	::init();
	add_action(drink_it, "drink");
	add_action(wash_it, "wash");
}

