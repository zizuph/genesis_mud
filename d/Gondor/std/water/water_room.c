/*
 * /d/Gondor/std/water/water_room.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * inherited by onwater.c and underwater.c
 * many ideas borrowed from elessar's river code (thanks, elessar!)
 *
 *
 * Fixed typo. Toby, 2007-04-23
 *
 * 2007/04/23 Toby - Last updated
 * 2011/11/19 Lavellan - Added newline after fail message. Does WRITE not do
 *      that? Other messages may need changing too.
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water";

#include <composite.h>		/* for COMPOSITE_WORDS		*/
#include <ss_types.h>		/* for SS_SWIM			*/
#include <language.h>		/* for LANG_ADDART		*/
#include <stdproperties.h>	/* for properties		*/
#include <macros.h>		/* for QNAME			*/
#include <filter_funs.h>	/* for FILTER_LIVE		*/
#include <state_desc.h>		/* for SD_FATIGUE, SD_STAT_DENOM*/
#include "/d/Gondor/defs.h"	/* always ...			*/


#ifndef ROOM_I_NO_ALLOW_STEED
#include "/d/Gondor/std/steed/steed.h"
#endif /* !ROOM_I_NO_ALLOW_STEED */

#ifndef ROOM_M_DA_DRAGONSTEED_NO_LAND
#define ROOM_M_DA_DRAGONSTEED_NO_LAND "_room_m_da_dragonsteed_no_land"
#endif /* !ROOM_M_DA_DRAGONSTEED_NO_LAND */

#include "water_room.h"


static string	Watertype,	/* river, stream, pond, ...		*/
	       *Upstreamdir,	/* upstream direction(s)		*/
	       *Downstreamdir,	/* downstream direction(s)		*/
	       *Currentadj,	/* adjective(s) for current(s)		*/
	       *Waterrefs,	/* water refs for parse_command		*/
		Below,		/* the place to sink stuff		*/
		Above,		/* the place to bob up			*/
		Move_direction;	/* direction player wants to move	*/
static int     *Currentstr,	/* downstream current strength(s)	*/
		Depth,		/* water depth (in cm)			*/
		Rock_density;	/* many rocks here?			*/



/* for mapping abbreviations into full directions, default
 * current adjectives and fatigue calculations.
 * don't want a copy of these in every room.
 */
private static mapping	Dir_substitute;
private static string  *Current_adjectives;
private static int     *Fatigue_swim;
private static int	Nfatigue;
private static int     *Min_swim_skill;
private static string  *Fatigue_states;
private static string  *Mods;
private static int	Fatigue_size;
private static int	Mods_size;

/* prototypes */
public void	create_water_room();
nomask void	create_gondor();
public void	do_sanity_checks();
public void	init();
public void	enter_inv(object ob, object from);
public void	leave_inv(object ob, object to);
public int	unq_move(string arg);
public float	float_alarm(int str);
public void	float_downstream(object ob);
public void	float_here(object ob);
public void	sink(object ob, int silent);
public string	room_in_dir(string dir);
public int	check_efunc(string dir);
public int	swim_float_fatigue(int skill, string dir, int type, object pl);
public void	fatigue_message(object pl);
public int	take_damage(object tp, int str);
public int	do_swim(string arg);
public int	do_swim_func(string arg, int type);
public int	do_dive(string arg);
public int	do_float(string arg);
public int	query_min_swim_skill(int str);
public varargs int	add_exit(string place, string cmd, mixed efunc,
				 mixed tired, mixed non_obvious);
public void	msgs_before_move(string vb, string dir);
public string	scenery_msgs(object ob, string vb, string dir);
public void	msgs_after_move(object tp, string vb, string pcpl,
						int change_state);
public int	no_track(string arg);
public int	check_hit_rock(object ob);
public int	rock_damage(object pl, int str);
public int	check_capsize(object ob);
public int	check_panic(object tp, int str);
public void	panic_nazgul(object naz);
public int	current_too_strong(object tp, int sk, int str, string verb,
				   string dir);
public int	warn_swimmer(object tp, int sk);
public int	warn_boat(object tp, int sk, int maxstr, object boat);
public void	set_watertype(string type);
public void	set_upstreamdir(mixed dir);
public void	set_downstreamdir(mixed dir);
public void	set_currentadj(mixed adj);
public void	set_currentstr(mixed str);
public void	set_waterrefs(mixed refs);
public void	set_depth(int depth);
public void	set_rock_density(int rocks);
public string	query_watertype();
public string	*query_upstreamdir();
public string	*query_downstreamdir();
public string	*query_currentadj();
public int	*query_currentstr();
public string	*query_waterrefs();
public string	query_below();
public string	query_above();
public int	query_depth();
public int	query_rock_density();
public string	expand_dir(string dir);
public string	query_move_direction();


/*
 * Function name:	create_water_room
 * Description	:	creator for water rooms
 * Configure your room here.
 */
public void
create_water_room()
{
} /* create_water_room */

/*
 * Function name:	create_gondor
 * Description	:	gondor room creator
 */
nomask void
create_gondor()
{
    int		s;
    string	desc;

    set_noshow_obvious(1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_HIDE, 25);

    /* XXX might be able to relax this after i do some thinking
     * and testing.  new steed does have skills & fatigue.
     */
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_M_DA_DRAGONSTEED_NO_LAND, 1);

    /* it's too hard to make combat-while-swimming realistic.
     * some weapons -- knives, for example -- would work fine,
     * but a giant two-handed club would be doubtful. you can't
     * really prevent wielding, either -- can circumvent any
     * add_action by just putting your halberd in a pack when entering
     * the water, then removing and wielding.  i'd have to deal
     * with combat specials, too.  how do you charge? or
     * do a jumping kick? sooooo -- no combat.
     */
    add_prop(ROOM_M_NO_MAGIC_ATTACK,
	"That's too difficult in this aquatic environment.\n");
    add_prop(ROOM_M_NO_ATTACK, 
	"That's too difficult in this aquatic environment.\n");

    /* and if you can't attack someone who's just stolen from you,
     * then they shouldn't have been able to steal.
     */
    add_prop(ROOM_M_NO_STEAL, 
	"That's too difficult in this aquatic environment.\n");

    /* it's highly unlikely that you can cast spells while swimming */
    add_prop(ROOM_M_NO_MAGIC,
	"That's too difficult in this aquatic environment.\n");

    Dir_substitute = ([
	"n"  : "north", "s"  : "south", "w"  : "west", "e"  : "east",
	"u"  : "up", "d"  : "down", "sw" : "southwest",
	"se" : "southeast", "nw" : "northwest", "ne" : "northeast",
    ]);

    Current_adjectives = ({
	"still", "slight", "gentle", "moderate", "brisk", "strong",
	"rapid", "rough", "wild", "torrential", "ferocious", 
    });

    Fatigue_swim = ({
	40, 30, 20, 15, 12, 10, 8, 6, 5
    });
    Nfatigue = sizeof(Fatigue_swim) - 1;

    Min_swim_skill = ({
	10, /* skill */
	15, /* slight */
	15, /* gentle */
	20, /* moderate */
	20, /* brisk */
	30, /* strong */
	30, /* rapid */
	40, /* rough */
	50, /* wild */
	70, /* torrential */
	1000 /* ferocious */
    });

    Fatigue_states = SD_FATIGUE;
    Mods = SD_STAT_DENOM;
    Fatigue_size = sizeof(Fatigue_states);
    Mods_size = sizeof(Mods);

    Upstreamdir = ({});
    Downstreamdir = ({});
    Currentadj = ({});
    Waterrefs = ({});
    Currentstr = ({});

    create_water_room();
    do_sanity_checks();


} /* create_gondor */


/*
 * Function name:	do_sanity_checks
 * Description	:	do what we can to ensure this room makes sense
 */
