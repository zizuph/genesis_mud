/*
 * /d/Gondor/open/fireplace/fireplace.c	
 * fireplace/kiln/fire pit/forge ... inherited by a room
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * see ~Gondor/open/fireplace/fireplace_example.c and
 *     ~Gondor/open/fireplace/fireplace.doc for more info
 *
 * thanks to Mercade for suggesting using Parse_pattern!
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/open/fireplace/fireplace.h" 

static string	Fire_container = "fireplace";
static string	Parse_pattern = "[the] 'fireplace'";
static int	Dark_room_ok;
static string	Ashes_path;
static int	Ashes = 0;
static int	Wood = WOOD_AMT;
static int	Burn_alarm;
static int	Pattern_was_set;
static int	Effects_alarm;
static float	Effects_time = EFFECTS_TIME;
static string	*Effects = ({
	"Flames leap above the burning wood.\n",
	"A wet piece of wood hisses when the flames reach it.\n",
	"Shadows cast by the flames flicker as if dancing.\n",
        "Sparks flicker as they swirl up from the fire.\n",
	"The firewood crackles as it burns.\n",
	"A draft causes the flames to flicker wildly.\n",
        "A smouldering piece of wood suddenly bursts into flames.\n",
	"The burning wood shifts, sending up a shower of sparks.\n",
	"The fire burns very low for a moment, then blazes up again.\n",
});

/* prototypes for configuring/querying fire 
 * don't know why you'd want some of the query_ routines,
 * but they're here for completeness ...
 */
public void	set_fire_container(string name);
public string	query_fire_container();
public void	set_parse_pattern(string pat);
public string	query_parse_pattern();
public void	set_wood(int n);
public int	query_wood();
public void	set_fire_state(int state);
public int	query_fire_state();
public void	set_dark_room_ok(int ok);
public int	query_dark_room_ok();
public int	set_ashes_path(string path);
public string	query_ashes_path();
public int	query_ashes();
public void	set_effects(string *msgs);
public string	*query_effects();
public void	set_effects_time(int t);
public int	query_effects_time();


/* prototypes for handling user interaction */
public int	light_fire(string arg);
public int	kick_fire(string arg);
public int	get_fire(string arg);
public int	put_fire(string arg);
public int	search_fire(string arg);

/* prototypes for internal routines */
public void	init_fire();
public void	burn_wood();
static void	start_the_fire();
static void	stop_the_fire();
public void	fire_effects();


/*
 * Function name:	init_fire
 * Description	:	add player actions
 */
public void
init_fire()
{
    add_action(light_fire,  "light");
    add_action(kick_fire,   "extinguish");
    add_action(kick_fire,   "kick");
    add_action(get_fire,    "get");
    add_action(get_fire,    "take");
    add_action(get_fire,    "pick");
    add_action(put_fire,    "put");
    add_action(put_fire,    "place");
    add_action(search_fire, "search");
} /* init_fire */


/* the easy ones ... */
public void	set_dark_room_ok(int ok) { Dark_room_ok = ok;        }
public int	query_dark_room_ok()	 { return Dark_room_ok;      }
public string	query_fire_container()	 { return Fire_container;    }
public string	query_parse_pattern()	 { return Parse_pattern;     }
public int	query_wood()		 { return Wood;              }
public string	query_ashes_path()	 { return Ashes_path;        }
public int	query_ashes()		 { return Ashes;             }
public string	*query_effects()	 { return Effects;           }
public int	query_effects_time()	 { return ftoi(Effects_time);}


/*
 * Function name:	set_fire_container
 * Description	:	set the name of whatever holds the fire
 *			and (if it hasn't already been set by
 *			the inheriting room) set parse_pattern
 * Arguments	:	string name -- the container's name
 */
public void
set_fire_container(string name)
{
    string	*words;
    int		s;
    if (!strlen(name))
    {
	return;
    }
    Fire_container = name;
    if (!Pattern_was_set)
    {
	if (sizeof(words = explode(name, " ")) == 1)
	{
	    Parse_pattern = "[the] '"+name+"'";
	}
	else
	{
	    Parse_pattern = "[the] '"+implode(words, "' '")+"'";
	}
    }
} /* set_fire_container */


