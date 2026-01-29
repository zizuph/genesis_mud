/*
 * /d/Gondor/std/water/boat.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * based on boat code of Elessar and of Fysix -- thanks, guys!
 *
 * this is the outer boat object ... inside_boat.c is the room
 * that holds boat passengers.
 *
 */

#pragma strict_types

inherit "/std/object";

#include <language.h>		/* for LANG_THESHORT	*/
#include <macros.h>		/* for IS_CLONE		*/
#include <filter_funs.h>	/* for FILTER_LIVE, etc */
#include <stdproperties.h>	/* for OBJ_I_*		*/
#include <composite.h>		/* for COMPOSITE_LIVE	*/
#include <options.h>		/* for OPT_BRIEF	*/
#include "/d/Gondor/defs.h"
#include "water_room.h"
#include "boat.h"


/* may drag the boat in these directions */
#define	DRAG_DIRECTIONS \
    ({	"north", "northeast", "east", "southeast", "south", \
	"southwest", "west", "northwest", "n", "ne", "e", "se", \
	"s", "sw", "w", "nw", \
    })
#define	DRAG_FATIGUE_MULT	10	/* multiplier for normal fatigue */
#define	MIN_DRAG_FATIGUE	-30	/* min for dragging a boat	*/


static string  *Enter_cmd,		/* "board", "enter", ...	*/
		Orig_short,		/* original short desc		*/
		Capsized_adj;		/* "capsized" or "overturned"	*/
static int	Capacity,		/* how many people it holds	*/
		Last_gotten,		/* when boat was last taken	*/
		Capsized,		/* have we overturned?		*/
		Max_volume;		/* limit on volume of objs in	*/
					/*	passenger's inventory	*/
static object	Inside,			/* room containing passengers	*/
		Pilot;			/* person who last moved boat	*/


/* prototypes */
public void		create_boat();
nomask void		create_object();
public void		init();
public void		set_short(mixed val);
varargs public mixed	long(string str, object for_obj);
varargs public int	move(mixed dest, mixed subloc);
public void		enter_env(object dest, object old);
public void		move_to_surface();
public int		do_enter(string arg);
public void		remove_object();
public string		can_get_boat();
public void		set_capsized(int cap);
public void		hit_rock(int str);
public void		break_apart(string msg);
public int		flip_boat(string arg);
public int		move_boat(string arg);
public void		add_drag_fatigue(object tp, int fat_change);
public void		set_capacity(int n);
public void		set_inside_boat(mixed inside);
public void		set_enter_cmd(mixed cmd);
public string		*query_enter_cmd();
public int		query_capacity();
public object		query_inside_boat();
public int		query_last_gotten();
public int		query_capsized();
public int		query_max_current();
public void		set_max_volume(int v);
public int		query_max_volume();
public void		set_pilot(object p);
public object		query_pilot();


/*
 * Function name:	create_boat
 * Description	:	creator for boat rooms
 * Configure your boat here.
 */
public void
create_boat()
{
} /* create boat */


/*
 * Function name:	create_object
 * Description	:	object creator
 */
nomask void
create_object()
{
    string	*names;

    if (!IS_CLONE)
    {
	return;
    }

    /* set up reasonable defaults */
    set_short("row boat");
    set_long("The row boat is plain and somewhat battered.\n");
    Enter_cmd = ({ "enter", "board" });
    Capacity = DEFAULT_CAPACITY;

    add_prop(OBJ_I_BOAT, 1);
    add_prop(OBJ_I_FLOAT, 1);
    add_prop(OBJ_I_WEIGHT, DEFAULT_WEIGHT);
    add_prop(OBJ_I_VOLUME, DEFAULT_VOLUME);
    add_prop(OBJ_M_NO_GET, can_get_boat);

    create_boat();

    if (!sizeof(names = query_names()))
    {
	set_name( ({ "row boat", "boat", "rowboat" }) );
    }
    if (!Max_volume)
    {
	Max_volume = DEFAULT_MAX_VOLUME(query_prop(OBJ_I_VOLUME));
    }

    /* if no inside boat, roll our own */
    if (!objectp(Inside))
    {
	set_inside_boat(INSIDE_BOAT_FILE);
    }

} /* create_object */


/* Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    int		s;

    ::init();
    s = sizeof(Enter_cmd);
    while (s-- > 0)
    {
    	add_action(do_enter, Enter_cmd[s]);
    }

    add_action(flip_boat, "turn");
    add_action(flip_boat, "right");
    add_action(flip_boat, "flip");
    add_action(flip_boat, "tip");

    add_action(move_boat, "launch");
    add_action(move_boat, "move");
    add_action(move_boat, "drag");
    add_action(move_boat, "pull");
    add_action(move_boat, "push");

} /* init */


/*
 * Function name:	set_short
 * Description	:	mask parent so we remember the original short
 * Arguments	:	mixed short -- the desc, or VBFC, or function
 */
public void
set_short(mixed val)
{
    ::set_short(val);
    if (stringp(val))
    {
	Orig_short =val;
    }
} /* set_short */



/*
 * Function name:	long
 * Description	:	mask parent so we can append passenger list
 * Arguments	:	string str -- what is looking at
 *			object for_obj -- who's looking
 * Returns	:	mixed -- description or 1 if no such item
 */
varargs public mixed
long(string str, object for_obj)
{
    object	*passengers;
    mixed	desc;
    int		s;

    desc = ::long(str, for_obj);

    if (Capsized)
    {
	desc += "The " + query_name() + " is " + Capsized_adj + ".\n";
    }

    if (strlen(str) ||
	!stringp(desc) ||
	!(s = sizeof(passengers = FILTER_LIVE(all_inventory(Inside)))))
    {
	return desc;
    }

    return desc +
	BSN(capitalize(COMPOSITE_LIVE(passengers)) +
	( s == 1 ? " is" : " are" ) + " sitting in the " + query_name() + ".");
} /* long */


/*
 * Function name:       move
 * Description  :       mask parent so we display the new room to the
 *                              boat passengers when it moves
 * Arguments    :       mixed dest -- destination
 *                      subloc: 1 == Always move, otherwise name of subloc
 * Returns      :       0 on success, !0 on failure
 */
varargs public int
move(mixed dest, mixed subloc)
{
    int rval;
    object *live, *brief, *mortals, env;
 
    if (!(rval = ::move(dest, subloc)) &&
	objectp(TO) &&
	(env = ENV(TO))->query_prop(ROOM_I_IS))
    {
	live = FILTER_LIVE(all_inventory(Inside));
	brief = filter(live, &->query_option(OPT_BRIEF));
	mortals = filter(live, not @ &->query_wiz_level());
	tell_room(Inside, file_name(env) + "\n", (brief + mortals));
	tell_room(Inside, Inside->long_func(), brief);
    }
    return rval;
} /* move */


/*
 * Function name:	enter_env
 * Description	:	mask parent so that we make boats float to the surface
 *			if dropped underwater, and remove the ROOM_I_IS prop
 *			from inside_boat if this boat obj is not in a
 *			onwater room and not on dry land.
 * Arguments	:	object dest - the destination we are entering.
 *			object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old) 
{
    int	inroom1,	/* were we in an ok room in 'old'	*/
	inroom2,	/* are we in an ok room in 'dest'	*/
	prevtype,	/* type of old				*/
	type;		/* type of dest				*/

    prevtype = -1;
    if (!objectp(old))
    {
	Inside->remove_prop(ROOM_I_IS);
	inroom1 = 0;
    }
    else if (old->query_prop(ROOM_I_IS))
    {
	prevtype = old->query_prop(ROOM_I_TYPE);
	if (prevtype != ROOM_UNDER_WATER)
	{
	    inroom1 = 1;
	}
    }

    ::enter_env(dest, old);

    inroom2 = (objectp(dest) &&
	       dest->query_prop(ROOM_I_IS));
    if (inroom2)
    {
	if ((type = dest->query_prop(ROOM_I_TYPE)) == ROOM_UNDER_WATER)
	{
	    set_alarm(3.0, 0.0, &move_to_surface());
	}
	if (Capsized &&
	    type != prevtype)
	{
	    set_capsized(1);	/* so Capsized_adj is changed */
	}
    }
    else
    {
	Last_gotten = time();
	if (Capsized)
	{
	    set_capsized(0);
	}
    }

    if (inroom1 != inroom2)
    {
	Inside->add_prop(ROOM_I_IS, inroom2);
    }
} /* enter_env */