public void
do_sanity_checks()
{
    int		i, j, s1, s2, max;

    if (Depth <= 0)
    {
	Depth = DEFAULT_DEPTH;
    }

    /* shallow water can only have current str < ROUGH_CURRENT */
    if (Depth <= MIN_SWIM_DEPTH)
    {
	max = ROUGH_CURRENT - 1;
    }
    else
    {
	max = MAX_CURRENT;
    }

    /* Currentstr and Downstreamdir must exist and be same size */
    s1 = sizeof(Currentstr);
    s2 = sizeof(Downstreamdir);
    if (!s1 ||
	!s2)
    {
	Currentstr = ({ MIN_CURRENT });
	Downstreamdir = ({ "here" });
	s1 = s2 = 1;
    }
    else if (s1 < s2)
    {
	/* fewer strengths than directions
	 * fake it -- repeat last strength
	 */
	for (j = Currentstr[s1-1], i = s1; i < s2; ++i)
	{
	    Currentstr += ({ j });
	}
	s1 = s2;
    }
    else if (s2 < s1)
    {
	/* fewer directions than strengths. can't fake this one,
	 * so remove extra strengths
	 */
	Currentstr = Currentstr[0..(s2-1)];
	s1 = s2;
    }

    /* want MIN_CURRENT <= Currentstr <= max
     * and each current needs an adjective
     */
    if (!(s2 = sizeof(Currentadj)))
    {
	Currentadj = allocate(s1);
    }
    else if (s2 < s1)
    {
	Currentadj += allocate(s1-s2);
    }
    for (i = 0; i < s1; ++i)
    {
	Currentstr[i] = CHECK_RANGE(Currentstr[i], MIN_CURRENT, max);
	if (!strlen(Currentadj[i]))
	{
	    Currentadj[i] = Current_adjectives[Currentstr[i]];
	}
    }

    if (!sizeof(Upstreamdir) &&
	sizeof(Downstreamdir))
    {
	switch( Downstreamdir[0] )
	{
	case "north":		Upstreamdir = ({ "south" }); break;
	case "south":		Upstreamdir = ({ "north" }); break;
	case "east":		Upstreamdir = ({ "west" }); break;
	case "west":		Upstreamdir = ({ "east" }); break;
	case "northeast":	Upstreamdir = ({ "southwest" }); break;
	case "northwest":	Upstreamdir = ({ "southeast" }); break;
	case "southeast":	Upstreamdir = ({ "northwest" }); break;
	case "southwest":	Upstreamdir = ({ "northeast" }); break;
	}
    }

    if (!sizeof(Waterrefs))
    {
	Waterrefs = ({ "water", Watertype });
    }
    if (!sizeof(query_drink_from()))
    {
	set_drink_from(Waterrefs);
    }

} /* do_sanity_checks */


/* Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    init_drink();
    add_action(do_swim, "swim");
    add_action(do_swim, "tread");	/* "tread water" */
    add_action(do_dive, "dive");
    add_action(do_float, "float");
    add_action(no_track, "track");
} /* init */


/*
 * Function name:	enter_inv
 * Description	:	set alarms to float/sink objects
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    int		type;	/* WATER_MOVE_SWIM, FLOAT or WADE */


    ::enter_inv(ob, from);

    if (!objectp(ob) ||
	(!ob->query_prop(OBJ_I_SINK) &&
	 ob->query_prop(OBJ_I_NO_WASH)))
    {
	return;
    }

    /*
     * ok ... lots to do here:
     *    if it's a living object:
     *       check if entering ob hits rock.  do the you-hit msgs
     *          now, so they appear mid-move.
     *       if it's a nazgul, set an alarm to panic 'em.  the
     *		panic_nazgul routine will take care of setting
     *		a float_downstream alarm if needed.
     *       otherwise, if there's a current, set an alarm to float
     *          'em downstream
     *       if no current, set an alarm to incur fatigue for floating
     *		in place
     *    else if it's a boat:
     *	     check whether it hits a rock.
     *		do msgs now.
     *       check whether it capsizes in rough water.
     *		do msgs now.
     *       if there's a current, set an alarm to float it downstream
     *    else (some non-living non-boat ob)
     *       if it doesn't float, set an alarm to sink it.
     *       else if there's a current, set an alarm to float it downstream
     *    (corpses get special checks re msgs ... see comments below)
     */
    if (living(ob))
    {
	type = ob->query_prop(OBJ_I_WATER_MOVE);
	if (!type)
	{
	    type = ((query_depth() > MAX_WADE_DEPTH) ?	WATER_MOVE_SWIM :
							WATER_MOVE_WADE);
	}
	if (type != WATER_MOVE_WADE)
	{
	    if (check_hit_rock(ob) &&
		ob->query_ghost())
	    {
		/* they died of hitting the rock */
		return;
	    }
	}

	if (NAZGUL(ob))
	{
	    /* nazgul really don't like water */
	    ob->add_prop(OBJ_I_WATER_ALARM,
        	set_alarm(1.0, 0.0, &panic_nazgul(ob)));
	}
	else if (type != WATER_MOVE_WADE)
	{
	    if (Currentstr[0])	/* float 'em downstream */
	    {
		DBG(ob, "DBG: setting alarm to float you downstream in "+
		    ftoi(float_alarm(Currentstr[0]))+" seconds.\n");
		ob->add_prop(OBJ_I_WATER_ALARM,
		    set_alarm(float_alarm(Currentstr[0]), 0.0,
	        	&float_downstream(ob)));
	    }
	    else /* incur fatigue */
	    {
		ob->add_prop(OBJ_I_WATER_ALARM,
        	    set_alarm(float_alarm(0), 0.0, &float_here(ob)));
	    }
	}
    }
    else if (IS_BOAT(ob) &&
	     !ob->query_prop(OBJ_I_SINK))
    {
	if (check_hit_rock(ob))
	{
	    if (!objectp(ob))
	    {
		/* boat broke apart on rock */
		return;
	    }
	}
	if (check_capsize(ob))
	{
	    ob->set_capsized(1);
	}
	if (Currentstr[0] &&
	    !ob->query_prop(OBJ_I_NO_WASH))
	{
	    /* float it downstream */
	    ob->add_prop(OBJ_I_WATER_ALARM,
		set_alarm(float_alarm(Currentstr[0]), 0.0,
	            &float_downstream(ob)));
	}
    }
    else if (objectp(from) ||
	     MASTER_OB(ob) != "/std/corpse")
    {
	if (strlen(Below) &&
	    !DOES_FLOAT(ob))
	{
	    /* non-living obj, can't float -- sink it */
	    ob->add_prop(OBJ_I_WATER_ALARM,
		set_alarm(SINK_ALARM(Currentstr[0]), 0.0, &sink(ob, 0)));
	}
	else if (Currentstr[0] > MIN_CURRENT &&
		 !ob->query_prop(OBJ_I_NO_WASH))
	{
	    /* float non-living obj downstream */
	    ob->add_prop(OBJ_I_WATER_ALARM,
		set_alarm(float_alarm(Currentstr[0]), 0.0, 
		    &float_downstream(ob)));
	}
    }
    else
    {
	/* is a just-created corpse.  we have already said that the
	 * dying player sank beneath the water, so if the corpse sinks,
	 * it should do so silently.  if it floats, then we need
	 * to say something about it appearing.
	 */
	if (strlen(Below) &&
	    !DOES_FLOAT(ob))
	{
	    ob->add_prop(OBJ_I_WATER_ALARM,
		set_alarm(SINK_ALARM(Currentstr[0]), 0.0, &sink(ob, 1)));
	}
	else
	{
	    tell_room(TO, "A corpse bobs to the surface.\n");
	}
    }
} /* enter_inv */


/* 
 * Function name:	leave_inv
 * Description	:	remove any outstanding alarms & props
 * Arguments	:	object ob -- the object that leaves
 *			object to -- where it is going
 */
public void
leave_inv(object ob, object to)
{
    int		tmp;

    if ((tmp = ob->query_prop(OBJ_I_WATER_ALARM)))
    {
	remove_alarm(tmp);
	ob->remove_prop(OBJ_I_WATER_ALARM);
    }
    ob->remove_prop(OBJ_I_SWAM_HERE);
    ob->remove_prop(LIVE_I_FLOAT_DIR);
    ::leave_inv(ob, to);
    if (living(ob) &&
	(tmp = ENV(ob)->query_prop(ROOM_I_TYPE)) != ROOM_IN_WATER &&
	tmp != ROOM_UNDER_WATER)
    {
	ob->remove_prop(OBJ_I_WATER_MOVE);
    }
} /* leave_inv */


/*
 * Function name:	unq_move
 * Description	:	make "south" behave like "swim south", etc
 * Arguments	:	string arg - whatever the player typed (not used)
 * Returns	:	1 on success, 0 on failure
 */
public int
unq_move(string arg)
{
    string	vb = QVB;
    if (vb != "down")
    {
	return do_swim(vb);
    }
    return do_dive("");
} /* unq_move */



/*
 * Function name:	float_alarm
 * Description	:	compute the delay between object entering and
 *			floating downstream. the stronger the current,
 *			the smaller the delay
 * Arguments	:	int str -- current str
 * Returns	:	float -- the delay
 * XXX can we do something cheaper? a table, maybe?
 */
public float
float_alarm(int str)
{
    if (str > 0)
    {
	return itof(100 / str);
    }
    return 100.0;
} /* float_alarm */