/*
 * Function name:	set_parse_pattern
 * Description	:	set the pattern to use w parse_command()
 * Arguments	:	string pat -- the pattern
 */
public void
set_parse_pattern(string pat)
{
    Parse_pattern = pat;
    Pattern_was_set = 1;
} /* set_parse_pattern */


/*
 * Function name:	query_fire_state
 * Description	:	get the state of the fire
 * Returns	:	FIRE_BURNING, FIRE_UNLIT_WOOD or FIRE_ASHES
 */
public int
query_fire_state()
{
    if (Burn_alarm)
    {
	return FIRE_BURNING;
    }
    if (Wood > 0)
    {
	return FIRE_UNLIT_WOOD;
    }
    return FIRE_ASHES;
} /* query_fire_state */


/*
 * Function name:	set_fire_state
 * Description	:	set the state of the fire, adjust room light
 *			and OBJ_I_HAS_FIRE
 * Arguments	:	int state -- one of the FIRE_ states
 *
 * if the state requires wood and we've none, reset it to WOOD_AMT.
 * they can always call set_wood(), before or after set_fire_state(),
 * if they don't want the default.
 * don't write any msgs about the fire being lit or extinguished;
 * that's the caller's responsibility.
 */
public void
set_fire_state(int state)
{
    switch (state)
    {
    case FIRE_BURNING:
	if (!Burn_alarm)
	{
 	    if (!Wood)
	    {
		Wood = WOOD_AMT;
		Ashes = 0;
	    }
	    start_the_fire();
	}
	break;
    case FIRE_ASHES:
	if (Burn_alarm)
	{
	    stop_the_fire();
	}
	if (Wood)
	{
	    Ashes = Wood;
	    Wood = 0;
	}
	break;
    case FIRE_UNLIT_WOOD:
	if (Burn_alarm)
	{
	    stop_the_fire();
	}
	if (!Wood)
	{
	    Wood = WOOD_AMT;
	    Ashes = 0;
	}
	break;
    }
} /* set_fire_state */


/*
 * Function name:	set_wood
 * Description	:	set wood, kill fire if necessary
 * Arguments	:	int n -- if negative, default is used
 *
 * again, any msgs are the caller's responsibility
 */
public void
set_wood(int n)
{
    Wood = (n < 0 ? WOOD_AMT : n);
    Ashes = 0;
    if (Burn_alarm &&
	!Wood)
    {
	stop_the_fire();
    }
} /* set_wood */


/*
 * Function name:	set_ashes_path
 * Description	:	set the pathname of an object to give
 *			to player when s/he tries to "get ashes"
 * Arguments	:	string path -- the object path
 * Returns	:	0 if we can load the ob, 1 if not
 */
public int
set_ashes_path(string path)
{
    if (!strlen(path))
    {
	return 1;
    }

    FIX_EUID;
    path->short();
    if (objectp(find_object(path)))
    {
	Ashes_path = path;
	return 0;
    }
    return 1;
} /* set_ashes_path */



/*
 * Function name:	set_effects
 * Description	:	set noise/light messages to display
 * Arguments	:	string * msgs -- an array of msgs. 
 *				         if null, no effects
 */
public void
set_effects(string *msgs)
{
    Effects = msgs;
    if (Effects_alarm &&
	(!sizeof(msgs) ||
	 !strlen(msgs[0])))
    {
	remove_alarm(Effects_alarm);
	Effects_alarm = 0;
    }
} /* set_effects */



/*
 * Function name:	set_effects_time
 * Description	:	set the time between each special effects msg
 * Arguments	:	int t -- the time.  if <= 0, effects 
 *				 are turned off.
 */
