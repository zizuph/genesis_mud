/*
 * This is part of a road in Port Macdunn.
 *
 * Khail - May 16/97
 * Added drinking well Damaris@genesis 01/2006
 */
#pragma strict_types

#include "room.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
inherit ROADBASE;

public string
query_dir_to_jail()
{
    return "north";
}

public void
create_road()
{
	set_short("wide dirt road");
	set_long("   You are on a wide dirt road leading north "+
	"and south through the middle of the village. There is a "+
	"large stone drinking well. It is here that villagers will "+
	"stop to get fresh drinking water especially after a hard "+
	"days work. Low stone walls, either of very long buildings "+
	"or compounds of some sort, flank the road on either side.\n");
	add_item(({"area"}), query_long);
	
	add_prop(OBJ_I_CONTAIN_WATER, 1);
	add_exit(ROOM + "road_12_4", "north");
	add_exit(ROOM + "road_12_6", "south");
}
int
wash_it(string str)
{
	if(!strlen(str))
	{
		write("Wash what?\n");
		return 0;
	}
	if((str == "face"))
	{
		write("You pour some water from the bucket and "+
		"wash your face with some of the well water.\n"+
		"It feels cool on your skin.\n");
		
		say(QCTNAME(TP)+" pours some water from the bucket "+
		"and washes "+HIS+" face with some of the well water.\n");
		return 1;
	}
	if((str == "hands"))
	{
		write("You pour some water from the bucket and wash "+
		"your hands with some of the well water.\n"+
		"It feels cool on your skin.\n");
		say(QCTNAME(TP)+" pours some water from the bucket and "+
		"washes "+HIS+" hands with some of the well water.\n");
		return 1;
	}
	if((str == "neck"))
	{
		write("You pour some water from the bucket and wash "+
		"your neck with some of the well water.\n"+
		"It feels cool on your skin.\n");
		say(QCTNAME(TP)+" pours some water from the bucket and "+
		"washes "+HIS+" neck with some of the well water.\n");
		return 1;
	}
	if((str == "ears"))
	{
		write("You pour some water from the bucket and wash "+
		"your ears with some of the well water.\n"+
		"It feels cool on your skin.\n");
		say(QCTNAME(TP)+" pours some water from the bucket and "+
		"washes "+HIS+" ears with some of the well water.\n");
		return 1;
	}
	if((str == "feet"))
	{
		write("You pour some water from the bucket and wash "+
		"your feet with some of the well water.\n"+
		"It feels cool on your skin.\n");
		say(QCTNAME(TP)+" pours some water from the bucket and "+
		"washes "+HIS+" feet with some of the well water.\n");
		return 1;
	}
	if((str == "body"))
	{
		write("You change your mind about washing your body with "+
		"the well water, since this is a central location in "+
		"this village.\n");
		say(QCTNAME(TP)+" looks like "+HE+" is thinking "+
		"about something.\n");
		return 1;
	}
	if((str == "legs"))
	{
		write("You pour some water from the bucket and wash "+
		"your legs with some of the well water.\n"+
		"It feels cool on your skin.\n");
		say(QCTNAME(TP)+" pours some water from the bucket and "+
		"washes "+HIS+" legs with some of the well water.\n");
		return 1;
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
	if (sscanf(str, "%s from %s", what, where) != 2)
	{
		if (!sscanf(str, "from %s", where))
		{
			what = str;
		}
	}
	if (what && !parse_command(what, ({}), "[the] / [some] 'water'"))
	{
		notify_fail("Drink what?\n");
		return 0;
	}
	if (where && !parse_command(where, ({}), "[the] 'well' "))
	{
		notify_fail("Drink from where?\n");
		return 0;
	}
	/* Drink small amounts up to 500 soft */
	for (i = 0; i < 10; i++)
	{
		if (!this_player()->drink_soft(50))
		{
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
		write("You take a drink of the cool water.  Having " +
		"drunk your fill, you feel refreshed.\n");
	}
	else
	{
		write("You take a drink of the cool water.\n");
	}
	say(QCTNAME(this_player()) +" drinks some water from the "+
	"well.\n");
	return 1;
}

void
init()
{
	::init();
	add_action(drink_it, "drink");
	add_action(wash_it, "wash");
}


