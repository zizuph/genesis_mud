/*********************************************************************
 * - candle.c                                                      - *
 * - Based on Zima's code in Khalakhor.                            - *
 * - Created by Damaris@Genesis 08/2007                            - *
 *********************************************************************/
#pragma strict_types
inherit "/std/torch";
#include <stdproperties.h>
#include <macros.h>
 
void create_candle() { }

void create_torch()
{
	set_name("candle");
	set_long("Its a standard candle.\n");
	set_strength(1);
	set_time(60*15);
	create_candle();
}
 
 
public void
burned_out()
{
	object env = environment();
	object rm;
	string tmp = ::short();
	if (!objectp(env)) remove_object();
	
	if (living(env))
	{
		tell_object(env, "The " + tmp + " burns out and "+
		"melts away.\n");
		tell_room(environment(env), "The " + tmp + " that "+
		"" + QTNAME(env) + " is holding burns out.\n", env);
	}
	else if (env->query_prop(ROOM_I_IS))
	tell_room(env, "The " + tmp + " burns out and melts away.\n");
	else if (env->query_prop(CONT_I_ATTACH)) // on a table or such?
	{
		rm=environment(env);
		if (!objectp(rm)) remove_object();
		if (rm->query_prop(ROOM_I_IS))
		tell_room(rm,  "The " + tmp + " on the "+
		"" + (env->short()) + " burns out and melts away.\n");
	}
	remove_object();
}