public void
set_effects_time(int t)
{
    if (t > 0)
    {
	if (ftoi(Effects_time) != t)
	{
	    Effects_time = itof(t);
	    if (Effects_alarm)
	    {
		remove_alarm(Effects_alarm);
		Effects_alarm = set_alarm(Effects_time, Effects_time,
		    fire_effects);
	    }
	}
    }
    else
    {
	Effects_time = 0.0;
	if (Effects_alarm)
	{
	    remove_alarm(Effects_alarm);
	    Effects_alarm = 0;
	}
    }
} /* set_effects_time */


/*
 * Function name:	kick_fire
 * Description	:	handle attempts to extinguish the fire
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
kick_fire(string arg)
{
    string	*what = ({ "fire", "firewood", "wood" });

    if (!CAN_SEE_IN_ROOM(TP))
    {
	NF0("It is too dark to see.\n");
    }

    if (!strlen(arg))
    {
	return 0;
    }
    arg = LOW(arg);

    if (member_array(arg, what) < 0)
    {
	if (!parse_command(arg, ({ }), "%p 'in' "+Parse_pattern, what))
	{
	    return 0;
	}
	arg = what[0];
    }

    if (Burn_alarm)
    {
	WRITE("You kick the fire, scattering ashes and bits of "+
	    "charred wood. The fire goes out.");
	SAY(" kicks the fire, scattering ashes and bits of "+
	    "charred wood. The fire goes out.");
	stop_the_fire();
    }
    else if (query_verb() == "kick" &&
	     arg != "fire")
    {
	if (Wood <= 0)
	{
	    return 0;	/* get default soul response to 'kick' */
	}
	WRITE("You kick the "+arg+" in the "+Fire_container+
	    " -- ouch!");
	IF_LIGHT_SAY(TO, " kicks the "+arg+" in the "+Fire_container+".");
    }
    else
    {
	write("There is no fire to extinguish.\n");
    }
    return 1;
} /* kick_fire */


/*
 * Function name:	light_fire
 * Description	:	handle attempts to light the fire
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 *
 * for consistency w "light torch", allow lighting fire in dark room
 */
public int
light_fire(string arg)
{
    string	*what = ({ "fire", "firewood", "wood" });


    if (!strlen(arg))
    {
	return 0;
    }
    arg = LOW(arg);

    if (arg == "wood" ||
	arg == "firewood")
    {
	/* "light wood" can come to the room first even if player is 
	 * holding firewood. if player has firewood in hands or
	 * lying in room, i want "light" to apply there, not here.
	 */
    	if (objectp(present(arg, ({ TP, TO }))))
	{
	    return 0;
	}
    }
    else if (arg != "fire" &&
             !parse_command(arg, ({ }), "%p 'in' "+Parse_pattern, what))
    {
	return 0;
    }

    if (Burn_alarm)
    {
	write("The fire is already burning.\n");
    }
    else if (Wood > 0)
    {
	WRITE("You light the wood in the "+Fire_container+" and it "+
	    "quickly catches fire.");
	SAY(" lights the wood in the "+Fire_container+".");
	start_the_fire();
    }
    else
    {
	write("There is no wood in the "+Fire_container+" to light.\n");
    }
    return 1;
} /* light_fire */


