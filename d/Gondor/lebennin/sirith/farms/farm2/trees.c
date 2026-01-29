/*
 * /d/Gondor/lebennin/sirith/farms/farm2/trees.c
 * trees on small farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

#include <stdproperties.h>	/* for OBJ_S_SEARCH_FUN, OBJ_I_SEARCH_TIME */
#include <ss_types.h>		/* for SS_AWARENESS */
#include "/d/Gondor/defs.h"
#include "../defs.h"			
#include "/d/Gondor/common/mordor/sys/clock.h"

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

#define	NBEES	4			/* # of bees per reset		*/
#define	NAPPLES	3			/* # of apples per reset	*/

static object	*Bees = allocate(NBEES);
static int	Napples = NAPPLES;

public void	create_outdoors();
public void	reset_room();
public void	init();
static int	pick_apple(string arg);	/* handle picking an apple	*/
public string	do_search(object tp, string arg); /* handle searches	*/
static int	kill_bees(string arg);	/* handle attacks on bee items	*/
public void	sunrise();		/* change items to day descs	*/
public void	sunset();		/* change items to night descs	*/


/*
 * Function name:	create_outdoors
 * Description	:	set up room
 */
public void
create_outdoors()
{
    string timestr = tod();

    set_areatype("farmyard");
    set_short("a hedged farmyard in southern Lebennin");

    /* room desc & items related to bees are different at night */
    if (timestr == "dusk" ||
	timestr == "evening" ||
	timestr == "night")
    {
	sunset();
    CLOCK->notify_dawn(sunrise);
    }
    else
    {
	sunrise();
    CLOCK->notify_dusk(sunset);
    }

    add_exit("eastyard", "south", 0, 2);
    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"southwest", "west", "northwest", "down" }),
	BSN("You stroll among the baskets.") );
    set_no_exit_msg("up",
	BSN("You grab a low branch and start to hoist yourself into "+
	    "the tree, but it bends beneath your weight. You drop "+
	    "back to the ground."));

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 3);

    add_item( ({ "hedged farmyard", "farm", "farmyard" }),
	BSN("The tidy farmyard contains a garden, fruit trees and "+
	    "buildings, all enclosed by a sturdy hedge."));
    add_item( ({ "hedge" }),
	BSN("The hedge is about head-high and very thick."));
    add_item( ({ "squat tree", "squat trees", "squat apple tree",
    		     "squat apple trees", "apple tree", "apple trees",
    		     "tree", "trees" }),
	BSN("The apple trees are not very tall, but appear to be "+
	    "in good health."));
    add_item( ({ "fruit", "apple", "apples", "branch", "branches" }),
	BSN("Apples hang in the branches above your head."));
    add_item( ({ "ground", "grass", "grasses" }),
	BSN("Short, broad-bladed grass grows thickly beneath the trees. "+
	    "Round baskets are scattered about the grass."));

    add_item( ({ "garden", "vegetable garden", "vegetables" }),
	BSN("The vegetable garden lies across the farmyard to the south, "+
	    "but you can't see much of it from here."));
    add_item( ({ "building", "buildings" }),
	BSN("From here, the only building you can see is the barn "+
	    "immediately to the west."));
    add_item( ({ "barn", "wall", "barn wall" }),
	BSN("The barn wall facing the trees has weathered to "+
	    "a silvery grey."));

    add_cmd_item( ({ "squat tree", "squat trees", "squat apple tree",
    		     "squat apple trees", "apple tree", "apple trees",
    		     "tree", "trees" }),
	({ "climb" }),
	BSN("You grab a low branch and start to hoist yourself into "+
	    "the tree, but it bends beneath your weight. You drop "+
	    "back to the ground."));

/*
    if (!objectp(find_object(SIRITH_MASTER)))
    {
	SIRITH_MASTER->create_object();
    }
*/

    reset_room();	/* clone bees if it's daytime */
} /* create_outdoors */