/*
 * Function name:	move_to_surface
 * Description	:	boat has been dropped underwater ... move it
 *				to the surface
 */
public void
move_to_surface()
{
    string	surface, name = query_name();
    object	env = ENV();

    if (strlen(surface = env->room_in_dir("up")))
    {
	FIX_EUID;
	surface->short();
	tell_room(env,
	    "The " + name + " floats upwards.\n");
	tell_room(surface,
	    capitalize(LANG_ADDART(name)) +
		" floats into view from below.\n");
	move(surface, 1);
    }
} /* move_to_surface */


/*
 * Function name:	do_enter
 * Description	:	handle attempts to enter boat
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 */
public int
do_enter(string arg)
{
    object	ob,
		*toobig,
		*passengers,
		env = ENV();
    string	vb = QVB,
		name = query_name();
    int		type,
		*str;

    if (!env->query_prop(ROOM_I_IS))
    {
	return 0;
    }

    if (!strlen(arg) ||
	!parse_command(LOW(arg), ({ TO }), "[the] %o", ob))
    {
	NF0(capitalize(vb) + " what?\n");
    }

    if ((type = env->query_prop(ROOM_I_TYPE)) == ROOM_UNDER_WATER)
    {
	write("The " + name + " floats out of reach.\n");
	return 1;
    }

    if (Capsized)
    {
	WRITE("You cannot " + vb + " the " + name + " while it is upside down.");
	return 1;
    }

    passengers = FILTER_LIVE(all_inventory(Inside));
    if (sizeof(passengers) >= Capacity)
    {
	write("The " + name + " is full.\n");
	return 1;
    }

    /* prevent, for example, entering a boat while carrying another boat */
    toobig = filter(all_inventory(TP), 
	&operator(<=)(Max_volume) @ &->query_prop(OBJ_I_VOLUME));
    if (sizeof(toobig))
    {
	WRITE("You cannot enter the " + name + " while carrying " +
	    LANG_THESHORT(toobig[0]) + ".");
	return 1;
    }


    if (type != ROOM_IN_WATER)
    {
    	write("You " + vb + " the " + name + "\n");
	TP->move_living("into the " + name, Inside);
	return 1;

    }
    str = env->query_currentstr();
    if (str[0] >= ROUGH_CURRENT &&
	random(str[0] - ROUGH_CURRENT + 2))
    {
	WRITE("You attempt to hoist yourself into the " + name +
	    ", but the current causes you to lose your grip and " +
	    "fall back into the water.");
	SAY(" tries to enter the " + name + ", but falls back into " +
	    "the water.");
	return 1;
    }
    write("You hoist yourself into the " + name + ".\n");
    TP->move_living("into the " + name, Inside);
    return 1;
} /* do_enter * /


/*
 * Function name:	remove_object
 * Description	:	only allow 'em to remove this object if
 *			inside boat is empty.
 * apparently, returning failure here does not prevent the boat
 * being removed.  oh, well, at least we log it.
 */
public void
remove_object()
{
    object	prev;
    int		i;
    string	errmsg;

    if (IS_CLONE &&
	objectp(Inside) &&
	sizeof(FILTER_LIVE(all_inventory(Inside))))
    {
	errmsg = "remove_object() called in non-empty boat from:\n";
	i = 0;
	while (objectp(prev = previous_object(i)))
	{
	    errmsg += "	" + file_name(prev) + "\n";
	    --i;
	}
	if (i == 0)
	{
	    errmsg += "	no previous object\n";
	}
	ERR_LOG(errmsg);
	return 0;
    }
    Inside->remove_object();
    ::remove_object();
} /* remove_object */


/*
 * Function name:	can_get_boat
 * Description	:	never get boat, but have different msgs if there
 *				are people inside, or if it's in the water.
 * Returns	:	string -- the message
 */
public string
can_get_boat()
{
    object env;
    if (objectp(Inside) &&
	sizeof(FILTER_LIVE(all_inventory(Inside))))
    {
	return BSN("You cannot possibly get the " + query_name() +
	   " while people are in it.");
    }
    if (objectp(env) &&
	env->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
	return BSN("You attempt to lift the " + query_name() +
	    " out of the water, but only succeed in ducking yourself.");
    }
    return BSN("You attempt to hoist the boat, but only succeed " +
	"in dragging it a short distance.");
} /* can_get_boat */


