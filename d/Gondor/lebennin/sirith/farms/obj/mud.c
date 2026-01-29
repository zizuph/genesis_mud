/*
 * /d/Gondor/lebennin/sirith/farms/obj/mud.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * mud for pigsty
 * adds a subloc to player so s/he is "liberally splattered with mud".
 * lasts 10 minutes.
 *
 */

#pragma strict_types

inherit	"/std/object";

#include <stdproperties.h>	/* for OBJ_I_WEIGHT, etc */
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define	SIRITH_MUD_SUBLOC	(SIRITH_MUD+"subloc")
#define	MUD_DURATION		600.0	/* 10 minutes */

static int	Alarm_id;

public void	create_object();
public void	enter_env(object env, object from);
public void	leave_env(object env, object dest);
public string	show_subloc(string subloc, object on_obj, object for_obj);


/*
 * Function name:	create_object
 * Description	:	set up the mud
 */
public void
create_object()
{
    ::create_object();

    set_name(SIRITH_MUD);
    set_short(0);
    set_long(SIRITH_MUD+" object should be invisible\n");
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    set_no_show();
} /* create_object */


/*
 * Function name:	enter_env
 * Description	:	mask parent enter_env to set subloc & set alarm to
 *			remove us after a while.
 * Arguments	:	object env - the destination we are entering.
 *			object from  - the location we came from.
 *
 */
public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (living(env))
    {
	if (Alarm_id > 0)	/* "cannot" happen */
	{
	    remove_alarm(Alarm_id);
	}
	env->add_subloc(SIRITH_MUD_SUBLOC, TO);
	Alarm_id = set_alarm(MUD_DURATION, 0.0, &remove_object());
    }
} /* enter_env */


/*
 * Function name:	leave_env
 * Description	:	mask parent to remove subloce
 * Arguments	:	object env  - the location we are leaving.
 *			object dest - the destination we are going to.
 *
 * Assumes that what causes to leave the env us is our own call to
 * remove_object(), since we are invis and cannot be dropped or given.
 * Therefore don't call remove_object() again here.
 */
public void
leave_env(object env, object dest)
{
    ::leave_env(env, dest);
    if (living(env))
    {
	if (!objectp(present(SIRITH_MUD, env)))
	{
	    env->remove_subloc(SIRITH_MUD_SUBLOC);
	}
	if (Alarm_id > 0)	/* "cannot" happen */
	{
	    remove_alarm(Alarm_id);
	    Alarm_id = 0;
	}
    }
} /* leave_env */

	
/*
 * Function name:	show_subloc
 * Description	:	show the mud
 * Arguments	:	string subloc -- the subloc to display
 *			object on_obj -- object to which the subloc is linked
 *			object for_obj -- object that wants to see the subloc
 * Returns	:	string desc -- description of the subloc
 */
public string
show_subloc(string subloc, object on_obj = TP, object for_obj = TP)
{
    if (on_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
        subloc != SIRITH_MUD_SUBLOC)
    {
        return on_obj->show_subloc(subloc, on_obj, for_obj);
    }

    if (for_obj == on_obj)
    {
	return "You are liberally splattered with mud.\n";
    }

    return CAP(PRONOUN(on_obj))+" is liberally splattered with mud.\n";
} /* show_subloc */
