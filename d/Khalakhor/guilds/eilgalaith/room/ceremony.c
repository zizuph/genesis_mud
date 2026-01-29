/**********************************************************************
 * - ceremony.c                                                     - *
 * - An open room to all players where members of EG can conduct    - *
 * - ceremonies.                                                    - *
 * - Has free emotes to assist with roleplay environment.           - *
 * - Created by Damaris@Genesis 04/2007                             - *
 **********************************************************************/
#include "../guild.h"
#include <stdproperties.h>


#include "/d/Khalakhor/sys/terrains.h"
#define HERBMASTER   ("/d/Khalakhor/common/herbs/herb_master")
#define STDHERBSEARCH ("/d/Khalakhor/lib/herb_search")
#define TERRAINSERVER ("/d/Khalakhor/lib/terrain_server")
#define PATH "/d/Khalakhor/inisi/galaith/room/isl0505"
#define ONE_OF(x)    one_of_list(x)
inherit GUILD_ROOM;
inherit "/d/Khalakhor/lib/herbsearch";

#include "emotes.c"

string *herbs; // init in setup_forest_herbs()
public void
setup_forest_herbs()
{
	herbs = HERBMASTER->query_herbs(({TERRAIN_MIXEDWOOD,}));
	set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
	ONE_OF(herbs)}), ({"grass","here"}),2);
}
public void
create_guild_room()
{

	set_short("a circular grove");
	set_long("   Massive ancient tress outline this circular "+
	"grove where twelve large granite stones emerge from the "+
	"ground. Light gently cascades through the canopy above to "+
	"shine upon a small spring, mound of earth and a small swirl of "+
	"leaves that are direct center, which could be described as "+
	"monuments. A small path is visible just within a cluster "+
	"of trees.\n");
	add_item(({"room", "area", "grove", "circular grove"}), query_long);
	add_item(({"cluster of trees"}),
	"There is clusters of trees circling the grove.\n");
	
	add_item(({"bushes"}),
	"There are thick green bushes within the tresses.\n");
	add_item(({"path"}),
	"Entering the path will lead out of the grove.\n");
	
	add_item(({"wall", "walls", "eilgalaith","ceiling", "floor", "flooring","marble","pattern", "patterns","eil-galaith"}),
	"What?\n");
	add_item(({"light"}),
	"Light gently cascades through the canopy above.\n");
	add_item(({"ground"}),
	"The ground is blanketed with soft vibrant green grass.\n");
	add_item(({"grass", "vibrant green grass", "green grass"}),
	"The grass is soft and vibrant green.\n");
	add_item(({"tree", "trees", "massive tree", "massive trees"}),
	"Massive trees enshroud this grove protectively.\n");
	add_item(({"sky"}),
	"The sky is barely visible through the canopy.\n");
	add_item(({"canopy"}),
	"The canopy from the trees cover this grove protectively.\n");
	add_item(({"spring", "small stream"}),
	"The spring bubbles forth with fresh crystal clear water.\n");
	add_item(({"earth", "mound", "mound of earth"}),
	"A mound of earth rises in the center of this grove.\n");
	add_item(({"swirl", "swirl of wind", "swirl of leaves"}),
	"A small yet continuous swirl of air circulates leaves in "+
	"a soft whimsical path in the center of this grove.\n");
	add_item(({"leaves", "leaf"}),
	"There are different coloured leaves scattered the ground "+
	"and on the trees along with some that have been caught up "+
	"in a soft whimsical swirl of air in the center of this grove.\n");
	add_item(({"wind"}),
	"There is only the slightest breeze here.\n");
	add_item(({"symbol", "symbols"}),
	"There are many different symbols carved on the granite "+
	"stones.\n");
	
	add_item(({"stone", "stones", "large stone", "large stones", "large granite stone", "large granite stones","granite stone", "granite stones"}),
	"There are twelve large granite stones here.\n");
	
	add_item(({"first stone","first large stone", "first granite stone"}),
	"This large granite stone has the word 'Driliau' carved into "+
	"it's surface with flowing elven script along with the symbol of "+
	"water and alchemy.\n");
	add_item(({"second stone","second large stone", "second granite stone"}),
	"This large granite stone has the word 'Xelith' carved into it's "+
	"surface with flowing elven script along with the symbol of "+
	"air and warriors.\n");
	add_item(({"third stone","third large stone", "third granite stone"}),
	"This large granite stone has the word 'Ellilith' carved into "+
	"it's surface with flowing elven script along with the symbol of "+
	"earth and tiller.\n");
	add_item(({"fourth stone", "fourth large stone", "fourth granite stone"}),
	"This large granite stone has the word 'Khilarith' carved into "+
	"it's surface with flowing elven script along with the symbol of "+
	"water and elf.\n");
	add_item(({"fifth stone", "fifth large stone", "fifth granite stone"}),
	"This large granite stone has the word 'Quillith' carved into "+
	"it's surface with flowing elven script along with the symbol of "+
	"air and scholar.\n");
	add_item(({"sixth stone", "sixth large stone", "sixth granite stone"}),
	"This large granite stone has the word 'Jilaith' carved into "+
	"it's surface with flowing elven script along with the symbol of "+
	"earth and herbs.\n");
	add_item(({"seventh stone", "seventh large stone", "seventh granite stone"}),
	"This large granite stone has the word 'Silith' carved into it's "+
	"surface with flowing elven script along with the symbol of "+
	"water and commerce.\n");
	add_item(({"eighth stone", "eighth large stone", "eighth granite stone"}),
	"This large granite stone has the word 'Uluith' carved into it's "+
	"surface with flowing elven script along with the symbol of "+
	"air and magic.\n");
	add_item(({"ninth stone", "ninth large stone", "ninth granite stone"}),
	"This large granite stone has the word 'Sillaith' carved into "+
	"it's surface with flowing elven script along with the symbol of "+
	"earth and forge.\n");
	add_item(({"tenth stone", "tenth large stone", "tenth granite stone"}),
	"This large granite stone has the word 'Wylith' carved into it's "+
	"surface with flowing elven script along with the symbol of "+
	"water and cartography.\n");
	add_item(({"eleventh stone", "eleventh large stone", "eleventh granite stone"}),
	"This large granite stone has the word 'Eilaith' carved into "+
	"it's surface with flowing elven script along with the symbol of "+
	"air and scribe.\n");
	add_item(({"twelfth stone", "twelfth large stone", "twelfth granite stone"}),
	"This large granite stone has the word 'Ailia' carved into it's "+
	"surface with flowing elven script along with the symbol of "+
	"air and healing.\n");
	add_fail("auto", "The trees are too thick to pass in that "+
	"direction.\n");
	add_prop(OBJ_I_CONTAIN_WATER, 1);	
	setup_forest_herbs();
	add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_FOREST);
}