/*
 * Function name:	set_capsized
 * Description	:	set the capsized flag, alter short desc as needed
 * Arguments	:	int cap -- 0 if upright, 1 if capsized
 *
 * If short is a string, we take care of alterating for capsized boats.
 * If it's a function, the inheriting boat is on its own.
 * Notice that we have to invoke our parent's set_short(), else we'll
 * overwrite Orig_short.
 */
public void
set_capsized(int cap)
{
    object env = ENV();
    int type;

    if (cap)
    {
	if (env->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
	{
	    Capsized_adj = "capsized";
	}
	else
	{
	    Capsized_adj = "overturned";
	}
    }
    if (cap == Capsized)	/* no change in state */
    {
	return;
    }

    Capsized = cap;
    if (Capsized)
    {
	/* change the short desc *before* dumping passengers, so
	 * that if this is done on entrance to a room, they'll
	 * see a capsized boat in the room inv
	 */
	if (stringp(query_short()))
	{
	    ::set_short(Capsized_adj + " " + Orig_short);
	}
	Inside->capsize(env);
    }
    else if (stringp(query_short()))
    {
	::set_short(Orig_short);
    }
} /* set_capsized */


/*
 * Function name:	hit_rock
 * Description	:	boat hits a rock .. maybe capsize,
 *			maybe break apart
 * Arguments	:	int str -- current str
 */
public void
hit_rock(int str)
{
    object	env = ENV();
    int		count = query_prop(OBJ_I_HIT_ROCK);
    string	name = query_name();

    tell_room(Inside,
	"The " + name + " hits a rock, and shudders with the impact.\n");
    tell_room(env,
	"The " + name + " hits a rock, and shudders with the impact.\n");

    if (str < ROUGH_CURRENT)
    {
    	++count;
    }
    else
    {
	count += 2;
    }
    if (count <= (MIN_ROCK_HITS + random(MIN_ROCK_HITS)))
    {
	add_prop(OBJ_I_HIT_ROCK, count);
    }
    else
    {
	break_apart("The impact with the rock breaks the " + name + " apart.\n");
    }
} /* hit_rock */


/*
 * Function name:	break_apart
 * Description	:	reduce boat to splinters
 * Arguments	:	string msg -- (optional) msg to give the room
 */
public void
break_apart(string msg)
{
    object	env = ENV(),
		wood;
    if (!Capsized)
    {
	set_capsized(1);
    }
    tell_room(env,
	( strlen(msg) ? msg: "The " + query_name() + " breaks apart!\n" ));
    FIX_EUID;
    wood = clone_object(SPLINTERED_WOOD);
    wood->set_heap_size(1 + random(4));
    wood->move(env, 1);
    remove_object();
} /* break_apart */


/*
 * Function name:	flip_boat
 * Description	:	handle attempts to flip/turn/.. boat
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
flip_boat(string arg)
{
    string	vb = QVB, name;
    object	ob, env;
    int		type;

    if (!strlen(arg) ||
	!parse_command(arg, ({ TO }), "[the] %o [over]", ob))
    {
	NF0(capitalize(vb) + " what?\n");
    }

    if (sizeof(FILTER_LIVE(all_inventory(Inside))))
    {
	write("The boat is too heavy to " + vb + ".\n");
	return 1;
    }

    name = query_name();
    env = ENV();
    type = env->query_prop(ROOM_I_TYPE);
    if ((type != ROOM_IN_WATER &&
	 type != ROOM_UNDER_WATER) ||
	CAN_FLIP(TP, env->query_currentstr()[0], Inside->query_max_current()))
    {
	write("You flip the " + name + " over.\n");
	SAY(" flips the " + name + " over.");
	set_capsized(!Capsized);
    }
    else
    {
	write("You try to flip the " + name +
	    ", but only succeed in ducking yourself.\n");
	SAY(" tries to flip the " + name +
	    ", but only succeeds in ducking " + TP->query_objective() +
	    "self.\n");
    }
    return 1;
} /* flip_boat */


/*
 * Function name:	move_boat
 * Description	:	handle attempts to move/push/.. boat
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
move_boat(string arg)
{
    int		i,
		oldfat;
    object	ob,
		env;
    string	dir,
		m_in,
		m_out,
		name,
		vb = QVB;

    if (!strlen(arg) ||
	!parse_command(LOW(arg), ({ TO }), "[the] %o %s", ob, dir))
    {
	NF0(CAP(vb) + " what?\n");
    }

    name = query_name();
    if (vb == "launch")
    {
	NF0("You must be inside the " + name + " to launch it.\n");
    }

    if (!strlen(dir))
    {
	NF0(CAP(vb) + " the " + name + " where?\n");
    }

    if (objectp(Inside) &&
	sizeof(FILTER_LIVE(all_inventory(Inside))))
    {
	NF0("You try to " + vb + " the " + name +
	    ", but cannot budge it.\n");
    }

    if ((i = member_array(dir, DRAG_DIRECTIONS)) < 0)
    {
	NF0("You can't seem to " + vb + " the " + name +
	    " in that direction.\n");
    }
    else if (i >= 8)
    {
	dir = DRAG_DIRECTIONS[i-8];	/* use "north" if they typed "n" */
    }

    if (TP->query_wiz_level())
    {
	WRITE("Ordinarily, we would use 'command' here to move " +
	    "you and the boat. Since you're a wizard, " +
	    "that won't work. Sorry.");
	return 1;
    }

    /* use command() here ... i don't want to deal with all the
     * stuff of exits myself.  this may not be perfect ...
     * we might end up getting the "dragging" msg when in fact the 
     * boat doesn't move ... but let's risk it.
     */
    write("You take a firm grip on the " + name + ".\n");
    SAY(" takes a firm grip on the " + name + ".");

    m_in = TP->query_m_in();
    m_out = TP->query_m_out();
    TP->set_m_in("arrives, dragging " + LANG_ADDART(name) + ",");
    TP->set_m_out("drags the " + name);
    oldfat = TP->query_fatigue();
    TP->command("$" + dir);
    TP->set_m_in(m_in);
    TP->set_m_out(m_out);

    if ((env = ENV(TP)) != ENV(TO))
    {
	move(env);
	add_drag_fatigue(TP, (TP->query_fatigue() - oldfat));
    }
    write("You release your grip on the " + name + ".\n");
    return 1;
} /* move_boat */


