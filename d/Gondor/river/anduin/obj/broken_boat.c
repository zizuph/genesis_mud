/*
 * /d/Gondor/river/anduin/obj/broken_boat.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * a boat with its bottom staved in. sinks like a stone
 * if you drag it into the water.
 *
 * XXX self destruct after underwater for some time
 */

#pragma strict_types

/* XXX 	inherit standard anduin boat when ready */
inherit "/d/Gondor/std/water/boat";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/water_room.h"

#define	BREAK_ALARM	300.0

/* prototypes */
public void	create_boat();
public void	enter_env(object dest, object old);
public int	do_enter(string arg);


/* global variables */
static int	Breakalarm;


/*
 * Function name:	create_boat
 * Description	:	set up the boat
 */
public void
create_boat()
{
    set_name( ({ "boat", "row boat", "rowboat", BROKEN_BOAT_NAME }) );
    add_adj("broken");
    set_short("broken wooden boat");
    set_long(BSN("The wooden boat is plain and somewhat battered. It " +
	"has a great jagged hole in its bottom."));

    remove_prop(OBJ_I_FLOAT);
    add_prop(OBJ_I_SINK, 1);
    add_prop(OBJ_I_NO_WASH, 1);
} /* create_boat */


/*
 * Function name:	enter_env
 * Description	:	avoid special handling to force boats to the
 *			surface -- this boat is supposed to sink -- and 
 *			schedule break-up of boat.
 * Arguments	:	object dest - the destination we are entering.
 *			object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::::enter_env(dest, old);
    if (!Breakalarm &&
	ENV()->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
	Breakalarm = set_alarm(BREAK_ALARM, 0.0, &break_apart());
    }
} /* enter_env */


/*
 * Function name:	do_enter
 * Description	:	mask parent so they don't enter the boat.
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 * preventing enter is much simpler than trying to handle all
 * the things that should happen when a boat with a hole in
 * it enters the water.
 */
public int
do_enter(string arg)
{
    object	ob;

    if (!ENV()->query_prop(ROOM_I_IS))
    {
	return 0;
    }

    if (!strlen(arg) ||
	!parse_command(LOW(arg), ({ TO }), "[the] %o", ob))
    {
	NF0(CAP(QVB) + " what?\n");
    }
    WRITE("With that huge hole in the bottom, there's no place " +
	"for you to sit in the boat.");
    return 1;
} /* do_enter */


/*
 * Function name:	break_apart
 * Description	:	mask parent so the boat just disappears --
 *			no splinters
 * Arguments	:	string msg -- unused
 */
public void
break_apart(string msg)
{
    tell_room(ENV(), "The wooden boat breaks apart!\n");
    remove_object();
} /* break_apart */