/*
 * Function name:	float_downstream
 * Description	:	currents moves an object downstream
 * Arguments	:	object ob -- the object to move
 */
public void
float_downstream(object ob)
{
    int		i, s,		/* tmp ints */
		fatigue,	/* fatigue of floating downstream */
		str,		/* current strength */
		changestate;	/* in destination room, float becomes */
				/* wade, or vice versa		     */
    string	room,		/* destination room name */
		dir,		/* direction to float */
		participle;	/* to pass to msgs_after_move */
    object	tp,		/* remember this_player */
		roomob,		/* destination room */
		inside_boat;	/* inside room for boat ob */

    if (!objectp(ob) ||
	ENV(ob) != TO)
    {
	return;
    }

    if (ob->query_prop(OBJ_I_SWAM_HERE))
    {
        /* player did "swim here" or "row here";
	 * fatigue was incurred when did command.
	 */
        ob->remove_prop(OBJ_I_SWAM_HERE);
	if (!ob->query_prop(OBJ_I_NO_WASH))
	{
            ob->add_prop(OBJ_I_WATER_ALARM,
        	set_alarm(float_alarm(Currentstr[0]), 0.0,
                    &float_downstream(ob)));
	}
        return;
    }

    /* ok, gonna float downstream ... determine direction */
    ob->remove_prop(OBJ_I_WATER_ALARM);
    s = sizeof(Downstreamdir);
    if ((i = ob->query_prop(LIVE_I_FLOAT_DIR)) > 0)
    {
	ob->remove_prop(LIVE_I_FLOAT_DIR);
	--i;	/* we bumped it by one when it was set */
    }
    else if (s == 1)
    {
	i = 0;
    }
    else
    {
	/* make an somewhat-random choice among the different current
	 * directions.  "somewhat" because main current gets more weight.
	 */
	i = random(s + MAIN_CURRENT_WEIGHT);
    }
    if (i >= s)
    {
	i = 0;
    }

    dir = Downstreamdir[i];
    str = Currentstr[i];
    /* does water flow somewhere? and is there a room there? */
    if (!str ||
	!strlen(room = room_in_dir(dir)))
    {
	/* can we float it in main downstream direction? */
	if (str == Currentstr[0])
	{
	    /* nope, already tried that */
	    return;
	}
	str = Currentstr[0];
	if (!str ||
	    !strlen(room = room_in_dir(0)))
	{
	    /* no main current, or no room there */
	    return;
	}
    }

    FIX_EUID;
    room->short();
    roomob = find_object(room);

    participle = "floating";
    if (living(ob))
    {
	/* need this_player() to be ob so say's work out */
	tp = this_player();
	set_this_player(ob);

	if ((i = roomob->query_depth()) > MAX_WADE_DEPTH)
	{
	    /* too deep to wade -- continue to float */
	    ob->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_FLOAT);
	}
	else if (i > 0)
	{
	    /* shallow enough to stand up, so change to wading */
	    ob->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_WADE);
	    changestate = 1;
	}
	else
	{
	    /* they're washing ashore */
	    ob->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_ASHORE);
	    changestate = 1;
	    participle = "from the "+Watertype;
	    /* dir = "ashore"; */
	}

	msgs_before_move("wash", "downstream");
	s = ob->query_skill(SS_SWIM);
	fatigue = swim_float_fatigue(s, dir, WATER_MOVE_FLOAT, ob);
	if (fatigue > 0)
	{
	    DBG(ob, "checking fatigue "+ob->query_fatigue()+
		    " against "+fatigue+" for damage\n");
	    if (ob->query_fatigue() < fatigue)
	    {
		if (take_damage(ob, str))
		{
		     /* player drowned */
		     set_this_player(tp);
		     return;
		}
	    }
	    ob->add_fatigue(-(fatigue));
	    fatigue_message(ob);
	}
	else
	{
	    /* swim_float_fatigue thought it was a bad direction. this
	     * "cannot happen". oh, well, log it and float 'em anyway.
	     */
	    ERR_LOG("float_downstream: fatigue for dir '"+dir+"' failed\n");
	}

	write(scenery_msgs(ob, "wash", "downstream"));
	ob->move_living("M", roomob);
	warn_swimmer(ob, s);
	msgs_after_move(ob, "float", participle, changestate);
	set_this_player(tp);
	return;
    }

    /* non-living */
    if (IS_BOAT(ob) &&
	!ob->query_capsized())
    {
	tell_room(TO,
	    "The current washes the "+ob->query_name()+" downstream.\n");
	inside_boat = ob->query_inside_boat();
	if (sizeof(FILTER_LIVE(all_inventory(inside_boat))))
	{
	    tell_room(inside_boat,
		"The current washes your "+
		ob->query_name()+" downstream.\n"+
		scenery_msgs(ob, "wash", "downstream"));
	}
	tell_room(roomob,
	    CAP(LANG_ADDART(ob->short()))+
	    " arrives floating in the water.\n");
	ob->move(roomob, 1);
	if (!objectp(ob))
	{
	    return; /* smashed on rocks */
	}
	if (!ob->query_capsized())
	{
	    if (roomob->query_depth() < ob->query_min_depth())
	    {
		tell_room(inside_boat,
		    "The "+ob->query_name()+" runs aground in "+
		    "the shallow water.\n");
	    }
	    else
	    {
		roomob->warn_boat(0, 0,
		    inside_boat->query_max_current(), inside_boat);
	    }
	}
	return;
    }

    /* not a boat, or else a capsized boat -- just float it downstream */
    tell_room(TO,
	"The current washes the "+ob->query_name()+" downstream.\n");
    switch( ob->num_heap() )
    {
    case 0:
        tell_room(roomob,
	    "The "+ob->short()+" arrives floating in the water.\n");
        break;
    case 1:
        tell_room(roomob,
	    CAP(ob->short())+" arrives floating in the water.\n");
        break;
    default:
        tell_room(roomob,
	    CAP(ob->short())+" arrive floating in the water.\n");
        break;
    }
    ob->move(roomob, 1);
} /* float_downstream */


/*
 * Function name:	float_here
 * Description	:	incur fatigue for floating in still water
 * Arguments	:	object ob -- the living that floats 
 */
public void
float_here(object ob)
{
    int		i, s, fatigue, hp, dmg, str;
    string	tmpstr;
    object	tp;

    if (!objectp(ob) ||
	ENV(ob) != TO)
    {
	return;
    }

    if (ob->query_prop(OBJ_I_SWAM_HERE))
    {
        /* fatigue was added when they did "swim/row here" */
        ob->remove_prop(OBJ_I_SWAM_HERE);
	if (!ob->query_prop(OBJ_I_NO_WASH))
	{
            ob->add_prop(OBJ_I_WATER_ALARM,
        	set_alarm(float_alarm(0), 0.0, &float_here(ob)));
	}
        return;
    }

    ob->remove_prop(OBJ_I_WATER_ALARM);

    /* need this_player() to be ob so say's work out */
    tp = this_player();
    set_this_player(ob);

    s = ob->query_skill(SS_SWIM);
    fatigue = swim_float_fatigue(s, "here", WATER_MOVE_FLOAT, ob);
    if (fatigue > 0)
    {
	DBG(ob, "checking fatigue "+ob->query_fatigue()+
	    " against "+fatigue+" for damage\n");
	if (ob->query_fatigue() >= fatigue)
	{
	    write("You float in the water.\n");
	    ob->add_fatigue(-(fatigue));
	    fatigue_message(ob);
	    if (!ob->query_prop(OBJ_I_NO_WASH))
	    {
		ob->add_prop(OBJ_I_WATER_ALARM,
		    set_alarm(float_alarm(0), 0.0, &float_here(ob)));
	    }
	}
	else
	{
	    take_damage(ob, str);
	}
    }
    else
    {
        /* swim_float_fatigue() thinks "here" is a bad direction.
	 * this "cannot happen".
	 */
        ERR_LOG("float_here: fatigue for dir 'here' failed\n");
    }
    set_this_player(tp);
} /* float_here */


/*
 * Function name:	sink
 * Description	:	sink a non-living object to bottom of body of water
 * Arguments	:	object ob -- the object to sink
 *			int silent -- if true, no msgs
 */
