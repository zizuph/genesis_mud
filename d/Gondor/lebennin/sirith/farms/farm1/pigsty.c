/*
 * /d/Gondor/lebennin/sirith/farms/farm1/pigsty.c
 * pigsty of large farmstead in southern lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * Finwe,May 2019: Removed hidden exits
 *
 */

#pragma strict_types

#include <stdproperties.h>	/* for OBJ_S_SEARCH_FUN, etc	*/
#include <macros.h>		/* for OB_NUM			*/
#include <filter_funs.h>	/* for FILTER_PLAYERS		*/
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

#define	EASTYARD	(SIRITH_FARMS_DIR+"farm1/eastyard")
#define	SOUTHYARD	(SIRITH_FARMS_DIR+"farm1/southyard")
#define	MUD		(SIRITH_FARMS_DIR+"obj/mud")

#define	NFIELDS		9
#define	NPASTURES	6
#define	NTRACKS		9

/* if player has led pig into pigsty, pig stays here for 
 * N_RESETS_PER_ESCAPE, then runs away again
 */
#define	N_RESETS_PER_ESCAPE	2

/* how many resets since escaped; init to max so pig begins in fields */
static int	Nresets = N_RESETS_PER_ESCAPE;
static object	Pig;

/* prototypes */
public void	create_outdoors();
public void	init();
public object	query_pig();
public void	set_nresets(int	n);
public object	query_pig_env();
public void	reset_room();
public void	move_pig(object env, int onlyifopen);
public void	leave_sty(int state);
public int	climb_fence(string arg);
public void	opened_gate(object tp);
public void	leave_inv(object ob, object dest);
public string	muddy_player(string arg);
public string	do_search(object tp, string arg);
public int	do_close(string arg);
public int	do_open(string arg);


/*
 * Function name:	create_outdoors
 * Description	:	set up room
 */
public void
create_outdoors()
{
    set_areatype("farmyard");
    set_short("a muddy pen");
    set_extraline("Sturdy fencing encloses the area, and "+
	"a wooden gate leads north. A covered "+
	"shelter stands inside the fence to the south.");

    add_exit("southyard", "north", 0, 2);
    set_door(SIRITH_FARMS_DIR + "obj/f1_pigsty_gate2");
    set_climbdest(SIRITH_FARMS_DIR + "farm1/southyard");
    set_no_exit_msg( ({ "northeast", "east", "southeast",
	"southwest", "west", "northwest", "up", "down" }),
	BSN("You wander around the muddy pen.") );

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 2);

    add_item( ({ "area", "sty", "pen" }),
	BSN("A very muddy area, enclosed by a sturdy fence."));
    add_item( ({ "shelter", "wall", "walls", "roof" }),
	BSN("The shelter is primitive -- just three walls and a roof."));
    add_item( ({ "ground", "mud", "dirt" }),
	BSN("The mud oozes beneath your feet."));
    
    add_item( ({ "fence", "fencing" }),
	BSN("A sturdy fence encloses the pen."));

    /* dead simple .. even a pig can sometimes open it :-) */
    add_item( ({ "latch", "prong", "prongs", "fencepost", "post" }),
	BSN("The latch is simply two wooden prongs that swivel to "+
	    "fall one on either side of the fencepost."));
    
    add_cmd_item( "shelter", ({ "enter" }),
	&muddy_player("shelter") );
    add_cmd_item( ({ "around shelter", "around inside shelter",
    	"inside shelter" }), ({ "poke" }),
	&muddy_player("shelter") );

    add_cmd_item( ({ "mud", "ooze", "dirt" }), ({ "get", "take" }),
	&muddy_player("mud") );
    add_cmd_item( ({ "in mud", "mud", "in ooze", "ooze", "in dirt",
    	"dirt" }), ({ "scrabble" }),
	&muddy_player("mud") );
    
    reset_room();
} /* create_outdoors */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(climb_fence, "climb");
    add_action(climb_fence, "jump");
    add_action(muddy_player, "south");
    add_action(do_close, "close");
    add_action(do_open, "open");
} /* init */


/* the 3 easy ones ... */
public object	query_pig() 		{ return Pig; }
public void	set_nresets(int n)	{ Nresets = n; }
public object	query_pig_env() { return (objectp(Pig) ? ENV(Pig) : 0); }



/*
 * Function name:	reset_room
 * Description	:	replenish pig if necessary, be sure
 *			she is where she belongs
 *
 * pig starts out wandering in LIVESTOCK_RESTRAIN rooms.
 * when player returns her here, she'll stay put for N_RESETS_PER_ESCAPE,
 * then run away again.
 */
