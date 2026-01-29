/**********************************************************************
 * - vil0510.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "../defs.h"
inherit SAMORGAN_BASE;
#include <macros.h>
#include <stdproperties.h>

#define LIVE_I_DIRTY   "_live_i_dirty"   /* how dirty is the player? */
/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
	return ({5, 9});
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
	"This area is a dead end with tall trees blocking all paths "+
	"save the path back toward the village. A small spring erupts "+
	"from the ground here. It is bubbling with cool refreshing "+
	"water. There seems to be a few trinkets left here which "+
	"denotes this is a special shrine of some sort. The quiet "+
	"village of SaMorgan continues back toward the west.",
	"This area is a dead end with tall trees blocking all paths "+
	"save the path back toward the village. A little spring erupts "+
	"from the ground here. It is bubbling with cool refreshing "+
	"water. There seems to be a few jewels left here which denotes "+
	"this is a distinctive shrine of some sort. The quiet village "+
	"of SaMorgan continues back toward the west.",
	"This area is a dead end with tall trees blocking all paths "+
	"save the path back toward the village. A slight spring gushes "+
	"from the ground here. It is sparkling with cool refreshing "+
	"water. There seems to be a few ornaments left here which "+
	"denotes this is a shrine of some sort. The quiet village "+
	"of SaMorgan continues back toward the west.",
	"This area is a dead end with tall trees blocking all paths "+
	"save the path back toward the village. A little spring erupts "+
	"from the ground here. It is bubbling with cool refreshing "+
	"water. There seems to be a few charms left here which denotes "+
	"this is a small shrine of some sort. The quiet village of "+
	"SaMorgan continues back toward the west.",}));
	
	config_room("eastern");
	
	add_item(({ "southwest", "northwest","north","south"}),
	"There is a building in that direction.\n");
	add_item(({"west" }),
	"The street continues in that direction.\n");
	add_item(({ "northeast", "southeast"}),
	"A rocky beach is in that direction.\n");
	add_item(({"east"}),
	"That is a dead end.\n");
	
	add_item(({"spring", "water", "spring water"}),
	"This is a cool spring that isn't too large by any means "+
	"but is large enough to drink and wash from.\n");
	add_item(({"shrine", "unique shrine", "distinctive shrine", "special shrine" }),
	"By the trinkets placed along here it designates that this "+
	"shrine is for the god of love, Oenghus.\n");
	add_item(({"trinkets", "trinket"}),
	"There are a few small trinkets that are placed here at "+
	"the shrine.\n");
	add_item(({"jewels", "jewel"}),
	"There are a few small jewels that are placed here at "+
	"the shrine.\n");	
	add_item(({"ornaments", "ornament"}),
	"There are a few small ornaments that are placed here at "+
	"the shrine.\n");	
	add_item(({"charms", "charm"}),
	"There are a few small charms that are placed here at "+
	"the shrine.\n");
	add_fail(({"east"}),
	"It is a dead end.\n");
	add_fail(({"northwest", "southwest", "north", "northeast", "southeast", "south"}),
	"Rocks block your path.\n");
	
	add_exit("vil0509", "west");
	
        add_prop(OBJ_I_CONTAIN_WATER, 1);
        
}
int
do_enter(string str)
{
	if (member_array(str, ({"temple", "spring","water"})) == -1)
	{
		notify_fail("Enter what?\n");
		return 0;
	}
	write("You step into the flowing spring and enter the "+
	"Otherworld.\n\nStrangely you hear a voice say: To return to "+
	"this village, simply <return village>.\n");
	say(QCTNAME(this_player())+" vanishes.\n");
	this_player()->move_living("M", "/d/Khalakhor/guilds/tempt/room/entrance", 1, 0);
	say(QCTNAME(this_player())+" suddenly appears.\n");
	return 1;
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
	if (where && !parse_command(where, ({}), "[the] 'spring' "))
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
	"spring.\n");
	return 1;
}
int
wash_it(string str)
{
	object *ob;
	int i;
	
	if(!strlen(str))
	{
		write("Wash what?\n");
		return 0;
	}
	if((str == "face"))
	{
		write("The cool spring water refreshes you as you wash "+
		"your face.\n");
		say(QCTNAME(TP)+" washes "+HIS+" face with some of "+
		"the spring water.\n");
		return 1;
	}
	if((str == "hands"))
	{
		write("The cool spring water refreshes you as you wash "+
		"your hands.\n");
		say(QCTNAME(TP)+" washes "+HIS+" hands with some of the "+
		"spring water.\n");
		return 1;
	}
	if((str == "neck"))
	{
		write("The cool spring water refreshes you as you wash "+
		"your neck.\n");
		say(QCTNAME(TP)+" washes "+HIS+" neck with some of the "+
		"spring water.\n");
		return 1;
	}
	if((str == "ears"))
	{
		write("The cool spring water refreshes you as you wash "+
		"your ears.\n");
		say(QCTNAME(TP)+" washes "+HIS+" ears with some of the "+
		"spring water.\n");
		return 1;
	}
	if((str == "feet"))
	{
		write("The cool spring water refreshes you as you wash "+
		"your feet.\n");
		say(QCTNAME(TP)+" washes "+HIS+" feet with some of the "+
		"spring water.\n");
		return 1;
	}
	if((str == "body"))
	{
		write("The cool spring water refreshes you as you wash "+
		"your body.\n");
		say(QCTNAME(TP)+" washes "+HIS+" body with some of the "+
		"spring water.\n");
		return 1;
		TP->add_prop(LIVE_I_DIRTY,0);
		ob = deep_inventory(TP);
		for (i = 0; i < sizeof(ob); i++)
		if (ob[i]->id("dirty"))
		ob[i]->remove_object();
	}
	if((str == "legs"))
	{
		write("The cool spring water refreshes you as you wash "+
		"your legs.\n");
		say(QCTNAME(TP)+" washes "+HIS+" legs with some of the "+
		"spring water.\n");
		return 1;
	}
}
void
init()
{
	::init();
	add_action(drink_it, "drink");
	add_action(do_enter, "enter");
	add_action(wash_it, "wash");
}