public void
sink(object ob, int silent)
{
    string oname;

    if (!objectp(ob) ||
	ENV(ob) != TO)
    {
	return;
    }
    
    ob->remove_prop(OBJ_I_WATER_ALARM);
    if (living(ob))
    {
	/* "cannot happen" */
	ERR_LOG("tried to sink living "+ob->query_real_name()+
	    " "+file_name(ob)+"\n");
	return;
    }
    if (!silent)
    {
	/* using "the "+ short() in this msg looks silly for heaps:
	 *	The a piece of ham sinks beneath the water.
	 * i could use LANG_THESHORT, but i'd still have to check
	 * num_heap() to see if it's "sink" or "sinks", so may as
	 * well just do the whole thing myself.
	 */
	switch( ob->num_heap() )
	{
	case 0:
	    tell_room(TO,
		"The "+ob->short()+" sinks beneath the water.\n");
	    break;
	case 1:
	    tell_room(TO,
		CAP(ob->short())+" sinks beneath the water.\n");
	    break;
	default:
	    tell_room(TO,
		CAP(ob->short())+" sink beneath the water.\n");
	    break;
	}
    }

    if (strlen(Below))
    {
	FIX_EUID;
	Below->short();
	ob->move(Below, 1);
	tell_room(ENV(ob),
	    CAP(LANG_ADDART(ob->short())) +
	    " drifts into view from above.\n");
    }
    else if (query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
	/* no place to sink it. this only happens if someone has
	 * done some work to make it so.  by default, there always
	 * will be a room below an onwater room.
	 */
	ob->remove_object();
    }
} /* sink */


/*
 * Function name:	room_in_dir
 * Description	:	get the name of a room in a given direction
 * Arguments	:	string dir -- the direction of interest
 * Returns	:	string room -- the name of the room
 */
public string
room_in_dir(string dir)
{
    mixed	*exit_arr;
    int		i;

    if (dir == "upstream")
    {
	dir = Upstreamdir[0];
    }
    else if (dir == "downstream")
    {
	dir = Downstreamdir[0];
    }
    exit_arr = query_exit();
    if ((i = member_array(dir, exit_arr)) > 0)
    {
	return check_call(exit_arr[i-1]);
    }
    return "";
} /* room_in_dir */


/*
 * Function name:	check_efunc
 * Description	:	call efunc to see if can take this exit
 * Arguments	:	string dir -- the direction of interest
 * Returns	:	0 if may exit, !0 if not
 *
 * N.B. unlike efuncs for normal rooms, this is *not* the place
 *      to issue "You move ..." msgs. Do that by masking
 *	msgs_before_move(), scenery_msgs() and/or msgs_after_move().
 *	this is only to check if player is permitted to move.
 */
public int
check_efunc(string dir)
{
    string	tmpstr;
    mixed	*exit_arr;
    int		i;

    if (dir == "upstream")
    {
	dir = Upstreamdir[0];
    }
    else if (dir == "downstream")
    {
	dir = Downstreamdir[0];
    }
    exit_arr = query_exit();
    if ((i = member_array(dir, exit_arr)) > 0 &&
	exit_arr[i+1])
    {
	return check_call(exit_arr[i+1]);
    }
    return 0;
} /* check_efunc */


/*
 * Function name:	swim_float_fatigue
 * Description	:	determine fatigue to swim or float in direction
 *				also called from boat to determine
 *				fatigue of rowing.
 * Arguments	:	int skill -- player's swimming (or boating) skill
 *			string dir -- the direction to swim
 *			int type -- WATER_MOVE_SWIM, WATER_MOVE_FLOAT or 
 *				    WATER_MOVE_WADE
 *			object pl -- the player
 * Returns	:	positive integer -- the fatigue to be incurred;
 *			    caller must check against player's current fatigue
 *			    and decide whether to invoke add_fatigue(),
 *			    or to fail the swim attempt.
 *			or -1 -- cannot swim in that dir
 */
public int
swim_float_fatigue(int skill, string dir, int type, object pl)
{
    string	which;		/* "upstream", "downstream" or "here" */
    int		i,		/* tmp int */
		fatigue,	/* the fatigue incurred */
		str,		/* current strength for this direction */
		panics;		/* player panics if current too strong */

    if (!strlen(dir))
    {
	return -1;
    }

    if (type != WATER_MOVE_FLOAT)
    {
	if (dir == "downstream")
	{
	    dir = Downstreamdir[0];
	    str = Currentstr[0];
	    which = "downstream";
	}
	else if ((i = member_array(dir, Downstreamdir)) >= 0)
	{
	    str = Currentstr[i];
	    which = "downstream";
	}
	else if (dir == "upstream")
	{
	    dir = Upstreamdir[0];
	    str = Currentstr[0];
	    which = "upstream";
	}
	else if ((i = member_array(dir, Upstreamdir)) >= 0)
	{
	    str = Currentstr[0];
	    which = "upstream";
	}
	else if (dir == "here" ||
		 strlen(room_in_dir(dir)))
	{
	    str = Currentstr[0];
	    which = "here";
	}
	else if (dir == "up")
	{
	    str = Currentstr[0];
	    which = "up";
	}
	else
	{
	    return -1;
	}

    }
    else	/* WATER_MOVE_FLOAT */
    {
	i = member_array(dir, Downstreamdir);
	if (i < 0)
	{
	    /* "cannot happen" */
	    ERR_LOG("swim_float_fatigue called from float_downstream() with "+
		"bad direction '"+dir+"'\n");
	    i = 0;	/* shrug */
	}
	str = Currentstr[i];
	which = "downstream";
    }

    if (skill < Min_swim_skill[str])
    {
	/* current is too strong for player's skills -- panic.
	 * we can't issue a you-feel-panicky msg here,
	 * because it would come too early in the you-move-dir
	 * sequence. caller will do it after move_living(),
	 * via warn_swimmer() (which also actually adds the panic).
	 * all we need do here is increase the fatigue because of panic.
	 */
	skill = Min_swim_skill[str];
	panics = 1;
    }

    /* compute index into fatigue array based on current strength and
     * swimming skill. the lower the index, the higher the fatigue.
     */
    if (str < ROUGH_CURRENT ||
	skill < LIMIT_SKILL)
    {
	i = (skill / 10) + START_INDEX - str;
    }
    else
    {
	i = LIMIT - str;
    }

    if (str > MIN_CURRENT &&
	which == "upstream")
    {
	--i;	/* upstream is harder */
    }
    else if (which == "downstream" &&
	     MODERATE_CURRENT < str &&
	     str < ROUGH_CURRENT)
    {
	++i;	/* in middle range, downstream is easier */
    }
   

    i = CHECK_RANGE(i, 0, Nfatigue);
    fatigue = Fatigue_swim[i];

    if (type == WATER_MOVE_FLOAT ||
	which == "up")
    {
	/* if we're not encumbered, floating in water or rising
	 * to surface is not as tiring as swimming or wading
	 */
	if (fatigue > 1 &&
	    pl->query_encumberance_weight() < ENCUMBERANCE)
	{
	    fatigue /= 2 ;
	}
    }
    else if (pl->query_encumberance_weight() > ENCUMBERANCE)
    {
	/* swimming while encumbered is very tiring */
	fatigue *= 2;
    }

    if (panics ||
	NAZGUL(pl))
    {
	/* panic'd players tire much more quickly */
	DBG(pl, "panic ... increasing base fatigue of "+fatigue+"\n");
	fatigue = PANIC_FATIGUE(fatigue);
    }

    /* wading thru deep water is more tiring than swimming */
    if (type == WATER_MOVE_WADE &&
	Depth > MIN_SWIM_DEPTH)
    {
	fatigue += (fatigue / 2);
    }

    DBG(pl, "skill "+skill+" str "+str+" "+
	which+" i "+i+" fatigue "+fatigue+"\n");

    return fatigue;
} /* swim_float_fatigue */


/*
 * Function name:	fatigue_message
 * Description	:	warn player if getting tired
 * Arguments	:	object pl -- the player
 */
public void
fatigue_message(object pl)
{
    int		fat, max, i, j, k, l;

    /* swiped from cmd/live/state.c */
    max = pl->query_max_fatigue();
    fat = pl->query_fatigue();
    j = max - fat;
    k = 100 * j / (max ? max : j);
    k = CHECK_RANGE(k, 0, 99);
    i = Fatigue_size * k / 100;    
    if (!i)
    {
	/* still alert */
	return;
    }
    l = k - (i * 100 / Fatigue_size);
    j = (Mods_size * l * Fatigue_size) / 100;
    if (i < 1)
    {
	j = (Mods_size - 1) - j;
    }
    tell_object(pl, "You are "+Mods[j]+Fatigue_states[i]+".\n");
}/* fatigue_message */


/*
 * Function name:	take_damage
 * Description	:	player is exhausted -- starts swallowing water
 * Arguments	:	object tp -- player
 *			int str -- current str for dir that tried to swim
 * Returns	:	1 if player drowns, 0 if not
 */