int
wash_it(string str)
{
	if((str == "face"))
	{
		write("You dip your hands into the spring washing "+
		"your face with the refreshing water.\n"+
		"It feels refreshing on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP) + " dips " + HIS(TP) + " hands into "+
		"the spring washing " + HIS(TP) + " face with the "+
		"refreshing water.\n");
		return 1;
	}
	if((str == "hands"))
	{
		write("You dip your hands into the spring washing them "+
		"with the refreshing water.\n"+
		"It feels refreshing on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP) + " dips " + HIS(TP) + " hands into the "+
		"spring washing them with the refreshing water.\n");
		return 1;
	}
	if((str == "neck"))
	{
		write("You dip your hands into the spring washing your "+
		"neck with the refreshing water.\n"+
		"It feels refreshing on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP) + " dips " + HIS(TP) + " hands into the "+
		"spring washing "+ HIS(TP) +" neck with the refreshing "+
		"water.\n");
		return 1;
	}
	if((str == "ears"))
	{
		write("You dip your hands into the spring washing your "+
		"ears with the refreshing water.\n"+
		"It feels refreshing on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP) + " dips " + HIS(TP) + " hands into the "+
		"spring washing " + HIS(TP) + " ears with the refreshing "+
		"water.\n");
		return 1;
	}
	if((str == "feet"))
	{
		write("You dip your hands into the spring washing your "+
		"feet with the refreshing water.\n"+
		"It feels refreshing on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP) + " dips " + HIS(TP) + " hands into the "+
		"spring washing " + HIS(TP) + " feet with the refreshing "+
		"water.\n");
		return 1;
	}
	if((str == "body") | (str == "me"))
	{
		write("You dip your hands into the spring washing your "+
		"body with the refreshing water.\n"+
		"It feels refreshing on your skin.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP) + " dips " + HIS(TP) + " hands into the "+
		"spring washing " + HIS(TP) + " body with the refreshing "+
		"water.\n");
		return 1;
	}
	return notify_fail("Wash what?\n");
}

int
drink_it(string str)
{
	string what, where;
	int i;
	if (!strlen(str))
	{
		return notify_fail("Drink what?\n");
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
		return notify_fail("Drink what?\n");
	}
	if (where && !parse_command(where, ({}), "[the] 'spring' "))
	{
		/* Technically, this isn't going to show because of 
		 * the standard 'drink' command.  Really, there's not 
		 * much choice, though, since we don't want to return 1.
		 */
		return notify_fail("Drink from where?\n");
	}
	
	/* Drink small amounts up to 500 soft */
	for (i = 0; i < 10; i++)
	{
		if (!TP->drink_soft(50))
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
	if (!TP->drink_soft(50, 1))
	{
		write("You take a drink from the spring.\n"+
		"Drinking your fill, you feel refreshed.\n");
	}
	else
	{
		write("You take a drink from the spring.\n");
	}
	say(QCTNAME(TP) +" drinks some water from the spring.\n");
	return 1;
}

int
enter_path(string str)
{
	if (str != "path")
	{
		return notify_fail("Enter what?\n");
	}
	write("You start on the path finding your way through the trees.\n\n");
	say(QCTNAME(TP) + " starts down the path.\n");
	TP->move_living("M", PATH, 1, 0);
	
	say(QCTNAME(TP)+" suddenly appears through a grove of trees.\n");
	return 1;
}

void
init()
{
	::init();
	init_emotes();
	add_action(drink_it,   "drink");
	add_action(wash_it,     "wash");
	add_action(enter_path, "enter");
}
