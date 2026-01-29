/*
 * /d/Gondor/pelargir/misc/bathhouse/entry.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * entrance for bathhouse. here is where they pay ...
 *
 */

#pragma strict_types


inherit	"/d/Gondor/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "bath.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define	BENCH_NAME	"cushioned bench"

static object	Owner;

/* prototypes in order of appearance */
public void	create_gondor();
public void	reset_room();
public void	init();
public void	enter_inv(object ob, object from);
public void	leave_inv(object ob, object dest);
public int	check_allowed();
public mixed	no_theft(object tp);
public mixed	no_fights(object tp);
public void	eject_banned(object pl, string reason);
public void	knock_on_door(object pl, object env);
public string	look_at();
public object	query_owner();



/*
 * Function name:	create_gondor
 * Description	:	set up the eroom
 */
public void
create_gondor()
{
    FIX_EUID;

    set_short("Entry hall");
    set_long(BSN(
	"Creamy plaster walls and a light pine floor make " +
	"this entry hall seem larger than it actually is. " +
	"Doorways open to the east and west, and a wooden " +
	"door leads south. Save for a " +
	"cushioned bench and a discreet brass plaque " +
	"on the north wall, the hall is bare of furnishings."));

    add_exit(OUTSIDE_ENTRY, "south", check_allowed);
    add_exit("womens_bath", "east", check_allowed);
    add_exit("mens_bath",   "west", check_allowed);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 100);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_MAGIC, 1);
//    add_prop(ROOM_M_NO_MAGIC_ATTACK, no_fights);
//    add_prop(ROOM_M_NO_ATTACK, no_fights);
//    add_prop(ROOM_M_NO_STEAL, no_theft);

    add_chair(BENCH_NAME,
	"[down] [in] / [on] [the] [cushioned] 'bench'", 8);
    add_item( ({ "cushioned bench", "bench" }), look_at);


    add_item( ({ "entry", "entry hall", "hall", }), long);
    add_item( ({ "west wall", "south wall", "east wall", "creamy wall",
	"creamy walls", "wall", "walls" }),
	"The smooth plaster walls are the colour of new cream.\n");
    try_item( ({ "creamy surface", "smooth plaster", "plaster surface",
	"surface", "surface of plaster", "creamy plaster", "plaster" }),
	BSN("The plaster is very smooth. No cracks or bumps " +
	    "mar its creamy surface."));
    add_item( "north wall",
	"A small brass plaque hangs from the north wall.\n");
    add_item( ({ "brass surface", "plaque surface", "gleaming brass",
	"brass surface of plaque", "brass surface of the plaque",
	"surface of plaque", "surface of the plaque",
	"polished brass", "brass", }),
	BSN("The brass surface of the plaque gleams as if " +
	    "recently polished."));
    add_item( ({ "light pine floor", "light floor", "pine", 
	"pine floor", "light pine planks", "pine planks", "planks",
	"light pine plank", "pine plank", "plank", "floor", }),
	BSN("The pine planks of the floor have been bleached to " +
	    "a light bone colour."));
    add_item( ({ "low open doorway", "low open doorways",
    	"low doorway", "low doorways", "open doorway", "open doorways",
	"east doorway", "west doorway", "doorway", "doorways", }),
	"Low open doorways, gently arched, lead east and west.\n");
    add_item( "ceiling",
	"The ceiling is of the same creamy plaster as the walls.\n");
    add_item( ({ "doors", "south door", "wooden door", "door", }),
	"The door is made of dark brown wood.\n" +
	"It is closed.\n");
    add_item( ({ "dark brown wood", "brown wood", "dark wood", "wood", }),
	"The wood is very dark, almost black.\n");
    add_item( ({ "plump cushion", "plump cushions", "cushion", 
	"cushions" }),
	BSN("The plump cushions are made of dark blue fabric, "+
	    "and appear quite soft."));
    add_item( ({ "dark blue fabric", "blue fabric", "fabric" }),
	"The fabric of the cushions is a dark rich blue.\n");
    add_item( "furnishings",
	"Except for the plaque and the bench, the hall is bare.\n");

    add_cmd_item( ({ "wooden door", "door" }),
        ({ "open", "push", }),
        BSN("You push gently on the door. It swings open for a moment, " +
	    "then falls shut again."));
    add_cmd_item( ({ "wooden door", "door" }),
        "close", 
        "The door is already closed.\n");
    add_cmd_item( ({ "wooden door", "door" }),
        ({ "lock", "unlock",  }),
        "No lock or keyhole is visible on the door.\n");


    add_item( ({ "discreet brass plaque", "small brass plaque",
	"discreet plaque", "small plaque", "brass plaque", "plaque" }),
	"\n\n" +
	"          Welcome to the Pelargir Public Baths.\n\n"+
	"          Price: 35 silver coins\n"+
	"                 (includes soap, towel and unlimited "+
	"hot water)\n\n" +
	"          Please pay attendant.\n\n");

    add_cmd_item( ({ "discreet brass plaque", "small brass plaque",
	"discreet plaque", "small plaque", "brass plaque", "plaque" }),
	"read",
	"\n\n" +
	"          Welcome to the Pelargir Public Baths.\n\n"+
	"          Price: 35 silver coins\n"+
	"                 (includes soap, towel and unlimited "+
	"hot water)\n\n" +
	"          Please pay attendant.\n\n");
    
    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	clone up owner
 */