public void
reset_room()
{
    object	pigenv,
		gate,
		othergate,
		tp;
    string	tmpstr;

    ::reset_room();
    ++Nresets;

    if (!objectp(Pig))
    {
	if (!objectp(Pig = find_living(PIGNAME)))
	{
    	    Pig = clone_object(SIRITH_FARMS_DIR + "npc/pig");
	}
	else
	{
	    /* "cannot" happen */
	    TMP_LOG("had lost track of Pig "+file_name(Pig)+"\n");
	}
    }
    TMP_LOG("reset_room: ++Nresets ->  "+Nresets+", Pig #"+OB_NUM(Pig)+"\n");

    if (objectp(pigenv = ENV(Pig)))
    {
	/* if pig is already in a good outside room, leave her alone */
	if (sscanf(file_name(pigenv), (LIVESTOCK_RESTRAIN+"%s"), tmpstr))
	{
	    TMP_LOG("leaving pig in "+file_name(pigenv)+"\n");
	    return;
	}
    }

    /* if pig is following someone, leave her alone */
    if (strlen(tmpstr = Pig->query_follow()))
    {
	TMP_LOG("pig is in "+file_name(pigenv)+" following "+
	    tmpstr+"\n");
	return;
    }

    /* else pig is (a) newly cloned with no env, (b) in pigsty, or (c) in
     * a room where she shouldn't be wandering (but could be led).
     * also, pig is not following anyone.
     *
     * if in sty and don't have enough resets, wait.
     * otherwise, move outside.
     */
    if (Nresets < N_RESETS_PER_ESCAPE &&
	pigenv == TO)
    {
	/* pig is in sty and we need more resets before moving her */
	TMP_LOG("leaving pig in sty w "+Nresets+" resets\n");
	return;
    }

    /* pig has no env, or pig is somewhere she shouldn't be, or
     * pig is in sty and we have waited the required # of resets.
     * move her outside.
     * quest props will be removed in leave_inv().
     */
    Nresets = 0;
    move_pig(pigenv, 0);
    TMP_LOG("moved pig to "+file_name(environment(Pig))+"\n");
} /* reset_room */


/*
 * Function name:	move_pig
 * Description	:	move the pig to random field pasture or track
 * Arguments	:	object env -- the pig's environment
 *			int onlyifopen -- if pig is in sty, only move
 *					  if gate is open
 *
 * Called by this room's reset_room(), by this room's opened_gate(), by
 * this room's leave_inv() if player leaves without closing gate, by pig
 * when player feeds her in sty without first closing gate or when
 * she's led to a wrong place, and by pigwoods when pig is through hiding.
 */
public void
move_pig(object env, int onlyifopen)
{
    object	tp = TP,
		door;
    int		m, n;
    string	env_name = "",
		away_msg = "The huge pig ambles away.\n",
		move_to;

    if (!objectp(Pig))
    {
	/* "cannot" happen */
	if (!objectp(Pig = find_living(PIGNAME)))
	{
	    TMP_LOG("move_pig called but no pig\n");
	    return;
	}
	TMP_LOG("move_pig: had lost track of Pig "+file_name(Pig)+"\n");
    }

    if (env == TO)
    {
	if (onlyifopen &&
	    objectp(door = present(SIRITH_DOOR, TO)) &&
	    !door->query_open())
	{
	    return;
	}
	leave_sty(PIG_OK);
	away_msg = "The huge pig ambles north.\n";
    }

    m = NFIELDS + NPASTURES + NTRACKS;
    if ((n = random(m)) < NFIELDS)
    {
    	move_to = SIRITH_FARMS_DIR + "fields/field" + (n + 1);
    }
    else if (n < (NFIELDS + NPASTURES))
    {
	move_to = SIRITH_FARMS_DIR + "fields/pasture" + (n - NFIELDS + 1);
    }
    else
    {
	move_to = SIRITH_FARMS_DIR + "fields/track" +
	    (n - NFIELDS - NPASTURES + 1);
    }

    if (objectp(env))
    {
	env_name = file_name(env);
    }
    if (move_to != env_name)
    {
	if (objectp(env))
	{
	    tell_room(env, away_msg);
	}
	Pig->move(move_to);
	tell_room(move_to, "A huge pig ambles into view.\n");
	Pig->set_restrain_path(LIVESTOCK_RESTRAIN);
	Pig->set_random_move(random(5)+1);
    }
} /* move_pig */


/*
 * Function name:	leave_sty
 * Description	:	do msgs for opening pigsty gate if necessary
 *			do suitable msgs to adjacent rooms
 * Arguments	:	int state -- ok, drunk or hurt
 */
