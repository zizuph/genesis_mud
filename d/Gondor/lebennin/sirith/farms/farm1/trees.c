/*
 * /d/Gondor/lebennin/sirith/farms/farm1/trees.c
 * trees on large farmstead in southern lebennin;
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

#include <stdproperties.h>   /* for OBJ_S_SEARCH_FUN, OBJ_I_SEARCH_TIME */
#include <language.h>		/* for LANG_ADDART			*/
#include <ss_types.h>		/* for SS_AWARENESS			*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			
#include "/d/Gondor/common/mordor/sys/clock.h"

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";


#define	NPLUMS	3			/* # of plums per reset		*/
static int	Nplums = NPLUMS;	/* how many plums are left	*/
static int	pick_plum(string arg);	/* handle picking a plum	*/
#define	NEGGS	2			/* # of eggs per reset		*/
static int	Neggs = NEGGS;		/* how many eggs are left	*/
#define	NHENS	4			/* # of hens per reset		*/
static object	*Hens = allocate(NHENS);
static object	Rooster;


public void		create_outdoors();
public void		reset_room();
public void		init();
public int		pick_plum(string arg);
public string		do_search(object tp, string arg);
static varargs string	search_box(object tp, string where, string what);
public void		sunrise();
public void		sunset();


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    string timestr = tod();

    set_areatype("farmyard");
    set_short("a farmyard in southern Lebennin");
    set_extraline("Sparse grass grows beneath squat plum trees, "+
	"and a long white box is set against the hedge.");

    add_exit("hedgeyard", "north", 0, 2);
    add_exit("garden", "northeast", 0, 2);
    set_no_exit_msg( ({ "east", "southeast",
	"south", "southwest", "west", "northwest", "down" }),
	BSN("You stroll beneath the trees.") );
    set_no_exit_msg("up",
	BSN("You catch a branch and start to pull yourself up into "+
	    "the tree, but it creaks loudly. You drop back to the ground."));

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 2);

    add_item( ({ "farm", "farmyard", "yard" }),
	BSN("The garden, trees and house are enclosed by a sturdy hedge."));
    add_item( ({ "hedge" }),
	BSN("The hedge is very thick and about head-high."));
    add_item( ({ "fruit tree", "fruit trees", "plum tree", "plum trees",
    	"tree", "trees" }),
	BSN("The plum trees are rather short and twiggy, but they "+
	    "seem to bear healthy fruit."));
    add_item( ({ "fruit", "plum", "plums", "branch", "branches" }),
	BSN("Plums dangle from the branches above your head."));
    add_item( ({ "sparse grass", "ground", "grass", "clump", "clumps" }),
	BSN("Short, broad-bladed grass grows in clumps beneath the trees."));
    add_item( ({ "garden", "vegetable garden", "vegetables" }),
	BSN("The vegetable garden to the northeast appears to be thriving."));
    add_item( ({ "building", "buildings" }),
	BSN("From here, the only building you can see is a farmhouse "+
	    "to the northwest."));
    add_item( ({ "farmhouse", "house" }),
	BSN("You don't have a clear view from here, but the farmhouse "+
	    "looks well-kept."));

    add_cmd_item( ({ "tree", "trees", "plum tree", "plum trees" }),
	({ "climb" }),
	BSN("You catch a branch and start to pull yourself up into "+
	    "the tree, but it creaks loudly. You drop back to the ground."));

/*
    if (!objectp(find_object(SIRITH_MASTER)))
    {
	SIRITH_MASTER->create_object();
    }
*/

    /* set box items, create chickens if necessary */
    if (timestr != "dusk" && timestr != "evening" && timestr != "night")
    {
	sunrise();
    CLOCK->notify_dusk(sunset);
    }
    else
    {
	sunset();
    CLOCK->notify_dawn(sunrise);
    }
} /* create_outdoors */


/*
 * Function name:	reset_room
 * Description	:	replenish plums, eggs, chickens
 */