public void
reset_room()
{
    if (!objectp(Owner))
    {
        Owner = clone_npc(Owner, OWNER_FILE);
    }
} /* reset_room */


/*
 * Function name:	init
 * Description	:	mask parent so we can call init_room_chairs()
 */
public void
init()
{
    object	wiz;
    string	name;

    ::init();
    init_room_chairs();	/* add chair verbs */

    if (interactive(TP) &&
	!TP->query_prop(PLAYER_I_BATH))
    {
	TP->add_prop(PLAYER_I_BATH, I_AM_DRY_AND_DIRTY);
	TP->add_subloc(WET_SUBLOC, (BATH_DIR + "bath"));
    }
} /* init */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to evict thieves & fighters
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    string	reason;
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
	/* the banned check is probably unnecessary now that 
	 * we require knocking to enter, but it doesn't hurt ...
	 */
	if (strlen(reason = Owner->query_banned(ob->query_name())))
	{
	    set_alarm(1.0, 0.0, &eject_banned(ob, reason));
	    return;
	}

	if (!Owner)
	{
	    reset_room();
	}
	set_alarm(1.0, 0.0, &Owner->greet(ob, QVB));
    }
} /* enter_inv */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to recover from owner leaving,
 *			remove bath props
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    string vb;

    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);

    if (ob == Owner &&
	((vb = QVB) != "Clean" &&
	  vb != "Destruct" &&
	  vb != "destruct" &&
	  vb != "update"))
    {
	set_alarm(3.0, 0.0, reset_room);
    }
    if (interactive(ob))
    {
	if (!strlen(function_exists("create_bath", ENV(ob))))
	{
	    ob->remove_prop(PLAYER_I_PAID);
	    ob->remove_prop(PLAYER_I_BATH);
	    ob->remove_prop(PLAYER_I_TIPPED);
	    ob->remove_subloc(WET_SUBLOC);
	}
	if (QVB == "south")
	{
	    tell_room(TO, "The door swings shut.\n");
	}
    }
} /* leave_inv */


/*
 * Function name:	check_allowed
 * Description	:	check whether can enter baths
 *			(e.g., have paid, are not banned, ...)
 *			and prevent owner from leaving
 * Returns	:	int -- 0 if allowed, nonzero if not
 */
public int
check_allowed()
{
    string	vb;
    int		g = -1;

    if (TP == Owner)
    {
	return 1;
    }
    if ((vb = QVB) == "south")
    {
	if (!(g = check_sitting()))
	{
	    write("You open the door.\n");
	    SAY(" opens the door.");
	}
	return g;
    }

    if (TP->query_prop(PLAYER_I_PAID) &&
	((g = TP->query_gender()) == G_FEMALE && vb == "east") ||
	(g == G_MALE && vb == "west") ||
	g == G_NEUTER ||
	TP->query_wiz_level())
    {
	return check_sitting();
    }

    if (CAN_SEE_IN_ROOM(Owner) &&
	CAN_SEE(Owner, TP))
    {
	Owner->command("emote steps in front of the doorway.");
	Owner->command("frown gently " + OB_NAME(TP));
	if (g == G_FEMALE)
	{
	    Owner->command("say to " + OB_NAME(TP) + 
		" The women's bath is to the east.");
	}
	else if (g == G_MALE)
	{
	    Owner->command("say to " + OB_NAME(TP) +
		" The men's bath is to the west.");
	}
	else
	{
	    Owner->command("say to " + OB_NAME(TP) +
		" You must pay me first.");
	}
    }
    else
    {
	if (CAN_SEE_IN_ROOM(TP) &&
	    CAN_SEE(TP, Owner))
	{
            TP->catch_msg(QCTNAME(Owner) +
	        " is standing so as to block the doorway.\n");
	}
	else
	{
	    write("You bump into someone blocking the doorway.\n");
	}
    }
    return 1;
} /* check_allowed */


/*
 * Function name:	no_theft
 * Description	:	evicts thief, remember 'em til next reboot
 * Returns	:	mixed -- int 1 if owner cannot see the fighter
 *				 	(so they just get default msg).
 *				 string "" -- if owner can see, all msgs
 *					are written before return.
 */
