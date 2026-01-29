/*
 * /d/Gondor/std/water/shore_room.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * inherited by banks/shores/beaches/... 
 * assumes adjacent water is inheriting water_room.c
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <composite.h>		/* for COMPOSITE_LIVE, etc	*/
#include <filter_funs.h>	/* for FILTER_LIVE		*/
#include <ss_types.h>		/* for SS_SWIM			*/
#include <stdproperties.h>	/* for ROOM_BEACH, etc		*/
#include <macros.h>		/* for QCNAME			*/
#include "/d/Gondor/defs.h"	/* always ...			*/
#include "water_room.h"


/*
 * Water mapping indices are exit directions; values are arrays of
 * names and aliases of the body of water in the given direction.
 * These are used to parse enter/swim in/dive into/wade in/ ...
 *
 * for example, the value for Water["east"] might be
 *	   ({ "river", "water", "anduin", "river anduin",
 *	      "anduin river", "great river" })
 */	
static mapping	Water;

/* for expanding "n" to "north" etc */
private static mapping	Dir_substitute;

/* prototypes */
public void	create_shore_room();
nomask void	create_gondor();
public void	set_water(string dir, string *refs);
public void	init();
public int	unq_move(string str);
public int	enter_water(string arg);
public int	do_enter_water(string vb, string dir, string path);
public int	check_efunc(string dir);
public void	msgs_before_move(object tp, string verb, string watertype);
public void	msgs_after_move(object tp, string vb, string pcpl);
public string	room_in_dir(string dir);
public string	query_waterroom(string mod);
public string	exa_water(mixed room, string desc);


/*
 * Function name:	create_shore_room
 * Description	:	creator for shore rooms
 * Configure your room here.
 */
public void
create_shore_room()
{
} /* create_shore_room */


/*
 * Function name:	create_gondor
 * Description	:	gondor room creator
 */
nomask void
create_gondor()
{
    mixed	*exit_arr;
    string	*dirs;
    int		i, s;

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    Water = ([ ]);
    Dir_substitute = ([
	"n"  : "north", "s"  : "south", "w"  : "west", "e"  : "east",
	"u"  : "up", "d"  : "down", "sw" : "southwest",
	"se" : "southeast", "nw" : "northwest", "ne" : "northeast",
    ]);

    create_shore_room();

} /* create_gondor */

/*
 * Function name:	set_water
 * Description	:	set up info about adjacent water rooms
 * Arguments	:	string dir -- the exit direction to the water.
 *				this should be the full direction
 *				(e.g., "east", not "e").
 *			string *refs -- array of aliases for the water 
 *				(used to parse enter/swim in/dive in/etc)
 *
 * for example, the value for Water["east"] might be
 *	   ({ "river", "water", "anduin", "river anduin",
 *	      "anduin river", "great river" })
 */	
public void
set_water(string dir, string *refs)
{
    if (strlen(dir) &&
	sizeof(refs) &&
	strlen(refs[0]))
    {
	Water[dir] = refs;
    }
} /* set_water */


/* Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(enter_water, "swim");
    add_action(enter_water, "dive");
    add_action(enter_water, "jump");
    add_action(enter_water, "enter");
    add_action(enter_water, "wade");
} /* init */


/*
 * Function name:	unq_move
 * Description	:	mask parent's unq_move() so that moving into the water
 *		 	behaves like "enter water".
 * Arguments	:	string str - the command line argument.
 * Returns	:	1 on success, 0 o failure
 */
public int
unq_move(string str)
{
    string	vb = QVB,
		room;
    if (pointerp(Water[vb]) &&
	strlen(room = room_in_dir(vb)))
    {
	return do_enter_water(vb, vb, room);
    }
    return ::unq_move(str);
} /* unq_move */