public int
take_damage(object tp, int str)
{
    int		dmg,
		hp = tp->query_max_hp(),
		i;
    string	tmpstr = "";

    dmg = CURRENT_DAMAGE(str, hp);
    if (NAZGUL(tp) ||
	check_panic(tp, str))
    {
        DBG(tp, "panic attack -- hp "+tp->query_hp()+
	    " max hp "+hp+" orig dmg "+dmg+"\n");
        tp->add_panic(PANIC_AMOUNT);
        dmg *= 2;
	switch(tp->query_panic())
	{
	case 100..1000:
	    tmpstr = "You are filled with terror as y";
	    break;
	case 50..99:
	    tmpstr = "You feel quite panicky as y";
	    break;
	default:
            tmpstr = "You feel a bit panicky as y";
	    break;
	}
    }
    else
    {
        tmpstr = "Y";
    }

    /* these msgs must make sense on and under water */
    i = random(4);
    write(tmpstr + ({
        "ou swallow water and choke!\n",
        "our lungs burn from your attempts to breathe water.\n",
        "ou gag from swallowing water.\n",
        "ou cough and sputter in the water!\n",
         })[i] );
    /* not silent -- no need for SAYBB */
    SAY( ({
        " swallows water and chokes!\n",
        " appears to be trying to breathe water.\n",
        " gags from swallowing water.\n",
        " coughs and sputters in the water!\n",
         })[i] );

    tp->reduce_hit_point(dmg);
    DBG(tp, "damage "+dmg+" hp left "+tp->query_hp()+"\n");
    if (tp->query_hp() <= 0)
    {
	write("You drown in the "+Watertype+".\n");
	if (query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
	{
	    SAY(" struggles desperately to remain afloat, but "+
		"sinks beneath the water and drowns.");
	}
	else
	{
	    SAY(" struggles desperately for air, but "+
		"swallows water and drowns.");
	}
	INFO_LOG(tp->query_real_name()+" ("+tp->query_average_stat()+
	    ") drowned.\n");
	tp->do_die(TO);
	return 1;
    }
    return 0;
} /* take_damage */


/*
 * Function name:	do_swim
 * Description	:	handle player's swim/tread cmd
 * Argument	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 * calls do_swim_func() so that onwater rooms can mask do_swim()
 * 	to specify WATER_MOVE_SWIM or WATER_MOVE_WADE
 */
public int
do_swim(string arg)
{
    return do_swim_func(arg, WATER_MOVE_SWIM);
} /* do_swim */


/*
 * Function name:	do_swim_func
 * Description	:	handle player's "swim" cmd
 * Argument	:	string arg -- whatever the player typed
 *			int type -- WATER_MOVE_SWIM or WATER_MOVE_WADE
 * Returns	:	1 on success, 0 on failure
 */
public int
do_swim_func(string arg, int type)
{
    object	tp = TP,	/* this_player */
		roomob,		/* destination room */
		*weapons;	/* what player is wielding */
    string	room,		/* destination room name */
		tmpstr,		/* junk */
		verb,		/* "swim" or "wade" */
		participle;	/* "swimming" or "wading" */
    int		fatigue_cost,	/* fatigue cost of cmd */
		downstream,	/* true if heading downstream */
		hp,		/* player's hp */
		sk,		/* player's swim skill */
		str,		/* current strength */
		i,		/* index */
		changestate,	/* true if swim will change to wade,  */
				/* or vice versa, in destination room */
		roomtype;	/* ROOM_I_TYPE */


    if (sizeof(weapons = tp->query_weapon(-1)) &&
	type != WATER_MOVE_WADE)
    {
	NFN0("It is too difficult to move around in the water "+
	     "while wielding the "+COMPOSITE_WORDS(weapons->short())+".");
    }

    if (QVB == "tread")
    {
	if (arg != "water")
	{
	    NF0("Tread water, perhaps?\n");
	}
	arg = "here";
    }
    else if (!strlen(arg) ||
             parse_command(LOW(arg), ({}), "[in] [the] %p", Waterrefs))
    {
	arg = "here";
    }
    else if (strlen(tmpstr = Dir_substitute[arg]))
    {
	/* expand "ne" to "northeast", etc */
	arg = tmpstr;
    }

    Move_direction = arg;
    sk = tp->query_skill(SS_SWIM);
    /* get fatigue for player 'tp' of skill 'sk' moving 'arg' direction
     * by 'type' movement (SWIM or WADE)
     */
    fatigue_cost = swim_float_fatigue(sk, arg, type, tp);

    if (arg == "here" &&
	type == WATER_MOVE_WADE)
    {
	/* nothing much to do for wading */
	if (fatigue_cost > 0)
	{
	    tp->add_fatigue(-fatigue_cost);
	}
	write("You wade in place.\n");
	return 1;
    }


    if (type == WATER_MOVE_SWIM)
    {
	verb = "swim";
	participle = "swimming";
    }
    else
    {
	verb = "wade";
	participle = "wading";
    }

    if (fatigue_cost < 0)
    {
	/* bad direction */
	NF0("You cannot "+verb+" "+arg+".\n");
    }

    if (arg != "here" &&
	!strlen(room = room_in_dir(arg)))
    {
	/* someone set an upstream or downstream direction,
	 * but did not add a corresponding exit.  tsk tsk.
	 */
	ERR_LOG("no room for dir '"+arg+"'\n");
	NF0("You cannot "+verb+" "+arg+".\n");
    }

    if ((i = member_array(arg, Downstreamdir)) >= 0)
    {
	/* use current strength for this particular downstream direction */
	str = Currentstr[i];
	downstream = 1;
    }
    else
    {
	/* use main current strength */
	str = Currentstr[0];
    }

    DBG(tp, "checking fatigue "+tp->query_fatigue()+
	" against "+fatigue_cost+" for damage\n");
    if (fatigue_cost > tp->query_fatigue())
    {
	/* oops, too tired to move.  take damage (possibly die) */
	//WRITE("You try to "+verb+" "+arg+
	//    ", but the effort is too much for you.");
    write("You try to "+verb+" "+arg+
        ", but the effort is too much for you.\n");
	/* there is some fatigue involved in making the attempt */
	tp->add_fatigue(-(fatigue_cost / 4));
	if (type != WATER_MOVE_WADE)
	{
	    take_damage(tp, str);
	}
	return 1;
    }

    /* destination is good and they're not too fatigued.  however,
     * the efunc from add_exit or current_too_strong() may still block
     * the move.  in any case, tho, player acquires fatigue, since
     * s/he has tried to swim. that will be tiring whether or not
     * it succeeds.
     */

    if (check_efunc(arg))
    {
	/* add_exit() efunc says no. if it didn't kill them, 
	 * incur fatigue and do any "You are tired" msgs
	 */
	if (!tp->query_ghost())
	{
	    tp->add_fatigue(-(fatigue_cost));
	    fatigue_message(tp);
	}
	return 1;
    }


    /* if trying to swim across or against the current, and it is too
     * strong for the player's swimming skill, give room a chance
     * to do something.
     */
    if (!downstream &&
	sk < Min_swim_skill[str] &&
        current_too_strong(tp, sk, str, verb, arg))
    {
	/* nope, current too strong for them. if it didn't kill them, 
	 * incur fatigue and do any "You are tired" msgs
	 */
	if (!tp->query_ghost())
	{
	    tp->add_fatigue(-(fatigue_cost));
	    fatigue_message(tp);
	}
	return 1;
    }


    if (arg == "here")
    {
	/* set prop so next float-away alarm ignores this player.
	 * add fatigue and do any "you feel tired" warnings.
	 */
	tp->add_prop(OBJ_I_SWAM_HERE, 1);
	msgs_before_move("swim", "here");
	tp->add_fatigue(-(fatigue_cost));
	fatigue_message(tp);
	return 1;
    }

    FIX_EUID;
    room->short();
    roomob = find_object(room);
    roomtype = roomob->query_prop(ROOM_I_TYPE);

    /* if we are going to change the move type when they arrive (stand up
     * when they swam, or start swimming when they waded), we must change
     * it before moving the player to prevent unnecessary alarms to
     * float em downstream from being set. also, msgs_before_move() needs 
     * to know if player is going ashore.
     */
    if (roomtype == ROOM_IN_WATER ||
	roomtype == ROOM_UNDER_WATER)
    {
	if (type == WATER_MOVE_SWIM)
	{
	    if (roomob->query_depth() <= MAX_WADE_DEPTH)
	    {
		changestate = 1;
		type = WATER_MOVE_WADE;
	    }
	}
	else if (roomob->query_depth() > MAX_WADE_DEPTH) 
	{
	    /* type == WATER_MOVE_WADE */
	    changestate = 1;
	    type = WATER_MOVE_SWIM;
	}
    }
    else
    {
	changestate = 1;
	type = WATER_MOVE_ASHORE;
	participle = "from the "+Watertype;
    }

    /* ok, they can swim/wade there. do msgs & fatigue and move them.  */
    msgs_before_move(verb, arg);
    tp->add_fatigue(-(fatigue_cost));
    fatigue_message(tp);
    tp->add_prop(OBJ_I_WATER_MOVE, type);
    write(scenery_msgs(tp, verb, arg));
    if (QVB == "swim")
    {
	set_dircmd(arg);
    }
    tp->move_living("M", roomob);
    warn_swimmer(tp, sk);
    msgs_after_move(tp, verb, participle, changestate);

    return 1;
} /* do_swim_func */



/*
 * Function name:	do_dive
 * Description	:	respond to attempts to dive
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 */
public int
do_dive(string arg)
{
    object	tp = TP,
		*weapons;	/* what player is wielding */
    int		fatigue_cost,
		sk;
    string	tmpstr;

    if (strlen(arg) &&
	arg != "down" &&
        !parse_command(LOW(arg), ({}), "[in] / [into] [the] %p", Waterrefs))
    {
	NF0("Dive where?\n");
    }

    if (Depth <= MAX_WADE_DEPTH)
    {
	NF0("The water is not deep enough to dive here.\n");
    }

    if (sizeof(weapons = tp->query_weapon(-1)))
    {
	NFN0("It is too difficult to dive "+
	     "while wielding the "+COMPOSITE_WORDS(weapons->short())+".");
    }


    if (!strlen(Below))
    {
	if (query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
	{
	    WRITE("You dive beneath the water for a moment, "+
		"then return to the surface.");
	    SAYBB(" dives beneath the water for a moment, "+
		"then return to the surface.");
	}
	else	/* they're underwater */
	{
    	    write("You cannot dive further.\n");
	}
	return 1;
    } 

    sk = tp->query_skill(SS_SWIM);
    fatigue_cost = swim_float_fatigue(sk, "here", WATER_MOVE_SWIM, tp);

    if (fatigue_cost > 0)
    {
	DBG(tp, "checking fatigue "+tp->query_fatigue()+
	    " against "+fatigue_cost+" for damage\n");
	if (fatigue_cost > tp->query_fatigue())
	{
	    WRITE("You try to dive, but the effort is too much for you.");
	    /* there is some fatigue involved in making the attempt */
	    tp->add_fatigue(-(fatigue_cost / 4));
	    take_damage(tp, Currentstr[0]);
	    return 1;
	}
    }

    /* whether or not the move succeeds, they incur the fatigue
     * since they've made the attempt to dive. however, i think
     * it looks better to do the fatigue warnings after the
     * efun/too_strong checks.
     */
    tp->add_fatigue(-(fatigue_cost));
    if (check_efunc("down"))
    {
	fatigue_message(tp);
	return 1;
    }
    if (sk < Min_swim_skill[Currentstr[0]] &&
        current_too_strong(tp, sk, Currentstr[0], "dive", "down"))
    {
	fatigue_message(tp);
	return 1;
    }

    tp->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_SWIM);
    msgs_before_move("dive", "down");
    set_dircmd("water");
    fatigue_message(tp);
    write(scenery_msgs(tp, "dive", "down"));
    tp->move_living("M", Below);
    warn_swimmer(tp, sk);
    msgs_after_move(tp, "dive", "diving", 0);
    return 1;
} /* do_dive */


/*
 * Function name:	do_float
 * Description	:	handle player's attempts to float
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 * you have to wait for the current to move you if you float. if
 * you want it to happen immediately, you have to swim
 */
public int
do_float(string arg)
{
    string	tmpstr;
    int		i;
    object	tp = TP;

    if (Depth < MIN_SWIM_DEPTH)
    {
	NF0("The water is too shallow for floating.\n");
    }

    if (!strlen(arg) ||
	arg == "here" ||
        parse_command(LOW(arg), ({}), "[in] [the] %p", Waterrefs))
    {
	/* not going in any particular direction */
	write("You float in the water.\n");
    }
    else if (Currentstr[0] <= MIN_CURRENT)
    {
	/* no current to move player */
	WRITE("You float in the water. The "+Currentadj[0]+
	   " water does not move you in any particular direction.");
    }
    else
    {
    	/* there is current, and player is trying to go in a 
	 * particular direction
	 */
	if (strlen(tmpstr = Dir_substitute[arg]))
	{
	    arg = tmpstr;
	}
	if (arg == "upstream" ||
	    member_array(arg, Upstreamdir) >= 0)
	{
	    NF0("You cannot float "+arg+" against the current.\n");
	}
	if (arg == "downstream")
	{
	    arg = Downstreamdir[0];
	    i = 0;
	}
	else if ((i = member_array(arg, Downstreamdir)) < 0)
	{
	    NF0("You cannot float "+arg+" across the current.\n");
	}

	WRITE("You try to orient yourself toward the "+arg+
	    " as you float in the "+Watertype+".");

	/* add 1 to direction index so we can tell it's been set */
	tp->add_prop(LIVE_I_FLOAT_DIR, (i+1));
    }

    tp->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_FLOAT);
    if (Currentstr[0] &&
	!tp->query_prop(OBJ_I_NO_WASH) &&
	!tp->query_prop(OBJ_I_WATER_ALARM))
    {
	/* there's a current, and players changed from standing to
	 * floating ... set alarm to float 'em downstream 
	 */
	tp->add_prop(OBJ_I_WATER_ALARM,
	    set_alarm(float_alarm(Currentstr[0]), 0.0,
		&float_downstream(tp)));
    }
    return 1;
} /* do_float */


