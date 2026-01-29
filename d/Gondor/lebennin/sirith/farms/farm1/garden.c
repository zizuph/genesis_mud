/*
 * /d/Gondor/lebennin/sirith/farms/farm1/garden.c
 * vegetable garden fo large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
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

public void	create_outdoors();
public void	init();
public int	pick_veg(string arg);
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
    set_extraline("Vegetables are planted in rows beside the hedge, "+
	"and a covered well stands at the end of the rows.");

    add_exit("hedgeyard", "west", 0, 2);
    add_exit("trees", "southwest", 0, 2);
    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"south", "southwest", "west", "northwest", "up", "down" }),
	BSN("You stroll among the rows of vegetables.") );

    herbslist =  ({ HERB_DIR + "bean_green", HERB_DIR + "bean_kidney",
	HERB_DIR + "bean_lima", HERB_DIR + "basil", HERB_DIR + "carrot",
	HERB_DIR + "garlic", HERB_DIR + "gonion", HERB_DIR + "rpotato" });
    set_up_herbs( ({ ONE_OF_LIST(herbslist), ONE_OF_LIST(herbslist),
	ONE_OF_LIST(herbslist) }),
	({ "garden", "vegetables", "vegetable garden", "rows" }),
	5);

    add_item( ({ "farm", "farmyard", "yard" }),
	BSN("The garden, trees and house all seem well cared for."));
    add_item( ({ "dense hedge", "hedge" }),
	BSN("A dense hedge circles the farmyard."));
    add_item( ({ "tree", "trees", "fruit tree", "fruit trees" }),
	BSN("Squat trees grow along the hedge to the southwest."));
    add_item( ({ "row", "rows", "garden", "vegetable garden",
	    "vegetable", "vegetables" }),
	BSN("Vegetables grow in long rows parallel to the hedge. "+
	    "They appear to be thriving."));
    add_item( ({ "building", "buildings" }),
	BSN("The only building visible from here is the farmhouse."));
    add_item( ({ "house", "farmhouse" }),
	BSN("The farmhouse on the west side of the yard appears to be "+
	    "in good shape, although you can't see details from here."));
    add_item( ({ "well", "cover" }),
	BSN("A waist-high stone wall, with a whitewashed wooden cover, "+
	    "encloses the well."));
    add_item( ({ "cover" }),
	BSN("The whitewashed cover fits snugly over the well."));
    add_item( ({ "wall", "well wall", "stone wall" }),
	BSN("The wall around the well is built of brown river stones."));
    add_item( ({ "stone", "stones", "river stone", "river stones" }),
	BSN("The speckled brown stones are very smooth."));
    add_item( ({ "soil", "dirt", "loam", "ground" }),
	BSN("The soil seems to be a well-drained, fertile loam."));
    add_cmd_item( ({ "cover", "well cover" }),
	({ "open", "get", "take", "lift", "move", "slide" }),
	BSN("You slide the cover to one side and gaze into the "+
	    "well. You see nothing but darkness, so you replace the cover."));
    add_cmd_item( ({ "well" }),
	({ "open", "enter", "search", "climb down" }),
	BSN("You slide the cover to one side and gaze into the "+
	    "well. You see nothing but darkness, so you replace the cover."));
} /* create_otudoors */


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
    string where, what;
    object *match;

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
     * or pick by name (e.g., "pick carrot from vegetables")
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
 *			search for vegetable[s]
 * Arguments	:	object player -- person doing the search
 *			string str -- their search string
 * Returns	:	string describing results of search
 */
public string
herb_search(object player, string str)
{
    string where, what;

    /* we want to accept searching for "vegetables", as well as "herbs"
     * and herbs by name, so intercept:
     *	"search [vegetable] garden [for vegetables]" 
     *	"search vegetables"
     *	"search rows [for vegetables]" 
     * and turn them into:
     *	"search garden for herbs"
     * pass anything else thru unchanged
     */

    if (!strlen(str))
    {
	return "";
    }

    if (sscanf(str, "%s for %s", where, what) != 2)
    {
	where = str;
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
	what =  ::herb_search(player, "garden for herbs");
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
     * ... let's see if anyone notices and files a report. 
     */
    if (!strlen(str) &&
        what == "You search everywhere, but find no herbs.\n")
    {
	return "You search everywhere, but find no vegetables.\n";
    }
	
    return what;
} /* herb_search */
