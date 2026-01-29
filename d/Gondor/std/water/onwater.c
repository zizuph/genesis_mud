/*
 * /d/Gondor/std/water/onwater.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * inherited by river/stream/pond/... rooms.
 * based on elessar's river code (thanks, elessar!)
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/water_room";

#include <ss_types.h>		/* for SS_SWIM			*/
#include <composite.h>		/* for COMPOSITE_WORDS		*/
#include <language.h>		/* for LANG_ADDART		*/
#include <stdproperties.h>	/* for properties		*/
#include "/d/Gondor/defs.h"	/* always ...			*/
#include "onwater.h"

static string	Watername;	/* the proper name of the water	*/

/* prototypes */
public void	create_onwater();
nomask void	create_water_room();
public void	init();
public int	do_swim(string arg);
public int	do_stand(string arg);
public void	set_watername(string name);
public string	query_watername();


/*
 * Function name:	create_onwater
 * Description	:	creator for onwater rooms
 * Configure your room here.
 */
public void
create_onwater()
{
} /* create_onwater */

/*
 * Function name:	create_water_room
 * Description	:	water_room creator
 */
nomask void
create_water_room()
{
    object pocket;

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    create_onwater();

    if (Depth > MAX_WADE_DEPTH &&
	file_name(TO) != ONWATER &&
	!strlen(Below))
    {
	/* deepish water must have a place to sink objects */
	FIX_EUID;
	pocket = clone_object(POCKET);
	pocket->add_exit(file_name(TO), "up", 0, 1, 1);
	pocket->set_watertype(Watertype);
	add_exit(file_name(pocket), "down", 0, 1, 1);
    }

} /* create_water_room */


/* Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(do_swim, "wade");
    add_action(do_stand, "stand");
} /* init */


/*
 * Function name:	do_swim
 * Description	:	handle player's swim/tread/wade cmd
 * Argument	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_swim(string arg)
{
    int type;
    switch ( QVB )
    {
    case "swim":
    case "tread":
	if (Depth < MIN_SWIM_DEPTH)
	{
	    NF0("The water is too shallow for swimming.\n");
	}
	type = WATER_MOVE_SWIM;
	break;
    case "wade":
	if (Depth > MAX_WADE_DEPTH)
	{
	    NF0("The water is too deep for wading.\n");
	}
	type = WATER_MOVE_WADE;
	break;
    default:	/* north, etc*/
	if ((type = TP->query_prop(OBJ_I_WATER_MOVE)) != WATER_MOVE_SWIM)
	{
	    type = ( Depth > MAX_WADE_DEPTH ?
			     WATER_MOVE_SWIM : WATER_MOVE_WADE );
	}
	break;
    }
    return ::do_swim_func(arg, type);
} /* do_swim */


/*
 * Function name:	do_stand
 * Description	:	handle player's attempts to stand up in water
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_stand(string arg)
{
    int		alarm_id;
    object	tp = TP;

    if (strlen(arg) &&
	arg != "up")
    {
	NF0("Stand what? Stand up, perhaps?\n");
    }
    if (tp->query_prop(OBJ_I_WATER_MOVE) == WATER_MOVE_WADE)
    {
	write("You already are standing in the "+Watertype+".\n");
    }
    else if (Depth > MAX_WADE_DEPTH)
    {
	write("The water is too deep.\n");
    }
    else
    {
	write("You stand up in the "+Watertype+".\n");
	SAY(" stands up in the "+Watertype+".\n");
	if ((alarm_id = tp->query_prop(OBJ_I_WATER_ALARM)))
	{
	    remove_alarm(alarm_id);
	    tp->remove_prop(OBJ_I_WATER_ALARM);
	}
	tp->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_WADE);
    }
    return 1;
} /* do_stand */


/*
 * Function name:	unq_no_move
 * Description	:	mask parent so player sees a "swim" or "wade" 
 *			failure msg
 * Arguments	:	string arg -- whatever the player typed (not used)
 * Returns	:	0 (msg written via notify_fail)
 */
public int
unq_no_move(string arg)
{
    string vb = QVB;

    /* If there is a no-exit message, pass to original routine. */
    if (query_no_exit_msg(vb))
    {
    	return ::unq_no_move(arg);
    }

    if (vb != "down")
    {
	if (TP->query_prop(OBJ_I_WATER_MOVE) == WATER_MOVE_WADE)
	{
	    notify_fail("You cannot wade "+vb+".\n");
	}
	else
	{
	    notify_fail("You cannot swim "+vb+".\n");
	}
    }
    else
    {
	notify_fail("The water is not deep enough to dive here.\n");
    }
    return 0;
} /* unq_no_move */


/* the generic set-and-query stuff */
public void	 set_watername(string name)	{ Watername = name; }
public string	 query_watername()		{ return Watername; }