/*
 * Function name:	query_min_swim_skill
 * Description	:	determine min swim skill for given current
 * Arguments	:	int str -- the current strength
 *				   if is negative, main current is used.
 * Returns	:	int -- skill required
 * 
 */
public int
query_min_swim_skill(int str)
{
    if (str < 0)
    {
	str = Currentstr[0];
    }
    else
    {
	str = CHECK_RANGE(str, MIN_CURRENT, MAX_CURRENT);
    }
    return Min_swim_skill[str];
} /* query_min_swim_skill */


/*
 * Function name:	add_exit
 * Description	:	mask parent to set Below if have down exit,
 *			and Above if have up exit.
 * Arguments	:	string place: The filename of the room to move to
 *                	string cmd:   The command given to move
 *                	mixed efunc: The delay value often given by VBFC.
 *		  	mixed tired: How much more tired the player should 
 *				     become
 *                	mixed non_obvious: When true, player will not see 
 *					   this exit.
 * Returns	:	1 if added exit, 0 otherwise
 */
public varargs int
add_exit(string place, string cmd, mixed efunc, mixed tired,
	 mixed non_obvious)
{
    mixed	*exit_arr;
    int		i, rval;

    rval = ::add_exit(place, cmd, efunc, tired, non_obvious);
    if (rval)
    {
	if (cmd == "down")
	{
	    /* can't just use 'place' because we want full pathname */
	    exit_arr = query_exit();
	    /* checking i is redundant, but what the heck */
	    if ((i = member_array("down", exit_arr)) > 0)
	    {
	        Below = exit_arr[i-1];
	    }
	}
	else if (cmd == "up")
	{
	    /* can't just use 'place' because we want full pathname */
	    exit_arr = query_exit();
	    /* checking i is redundant, but what the heck */
	    if ((i = member_array("up", exit_arr)) > 0)
	    {
	        Above = exit_arr[i-1];
	    }
	}
    }
    return rval;
} /* add_exit */


/*
 * Function name:	msgs_before_move
 * Description	:	write and say msgs before player swims/wades/dives
 * Arguments	:	string vb -- "wash", "swim", "wade", "dive"
 *			string dir -- the direction of movement
 */