public void
reset_room()
{
    string timestr = tod();

    ::reset_room();
    Nplums = NPLUMS;
    Neggs = NEGGS;

    if (timestr != "dusk" &&
	timestr != "evening" &&
	timestr != "night")
    {
	clone_npcs(Hens, (SIRITH_FARMS_DIR+"npc/hen"), 4.0,
	           ({ (SIRITH_FARMS_DIR+"farm1/trees"),
	              (SIRITH_FARMS_DIR+"farm1/garden") }) );
	Hens->set_random_move(120);
	Rooster = clone_npc(Rooster, (SIRITH_FARMS_DIR+"npc/rooster"),
		            ({ (SIRITH_FARMS_DIR+"farm1/trees"),
	                       (SIRITH_FARMS_DIR+"farm1/garden") }) );
	Rooster->set_random_move(120);
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
    add_action(pick_plum, "pick");
    add_action(pick_plum, "take");
    add_action(pick_plum, "get");
} /* init */


/*
 * Function name:	pick_plum
 * Description  :	let player pick a plum (if any are left)
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if arg is sensible (whether or not there
 *				are any plums left to pick)
 *			0 if arg doesn't parse
 * For consistency with gardens, and in case apples/plums ever 
 * become herbs, force "pick" to become "search".
 */
public int
pick_plum(string arg)
{
    string type, where, what;

    if (!strlen(arg))
    {
	return 0;
    }

    /* allow "pick plum[s]|fruit[s] [from plum|fruit tree[s]]" */
    if (sscanf(arg, "%s from %s %s", what, type, where) == 3 ||
        sscanf(arg, "%s from %s", what, where) == 2)
    {
    	if (where != "tree" &&
	    where != "trees")
	{
	    return 0;
	}
    }
    else
    {
	what = arg;
    }
    if (what != "plum" &&
	what != "plums" &&
        what != "fruit" &&
	what != "fruits")
    {
	return 0;
    }
    if (strlen(type) &&
	type != "plum" &&
	type != "fruit")
    {
	return 0;
    }

    if (!TP->query_wiz_level())
    {
	TP->command("$search trees for plums");
    }
    else
    {
	write("Ordinarily, this room would do\n"+
	    "	this_player()->command(\"$search trees for plums\");\n"+
	    "Since you're a wizard, that won't work.\n"+
	    "Please do the search yourself.\n");
    }
    return 1;
} /* pick_plum */


/*
 * Function name:	do_search
 * Description	:	handle searching trees for plums
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 * Return	:	string describing results of search
 *
 * passes search for other stuff (e.g., chicken coop) off to search_box()
 */
public string
do_search(object tp, string arg)
{
    object	plum;
    string	type, where, what;
    int		nmatch;

    /* check first for the command() from pick_plum() */
    if (arg != "trees for plums")
    {
	/* not from pick_plum() -- player searched directly */
	if (!strlen(arg))
	{
	    return "";
	}

	/* allow "search [plum|fruit] tree[s] [for plum[s]|fruit[s]]" */
	if ((nmatch = sscanf(arg, "%s %s for %s", type, where, what)) == 3 ||
	    (nmatch = sscanf(arg, "%s for %s", where, what)) == 2)
	{
	    if (what != "plum" &&
		what != "plums" &&
	        what != "fruit" &&
		what != "fruits")
	    {
		/* a little work here saves having to repeat the
		 * calls to sscanf() in search_box()
		 */
		if (nmatch == 2)
		{
		    return search_box(tp, where, what);
		}
		return search_box(tp, type+" "+where, what);
	    }
	}
	else
	{
	    where = arg;
	}
	if (where != "tree" &&
	    where != "trees");
	{
	    return search_box(tp, where);
	}
	if (nmatch == 3 &&
	    type != "plum" &&
	    type != "fruit")
	{
	    return "";
	}
    }

    if (Nplums > 0 &&
        TP->query_skill(SS_AWARENESS) >= (MIN_AWARE + random(RANDOM_AWARE)) &&
        objectp(plum = clone_object(SIRITH_FARMS_DIR+"obj/plum")))
    {
	--Nplums;
	what = "You reach up to a low-hanging branch and pick "+
	       "a plum.\n";
	SAY(" picks a plum.");
	if (plum->move(TP))
	{
	    what += "Oops, you dropped the plum.\n";
	    SAY(" drops a plum.");
	    plum->move(TO);	/* assume this works :-) */
	}
    }
    else
    {
	what = "None of the plums within your reach appears ripe.\n";
    }
    return what;
} /* do_search */


/*
 * Function name:	search_box
 * Description	:	handle searching the chicken coop
 * Arguments	:	object tp	this player
 *			string where	where to search
 *			string what	what to search for (optional)
 * Return	:	string describing search results
 */
static varargs string
search_box(object tp, string where, string what = 0)
{
    object	egg;
    string	msg,
		timestr = tod();

    if (strlen(what) &&
	what != "egg" &&
	what != "eggs")
    {
	return "";
    }

    if (where != "box" &&
	where != "straw" &&
	where != "bottom" &&
        where != "box bottom" &&
	where != "bottom of box")
    {
	return "";
    }

    if (timestr == "dusk" ||
	timestr == "evening" ||
	timestr == "night")
    {
	return "You search the closed box, but find nothing.\n";
    }

    if (Neggs > 0 &&
        TP->query_skill(SS_AWARENESS) >= (MIN_AWARE + random(RANDOM_AWARE)) &&
        objectp(egg = clone_object(SIRITH_FARMS_DIR + "obj/egg")))
    {
	--Neggs;
	msg = "You find an egg buried in the straw.\n";
	SAY(" finds an egg in the box.");
	if (egg->move(TP))
	{
	    msg += "Oops, you dropped the egg.\n";
	    SAY(" drops an egg.");
	    /* we very kindly don't break the egg */
	    egg->move(TO);
	}
    }
    else
    {
    	msg = BSN("You search the "+where+
	   ", but do not find anything of interest.");
    }
    return msg;
} /* search_box */


/*
 * Function name:	sunrise
 * Description	:	fake moving the chickens from coop to room
 *
 * change coop description and clone chickens for room
 */
public void
sunrise()
{
    CLOCK->notify_dawn(sunrise);
    tell_room(TO, "A stout tanned male human arrives.\n"+
	"The stout tanned male human opens the box.\n"+
	"The stout tanned male human leaves north.\n");

    /* make the interval short so we don't have to worry
     * about players looking at the box while there are
     * still some chickens inside
     */
    clone_npcs(Hens, (SIRITH_FARMS_DIR+"npc/hen"), 1.0,
	       ({ (SIRITH_FARMS_DIR+"farm1/trees"),
	          (SIRITH_FARMS_DIR+"farm1/garden") }) );
    Hens->set_random_move(120);
    Rooster = clone_npc(Rooster, (SIRITH_FARMS_DIR+"npc/rooster"),
	    	        ({ (SIRITH_FARMS_DIR+"farm1/trees"),
	       	           (SIRITH_FARMS_DIR+"farm1/garden") }) );
    Rooster->set_random_move(120);

    add_item( ({ "long white box", "white box", "box", "block", "blocks" }),
	BSN("The box sits on blocks that raise it about two feet off "+
	    "the ground; its hinged door stands open. "+
	    "The bottom of the box is covered with straw."));
    add_item( ({ "door" }),
	"The door is folded back to lie flat atop the box.\n");
    add_item( ({ "straw", "bottom", "box bottom", "bottom of box" }),
	"The straw appears reasonably clean.\n");

    remove_cmd_item("box");
    remove_cmd_item("door");
    add_cmd_item( ({ "box", "door" }),
	({ "fold", "swing", "open", "close" }),
	BSN("You swing the door back and forth for a while, then "+
	    "fold it back atop the box."));
} /* sunrise */


/*
 * Function name:	sunset
 * Description	:	fake moving the chickens from room to coop
 *
 * change coop description and remove chickens
 */
public void
sunset()
{
    int		i,
		found_chicken;
    object	env;

    CLOCK->notify_dusk(sunset);
    for (i = 0; i < NHENS; ++i)
    {
	if (objectp(Hens[i]) &&
	    !objectp(Hens[i]->query_attack()))
	{
	    if (objectp(env = ENV(Hens[i])) &&
		env != TO)
	    {
		Hens[i]->move_living("southwest", TO, 1, 1);
	    }
	    ++found_chicken;
	    Hens[i]->remove_object();
	    Hens[i] = 0;
	}
    }
    if (objectp(Rooster) &&
	!objectp(Rooster->query_attack()))
    {
	if (objectp(env = ENV(Rooster)) &&
	    env != TO)
	{
	    Rooster->move_living("southwest", TO, 1, 1);
	}
	++found_chicken;
	Rooster->remove_object();
	Rooster = 0;
    }

    if (found_chicken)
    {
	tell_room(TO, "A stout tanned male human arrives.\n"+
	    "The stout tanned male human shoos the chicken"+
	    	(found_chicken > 1 ? "s " : " ")+
	    	"into the box.\n"+
	    "The stout tanned male human closes and latches the box.\n"+
	    "The stout tanned male human leaves north.\n");
    }
    else /* no chickens */
    {
	tell_room(TO, "A stout tanned male human arrives.\n"+
	    "The stout tanned male human closes and latches the box.\n"+
	    "The stout tanned male human leaves north.\n");
    }

    add_item( ({ "long white box", "white box", "box", "block", "blocks" }),
	BSN("The box sits on blocks that raise it about two feet off "+
	    "the ground; its hinged door is shut. "));
    add_item( ({ "door", "latch", "wedge" }),
	BSN("The door is shut and a stout wooden wedge has been "+
	    "jammed into the latch."));

    remove_cmd_item("box");
    remove_cmd_item("door");
    add_cmd_item( ({ "box", "door" }), ({ "open" }),
	"You cannot budge the wedge.\n");
    add_cmd_item( ({ "box", "door" }), ({ "close" }),
	"It is already closed.\n");

    remove_item("straw");
    remove_item("bottom");
    remove_item("box bottom");
    remove_item("bottom of box");
} /* sunset */