public void
leave_sty(int state)
{
    object	gate,
		othergate,
		yard,
		tp = TP;
    string	movemsg,
		doormsg;
	

    if (!objectp(Pig))
    {
	/* "cannot" happen */
	if (!objectp(Pig = find_living(PIGNAME)))
	{
	    TMP_LOG("leave_sty called but no pig\n");
	    return;
	}
	TMP_LOG("leave_sty: had lost track of Pig "+file_name(Pig)+"\n");
    }

    switch (state)
    {
    case PIG_DRUNK:
	movemsg = "wanders tipsily";
	doormsg = BSN("The huge pig weaves a tipsy path to the gate and "+
	    "clumsily nudges the latch up with her snout.");
	break;
    case PIG_HURT:
	movemsg = "staggers";
	doormsg = BSN("The huge pig staggers painfully to the gate "+
	    "and with a desperate grunt thrusts the "+
	    "latch up with her snout.");
	break;
    default:
	movemsg = "ambles";
	doormsg = BSN("The huge pig walks to the gate and "+
	    "nudges the latch up with her snout.");
	break;
    }

    if (objectp(gate = present(SIRITH_DOOR)) &&
	!gate->query_open())
    {
	    set_this_player(Pig);
	    gate->do_open_door(doormsg);
	    if (objectp(othergate = gate->query_other_door()))
	    {
		othergate->do_open_door("The gate opens.\n");
	    }
	    set_this_player(tp);
    }
    /* if southyard or eastyard is loaded, then do msgs to show pig leaving.
     */
    if (objectp(yard = find_object(SOUTHYARD)))
    {
	tell_room(yard, "A huge pig "+movemsg+" into view.\n"+
	  		 "The huge pig "+movemsg+" north.\n");
    }
    if (objectp(yard = find_object(EASTYARD)))
    {
	/* say "away", rather than "east" -- gate in eastyard
	 * might be closed
	 */
	tell_room(yard, "A huge pig "+movemsg+" into view.\n"+
	    		 "The huge pig "+movemsg+" away.\n");
    }
} /* leave_sty */


/*
 * Function name:	climb_fence
 * Description	:	handle climb fence/fencing
 * Arguments	:	string arg -- whatever the player typed
 * Return	:	1 if we recognize the arg, 0 if not
 */
public int
climb_fence(string arg)
{
    object gate;

    if (arg == "fence" ||
	arg == "fencing")
    {
	set_dircmd("fence");
	write(BSN("You scramble over the fence."));
	TP->move_living("over the fence",
	    SIRITH_FARMS_DIR+"farm1/southyard");
	return 1;
    }
    else if (arg == "gate" || 
	     arg == "wooden gate" ||
	     arg ==  "fence gate")
    {
	if (objectp(gate = present(SIRITH_DOOR)) &&
	    gate->query_open())
	{
	    write(BSN(capitalize(query_verb())+
	 	  "ing an open gate is pointless."));
	}
	else
	{
	    set_dircmd("gate");
	    write(BSN("You scramble over the gate."));
	    TP->move_living("over the gate",
	        SIRITH_FARMS_DIR+"farm1/southyard");
	}
	return 1;
    }
    return 0;
} /* climb_fence */


/*
 * Function name:	opened_gate
 * Description	:	handle pig escaping when player opens gate
 * Arguments	:	object tp -- the player who opened the gate
 */
public void
opened_gate(object tp)
{
    string	pname;
    /* if pig was not led in, or if pig has been here for
     * the required # of resets, escape 
     */
    if (!objectp(tp) ||
	!objectp(Pig) ||
        (!strlen(pname = Pig->query_prop(SIRITH_S_WAS_LED)) && 
         Nresets < N_RESETS_PER_ESCAPE))
    {
	return;
    }

    /* piggie was led into sty. if the person who led is the one who
     * opened the gate, always escape. if gate opened by someone else
     * 1/3 chance of escape
     * quest props will be removed in leave_inv().
     */
    if (pname != tp->query_real_name() &&
	random(3))
    {
	return;
    }
    DEBUG_LOG(tp->query_real_name()+" opened gate and pig escaped.\n");
    set_alarm(1.0, 0.0, &move_pig(TO, 1));
} /* opened_gate */


/*
 * Function name:	leave_inv
 * Description	:	after parent's leave_inv(), check player props.
 * Arguments	:	ob: The object that just left this inventory
 *                	dest: Where it went.
 */