public mixed
no_theft(object tp)
{
    string	name;

    if (!objectp(tp))
    {
	tp = TP;
    }
    name = tp->query_name();
    Owner->add_banned(name, "Thieves");
    if (!CAN_SEE_IN_ROOM(Owner) ||
	!CAN_SEE(Owner, tp))
    {
	return 1;
    }
    Owner->command("glare " + OB_NAME(tp));
    Owner->command("shout We don't like thieves here, " +
	(tp->query_met(Owner) ?
	     tp->query_name() : tp->query_nonmet_name())
	    + "!");
    tell_room(TO,
	QCTNAME(Owner) + " hustles " + QTNAME(tp) +
	    " out of the room.\n", tp);
    tp->catch_msg(QCTNAME(Owner) +
	" hustles you out of the bathhouse.\n");
    tp->move_living("M", OUTSIDE_ENTRY);
    tell_room(ENV(tp),
	QCNAME(tp) +
	" is propelled from the building to the north into the street.\n",
	tp);
    return "";
} /* no_theft */


/*
 * Function name:	no_fights
 * Description	:	evicts fighter, remember 'em til next reboot
 * Returns	:	mixed -- int 1 if owner cannot see the fighter
 *				 	(so they just get default msg).
 *				 string "" -- if owner can see, all msgs
 *					are written before return.
 */
public mixed
no_fights(object tp)
{
    string	name;

    if (!present(this_player(), this_object()))
	return 1;

    if (!objectp(tp))
    {
	tp = TP;
    }
    name = tp->query_name();
    Owner->add_banned(name, "Bullies");
    if (!CAN_SEE_IN_ROOM(Owner) ||
	!CAN_SEE(Owner, tp))
    {
	return 1;
    }
    Owner->command("glare " + OB_NAME(tp));
    Owner->command("shout Hey, no fighting in the baths, " +
	(tp->query_met(Owner) ?
	     tp->query_name() : tp->query_nonmet_name())
	    + "!");
    tell_room(TO,
	QCTNAME(Owner) + " hustles " + QTNAME(tp) +
	    " out of the room.\n", tp);
    tp->catch_msg(QCTNAME(Owner) +
	" hustles you out of the bathhouse.\n");
    tp->move_living("M", OUTSIDE_ENTRY);
    tell_room(ENV(tp),
	QCNAME(tp) +
	" is propelled into the street.\n", tp);
    return "";
} /* no_fights */


/*
 * Function name:	eject_banned
 * Description	:	eject thieves and fighters
 * Arguments	:	object pl -- the offending player
 *			string reason -- why they were banned
 */
public void
eject_banned(object pl, string reason)
{


    if (!objectp(pl) ||
	ENV(pl) != TO)
    {
	return;
    }

    Owner->command("emote hurries across the room.");
    Owner->command("shout " + reason + " are not welcome here, " + 
	(pl->query_met(Owner) ?
	     pl->query_name() : pl->query_nonmet_name())
	+ "!");
    tell_room(TO,
    	QCTNAME(Owner) + " shoves " + QTNAME(pl) +
	" out onto the street.\n",
	pl);
    pl->catch_msg(QCTNAME(Owner) + " shoves you out onto the street.\n");
    pl->move_living("M", OUTSIDE_ENTRY);
    tell_room(ENV(pl),
	QCNAME(pl) +
	" is propelled from the building to the north into the street.\n",
	pl);
} /* eject_banned */



/*
 * Function name:	knock_on_door
 * Description	:	respond to someone knocking on street door
 * Arguments	:	object pl -- the person who knocked
 *			object env -- the street room
 */
public void
knock_on_door(object pl, object env)
{
    string	reason;

    if (!Owner)
	reset_room();

    tell_room(TO,
	"You hear someone knocking on the door from outside.\n");
    Owner->command("emote opens the door and peers out.");
    tell_room(env,
	"The door opens, and " + QNAME(Owner) + " peers out.\n");
    if (!CAN_SEE(Owner, pl))
    {
	Owner->command("shrug annoyedly");
	Owner->command("emote closes the door.");
	tell_room(env,
	    QCTNAME(Owner) + " shrugs annoyedly.\n" +
	    "The door closes.\n");
	return;
    }
    if (strlen(reason = Owner->query_banned(pl->query_name())))
    {
	Owner->command("shout " + reason + " are not welcome here, " + 
	   (pl->query_met(Owner) ?
		 pl->query_name() : pl->query_nonmet_name())
	   + "!");
	Owner->command("emote slams the door.");
	tell_room(env, "The door slams shut.\n");
	return;
    }
    Owner->command("emote bows and opens the door wide.");
    tell_room(env,
	QCTNAME(Owner) + " bows to " + QTNAME(TP) +
	" and opens the door wide.\n", pl);
    pl->catch_msg(
	QCTNAME(Owner) + " bows to you and opens the door wide.\n" +
	"You walk through the door, which she closes behind you.\n");
    pl->move_living("north", TO);
    Owner->command("emote closes the door.");
    tell_room(env, "The door closes.\n");
} /* knock_on_door */



/*
 * Function name:	look_at
 * Description	:	VBFC to describe bench + occupants
 * Returns	:	string -- the description
 */
public string
look_at()
{
    return "The bench is softened by plump cushions. It is " +
	"long enough to hold several people quite comfortably.\n" +
	    sitting_on_chair(BENCH_NAME, this_player(), 0);
} /* look_at */


public object	query_owner()	{ return Owner; }