/*
 * Function name:	add_drag_fatigue
 * Description	:	have player incur fatigue of dragging boat
 * Arguments	:	object tp -- the player
 *			int fat_change -- how much fatigue was incurred
 *					  just taking the exit
 *
 * N.B. this is a separate routine so it may be easily masked
 *
 */
public void
add_drag_fatigue(object tp, int fat_change)
{
    if (fat_change < 0)
    {
	fat_change *= DRAG_FATIGUE_MULT;
    }
    else
    {
	fat_change = MIN_DRAG_FATIGUE;
    }
    tp->add_fatigue(fat_change);
} /* add_drag_fatigue */


/*
 * Function name:	set_capacity
 * Description	:	set max # boat can hold
 * Arguments	:	int n -- the capacity
 *
 * N.B. we enforce a "reasonable" range of values
 */
public void
set_capacity(int n)
{
    Capacity = CHECK_RANGE(n, 1, MAX_CAPACITY);
} /* set_capacity */


/*
 * Function name:	set_inside_boat
 * Description	:	set the place to hold boat's occupants
 * Arguments	:	mixed inside -- inside_boat object or name
 */
public void
set_inside_boat(mixed inside)
{
    if (objectp(inside))
    {
	Inside = inside;
    }
    else
    {
	FIX_EUID;
	Inside = clone_object(inside);
    }
    Inside->set_boat(TO);
} /* set_inside_boat */


/* the simple set-and-query config stuff follows. */
public void	set_enter_cmd(mixed cmd)   { Enter_cmd = ARRAY(cmd);}
public string  *query_enter_cmd()          { return Enter_cmd;		}
public int	query_capacity()           { return Capacity;		}
public object	query_inside_boat()        { return Inside;		}
public int	query_last_gotten()	   { return Last_gotten;	}
public int	query_capsized()	   { return Capsized;		}
public int	query_max_current() { return Inside->query_max_current(); }
public void	set_max_volume(int v)	   { Max_volume = v;		}
public int	query_max_volume()	   { return Max_volume;		}
public void	set_pilot(object p)	   { Pilot = p;		}
public object	query_pilot()		   { return Pilot;		}