/*
 * Function name:	get_fire
 * Description	:	handle attempts to get the fire/wood/ashes
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
get_fire(string arg)
{
    object	ob;
    string	vb = query_verb(),
		*what = ({ "firewood", "wood", "ash", "ashes" });

    if (!CAN_SEE_IN_ROOM(TP))
    {
	NF0("It is too dark to see.\n");
    }

    if (!strlen(arg))
    {
	return 0;
    }
    arg = LOW(arg);


    /* "get fire" and "get foo from fire" always fail ... */
    if (arg == "fire")
    {
	if (!Burn_alarm)
	{
	    write("There is no fire to "+vb+".\n");
	}
	else
	{
	    WRITE("You reach for the fire, but it is too hot.");
	    SAY(" reaches into the fire, but quickly draws back.");
	}
	return 1;
    }
    if (parse_command(arg, ({ }), "%p 'from' [the] 'fire'", what))
    {
	if (!Burn_alarm)
	{
	    write("There is no fire from which to "+vb+" "+what[0]+".\n");
	}
	else
	{
	    WRITE("You reach for the "+what[0]+
		", but the fire is too hot.");
	    SAY(" reaches into the fire, but quickly draws back.");
	}
	return 1;
    }

    if (member_array(arg, what) < 0)
    {
	if (!parse_command(arg, ({ }), "%p 'from' "+Parse_pattern, what))
	{
	    return 0;
	}
	arg = what[0];
    }

    if (arg == "ash" ||
	arg == "ashes")
    {
	if (!Burn_alarm)
	{
	    if (Ashes <= 0 ||
		!strlen(Ashes_path))
	    {
		write("The ashes slip through your fingers.\n");
		IF_LIGHT_SAY(TO, " reaches into the "+Fire_container+".");
	    }
	    else
	    {
		FIX_EUID;
		--Ashes;
		ob = clone_object(Ashes_path);
		write("You "+vb+" some ashes from the "+Fire_container+".\n");
		IF_LIGHT_SAY(TO,
		    " "+vb+"s some ashes from the "+Fire_container+".\n");
		if (ob->move(TP))
		{
		    ob->move(TO);
		    write("Oops, you drop the ashes.\n");
		    IF_LIGHT_SAY(TO, " drops the ashes.");
		}
	    }
	}
	else
	{
	    WRITE("You reach for the ashes, but the fire is too hot.");
	    SAY(" reaches into the fire, but quickly draws back.");
	}
    }
    else if (Burn_alarm)	/* getting wood */
    {
	WRITE("You reach for the burning wood, "+
		 "but the fire is too hot.");
	SAY(" reaches into the fire, but quickly draws back.");
    }
    else if (Wood > 0)
    {
	FIX_EUID;
	--Wood;
	ob = clone_object(FIREWOOD);
	write("You "+vb+" some wood from the "+Fire_container+".\n");
	IF_LIGHT_SAY(TO, " "+vb+"s some wood from the "+Fire_container+".\n");
	if (ob->move(TP))
	{
	    ob->move(TO);
	    write("Oops, you drop it.\n");
	    IF_LIGHT_SAY(TO, " drops the firewood.");
	}
    }
    else
    {
	write("There is no wood in the "+Fire_container+" to "+vb+".\n");
    }
    return 1;
} /* get_fire */


/*
 * Function name:	put_fire
 * Description	:	handle attempts to put wood/ashes in Fire_container
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
put_fire(string arg)
{
    string	*what = ({ "firewood", "wood", "ash", "ashes" }),
		where;
    int		in_fire, n;
    object	ob;

    if (!CAN_SEE_IN_ROOM(TP))
    {
	NF0("It is too dark to see.\n");
    }

    if (!strlen(arg))
    {
	return 0;
    }
    arg = LOW(arg);

    if (arg == "out fire" &&
	query_verb() == "put")
    {
	return kick_fire("fire");
    }

    if (parse_command(arg, ({ }), "%p 'on' / 'in' [the] 'fire'", what))
    {
	in_fire = 1;
	where = "fire";
    }
    else
    {
	if (!parse_command(arg, ({ }), "%p 'in' "+Parse_pattern, what))
	{
	    return 0;
	}
	where = Fire_container;
    }
    arg = what[0];

    if (in_fire &&
	!Burn_alarm)
    {
	WRITE("There is no fire in which to put the "+arg+".");
	return 1;
    }

    if (!objectp(ob = present(arg, TP)))
    {
	NF0("You have no "+arg+" to place in the "+where+".\n");
    }

    if (ob->move(TO))
    {
	/* use ob->short() here to be sure player knows which item
	 * ain't working
	 */
	NFN0("You cannot seem to place the "+ob->short()+" in the "+
	    where+".");
    }

    /* XXX if firewood, this puts the entire heap on.  probably
     * should just put one at a time.
     */
    if ((n = ob->num_heap()) <= 0)
    {
	n = 1;	 /* just in case ... */
    }
    if (arg == "firewood" ||
	arg == "wood")
    {
	Wood += n;
    }
    else
    {
	Ashes += n;
    }

    ob->remove_object();

    if (Burn_alarm)
    {
	write("You place the "+arg+" on the fire.\n");
	SAY(" places some "+arg+" on the fire.");
    }
    else
    {
	write("You place the "+arg+" in the "+Fire_container+".\n");
	IF_LIGHT_SAY(TO,
	    " places some "+arg+" in the "+Fire_container+".");
    }
    return 1;
} /* put_fire */


