/*
 * /d/Gondor/lebennin/sirith/farms/farm2/garden.c
 * vegetable garder of small farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * XXX might eventually convert the add_cmd_item()'s to add_action()'s
 * so other people in the room will see a player lift the well cover,
 * climb the stilts, etc
 *
 * XXX respond to the enterprising soul who finds a bucket and rope
 * somewhere and tries to get water from the well.
 */

#pragma strict_types

#include <language.h>			/* for LANG_ADDART 	*/
#include <ss_types.h>			/* for SS_AWARENESS	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

static int	Snake_here = 1;		/* snake in the vegetables?	*/

public void	create_outdoors();
public void	reset_room();
public void	init();
public int	pick_veg(string arg);	/* pick vegetable from garden	*/
public string	herb_search(object player, string str);


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    string *herbslist;

    set_areatype("farmyard");
    set_short("a hedged farmyard in southern Lebennin");
    set_extraline("Vegetables are planted in rows parallel to the "+
	"south hedge, and a small shed stands between the garden "+
	"and the house. Next to the shed is a low, covered well.");

    add_exit("eastyard", "north", 0, 2);
    set_no_exit_msg( ({ "northeast", "east", "southeast",
	"south", "southwest", "west", "northwest", "down" }),
	BSN("You meander among the rows of vegetables.") );
    set_no_exit_msg( ({ "up" }),
	BSN("You hoist yourself up one of the stilts until your nose "+
	    "bumps the floor of the shed. You hang there for a moment, "+
	    "unable to climb higher or to reach the door, then drop back "+
	    "to the ground."));

    herbslist =  ({ HERB_DIR + "bean_green", HERB_DIR + "bean_kidney",
	HERB_DIR + "bean_lima", HERB_DIR + "basil", HERB_DIR + "carrot",
	HERB_DIR + "garlic", HERB_DIR + "gonion", HERB_DIR + "rpotato" });
    set_up_herbs( ({ ONE_OF_LIST(herbslist), ONE_OF_LIST(herbslist),
	ONE_OF_LIST(herbslist) }),
	({ "garden", "vegetables", "vegetable", "vegetable garden",
	   "row", "rows" }),
	5);

    add_item( ({ "farm", "farmyard" }),
	BSN("The garden, trees and buildings all seem well cared for."));
    add_item( ({ "hedge" }),
	BSN("A dense hedge encloses the entire farmyard."));
    add_item( ({ "tree", "trees", "fruit tree", "fruit trees" }),
	BSN("There are trees on the north side of the farmyard, but you "+
	    "can't see details from here."));
    add_item( ({ "row", "rows", "south hedge", "garden",
		 "vegetable garden", "vegetable", "vegetables" }),
	BSN("Vegetables grow in long rows parallel to the south hedge. "+
	    "They appear to be thriving."));
    add_item( ({ "building", "buildings" }),
	BSN("There's a small shed at the west end of the garden and "+
	    "beyond it, a farmhouse."));
    add_item( ({ "house", "farmhouse" }),
	BSN("The simple, sturdy farmhouse is built of river stones, with "+
	    "a shaggy thatch roof."));
    add_item( ({ "thatch", "roof" }),
	BSN("The thatch, although shaggy, appears to be in good condition."));
    add_item( ({ "shed" }),
	BSN("The shed is raised on stout log stilts; its floor is just "+
	    "above your head. The shed door is closed."));
    add_item( ({ "floor", "shed floor", "plank", "planks" }),
	BSN("The wooden floor of the shed is just above your head. The "+
	    "planks fit together tightly."));
    add_item( ({ "logs", "stilts", "log stilts" }),
	BSN("The stilts raise the shed well off the ground, possibly "+
	    "to protect its contents from the depredations of local "+
	    "wildlife."));
    add_item( ({ "door", "latch" }),
	BSN("The door is held closed by a stout iron latch."));
    add_item( ({ "well", "wall", "stone wall" }),
	BSN("The well's stone wall is perhaps two feet high; "+
	    "atop the well rests a sturdy wooden cover."));
    add_item( ({ "stones", "stone" }),
	BSN("The smooth stones fit neatly together."));
    add_item( ({ "cover" }),
	BSN("The wooden cover looks as if it's fairly heavy."));
    add_item( ({ "soil", "dirt", "loam", "ground" }),
	BSN("The soil seems to be a well-drained, fertile loam."));

    /* pity add_cmd_item doesn't support "say" */
    add_cmd_item( ({ "door", "latch" }), ({ "open" }),
	BSN("You cannot reach the latch." ));
    add_cmd_item( ({ "shed" }), ({ "enter", "open", "search" }),
	BSN("The door is closed, and you cannot reach the latch."));
    add_cmd_item( ({ "stilt", "stilts", "log", "logs", "log stilt",
		     "log stilts" }),
	({ "climb" }),
	BSN("You hoist yourself up one of the stilts until your nose "+
	    "bumps the floor of the shed. You hang there for a moment, "+
	    "unable to climb higher or to reach the door, then drop back "+
	    "to the ground."));
    add_cmd_item( ({ "cover", "well cover" }),
	({ "open", "get", "take", "lift", "move", "slide" }),
	BSN("With some difficulty, you lift the well cover and peer into the "+
	    "well. You find nothing of interest, and replace the cover."));
    add_cmd_item( ({ "well" }),
	({ "open", "enter", "search", "climb down" }),
	BSN("With some difficulty, you lift the well cover and peer into the "+
	    "well. You find nothing of interest, and replace the cover."));
} /* create_outdoors */


