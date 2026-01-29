/**********************************************************************
 * - well.c                                                         - *
 * - A special well that has a secret entrance that leads to a      - *
 * - secret area filled with deadly foes.                           - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "../defs.h"
inherit SAMORGAN_BASE;
#include <macros.h>
#include <stdproperties.h>

/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
	return ({6, 5});
}
public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	set_xlong(({
        "The center of this village square has an unadorned well that "+
        "villagers use to obtain fresh water for drinking. The village "+
        "square continues in all directions.",
        "The center of this village square has a plain drinking well "+
        "that villagers use to obtain fresh water. The village square "+
        "continues in all directions.",
        "The center of this village square has a simple well that "+
        "villagers use to obtain clean water for drinking. The village "+
        "square continues in all directions.",
        "The center of this village square has an austere drinking well "+
        "that villagers use to obtain crystal clear water. The village "+
        "square continues in all directions.",}));
        
        config_room("central");
    
        add_item(({"well", "water well", "simple well", "flowing well", "unadorned well", "austere well", "drinking well", "unembellished well", "meager well"}),
        "This is a simple flowing well to drink crystal clear water "+
        "from.\n");
        add_item(({"west", "east", "north", "south"}),
        "The village square continue in that direction.\n");
        add_item(({"northwest", "northeast", "southeast", "southwest"}),
        "The village square is in that direction.\n"); 
       
        add_prop(OBJ_I_CONTAIN_WATER, 1);
   
        add_exit("vil0505", "north");
        add_exit("vil0705", "south");
        add_exit("vil0604", "west");
        add_exit("vil0606", "east");
        
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

