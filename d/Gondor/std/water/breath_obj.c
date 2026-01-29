/*
 * /d/Gondor/std/water/breath_obj.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * an invisible, undroppable object, put on players when they
 * go underwater to keep track of how long they've held their
 * breath. when they run out of air, forces 'em to surface
 * if possible; drowns 'em if not.
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "water_room.h"

#define	MIN_BREATH_ALARMS       2
#define	ALARM_INTERVAL		15.0
#define	PANIC_INTERVAL		 2.0


static int	Nbreaths;	/* # of breath alarms before player	*/
				/* has to leave. if negative, no limit.	*/
static int 	Alarm_id;

nomask void	create_object();
public void	set_nbreaths(int n);
public int	query_nbreaths();
public void	enter_env(object dest, object from);
public void	leave_env(object from, object dest);
public void	start_breath(object pl);
public void	check_breath();


/*
 * Function name:	create_object
 * Description	:	create an invis obj to monitor
 *			player's breath while underwater
 */
nomask void
create_object()
{
    set_name("Breath_Object");
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_INVIS,1);
    set_no_show();
} /* create_object */

public void	set_nbreaths(int n)	{ Nbreaths = n; }
public int	query_nbreaths()	{ return Nbreaths; }


/*
 * Function name:	enter_env
 * Description	:	when moved into a player, start the
 *				breath monitoring
 * Arguments	:	object dest -- destination
 *			object from -- where we came from
 */
public void
enter_env(object dest, object from)
{
    ::enter_env(dest, from);

    if (!interactive(dest))
    {
	remove_object();
	return;
    }
    start_breath(dest);
} /* enter_env */


/*
 * Function name:	leave_env
 * Description	:	remove the breath alarm when we
 *				leave a player
 * Arguments	:	object from -- where we're leaving
 *			obejct dest -- where we're going
 */
public void
leave_env(object from, object dest)
{
    if (Alarm_id)
	remove_alarm(Alarm_id);
    ::leave_env(from, dest);
} /* leave_env */


/*
 * Function name:	start_breath
 * Description	:	start the alarm to monitor breath
 * Arguments	:	object pl -- the player
 */
public void
start_breath(object pl)
{
    int sk = pl->query_skill(SS_SWIM);

    if (sk < ENV(pl)->query_min_swim_skill())
    {
	/* if they don't have the skill, they get booted out,
	 * even if Nbreaths was negative
	 */
	Nbreaths = 0;
	Alarm_id = set_alarm(PANIC_INTERVAL, 0.0, &check_breath());
    }
    else if (Nbreaths >= 0)
    {
	/* Nbreaths may have been set by whatever cloned us.
	 * if so, leave it alone.
	 */
	if (!Nbreaths)
	{
	    Nbreaths = MIN_BREATH_ALARMS + (sk / 10);
	}
	Alarm_id = set_alarm(ALARM_INTERVAL, 0.0, &check_breath());
    }
} /* start_breath */


/*
 * Function name:	check_breath
 * Description	:	write status msg, move player if out of breath,
 *			or drown them if cannot move.
 */
public void
check_breath()
{
    int 	i;
    object	env, pl = ENV();

    if (!interactive(pl) ||
	!objectp(env = ENV(pl)) ||
	env->query_prop(ROOM_I_TYPE) != ROOM_UNDER_WATER)
    {
	remove_object();
	return;
    }

    if (Nbreaths > 0)
    {
	--Nbreaths;
    }
    i = CHECK_RANGE(Nbreaths, 0, 4);

    tell_object(pl, ({
	"Desperate for air, you struggle toward the surface.\n",
	"You are running out of air. Your lungs burn.\n",
        "You feel quite giddy from lack of air.\n",
	"You begin to feel giddy from holding your breath.\n",
	"You feel quite comfortable holding your breath.\n"
	})[i]);

    if (Nbreaths > 0)
    {
	Alarm_id = set_alarm(ALARM_INTERVAL, 0.0, &check_breath());
	return;
    }

    /* out of air.  damage them, but try to get them above water */
    pl->heal_hp(-(pl->query_hp() / 4));
    pl->add_panic(PANIC_AMOUNT);

    /* command() won't work for wizards, of course */
    if (!pl->query_wiz_level())
    {
	pl->command("$up");
    }
    else
    {
	write("Ordinarily, we would do:\n\tTP->command(\"$up\");\n"+
	    "Since you're a wizard, this won't work.\n");
    }
    if (ENV(pl) != env)
    {
	Alarm_id = set_alarm(PANIC_INTERVAL, 0.0, &check_breath());
	return;
    }

    /* well, we tried.  looks like they die. */
    write("Your lungs fill with water before you reach the surface ... \n");
    pl->heal_hp(-(pl->query_max_hp() * 2));
    INFO_LOG(pl->query_name()+" ("+pl->query_average_stat()+
	") drowned in "+file_name(env)+".\n");
    pl->do_die(ENV(pl));
    remove_object();
} /* check_breath */
