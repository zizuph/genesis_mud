/*
 * /d/Gondor/lebennin/sirith/farms/farm1/northyard.c
 * north yard of large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * a torch is hidden in the woodpile.
 * Finwe, May 2019: Removed hidden exits
 */

#pragma strict_types

#include <stdproperties.h>		/* for OBJ_S_SEARCH_FUN	*/
#include <macros.h>			/* for VBFC_ME	*/
#include <ss_types.h>			/* for SS_AWARENESS	*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

#define		MAX_WOOD	5	/* how many pieces of wood */

static int	Torch_here = 1;
static int	Wood_here = MAX_WOOD;
static object	Kellis;			/* farmer		*/

public void	create_outdoors();
public void	reset_room();
public void	init();
public string	do_search(object tp, string arg);
public string	look_smokehouse();	/* VBFC for smokehouse	*/
public string	get_wood(string arg);	/* VBFC for firewood	*/
public string	put_wood(string arg);	/* VBFC for firewood	*/
public int	set_fire(string arg);	/* handle attempts to burn stuff */


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_areatype("farmyard");
    set_short("a large farmyard in southern Lebennin");
    set_extraline("A heavy plank door leads into a large shed to the north. "+
     	"Firewood is stacked alongside the shed, "+
	"and several hayricks stand between the shed and the barn.");

    add_exit("smokehouse", "north", 0, 2);
    add_exit("eastyard", "south", 0, 2);
    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
	BSN("You wander among the hayricks.") );
    set_no_exit_msg( ({ "northeast", "east", "southeast", "down" }),
	BSN("You wander around the farmyard.") );
    set_no_exit_msg( ({ "up" }),
	BSN("The hay is too slippery to climb.") );


    set_door(SIRITH_FARMS_DIR + "obj/f1_smokeh_door1");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 3);

    add_item( ({ "farmyard", "farm",  "yard" }),
	BSN("The farmyard appears prosperous and well-tended."));
    add_item( ({ "barn", "wall", "barn wall", "grey plank", "grey planks",
    	"plank", "planks" }),
	BSN("The barn is built of weathered grey planks."));
    add_item( ({ "bank", "turf", "turf bank" }),
	BSN("A sturdy turf bank encloses the farmyard."));
    add_item( ({ "shed", "smokehouse" }),
	VBFC_ME("look_smokehouse"));
    /* smokehouse logs, not firewood */
    add_item( ({ "large log", "large logs", "log", "logs", "caulking" }),	
	BSN("The large, roughly surfaced logs are well caulked."));
    add_item( ({ "large stack", "large stack of firewood", "stack",
	"stack of firewood", "wood", "firewood" }),
	BSN("A large stack of firewood leans against the shed."));
    add_item( ({ "tall mound", "tall mounds", "mound", "mounds",
	"mound of hay", "mounds of hay", "hay", "hayrick", "hayricks" }),
	BSN("The tall mounds of sweet-smelling hay are covered with thatch."));
    add_item( ({ "thatch" }),
	BSN("The thatch probably protects the hay from bad weather."));
    add_item( ({ "ground", "bare dirt", "dirt" }),
	BSN("The ground is just bare dirt."));

    /* any adventurer worthy of the name will try to climb a hayrick */
    add_cmd_item( ({ "hay", "hayrick", "hayricks", "mound", "mounds" }),
	({ "climb" }),
	BSN("The hay is too slippery to climb."));

    add_cmd_item( ({ "hay", "hayrick", "hayricks", "mound", "mounds" }),
	({ "smell", "sniff" }),
	BSN("The hay tickles your nose, causing you to sneeze violently."));

    add_cmd_item( ({ "hay" }), ({ "get", "take" }),
	BSN("You reach to pull some hay from the hayrick, but "+
	    "you sneeze so violently that you abandon the attempt."));

    reset_room();
} /* create_outdoors */


/*
 * Function name:	reset_room
 * Description	:	replensih torch, wood, npc
 */
public void
reset_room()
{
    ::reset_room();
    Torch_here = 1;
    Wood_here = MAX_WOOD;

    Kellis = clone_npc(Kellis,
	     (SIRITH_FARMS_DIR+"npc/kellis"),
	     ({ (SIRITH_FARMS_DIR+"farm1"), (SIRITH_FARMS_DIR+"fields") }));
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(get_wood, "get");
    add_action(get_wood, "take");
    add_action(put_wood, "put");
    add_action(put_wood, "place");

    add_action(set_fire, "light");
    add_action(set_fire, "set");
    add_action(set_fire, "burn");
    add_action(set_fire, "ignite");
} /* init */


/*
 * Function name:	look_smokehouse
 * Description	:	VBFC for smokehouse
 * Returns	:	string  -- desc of smokehouse + door state
 *
 * not very exciting, but a smokehouse definitely would have a door,
 * and you should see it when you look at the smokehouse.
 */
public string
look_smokehouse()
{
    object door;
    string desc;

    desc = "The shed is built of stout logs, and even the smallest space "+
	"between the logs has been tightly caulked.";

    if (objectp(door = present(SIRITH_DOOR)) &&
	!door->query_open())
    {
        desc += " The door to the shed is closed.";
    }
    else
    {
	desc += " The door to the shed is open.";
    }
    return(BSN(desc));
} /* look_smokehouse */