public void
leave_inv(object ob, object dest)
{
    string	vb,
		pname;
    object	pigenv,
		player,
		thisob = TO;

    ::leave_inv(ob, dest);
    if (!objectp(Pig))
    {
	if (!objectp(Pig = present(PIGNAME, thisob)))
	{
	    return;
	}
	/* "cannot" happen */
	TMP_LOG("leave_inv: had lost track of Pig "+file_name(Pig)+"\n");
    }
    pigenv = ENV(Pig);

    /* player only retains the fed-pig prop if the pig is still here
     * and player climbs fence or gate to get out
     */
    if (ob->query_prop(SIRITH_I_LED_PIG))
    {
        if ((vb = QVB) != "climb" &&
            vb != "jump")
	{
	    DEBUG_LOG(ob->query_real_name()+" left sty via '"+
		vb+"' -- removing LED_PIG prop.\n");
	    ob->remove_prop(SIRITH_I_LED_PIG);
	    if (pigenv == thisob && 
	        Pig->query_prop(SIRITH_S_WAS_LED) == ob->query_real_name())
	    {
		DEBUG_LOG("no climb -> calling move_pig\n");
		set_alarm(1.0, 0.0, &move_pig(thisob, 1));
	    }
	}
	else
	{
            DEBUG_LOG(ob->query_real_name()+" did "+vb+" from sty\n");
	}

	if (pigenv != thisob)
	{
	    DEBUG_LOG("no pig in sty when "+ob->query_real_name()+
		" left, removing LED_PIG prop\n");
	    ob->remove_prop(SIRITH_I_LED_PIG);
	}
    }
    else if (ob->id(PIGNAME) &&
             strlen(pname = ob->query_prop(SIRITH_S_WAS_LED)))
    {
	DEBUG_LOG("pig #"+OB_NUM(ob)+" leaves sty, removing WAS_LED by "+
		pname+" prop\n");
	ob->remove_prop(SIRITH_S_WAS_LED);

	if (objectp(player = find_living(pname)) &&
	    player->query_prop(SIRITH_I_LED_PIG))
	{
	    DEBUG_LOG("and removing LED_PIG prop from "+pname+"\n");
	    player->remove_prop(SIRITH_I_LED_PIG);
	}
    }
} /* leave_inv */


/*
 * Function name:	muddy_player
 * Description	:	handle attempts to enter shelter or get mud
 * Arguments	:	string arg -- "shelter" or "mud"
 * Returns	:	null string -- response handled via write()
 *
 * makes the player muddy
 */
public string
muddy_player(string arg)
{
    if (arg == "mud")
    {
	write(BSN("The mud oozes from your grasp, leaving "+
	    "you rather dirty."));
	SAY(" scrabbles in the mud.");
    }
    else	/* shelter */
    {
	write(BSN("You poke around inside the shelter "+
	    "(becoming rather dirty in the process), but "+
	    "find nothing but more mud."));
	SAY(" pokes around inside the shelter.");
    }

    if (!objectp(present(SIRITH_MUD, TP)))
    {
   	FIX_EUID;
	clone_object(MUD)->move(TP, 1);
    }

    return "";
} /* muddy_player */


/*
 * Function name:	do_search
 * Description	:	handle searching mud/shelter
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 * Return	:	string describing results of search
 */
public string
do_search(object tp, string arg)
{
    if (arg != "ground" &&
	arg != "mud" &&
	arg != "dirt" &&
        arg != "shelter")
    {
	return "";
    }

    if (!objectp(present(SIRITH_MUD, tp)))
    {
   	FIX_EUID;
	clone_object(MUD)->move(tp, 1);
    }

    return "You find only mud. It oozes from your grasp, "+
	   "leaving you rather dirty.\n";
} /* do_search */


/*
 * Function name:	do_close
 * Description	:	allow close pen/sty/etc to work
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_close(string arg)
{
    object gate, othergate;

    if (arg != "pen" &&
	arg != "sty" &&
	arg != "pigsty" &&
        arg != "fence" &&
	arg != "fencing")
    {
	return 0;
    }

    if (!(gate = present(SIRITH_DOOR)))
    {
	ERR_LOG("no gate in sty?\n");
	return 0;
    }
    
    if (!gate->query_open())
    {
	write("The wooden gate is already closed.\n");
	return 1;
    }

    write("Ok.\n");
    SAY(" closes the wooden gate.");
    gate->do_close_door("");
    if (objectp(othergate = gate->query_other_door()))
    {
	othergate->do_open_door("The gate closes.\n");
    }
    return 1;
} /* do_close */


/*
 * Function name:	do_open
 * Description	:	allow open pen/sty/etc to work
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_open(string arg)
{
    object gate, othergate;

    if (arg != "pen" &&
	arg != "sty" &&
	arg != "pigsty" &&
        arg != "fence" &&
	arg != "fencing")
    {
	return 0;
    }

    if (!(gate = present(SIRITH_DOOR)))
    {
	ERR_LOG("no gate in sty?\n");
	return 0;
    }
    
    if (gate->query_open())
    {
	write("The wooden gate is already open.\n");
	return 1;
    }

    write("Ok.\n");
    SAY(" opens the wooden gate.");
    gate->do_open_door("");
    if (objectp(othergate = gate->query_other_door()))
    {
	othergate->do_open_door("The gate opens.\n");
    }
    return 1;
} /* do_open */