public void
msgs_before_move(string vb, string dir)
{
    int ashore = (TP->query_prop(OBJ_I_WATER_MOVE) == WATER_MOVE_ASHORE);
    if (vb == "wash")
    {
	if (!ashore)
	{
	    WRITE("The current washes you "+dir+".");
	    SAYBB(" is washed "+dir+" by the current.");
	}
	else
	{
	    WRITE("The current washes you ashore.");
	    SAYBB(" is washed ashore by the current.");
	}
	return;
    }

    if (vb == "dive")
    {
	if (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
	{
	    dir = "deeper into the "+Watertype;
	}
	else
	{
	    dir = "into the "+Watertype;
	}
    }
    else if (member_array(dir, Upstreamdir) >= 0)
    {
	dir += " against the "+Currentadj[0]+" current";
    }
    else if (dir == "here")
    {
	if (Currentstr[0] > MIN_CURRENT)
	{
	    dir = "in place against the "+Currentadj[0]+" current";
	}
	else
	{
	    dir = "in place";
	}
    }
    else if (ashore)
    {
	dir += " towards the shore";
    }

    write("You "+vb+" "+dir+".\n");
    SAYBB(" "+vb+"s "+dir+".");
    if (ashore)
    {
	write("You climb out of the "+Watertype+".\n");
    }
} /* msgs_before_move */


/*
 * Function name:	scenery_msgs
 * Description	:	return any msgs about the passing scenery (e.g.,
 *			("After short calm stretch, the river bends south
 *			  and begins to flow more swiftly.").  This is
 *			called after the "you swim/float/are washed/row"
 *			msgs and before the player/boat are moved
 *			to the new room.
 * Arguments	:	object ob -- the object that moved
 *			string vb -- "wash", "swim", "wade", "dive", "row"
 *			string dir -- the direction of movement
 * Returns	:	string -- the msg
 *
 * N.B. return the message, don't write it, because if this_player is
 *      in a boat we want all passengers to see the msg, not just
 *	the player who rowed.
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    return "";
} /* scenery_msgs */

/*
 * Function name:	msgs_after_move
 * Description	:	say msgs to new env after player swims/wades/dives
 * Arguments	:	object tp -- this_player
 *			string vb -- "swim", "wade", "dive"
 *			string pcpl -- participle phrase suitable for being
 *				appended to "Foo arrives " (e.g., "swimming")
 *				(no trailing period)
 *			int change_state -- if nonzero, swimmer will
 *				stand up or wader will swim
 *
 * we have to explicitly set and restore this_player here or
 * when teams move, you will see some team member enter twice
 * and will not see the team leader enter at all.
 */
public void
msgs_after_move(object tp, string vb, string pcpl, int change_state)
{
    string	wtype,
    		m_in;
    object	save_tp;
    int		len;

    save_tp = TP;
    set_this_player(tp);

    m_in = tp->query_m_in();
    SAYBB(" " + m_in + " " + pcpl + ".");

    if (change_state)
    {
	switch (tp->query_prop(OBJ_I_WATER_MOVE))
	{
	case WATER_MOVE_WADE:
	    wtype = ENV(tp)->query_watertype();
	    if (!strlen(wtype))
	    {
		wtype = "water";
	    }
	    write("Your feet find firm bottom and you stand up in the "+
	    	wtype+".\n");
	    SAYBB(" stands up in the "+wtype+".");
	    break;
	case WATER_MOVE_FLOAT:
	case WATER_MOVE_SWIM:
	    write("Your feet lift off the bottom and you begin "+
		"to swim.\n");
	    SAYBB(" begins swimming.");
	    break;
	case WATER_MOVE_ASHORE:
	    wtype = ENV(tp)->query_watertype();
	    if (!strlen(wtype))
	    {
		wtype = "water";
	    }
	    write("You emerge from the " + wtype + ".\n");
	    break;
	}
    }
    set_this_player(save_tp);
} /* msgs_after_move */

/*
 * Function name:	no_track
 * Description	:	intercept attempts to track
 * Arguments	:	string arg -- unused
 * Returns	:	1
 */
public int
no_track(string arg)
{
    write("That's too difficult in this aquatic environment.\n");
    return 1;
} /* no_track */


/*
 * Function name:	check_hit_rock
 * Description	:	decide whether a player or boat hits a rock
 * Arguments	:	object ob -- the player or boat
 * Returns	:	1 if hits rock, 0 if not
 */
public int
check_hit_rock(object ob)
{
    int		skill,
		does_hit,
		dmg;
    object	tp = TP;

    if (!Rock_density)
    {
	return 0;
    }

    if (living(ob))
    {
	skill = ob->query_skill(SS_SWIM);
    }
    else if (ob->query_prop(OBJ_I_WATER_MOVE) == WATER_MOVE_ROW)
    {
	skill = tp->query_skill(SS_BOAT_HANDL);
    }
    /* else boat is drifting -- skill == 0 */

    /* if lots of rocks and either don't have the skills to be here or
     * current >= ROUGH, have roughly 70% chance of hitting rock
     * (with a small allowance for skill).
     */
    if (Rock_density >= ROCKY &&
        (skill < Min_swim_skill[Currentstr[0]] ||
         Currentstr[0] >= ROUGH_CURRENT))
    {
	does_hit = (random(10 + (skill / 40)) < 7);
    }
    /* if more than scattered rocks and current > MODERATE, some risk
     * ... say, 1 in 3 chance if unskilled ... skill plays more of a role
     */
    else if (Currentstr[0] > MODERATE_CURRENT &&
	     Rock_density > SCATTERED_ROCKS)
    {
	does_hit = !random(3 + (skill / 20));
    }
    /* else few rocks, mild waters ... you have to be unlucky */
    else
    {
	does_hit = !random(20);
    }

    if (does_hit)
    {
	if (living(ob))
	{
	    dmg = rock_damage(ob, Currentstr[0]);
	    DBG(ob, "DBG: rock damage "+dmg+"\n");
	    if (dmg >= 50 ||
	        dmg > ob->query_hp())
	    {
		WRITE( ({
		    "You slam headfirst into a rock.",
		    "The waters dash you against a rock. You feel "+
			"bones crack with the impact.",
		    "You smash painfully onto a submerged rock.",
		    })[random(3)] );

		SAY(" slams headfirst into a rock.\n");
		ob->reduce_hit_point(dmg);
		if (ob->query_hp() <= 0)
		{
		    write(BSN("You are too stunned by the blow to keep "+
			"swimming. You drown in the "+Watertype+"."));
		    if (query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
		    {
			SAY(" appears stunned by the blow. "+
			    CAP(ob->query_pronoun())+
			    " sinks beneath the water and drowns.");
		    }
		    else
		    {
			SAY(" appears stunned by the blow. "+
			    CAP(ob->query_pronoun())+
			    " stops swimming and quickly drowns.");
		    }
		    INFO_LOG(tp->query_real_name()+" ("+
			tp->query_average_stat()+
			") hit a rock and drowned.\n");
		    tp->do_die(TO);
		}
	    }
	    else
	    {
		write("You hit a rock -- ouch!\n");
		SAY(" hits a rock.");
		ob->reduce_hit_point(dmg);
	    }
	}
	else
	{
	    /* let the boat handle it */
	    ob->hit_rock(Currentstr[0]);
	}
    }
    return does_hit;
} /* check_hit_rock */


/*
 * Function name:	rock_damage
 * Description	:	calculate damage done when hit a rock
 * Arguments	:	object pl -- the player
 *		:	int str -- current str
 * Returns	:	int -- damage (in hp) done
 */
public int
rock_damage(object pl, int str)
{
    int	maxhp;
    if (str <= MODERATE_CURRENT)
    {
	return (20 + random(20));
    }
    maxhp = pl->query_max_hp();
    if (str < ROUGH_CURRENT)
    {
	return (maxhp / 20);
    }
    return (maxhp / 10);
} /* rock_damage */


/*
 * Function name:	check_capsize
 * Description	:	if current is strong, or pilot unskilled,
 *			boat may capsize
 * Arguments	:	object ob -- the boat
 * Returns	:	1 if capsizes, 0 if not
 */
public int
check_capsize(object ob)
{
    int		max,
		str,
		does_capsize,
		skilldiff;
    object	pilot;

    if (!ob->query_prop(OBJ_I_NO_CAPSIZE) &&
        !ob->query_capsized())
    {
	/* does the boat capsize? */
	max = ob->query_max_current();
	str = Currentstr[0];
	if (objectp(pilot = ob->query_pilot()))
	{
	    skilldiff = Min_swim_skill[str] -
			    pilot->query_skill(SS_BOAT_HANDL);
	    if (skilldiff < 5)
	    {
		skilldiff = 0;
	    }
	}
	if (str > max)
	{
	    /* boat is in waters too rough for it. the larger the 
	     * difference between boat's max current and present 
	     * current's str, the greater the chance of capsizing
	     */
	    if (skilldiff ||
		!objectp(pilot))
	    {
		/* waters too rough *and* no or unskilled pilot -- byebye */
		does_capsize = 1;
	    }
	    else
	    {
	    	does_capsize = random(str - max + 1);
	    }
	}
	else if (skilldiff >= 10)
	{
	    /* current is within boat's capability, but 
	     * significantly not within the pilot's ... 
	     */
	    does_capsize = random((skilldiff / 10) +1);
	}
	else if (str >= ROUGH_CURRENT)
	{
	    /* current str is within the boat's capability and pilot
	     * is skilled, but these are rough waters  ... there's
	     * a chance of capsizing.
	     */
	    if (objectp(pilot))
	    {
	    	does_capsize = !random(max - str + 4);
	    }
	    else
	    {
		/* in rough waters and no one is steering ... */
		does_capsize = !random(3);
	    }
	}
	if (does_capsize)
	{
	    ob->set_capsized(1);
	}
    }
    return does_capsize;
} /* check_capsize */


/*
 * Function name:	check_panic
 * Description	:	check whether the player panics
 * Arguments	:	object tp -- the player
 *			int str -- current strength
 * Returns	:	1 if panics, 0 if not
 */
public int
check_panic(object tp, int str)
{
    int	sk = tp->query_skill(SS_SWIM),
    	dis = tp->query_stat(SS_DIS),
	enc = tp->query_encumberance_weight();

    if (str < MODERATE_CURRENT)
    {
	/* in a fairly calm body of water, a skilled (or a less skilled
	 * but more disciplined) swimmer probably isn't likely to panic even
	 * if exhausted and even if encumbered ... i'd think they'd just
	 * float and wait to catch their breath.  a player who can barely
	 * tread water, tho, or someone who flusters easily might well panic
	 * even in a tame backyard pond.
	 */
	if (sk > 25 ||
	    dis > 50)
	{
	     return 0;
	}
	/* unskilled and undisciplined */
	return !random(3);
    }
    if (str > ROUGH_CURRENT)
    {
	/* if the water is quite rough ... well, to a certain extent, it's
	 * still a question of skill and discipline.  if you don't have
	 * good swimming skills, i'd say you almost certainly panic unless
	 * you are highly disciplined.  even a strong swimmer may well
	 * lose her cool, tho, especially if she's encumbered with a full
	 * set of platemail.  (so encumberance becomes more important when
	 * the current is stronger.) i think there'd also be a larger
	 * chance of just plain bad-luck-you-panic once current strength
	 * picks up.
	 */
	if (enc >= ENCUMBERANCE ||
	    sk <= 25)
	{
	    return 1;
	}
	if (sk > 60 &&
	    dis > 50 &&
	    enc < 50)
	{
	    return !random(4);
	}
	return random(2);
    }
    /* in the moderate ranges of current, what? errrk.  well, less of a
     * bad-luck-you-panic chance, and probably a strong swimmer would need 
     * to be fairly encumbered before panicking.  a novice swimmer is still
     * likely to be in trouble tho, altho i'd ease off from "certainly".
     */
    if (sk > 60 &&
	dis > 50 &&
	enc < ENCUMBERANCE)
    {
	return 0;
    }
    if (sk <= 25)
    {
	return !random(3);
    }
    return !random(5);
} /* check_panic */


/*
 * Function name:	panic_nazgul
 * Description	:	at gorboth's request, cause nazgul to panic
 *			when they enter water
 * Arguments	:	object naz -- the nazgul
 */
public void
panic_nazgul(object naz)
{
    if (!objectp(naz) ||
	ENV(naz) != TO)
    {
	return;
    }

    tell_object(naz, BSN(
	({
	    "As the water envelops you, you are seized by a sense of "+
		"dread, as if your Master will not aid you here!",
	    "The waters send a terrible fear throughout you, making "+
		"you wish more than anything to remove yourself from "+
		"their grip!",
	    "The waters swirl menacingly around you, threatening to "+
		"end your undead existance!"
	})[random(3)]));

    /* values taken from morgul/city/cellar1 */
    naz->add_panic(MAX(120 - naz->query_stat(SS_DIS),20)*5);
    naz->add_fatigue(-MAX(120 - naz->query_stat(SS_DIS),20));

    if (Currentstr[0]&&
	!naz->query_prop(OBJ_I_NO_WASH))
    {
	naz->add_prop(OBJ_I_WATER_ALARM,
	    set_alarm(float_alarm(Currentstr[0]), 0.0,
	        &float_downstream(naz)));
    }
    else /* incur fatigue */
    {
	naz->add_prop(OBJ_I_WATER_ALARM,
	    set_alarm(float_alarm(0), 0.0, &float_here(naz)));
    }
} /* panic_nazgul */


/*
 * Function name:	current_too_strong
 * Description	:	called if player's swim skill is < minimum skill
 *			for this current strength.  there's a chance
 *			they'll be swept downstream
 * Arguments	:	object tp -- the player
 *			int sk -- her/his swim skill
 *			int str -- the current strength
 *			string verb -- "swim", "float", "dive", "row", ...
 *			string dir -- direction of movement
 * Returns	:	0 if swim/wade attempt may continue,
 *			1 if it fails.  if it fails, current_too_strong()
 *			must issue all messages.
 */
public int
current_too_strong(object tp, int sk, int str, string verb, string dir)
{
    /* if current is too strong for their skills and they're trying to swim
     * across or against the current, there's a chance they won't be 
     * able to do it before being swept downstream.
     */
    if (random(10) < (2 + (((Min_swim_skill[str]) - (sk))/10)))
    {
	write("You try to "+verb+" "+
	      ( dir != "here" ? dir : "in place")+
	      ", but the current is too strong for you.\n");
	return 1;
    }
    return 0;
} /* current_too_strong */


/*
 * Function name:	warn_swimmer
 * Description	:	if current str exceeds player's swimming skill,
 *			warn 'em and add some panic.
 * Arguments	:	object tp -- this_player
 *			int sk -- player's SS_SWIM
 * Returns	:	0 if no warning, 1 if warned
 */
public int
warn_swimmer(object tp, int sk)
{
    int	rtype;
    if (sk < Min_swim_skill[Currentstr[0]] &&
	((rtype = ENV(tp)->query_prop(ROOM_I_TYPE)) == ROOM_IN_WATER ||
	 rtype == ROOM_UNDER_WATER))
    {
	tell_object(tp,
	    BSN("You feel rather worried when you realize just "
	      + "how strong the current is here."));
	(tp)->add_panic(PANIC_AMOUNT);
	return 1;
    }
    return 0;
} /* warn_swimmer */


/*
 * Function name:	warn_boat
 * Description	:	if current str exceeds player's boating skill,
 *			warn player and add some panic.
 *			if exceeds boat's design limit, ditto all passengers.
 * Arguments	:	object tp -- this_player
 *			int sk -- player's SS_BOAT_HANDL
 *			int maxstr -- the boat's max current
 *			object boat -- the inside-boat room
 * Returns	:	0 if no warning, -1 if warned all passengers,
 *			1 if warned only this player
 */
public int
warn_boat(object tp, int sk, int maxstr, object boat)
{
    if (maxstr > 0 &&
	maxstr < Currentstr[0])
    {
	tell_room(boat,
	    BSN("You feel rather worried when you realize that the "+
	        "current may be too strong for the "+
		boat->query_name()+"."));
	FILTER_LIVE(all_inventory(boat))->add_panic(PANIC_AMOUNT);
	return -1;
    }
    if (objectp(tp) &&
	sk < Min_swim_skill[Currentstr[0]])
    {
	tell_object(tp,
	    BSN("You feel rather worried when you realize that "+
		"the current here may be more than you have skill "+
		"to manage."));
	return -1;
    }
    return 0;
} /* warn_boat */



/* here follow all the set_ and query_ functions */
public void	 set_watertype(string type)    { Watertype = type; }
public void	 set_upstreamdir(mixed dir)    { Upstreamdir = ARRAY(dir);}
public void	 set_downstreamdir(mixed dir)  { Downstreamdir = ARRAY(dir);}
public void	 set_currentadj(mixed adj)     { Currentadj = ARRAY(adj); }
public void	 set_currentstr(mixed str)     { Currentstr = ARRAY(str); }
public void	 set_waterrefs(mixed refs)     { Waterrefs = ARRAY(refs); }
public void	 set_depth(int depth) { Depth = CHECK_RANGE(depth, 1, depth); }
public void	 set_rock_density(int rocks) 
		   { Rock_density = CHECK_RANGE(rocks, 0, MAX_ROCKS); }

public string	 query_watertype()		{ return Watertype; }
public string	*query_upstreamdir()		{ return Upstreamdir; }
public string	*query_downstreamdir()		{ return Downstreamdir; }
public string	*query_currentadj()		{ return Currentadj; }
public int	*query_currentstr()		{ return Currentstr; }
public string   *query_waterrefs()		{ return Waterrefs; }
public string	 query_below()			{ return Below; }
public string	 query_above()			{ return Above; }
public int	 query_depth()			{ return Depth; }
public int	 query_rock_density()		{ return Rock_density; }
public string	 expand_dir(string dir)		{ return Dir_substitute[dir]; }
public string	 query_move_direction()		{ return Move_direction; }