/*
 * Function name:	reset_room
 * Description	:	replenish apples, bees
 */
public void
reset_room()
{
    string timestr = tod();

    ::reset_room();
    Napples = NAPPLES;
    if (timestr != "dusk" &&
	timestr != "evening" &&
	timestr != "night")
    {
	clone_npcs(Bees, (SIRITH_FARMS_DIR+"npc/bee"), 4.0, 
	    (SIRITH_FARMS_DIR+"farm2/trees"));
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
    add_action(pick_apple, "pick");
    add_action(pick_apple, "take");
    add_action(pick_apple, "get");
    add_action(kill_bees, "kill");
} /* init */


/*
 * Function name:	pick_apple
 * Description  :	let player pick an apple (if any are left)
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if arg is sensible (whether or not there
 *				are any apples left to pick)
 *			0 if arg doesn't parse
 * For consistency with gardens, and in case apples/plums ever 
 * become herbs, force "pick" to become "search".
 */
public int
pick_apple(string arg)
{
    string type, where, what;

    if (!strlen(arg))
    {
	return 0;
    }

    if (objectp(present(arg, this_object())))
    {
        return 0;
    }

    /* allow "pick apple[s]|fruit[s] [from apple|fruit tree[s]]" */
    if (sscanf(arg, "%s from %s %s", what, type, where) == 3 ||
        sscanf(arg, "%s from %s", what, where) == 2)
    {
    	if (where != "tree" && where != "trees")
	{
	    return 0;
	}
    }
    else
    {
	what = arg;
    }
    if (what != "apple" &&
	what != "apples" &&
        what != "fruit" &&
	what != "fruits")
    {
	return 0;
    }
    if (strlen(type) &&
	type != "apple" &&
	type != "fruit")
    {
	return 0;
    }
    if (!TP->query_wiz_level())
    {
	TP->command("$search trees for apples");
    }
    else
    {
	write("Ordinarily, this room would do\n"+
	    "	this_player()->command(\"$search trees for apples\");\n"+
	    "Since you're a wizard, that won't work.\n"+
	    "Please do the search yourself.\n");
    }
    return 1;
} /* pick_apple */


/*
 * Function name:	do_search
 * Description	:	handle searching trees for apples
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 * Return	:	string describing results of search
 */
public string
do_search(object tp, string arg)
{
    int		n;
    object	apple;
    string	type, where, what;

    /* check first for the command() from pick_apple() */
    if (arg != "trees for apples")
    {
	/* not from pick_apple() -- player searched directly */
	if (!strlen(arg))
	{
	    return "";
	}

	/* allow "search [apple|fruit] tree[s] [for apple[s]|fruit[s]]" */
	if ((n = sscanf(arg, "%s %s for %s", type, where, what)) == 3 ||
	    (n = sscanf(arg, "%s for %s", where, what)) == 2)
	{
	    if (what != "apple" &&
		what != "apples" &&
	        what != "fruit" &&
		what != "fruits")
	    {
		return "";
	    }
	}
	else
	{
	    where = arg;
	}
	if (where != "tree" && where != "trees")
	{
	    return "";
	}
	if (n == 3 && type != "apple" && type != "fruit")
	{
	    return "";
	}
    }

    if (Napples > 0 &&
        TP->query_skill(SS_AWARENESS) >= (MIN_AWARE + random(RANDOM_AWARE)) &&
        objectp(apple = clone_object(SIRITH_FARMS_DIR+"obj/apple")))
    {
	--Napples;
	what = BSN("You reach up to a low-hanging branch and pick "+
	    "an apple.");
	SAY(" picks an apple.");
	if (apple->move(TP))
	{
	    what += BSN("Oops, you dropped the apple.");
	    SAY(" drops an apple.");
	    apple->move(TO);	/* assume this works :-) */
	}
    }
    else
    {
	what = BSN("None of the apples within your reach appears ripe.");
    }
    return what;
} /* do_search */


/*
 * Function name:	sunrise
 * Description	:	change room & items descs, create some bees
 *			when sun comes up
 */
public void
sunrise()
{
    CLOCK->notify_dawn(sunrise);
    set_extraline("Several squat apple trees grow here; beneath "+
	"the trees, round baskets emit a low hum.");

    /* these remove's do seem to be necessary ... i was
     * getting nighttime responses during the day, otherwise
     */
    remove_cmd_item("basket"); remove_cmd_item("baskets");
    remove_cmd_item("bee hive"); remove_cmd_item("bee hives");
    remove_cmd_item("beehive"); remove_cmd_item("beehives" );
    remove_cmd_item("hive"); remove_cmd_item("hives");

    add_item( ({ "basket", "baskets", "hive", "hives", "bee hive",
		 "bee hives", "beehive", "beehives" }),
	BSN("Round domed baskets are scattered beneath the trees. "+
	    "They emit a low humming noise, and occasionally a bee "+
	    "darts out of a basket."));
    add_item( ({ "bee", "bees" }), BSN("Bees dart among the baskets."));
    add_cmd_item( ({ "basket", "baskets", "hive", "hives", "bee hive",
		     "bee hives", "beehive", "beehives" }),
	({ "search", "open", "get", "take"  }),
	BSN("As you touch the basket, the humming takes on a furious "+
	    "note. You quickly back away."));

    clone_npcs(Bees, SIRITH_FARMS_DIR+"npc/bee", 4.0, 
	SIRITH_FARMS_DIR+"farm2/trees");
}


/*
 * Function name:	sunset
 * Description	:	change room & items descs, remove bees
 *			when sun goes down
 */
public void
sunset()
{
    int i, foundbee;

    CLOCK->notify_dusk(sunset);
    set_extraline("Several squat apple trees grow here, and "+
	"round baskets lie beneath them.");

    /* these remove's do seem to be necessary ... i was
     * getting daytime responses at night, otherwise
     */
    remove_item("bee"); remove_item("bees");
    remove_cmd_item("basket"); remove_cmd_item("baskets");
    remove_cmd_item("bee hive"); remove_cmd_item("bee hives");
    remove_cmd_item("beehive"); remove_cmd_item("beehives" );
    remove_cmd_item("hive"); remove_cmd_item("hives");

    add_item( ({ "basket", "baskets", "hive", "hives", "bee hive",
		 "bee hives", "beehive", "beehives" }),
	BSN("Round domed baskets are scattered beneath the trees."));

    add_cmd_item( ({ "basket", "baskets", "hive", "hives", "bee hive",
		     "bee hives", "beehive", "beehives" }),
	({ "search", "open", "get", "take"  }),
	BSN("As you touch the basket, you hear a low but threatening "+
	    "hum. You quickly back away."));

    for (i = foundbee = 0; i < NBEES; ++i)
    {
	if (objectp(Bees[i]) && environment(Bees[i]) == TO &&
	!objectp(Bees[i]->query_attack()))
	{
	    ++foundbee;
	    Bees[i]->remove_object();
	    Bees[i] = 0;
	}
    }
    if (foundbee)
    	tell_room(TO, 
	    BSN("As the sun begins to set, the bees return to the baskets."),
	    Bees);
}

/*
 * Function name:	kill_bees
 * Description	:	handle attempts to kill bee items
 * Arguments	:	string arg -- whatever the user typed
 * Returns	:	0	if there are real bee npcs here
 *			1 	if only bee items 
 */
public int
kill_bees(string arg)
{
    string timestr;
    if (( arg == "bee" || arg == "bees" ))
    {
	if (living(present("bee")))
	    return 0;
	/* no living bee here, but if we talk about them
	 * in the item descriptions, need to say something more
	 * interesting than "You find no such living creature." :-)
	 */
	if ((timestr = tod()) != "dusk" && timestr != "evening" &&
	timestr != "night")
    	{
	    write("The bees dart out of reach.\n");
            return 1;
	}
    }
    return 0;
}