/*
 * Function name:	search_fire
 * Description	:	handle attempts to search the fire/wood/ashes
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
search_fire(string arg)
{
    string	*what = ({ "fire", "firewood", "wood", "ash", "ashes" });

    if (!strlen(arg))
    {
	return 0;
    }
    arg = LOW(arg);

    if (member_array(arg, what) < 0)
    {
    	if (!parse_command(arg, ({ }), "%p 'in' "+Parse_pattern, what))
	{
	    return 0;
	}
	arg = what[0];
    }

    if (Burn_alarm)
    {
	WRITE("The fire is too hot for you to search "+
	    (arg == "fire" ? "it." : "the "+arg+"."));
	return 1;
    }
    if (arg == "fire")
    {
	write("There is no fire to search.\n");
	return 1;
    }
    /* do normal search */
    return 0;
} /* search_fire */


/*
 * Function name:	burn_wood
 * Description	:	burn up one piece of wood; called via set_alarm
 */
public void
burn_wood()
{
    if (Wood > 0)
    {
	--Wood;
	++Ashes;
    }

    if (Wood > 0)
    {
	Burn_alarm = set_alarm(BURN_TIME, 0.0, burn_wood);
    }
    else
    {
	tell_room(TO,
	    "The fire in the "+Fire_container+" flickers and dies.\n");
	stop_the_fire();
    }
} /* burn_wood */


/*
 * Function name:	start_the_fire
 * Description	:	handle details of lighting the fire
 */
static void
start_the_fire()
{
    if (Wood <= 0)
    {
	return;
    }

    Burn_alarm = set_alarm(BURN_TIME, 0.0, burn_wood);
    TO->add_prop(OBJ_I_HAS_FIRE, (TO->query_prop(OBJ_I_HAS_FIRE) + 1));
    TO->add_prop(ROOM_I_LIGHT,   (TO->query_prop(ROOM_I_LIGHT) + 1));

    if (Effects_time > 0.0 &&
	!Effects_alarm &&
	sizeof(Effects) &&
	strlen(Effects[0]))
    {
	Effects_alarm = set_alarm(Effects_time, Effects_time, fire_effects);
    }

} /* start_the_fire */


/*
 * Function name:	stop_the_fire
 * Description	:	handle details of killing the fire
 */
static void
stop_the_fire()
{
    mixed	*alarm_info;
    int		prev_val;

    if (!Burn_alarm)
    {
	return;
    }

    if (sizeof(alarm_info = get_alarm(Burn_alarm)))
    {
	remove_alarm(Burn_alarm);
	if (Wood > 0 &&
	    ftoi(alarm_info[2]) < (BURN_TIME_I / 2))
	{
	    /* more than half burned -- use it up */
	    --Wood;
	    ++Ashes;
	}
    }
    Burn_alarm = 0;

    if (Effects_alarm)
    {
	remove_alarm(Effects_alarm);
	Effects_alarm = 0;
    }

    prev_val = TO->query_prop(OBJ_I_HAS_FIRE);
    TO->add_prop(OBJ_I_HAS_FIRE, (prev_val > 0 ? (prev_val - 1) : 0));

    prev_val = TO->query_prop(ROOM_I_LIGHT);
    if (prev_val > 1 ||
	Dark_room_ok)
    {
	TO->add_prop(ROOM_I_LIGHT, (prev_val - 1));
    }
} /* stop_the_fire */


/*
 * Function name:	fire_effects
 * Description	:	do random noise/light effects
 */
public void
fire_effects()
{
    int		s = sizeof(Effects);
    if (s)
    {
	tell_room(TO, Effects[random(s)]);
    }
} /* fire_effects */
