/*
 * /d/Gondor/common/guild/ithilien/erockchamber.c
 *
 * Created by Elessar.
 *
 * Modification history:
 * 26 August 1998, Gnadnar: make real curtain (door) so can
 *	block access to training recess if officers are using it 
 *	for privacy, add some items, tidy up.
 * 13 October 1998, Gnadnar: determine curtain status every time
 *	long is called, rather than storing it and only updating
 *	when it changes. less efficient, but the stored strings
 *	were sometimes getting out of sync. :-(
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

#define	RECESS	(RANGER_ITH_DIR + "ithilien_train")

public void	create_gondor();
public string	long_func();
public void	reset_room();
public void	init(); 
public int	start_here(string str);
public string	read_plaque();
public int	ring_bell(string arg);
public string	exa_curtain();
public string	exa_recess();
public void	change_my_desc(string desc, object ob);


static object	Curtain,
                   Eqrack,
		Tstand;

/*
 * Function name:	create_gondor
 * Description	:	set up the chamber
 */
public void
create_gondor()
{
    object curtain;

    FIX_EUID;

    set_short("the east end of the rock chamber");
    set_long(long_func);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit((RANGER_ITH_DIR + "rockchamber"), "west", 0, 0);
    add_exit((RANGER_ITH_DIR + "boardchamber"), "north", 0, 0);
    add_exit((RANGER_ITH_DIR + "foodchamber"), "southeast", 0, 0);
    add_exit(RECESS, "east", 0, 0);

    add_item( ({ "low bunks", "bunks", "bunk", "low bunk", "bed", "beds", }),
	BSN("The beds are simply low bunks with straw mattresses; " +
	"they allow Rangers to 'start here'."));
    add_item( ({ "sack", "sacks", "straw mattress", "straw mattresses",
	"straw", "mattress", "mattresses", }),
	BSN("The mattresses are simply rough sacks of straw -- " +
	   "softer than the floor, but far from luxurious."));
    add_item( ({ "ceiling", "roof", }),
	BSN("The roof is uneven, and stoops down at several points. " +
	"It seems to have been shaped only by nature itself."));
    add_item( ({  "passage", "passages", }),
	BSN("The passages, dark and narrow, lead away to the north " +
	"and southeast."));
    add_item( ({ "floor", "wall", "walls", }),
	BSN("Floor and walls are rough-surfaced grey stone."));
    add_item( ({ "stone", "grey stone", }),
	BSN("The stone is dark grey, and does not appear to have been " +
	    "polished or finished in any way."));
    add_item( ({ "cave", "chamber", "rock chamber", }), long_func);
    add_item( ({ "smooth heavy grey cloth", "smooth cloth", "heavy cloth",
	"grey cloth", "cloth", }),
	BSN("The grey cloth has a smooth, dull finish. It looks " +
	    "as if it is quite heavy."));
    add_item( ({ "small bell", "brass bell", "bell" }),
	BSN("The brass bell is about the size of a large walnut. Its " +
	    "surface is slightly tarnished."));

    add_item( ({ "back wall", "east wall", }), exa_curtain);
    add_item("recess", exa_recess);
    add_item("plaque", read_plaque);

    add_cmd_item("plaque", "read", read_plaque);

    /* we deliberately ignore the problem of players who touch
     * things while wearing gauntlets
     */
    add_cmd_item( ({  "floor", "wall", "walls", "stone", "grey stone", }),
	({ "touch", "feel", }),
	BSN("The stone is cool and slightly rough to the touch."));
    add_cmd_item( ({ "smooth heavy grey cloth", "smooth cloth", "heavy cloth",
	"grey cloth", "cloth", "grey cloth curtain", "grey curtain",
	"cloth curtain", "curtain", }),
	({ "touch", "feel", }),
	BSN("The grey cloth slides easily across your hand."));
    add_cmd_item( ({ "small bell", "brass bell", "bell" }),
	({ "rub", "polish", }),
	BSN("You energetically polish the surface of the bell, " +
	    "but have little effect."));

    reset_room();
} /* create_gondor */


/*
 * Function name:	long_func
 * Description	:	VBFC for the room desc
 * Returns	:	string -- the description
 */
public string
long_func()
{
    string	torch_extra = "stands empty.",
		curtain_extra = "a grey cloth curtain is drawn " +
		                "across the back of the cave. ";

    if (objectp(Curtain) &&
	Curtain->query_open())
    {
	curtain_extra = "at the back of the cave is a recess " +
            "partly screened by a grey cloth curtain. ";
    }
    if (objectp(Tstand) &&
	Tstand->query_torch_is_lit())
    {
	torch_extra = "holds a burning torch.";
    }

    return(BSN(
	"An uneven stooping roof makes this rock chamber look smaller " +
	"than it actually is. The cave extends westwards, and passages " +
	"lead north and southeast.  A few low beds are placed in a corner, " +
	"for the use of rangers who start here, and " + curtain_extra +
	"A plaque hangs on the south wall of the chamber; " +
	"beside the plaque, an iron torch stand " + torch_extra));
} /* long_func */


/*
 * Function name:	reset_room
 * Description	:	replace torchstand if needed
 */