/*
 * Function name:	do_search
 * Description	:	handle searching the room & items
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 */
public string
do_search(object tp, string arg)
{
    object	torch;
    string	where,
		what;

    if (!strlen(arg) || arg == "here")
    {
	/* a hint to give a target ... */
	return "You poke around the farmyard, "+
	       "but find nothing interesting.\n";
    }

    if (sscanf(arg, "%s for %s", where, what) != 2)
    {
	where = arg;
    }

    if ((where != "firewood" &&
	 where != "wood" &&
	 where != "stack") ||
        (strlen(what) &&
	 what != "torch"))
    {
	return BSN("You search the "+arg+", but find nothing interesting.");
    }

    if (Torch_here &&
        TP->query_skill(SS_AWARENESS) >= (MIN_AWARE + random(RANDOM_AWARE)) &&
        objectp(torch = clone_object(OBJ_DIR + "torch")))
    {
	Torch_here = 0;
    	if (!torch->move(tp))
	{
	    return "Among the "+arg+", you find a torch.\n";
	}
	/* move to player failed ... drop it */
	torch->move(TO);
	return "Among the "+arg+", you find a torch.\n"+
	       "Oops -- you dropped it.\n";
    }
    return BSN("You search the "+arg+
	       ", but do not find anything of interest.");
} /* do_search */


/*
 * Function name:	get_wood
 * Description	:	handle getting firewood from stack
 * Arguments	:	whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
get_wood(string arg)
{
    object	wood;

    if (!strlen(arg))
    {
	return 0;
    }

    if (arg == "stack" ||
	arg == "stack of firewood")
    {
	write("You cannot possibly carry the entire stack of firewood.\n");
	return 1;
    }

    if (arg == "wood" ||
	arg == "firewood")
    {
	if (objectp(present(arg, TO)))
	{
	    return 0;
	}
    }
    else if (arg != "wood from stack" &&
	     arg != "firewood from stack")
    {
	return 0;
    }

    if (Wood_here <= 0 || 
        !objectp(wood = clone_object("/d/Gondor/common/obj/firewood")))
    {
	write(BSN("You turn over a few pieces of the firewood. "+
	    "It's all too green to burn, so you leave it to "+
	    "finish drying."));
	return 1;
    }

    --Wood_here;
    SAY(" takes a piece of firewood from the stack.");
    write("You take a piece of firewood from the stack.\n");
    if (wood->move(TP))
    {
	wood->move(TO);
	SAY(" drops a piece of firewood.");
	write("Oops, you dropped it.\n");
    }
    return 1;
} /* get_wood */


/*
 * Function name:	put_wood
 * Description	:	handle putting firewood on stack
 * Arguments	:	whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
put_wood(string arg)
{
    object	wood;

    if (!strlen(arg))
    {
	return 0;
    }

    if (arg != "wood on stack" &&
	arg != "firewood on stack" &&
        arg != "wood in stack" &&
	arg != "firewood in stack")
    {
	return 0;
    }

    if (!objectp(wood = present("firewood", TP)))
    {
	write("You have no firewood.\n");
    }
    else if (wood->move(TO))
    {
	write("You cannot seem to put the firewood on the stack.\n");
    }
    else
    {
	Wood_here += wood->num_heap();
	wood->remove_object();
	write("You place the firewood on the stack.\n");
	SAY(" places some firewood on the stack.");
    }
    return 1;
} /* put_wood */


/*
 * Function name:	set_fire
 * Description	:	handle attempts to light firewood or hay
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understood arg, 0 if not
 *
 * don't do this as add_cmd_item() because add_cmd_item() will intercept
 * the command "light firewood" even if the player is holding firewood
 * in her hands.
 */
public int
set_fire(string arg)
{
    string	vb = query_verb(),
		tmpstr;

    if (!strlen(arg))
    {
	return 0;
    }

    if (vb == "set")
    {
	if (!sscanf(arg, "fire to %s", tmpstr) &&
	    !sscanf(arg, "%s on fire", tmpstr) &&
	    !sscanf(arg, "%s ablaze", tmpstr))
	{
	    return 0;
	}
	arg = tmpstr;
    }

    if (arg == "firewood" ||
	arg == "wood" ||
	arg == "stack" ||
        arg == "stack of firewood")
    {
	NFN0("Igniting the stack of firewood would engulf the shed, "+
	     "the hay and quite possibly you. You have second "+
	     "thoughts about such a foolhardy action.");
    }

    if (arg == "hay" ||
	arg == "hayrick" ||
	arg == "hayricks" ||
        arg == "mound" ||
	arg == "mounds" ||
        arg == "mound of hay" ||
	arg == "mounds of hay")
    {
	NFN0("Setting the hayricks ablaze would likely ignite the barn "+
	"and a good many other things in the area. You decide against it.");
    }

    NF0(capitalize(vb)+" what?\n");
} /* set_fire */