/*
 * Function name:	enter_water
 * Description	:	handle attempts to enter the water
 * Arguments	:	whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
enter_water(string arg)
{
    int		s;
    string	*dirs,
		*refs,
		room,
		tmpstr,
		vb = QVB;

    if (!strlen(arg))
    {
	NF0(CAP(vb)+" where?\n");
    }

    arg = LOW(arg);
    if (vb != "enter")
    {
	/* handle swim/dive/wade <direction> */
	if (strlen(tmpstr = Dir_substitute[arg]))
	{
	    /* expand "ne" to "northeast", etc */
	    arg = tmpstr;
	}
	if (pointerp(Water[arg])&&
	    strlen(room = room_in_dir(arg)))
	{
	    return do_enter_water(vb, arg, room);
	}
    }
    /* handle enter and swim/dive/jump into ... */
    dirs = m_indices(Water);
    s = sizeof(dirs);
    while (s-- > 0)
    {
	refs = Water[dirs[s]];
	if (parse_command(arg, ({}), "[in] / [into] [the] %p", refs) &&
	    strlen(room = room_in_dir(dirs[s])))
	{
	   return do_enter_water(vb, dirs[s], room);
	}
    }
    NF0(CAP(vb)+" where?\n");
} /* enter_water */


/*
 * Function name:	do_enter_water
 * Description	:	handle msgs and moving player into water
 * Arguments	:	string vb -- player verb
 *			string dir -- the direction of the water
 *			string path -- the destination
 * Returns	:	1 on success, 0 on failure
 */
public int
do_enter_water(string vb, string dir, string path)
{
    int		type;
    object	roomob,
		tp = TP;
    string	pcpl,
		watertype;

    if (!strlen(path))
    {
	return 0;	/* shrug */
    }
    FIX_EUID;
    path->short();
    roomob = find_object(path);
    if (!objectp(roomob))
    {
	return 0;	/* shrug */
    }
    if (check_efunc(dir))
    {
	return 1;	/* room blocked move */
    }

    switch ( vb )
    {
    case "wade":
	if (roomob->query_depth() > MAX_WADE_DEPTH)
	{
	    write("The water is too deep for wading.\n");
	    return 1;
	}
	type = WATER_MOVE_WADE;
	pcpl = "wading";
	break;
    case "swim":
    case "dive":
	if (roomob->query_depth() < MIN_SWIM_DEPTH)
	{
	    write("The water is too shallow to "+vb+".\n");
	    return 1;
	}
	type = WATER_MOVE_SWIM;
	vb = "dive";
	pcpl = "swimming";
	break;
    default:
	if (roomob->query_depth() <= MAX_WADE_DEPTH)
	{
	    vb = "wade";
	    pcpl = "wading";
	    type = WATER_MOVE_WADE;
	}
	else
	{
	    vb = "dive";
	    pcpl = "swimming";
	    type = WATER_MOVE_SWIM;
	}
	break;
    }

    if (type == WATER_MOVE_SWIM)
    {
	if (tp->query_skill(SS_SWIM) < roomob->query_min_swim_skill(-1))
	{
	    WRITE("You advance to the edge of the water, but then "+
		"have doubts about your swimming skills. You "+
		"decide to stay on dry land.");
	    return 1;
	}
    }
    watertype = roomob->query_watertype();
    tp->add_prop(OBJ_I_WATER_MOVE, type);
    msgs_before_move(tp, vb, watertype);
    set_dircmd("water");
    tp->move_living("M", roomob);
    msgs_after_move(tp, vb, pcpl);

    return 1;
} /* enter_water */


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

    exit_arr = query_exit();
    if ((i = member_array(dir, exit_arr)) > 0 &&
	exit_arr[i+1])
    {
	return check_call(exit_arr[i+1]);
    }
    return 0;
} /* check_efunc */


/*
 * Function name:	msgs_before_move
 * Description	:	provide a convenient place for inheriting
 *			rooms to roll their own you-enter-the-water msgs
 * Arguments	:	object tp -- this_player
 *			string verb -- swim, wade, dive, ...
 *			string watertype -- river, pool, ....
 *
 * N.B. OBJ_I_WATER_MOVE type has been set before msgs_before_move
 *      is called. you can change it here if needed.
 */
public void
msgs_before_move(object tp, string verb, string watertype)
{
    write("You "+verb+" into the "+watertype+".\n");
    SAYBB(" "+verb+"s into the "+watertype+".");
} /* msgs_before_move */