public void
reset_room()
{
    string *cnames;
    if (!objectp(Tstand))
    {
	Tstand = clone_object(OBJ_DIR + "torchstand");
	Tstand->set_lit(1);
	Tstand->set_replace_msg(BSN(
	    "A green-clad ranger arrives, carrying a few torches. " +
	    "He replaces the burned-out torch in the iron stand with " +
	    "a fresh one, lights it, and walks away."));
	Tstand->move(TO);
    }
    if (!objectp(Eqrack))
    {
        Eqrack = clone_object(RANGER_DIR + "obj/eq_rack");
        Eqrack->set_adj("sturdy");
        Eqrack->set_short("sturdy equipment rack");
        Eqrack->set_long(Eqrack->query_long()
          + "This rack holds equipment that will last a while.\n");
        Eqrack->move(TO);
    }

    if (!objectp(Curtain))
    {
	Curtain = clone_object(RANGER_ITH_DIR + "curtain1");
	Curtain->add_name("ith_curtain");
	Curtain->move(TO);
	cnames = Curtain->query_door_name();
	remove_item(cnames);
	add_item(cnames, exa_curtain);
	/* force other room to load now, to avoid the usual
	 * problems with npcs that call command() wiping out
	 * current player verb
	 */
	(RANGER_ITH_DIR + "ithilien_train")->short();
    }
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add 'start' and 'ring' verbs
 */
public void
init()
{
    ::init();
    add_action(start_here, "start");
    add_action(ring_bell,  "ring");
} /* init */



/*
 * Function name:	start_here
 * Description	:	handle attempts to start here
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
start_here(string str)
{
    if (str != "here")
    {
	NF0("Start where?\n");
    }

    if (TP->query_wiz_level())
    {
	NF0("Wizards should not enter the world in mortal startrooms.\n");
    }

    if (TP->query_skill(SS_PUNISHMENT) == NOACCESS)
    {
        WRITE("You may not change your start location, since the Council " +
	   "of Rangers has punished you with limited access to the " +
	   "guildhouses.");
	return 1;
    }

    if (TP->query_guild_name_occ() == RANGER_S_GUILD_NAME)
    {
	TP->set_default_start_location(file_name(TO));
	write("From now on you will enter the world here.\n");
	return 1;
    }
    NF0("But you are not one of the Rangers!\n");
} /* start_here */



/*
 * Function name:	read_plaque
 * Description	:	VBFC for the plaque
 * Returns	:	"" -- actual text is written here
 */
public string
read_plaque()
{
    write(read_file(RANGER_DIR + "txt/roi_plaque.txt"));
    return "";
} /* read_plaque */


/*
 * Function name:	ring_bell
 * Description	:	handle attempts to ring the bell
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
ring_bell(string arg)
{
    if (strlen(arg) &&
	parse_command(LOW(arg), ({}), "[the] [small] [brass] 'bell'"))
    {
	if (CAN_SEE_IN_ROOM(TP))
	{
	    write("You ring the bell.\n");
	    SAY(" rings the bell.");
	    tell_room(TO, 
	        BSN("The high-pitched jingle of the bell produces " +
		    "curious echoes in the cave."));
	    tell_room(RECESS, 
	        BSN("You hear a high-pitched jingling noise from " +
		    "beyond the curtain."));
	}
	else
	{
	    write("It is too dark -- you cannot find the bell.\n");
	}
	return 1;
    }
    NF0("Ring what?\n");
} /* ring_bell */


/*
 * Function name:	exa_curtain
 * Description	:	VBFC for the curtain
 * Returns	:	string -- the description
 */
public string
exa_curtain()
{
    if (objectp(Curtain) &&
	Curtain->query_open())
    {
	return BSN("A curtain of smooth heavy grey cloth " +
	    "partly covers the entrance to a small recess " +
    	    "in the back wall. A small bell hangs from the wall " +
	    "beside the curtain.");
    }
    return BSN("A curtain of smooth heavy grey cloth covers " +
	"the back wall of the rock chamber. A small bell hangs " +
	"from the wall beside the curtain.");
} /* exa_curtain */


/*
 * Function name:	exa_recess
 * Description	:	VBFC for the recess
 * Returns	:	string -- the description
 */
public string
exa_recess()
{
    string	desc;
    object	*in_recess;

    if (!objectp(Curtain) ||
	!Curtain->query_open())
    {
	return BSN("The curtain is completely drawn, blocking " +
		"all view of the recess.");
    }

    desc = BSN("Behind the partly drawn curtain lies " +
	"a small recess, tucked under the low roof.");

    RECESS->short();
    in_recess = FILTER_LIVE(all_inventory(find_object(RECESS)));
    switch (sizeof(in_recess))
    {
    case 0:
    	break;
    case 1:
	desc += BSN(in_recess[0]->query_Art_name(TP)+
	        " is standing in the recess.");
	break;
    default:
	desc += BSN(capitalize(COMPOSITE_LIVE(in_recess))+
	        " are standing in the recess.");
	break;
    }
    return desc;
} /* exa_recess */


/*
 * Function name:	change_my_desc
 * Description	:	mask parent so door state doesn't end up
 *			in room long.
 * Arguments	:	string desc -- the new desc
 *			object ob -- the object that changed
 */
public void
change_my_desc(string desc, object ob)
{

    if (!objectp(ob))
    {
	ob = previous_object();
    }
    if (!ob->id("ith_curtain"))
    {
	::change_my_desc(desc, ob);
    }
} /* change_my_desc */
