/*
 * Hallway at the top of the stairs from the main hall
 * of the Greystone Inn.  May want to add the ability
 * to turn off each of the sconce lamps.
 *
 * Mortis 11.2005
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_ROOMBASE;

#define FOUND_LATCH		"_player_found_latch"

int window = 1; // Starts closed.
int latch = 1;  // Starts closed.
string spring_found();

void 
init()
{    
    ::init();
//	add_action("search_latch", "search");
}

create_palan_room()
{
	SHORT("A lighted hall of doors with a staircase");
	LONG("A flight of stairs from below lands here in this hallway before "
	+ "spiraling up to the third floor.  The hallway stretches to your "
	+ "southwest with two doors to guest accomodations on each side and a "
	+ "window at its end.  A carpet of grey runs from the stairs to the "
	+ "window leaving a border of the polished wood beneath to its sides.  "
	+ "On each wall are hung dark iron sconces fitted with low burning "
	+ "torches illuminating the hallway with a steady, soft glow.\n");

//	ITEM("doors", "?\n");
	ITEM(({"torch", "torches", "sconce", "sconces", "lamp", "lamps"}),
	  "Dark iron fittings bolted to the walls hold what at first glance "
	+ "appear to be torches.  The torches in fact are iron oil-lamps.  "
	+ "The handle of the torch is an iron oil basin, and its top contains a "
	+ "recessed wick within a crenellated rim giving it the appearance of a "
	+ "steady glowing torch.\n");
	ITEM("carpet", "A thin, grey carpet has been rolled out from the stairs "
	+ "down the length of the hallway to the window.  It's not as wide as "
	+ "the hall, and the edges of the wood floor beneath can be seen.\n");
	ITEM("floor", "The floor is completely done with strips of dark stained "
	+ "mahogany.  Though old, the wood adds a rich tone to the hallway "
	+ "keeping it from appearing bright.  Only the edges along the walls "
	+ "can be seen due to the thin, grey carpet running the hallway's "
	+ "length.\n");
	ITEM(({"wall", "walls"}), "The lower portion of the walls is done in "
	+ "similar fashion to the strips of dark-stained mahogany in the "
	+ "floor then topped with an intricately trimmed strip of wood.  "
	+ "Above the strip the walls have been painted off-white and set "
	+ "with dark iron torch sconces between the doors.\n");
	ITEM("ceiling", "The ceiling is not directly lit.  Flickering shadows "
	+ "from the hall's lights cast shadow on its dark wood.\n");
	ITEM(({"stairs", "staircase", "staircases", "flight"}), "A flight of "
	+ "wooden stairs leads down to the main hall and spirals up from here "
	+ "to the floor above.  A wooden balustrade guards the outside of the "
	+ "steps.\n");
	ITEM("balustrade", "This wooden handrail is worn with age and use.  It "
	+ "lines the steps for safety.\n");
	ITEM("hallway", "You're in the hallway.  Have a look.\n");
	ITEM("window", "A two-sectioned window, each with four panes, looks "
	+ "out onto the alley behind the inn.  If you'd like to look through "
	+ "it, you may <check window>.  " + "@@window_state@@" + "  The window's "
	+ "latch keeps it shut and is currently " + "@@latch_state@@" +"\n");
	ITEM(({"latch", "window latch"}), "The latch between the two sections "
	+ "of the window turns to unblock the lower section from being raised.  "
	+ "It is currently " + "@@latch_state@@" + "  " + "@@latch_know@@" + "\n");
	ITEM("spring", "@@spring_found@@");

	CMD("window", "check", "@@check_window");
	CMD("latch", "turn", "@@turn_latch");

//	add_search(({"latch","window latch"}),4,"search_latch",1);

	EXIT(NOBLE + "greystone", "down", 0, 0);
	EXIT(NOBLE + "grey_up3", "up", 0, 0);

//	doors 1-4
}

window_state()
{
	/* Open or closed basically */
	if (window == 0)
	{ return "The lower section of the window is currently slid up behind "
	+ "the upper section allowing a cool breeze in."; }
	return "The window is at the moment shut.";
}

latch_state()
{
	/* Open or closed basically */
	if (latch == 0)
	{ return "unlatched."; }
	return "turned closed.";
}

latch_know()
{
	/* Whether or not a player has learned how to turn the latch. */
	if (TP->query_prop(FOUND_LATCH == 1))
	{
		return "While searching the window latch, your hand brushes against "
		+ "a spring recessed into the side of the window where the upper "
		+ "and lower window sections meet.  It's keeping a lever in place "
		+ "that blocks the latch from turning.  Using it, you should be "
		+ "able to turn the latch now.";
	}

	if (TP->query_skill(110) > 25 + random(16))
	{
		TP->add_prop(FOUND_LATCH, 1);
		return "While searching the window latch, your hand brushes against "
		+ "a spring recessed into the side of the window where the upper "
		+ "and lower window sections meet.  It's keeping a lever in place "
		+ "that blocks the latch from turning.  Using it, you should be "
		+ "able to turn the latch now.";
	}
	return "You perform a cursory search of the window latch.  It's "
	+ "certainly confusing how to get it to turn.";
}

string
spring_found()
{
	/* If prop for latch_know, returns desc for spring
	 * else exa what?
	 */
	 return "test.\n";
}

search_latch(string str)
{
	/*	SEARCH(({/* Gives prop for latch_know.  Search to find spring on left
		side that allows latch to turn and window to open.  }))
		This does NOT work right yet.

	if (!str || !str == "latch" || !str == "window latch")
	{
		return 0;
	}*/

	if (TP->query_prop(FOUND_LATCH == 1))
	{
		write("You've already found the spring that blocks the latch from "
		+ "turning.  If you're looking for love, this is the wrong place.\n");
		return 1;
	}
	write("You start to search the window latch.\n");
	say(QCTNAME(TP) + " starts to search the window.\n");

	if (TP->query_skill(110) > 25 + random(16))
	{
		TP->add_prop(FOUND_LATCH, 1);
		set_alarm(3.0, 0.0, "result_search_latch");
		return 1;
	}
	set_alarm(3.0, 0.0, "result_search_latch1");
	return 1;
}

result_search_latch()
{
	write("While searching the window latch, your hand brushes against "
	+ "a spring recessed into the side of the window where the upper "
	+ "and lower window sections meet.  It's keeping a lever in place "
	+ "that blocks the latch from turning.  Using it, you should be "
	+ "able to turn the latch now.\n");
	return 1;
}

result_search_latch1()
{
	write("You perform a cursory search of the window latch.  It's "
	+ "certainly confusing how to get it to turn.  You learn that "
	+ "much.\n");
	return 1;
}

check_window()
{

}

turn_latch()
{

}