/*
 * Function name:	reset_room 
 * Description	:	replenish snake
 */
public void
reset_room()
{
    ::reset_room();
    if (!objectp(present("snake", TO)))
    {
	Snake_here = 1;
    }
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(pick_veg, "pick");
    add_action(pick_veg, "take");
    add_action(pick_veg, "get");
} /* init */


/*
 * Function name:	pick_veg
 * Description	:	handle attempts to pick/get/take vegetables
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we recognize the arg, 0 otherwise
 *
 * Since vegetables are herbs and the standard herb_search always
 * imposes a search time, it seemed wrongheaded to allow "pick" instantly
 * to retrieve a herb. We force them to search, instead.
 */
public int
pick_veg(string arg)
{
    string	where, what;
    object	*match;

    /* parse_command(), rather than present(), so that
     * "get third torch" does the right thing
     */
    if (!strlen(arg) || 
        arg == "cover" ||
        arg == "well cover" ||
        parse_command(LOW(arg), all_inventory(TO), "%i", match))
    {
	return 0;
    }

    /* allow "pick vegetable[s] [from [vegetable] garden|rows]"
     * or pick by name (e.g., "pick carrot from vegetables").
     * this does allow for "pick vegetables from vegetables", but
     * i suppose i can live with it.
     */
    if (sscanf(arg, "%s from %s", what, where) == 2)
    {
    	if (where != "garden" &&
	    where != "vegetable garden" &&
	    where != "rows" &&
	    where != "vegetables")
	{
	    return 0;
	}
    }
    else
    {
	what = arg;
    }
    if (what == "vegetable")
    {
	what = "vegetables";
    }
    if (!TP->query_wiz_level())
    {
	TP->command("$search garden for "+what);
    }
    else
    {
	write("Ordinarily, this room would do\n"+
	    "	this_player()->command(\"$search garden for "+what+"\");\n"+
	    "Since you're a wizard, that won't work.\n"+
	    "Please do the search yourself.\n");
    }
    return 1;
} /* pick_veg */


/*
 * Function name:	herb_search
 * Description	:	intercept default herb_search() so players may
 *			search for vegetable[s] or [garter]snake
 * Arguments	:	object player -- person doing the search
 *			string str -- their search string
 * Returns	:	string describing results of search
 */
public string
herb_search(object player, string str)
{
    string	where,
		what,
		timestr = tod();
    object	snake;
    object	tp = TP;/* XXX sometimes, but not always, after moving
			 * the snake into this room, this_player() is
			 * the snake, not a player. i try to catch it.
			 */

    if (!strlen(str))
    {
	return "";
    }

    /* we want to accept searching for "vegetables", as well as "herbs"
     * and herbs by name, so intercept:
     *	"search [vegetable] garden [for vegetables]" 
     *	"search vegetables"
     *	"search rows [for vegetables]" 
     * and turn them into:
     *	"search garden for herbs"
     * pass anything else thru unchanged
     */

    if (sscanf(str, "%s for %s", where, what) != 2)
    {
	where = str;
    }

    /* if there's a snake in the garden, find it before anything else */
    if (Snake_here &&
	timestr != "dusk" &&
        timestr != "evening" &&
	timestr != "night")
    {
	if ((where == "here" ||
	     where == "garden" ||
	     where == "vegetables" ||
	     where == "vegetable garden" ||
	     where == "rows") &&
	    objectp(snake = clone_object(SIRITH_FARMS_DIR+"npc/gartersnake")))
	{
	    /* not using clone_npc() because it will say the snake "arrives"
	     * & i want them to seem to find the snake in the vegies.
	     */
	    if (snake->move(TO) == 0)
	    {
		if (tp != TP)	/* XXX */
		{
		    ERR_LOG("\n\tbefore calling move() in\n\t"+
			file_name(snake)+
			"\n\tTP was "+file_name(tp)+
			"\n\tafter, was "+file_name(TP)+"\n");
		    set_this_player(tp);
		}			/* XXX */
		Snake_here = 0;
		snake->set_restrain_path(file_name(TO));
		SAY(" finds a snake in the vegetables.");
		return BSN("You find a snake beneath the vegetables.");
	    }
	    /* else move() failed */
	    snake->remove_object();
	    if (what == "snake" || what == "gartersnake")
	    {
	        return "";
	    }
	}
    }

    if ((where == "here" ||
	 where == "garden" ||
	 where == "vegetables" ||
         where == "rows" ||
	 where == "vegetable garden") &&
        (!strlen(what) ||
	 what == "vegetables"))
    {
	str = "";
	what = ::herb_search(player, "garden for herbs");
    }
    else
    {
    	what = ::herb_search(player, str);
    }

    /* if str is null, then they searched for vegies, so make the failure
     * msg say vegetables, not herbs. 
     *
     * this is not quite enough. on success, search_for_herbs() in
     * /std/room/description.c is going to tell the room that "Foo finds
     * some herbs."  bummer. i'd have to roll my own search_for_herbs() to
     * get that to say "Foo finds some vegetables."  i doubt it's worth it
     * ... lets see if anyone notices and files a report. 
     */
    if (!strlen(str) &&
        what == "You search everywhere, but find no herbs.\n")
    {
	return "You search everywhere, but find no vegetables.\n";
    }
	
    return what;
} /* herb_search */