/*
 * Function name:	msgs_after_move
 * Description	:	provide a convenient place for inheriting
 *			rooms to roll their own foo-arrives msgs
 * Arguments	:	object tp -- this_player
 *			string vb -- "swim", "wade", "dive"
 *			string pcpl -- participle phrase suitable for being
 *				appended to "Foo arrives " (e.g., "swimming")
 *				(no trailing period)
 *
 * we have to explicitly set and restore this_player here or
 * when teams move, you will see some team member enter twice
 * and will not see the team leader enter at all.
 */
public void
msgs_after_move(object tp, string vb, string pcpl)
{
    object	save_tp;
    string	m_in;
    int		len;

    save_tp = TP;
    set_this_player(tp);
    m_in = tp->query_m_in();
    SAYBB(" " + m_in + " " + pcpl + ".");
    set_this_player(save_tp);
} /* msgs_after_move */


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

    exit_arr = query_exit();
    if ((i = member_array(dir, exit_arr)) > 0)
    {
	return check_call(exit_arr[i-1]);
    }
    return "";
} /* room_in_dir */


/*
 * Function name:	query_waterroom
 * Description	:	return name of adjacent water room
 * Arguments	:	string mod -- optional modifier to narrow room
 *			    selection. if a direction, return the water
 *			    in that direction. else if matched by one of
 *			    the references in Water mapping, return that room.
 * Returns	:	string -- the name of the water room, or "" if none
 *			    found.
 *
 * query_waterroom() returns the pathname of the first adjacent body
 * of water found.  query_waterroom("east") returns the pathname of the
 * water to the east. query_waterroom("pond") returns the pathname of the
 * first body of water whose refs array in the Water mapping include the
 * word "pond".
 */
public string
query_waterroom(string mod)
{
    string	*dirs,
		*refs;
    int		i,
		s;

    dirs = m_indices(Water);
    s = sizeof(dirs);
    if (!s)
    {
	return "";
    }
    if (!strlen(mod))
    {
	return room_in_dir(dirs[0]);
    }
    if ((i = member_array(mod, dirs)) >= 0)
    {
	return room_in_dir(dirs[i]);
    }
    while (s-- > 0)
    {
	refs = Water[dirs[s]];
	if (member_array(mod, refs) >= 0)
	{
	    return room_in_dir(dirs[s]);
	}
    }
    return "";
} /* query_waterroom */


/*
 * Function name:	exa_water
 * Description	:	VBFC for the water -- mention any swimmers or boats
 * Arguments	:	mixed room -- water room being exa'd (name or object)
 *			string desc -- the base description of the water
 * Returns	:	the water desc
 */
public string
exa_water(mixed room, string desc)
{
    object	roomob,
		*on_water,
		*live_on_water;
    string	type;
    int		s,
		d;

    if (objectp(room))
    {
	roomob = room;
    }
    else if (strlen(room))
    {
	FIX_EUID;
	room->short();
	roomob = find_object(room);
    }
    else
    {
	return "";
    }

    if (!strlen(desc))
    {
	desc = "";
    }

    if (sizeof(on_water = all_inventory(roomob)))
    {
	if (!TP->query_wiz_level())
	{
	    /* assume that from a distance, cannot see hidden or invis */
	    on_water = filter(filter(on_water,
		&not() @ &->query_prop(OBJ_I_HIDE)),
		&not() @ &->query_invis());
	}
	live_on_water = FILTER_LIVE(on_water);
	s = sizeof(live_on_water);
	type = roomob->query_watertype();
	if (s)
	{
	    d = roomob->query_depth();
	    desc += CAP(COMPOSITE_LIVE(live_on_water))+
		(s == 1 ? " is" : " are")+
		(d >= MAX_WADE_DEPTH ? " swimming" : " wading")+
		" in the "+type+".\n";
	    on_water -= live_on_water;
	}
	s = sizeof(on_water);
	if (s)
	{
	    desc += CAP(COMPOSITE_DEAD(on_water))+
		(s == 1 ? " is " : " are ")+
		"floating in the "+type+".\n";
	}
    }
    return desc;
} /* exa_water */
