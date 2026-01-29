/*
 * /d/Gondor/river/anduin/lorien2rauros/riverbottom21.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * underwater at sarn gebir ... you're pounded to death on the rocks.
 * XXX need to update this
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_underwater";

#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/underwater.h"
#include "../anduin.h"

#define	ALARM_INTERVAL	5.0

/* prototypes */
public void	create_anduin_underwater();
public void	enter_inv(object ob, object from);
public int	no_escape();
public int	check_hit_rock(object ob);
public int	current_too_strong(object tp, int sk, int str, string verb,
							string	dir);
public int	do_swim(string arg);	/* XXX temporary */



/*
 * Function name:	create_anduin_underwater
 * Description	:	create the room
 */
public void
create_anduin_underwater()
{
    set_short("underwater");
    set_long(BSN("Underwater. The waters churn violently "+
	"around dark jagged shapes."));

    set_watertype("river");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir( ({ "northeast", "north", "northwest" }) );
    set_downstreamdir("south");
    set_currentstr(MAX_CURRENT);
    set_rock_density(MAX_ROCKS);

    add_exit("river21", "up", no_escape, 0, 1);
    add_exit("riverbottom21", "west", no_escape, 0, 1);
    add_exit("riverbottom21", "east", no_escape, 0, 1);
    add_exit("riverbottom21", "here", no_escape, 0, 1);
    add_exit("riverbottom18e", "northeast", no_escape, 0, 1);
    add_exit("riverbottom18e", "north", no_escape, 0, 1);
    add_exit("riverbottom18w", "northwest", no_escape, 0, 1);
    add_exit("riverbottom22", "south", check_hit_rock, 0, 1);
    add_exit("riverbottom22", "southeast", check_hit_rock, 0, 1);
    add_exit("riverbottom22", "southwest", check_hit_rock, 0, 1);

    add_item( ({ "dark jagged shape", "dark jagged shapes", 
    	"jagged shape", "jagged shapes", "shape", "shapes", }),
	BSN("The waters plunge against dark jagged rocks."));
    add_item( ({ "dark jagged rock", "dark rock", "jagged rock", "rock",
	"dark jagged rocks", "dark rocks", "jagged rocks", "rocks" }),
	BSN("Jagged rocks, thrusting up towards the surface, "+
	    "roil the waters."));
    add_item( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }),
	BSN("The waters swirl and churn south around dark rocks."));
    add_item( ({ "surface" }),
	BSN("The waters are so agitated that it's hard to see."));
} /* create_anduin_underwater */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to ensure that livings hit rocks
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{

    int		set_prop;

    if (living(ob) &&
	!ob->query_ghost() &&
	!ob->query_prop(OBJ_I_NO_WASH))
    {
	set_prop = 1;
	ob->add_prop(OBJ_I_NO_WASH, 1);
    }

    ::enter_inv(ob, from);

    if (!objectp(ob))
    {
	return;
    }

    if (set_prop)
    {
	/* living MUST hit rock.
	 * check_hit_rock will set any alarms.
	 */
	ob->remove_prop(OBJ_I_NO_WASH);
	if (ENV(ob) == TO)
	{
	    check_hit_rock(ob);
	}
    }
    /* else alarm will have been set in parent */
} /* enter_inv */


/*
 * Function name:	no_escape
 * Description	:	block escape
 * Returns	:	1 -- no exit
 */
public int
no_escape()
{
    string	response,
		vb = QVB;

    /* swimmer */
    if (vb == "up")
    {
	response = "You try to rise to the surface";
    }
    else
    {
	response = "You try to swim "+query_move_direction();
    }
    write(BSN(response+", but the torrential currents are far "+
	"too strong. You are helpless to control your movement."));
    return 1;
} /* no_escape */


/*
 * Function name:	check_hit_rock
 * Description	:	mask parent --  entering ob hits rocks
 * Arguments	:	object ob -- the player or boat
 * Returns	:	1 (always)
 */
public int
check_hit_rock(object ob)
{
    int dmg;

    if (!ob &&
	ENV(TP) == TO)
    {
	ob = TP;
    }

    dmg = ob->query_max_hp()/4;
    dmg += random(dmg);
    write("Helpless in the torrential currents, "
	+ "you slam headfirst into a rock.\n");
    SAY(" slams headfirst into a rock.\n");
    ob->reduce_hit_point(dmg);
    if (ob->query_hp() <= 0)
    {
	write(BSN("You are too stunned by the blow to keep "+
	    "swimming. You drown in the rapids of Sarn Gebir."));
	SAY(" appears stunned by the blow. "+
	    CAP(ob->query_pronoun())+" drowns.");
	INFO_LOG(ob->query_real_name()+" ("+
	    ob->query_average_stat()+
	    ") hit a rock and drowned.\n");
	ob->do_die(TO);
    }
    else
    {
	/* they didn't die -- hit 'em again */
	ob->add_prop(OBJ_I_WATER_ALARM,
	    set_alarm(ALARM_INTERVAL, 0.0, &check_hit_rock(ob)));
    }
    return 1;
} /* check_hit_rock */


/*
 * Function name:	current_too_strong
 * Description	:	mask parent ... exit efun has already done this
 * Arguments	:	object tp -- the player
 *			int sk -- her/his swim skill
 *			int str -- the current strength
 *			string verb -- "swim", "float", "dive"
 *			string dir -- direction of movement
 * Returns	:	0 (always) -- movement succeeds
 */
public int
current_too_strong(object tp, int sk, int str, string verb, string dir)
{
    return 0;
} /* current_too_strong */


/*
 * Function name:	do_swim
 * Description	:	mask parent til fix ~gondor/std/water/underwater.c
 * Argument	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *XXX remove when underwater.c is fixed
 */
public int
do_swim(string arg)
{
    if (arg != "up" ||
	!no_escape())
    {
	return ::do_swim(arg);
    }
    return 1;
} /* do_swim */
