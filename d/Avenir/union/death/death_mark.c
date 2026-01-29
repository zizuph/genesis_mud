/*
 * death_mark.c
 *
 * The object that sends a player off to meet his maker.
 * In this particular case, that'd be Mascarvin.
 *
 *   Lucius, May 25, 2007
 *
 * Based off original death_mark.c by:
 * Khail, Nov. 15/96
 * Mrpr 901122
 * Tintin 911031
 * Nick 920211
 */
#pragma no_shadow
#pragma strict_types

#include "death.h"
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>

inherit "/std/object";

/* Global vars */
private static int death_id;


public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(DEATH_MARK_ID);

    add_prop(OBJ_I_VALUE,   0);
    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VOLUME,  0);
    add_prop(OBJ_M_NO_DROP, 1);
}

/*
 * Function name: start_death
 * Description  : Starts up the death routine. Delivers appropriate
 *                messages to player who died and those in the room,
 *                and either moves the player to death's room, or 
 *                calls reincarnate in him/her.
 */
private void
start_death(void)
{
    /* Figure out who's carrying the mark. */
    object me = environment();

    if (!me || !living(me) || !me->query_ghost())
    {
	remove_object();
	return;
    }

    /* Make sure the player isn't already a ghost. */
    if (MASTER_OB(me) == LOGIN_NEW_PLAYER)
    {
	remove_object();
	return;
    }

    me->move(DEATH_ROOM, 1);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    /* Don't bother with the alarm if the new environment isn't alive. */
    if (!to || !living(to))
	return;

    /* Don't run the alarm if it's already running. */
    if (death_id)
	return;

    /* Don't try to 'kill' a ghost. */
    if (MASTER_OB(to) == LOGIN_NEW_PLAYER)
	return;

    /* Ok, start the death sequence by calling start_death in 1 sec. */
    death_id = set_alarm(1.0, 0.0, start_death);
}

public void
init_arg(string str)
{
    if (death_id)
	return;

    death_id = set_alarm(1.0, 0.0, start_death);
}

public string
query_auto_load(void)	{ return MASTER + ":"; }
