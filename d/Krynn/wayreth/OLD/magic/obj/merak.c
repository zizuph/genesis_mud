/*
 * Merak object
 *
 * Give an object some light.
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/rastlin/open/spells2/magic.shadow";

string gPrev_long, gNo_light = "";
int gLight;

public void
init_spell(object caster, object target, object prev)
{
    int vol;

    set_remove_on_dispel();
    
    vol = target->query_prop(OBJ_I_VOLUME);

    if (vol < 500)
    {
        gNo_light = " But the glow is to weak to produce any " +
	  "additional light.";
	gLight = 0;
    }
    else
    {
        gLight = (vol / 10000) + 1;
	gLight = (gLight > 5 ? 5 : gLight);
    }

    target->add_prop(OBJ_I_LIGHT, target->query_prop(OBJ_I_LIGHT) + gLight);
}

public varargs string
long(mixed for_obj)
{
    string str = query_me()->long(for_obj);
    
    if (!stringp(str) || !strlen(str))
	str = "";

    str += "The " + query_me()->short() + " has a soft glowing " +
           "aura surrounding it." + gNo_light + "\n";

    return str;
}

public varargs string
short(mixed for_obj)
{
    return query_me()->short() + ", with a glowing aura";
}

public void
notify_dispel_magic(object ob)
{
    object me = query_me();
    object env = environment(me);

    me->add_prop(OBJ_I_LIGHT, me->query_prop(OBJ_I_LIGHT) - gLight);
    me->set_long(gPrev_long);

    if (!gLight)
    {
        tell_room(env, "The aura surrounding the " + me->short() + 
		  " slowly blinks and fades out, and so does the " +
		  me->short() + ".\n");
	return;
    }

    if (living(env))
    {
        env->catch_msg("The aura surrounding the " + me->short() + 
		       " slowly diminishes, also the " + me->short() +
		       " fades out of existence and it gets darker.\n");
	tell_room(E(env), "The aura surrounding the " + me->short() +
		  " that " + QTNAME(env) + " is holding slowly " +
		  "diminishes, also the " + me->short() + " fades out of " +
		  " existence and it gets darker.\n", env);
    }
    else
        if (env->query_prop(ROOM_I_IS))
	{
	    tell_room(env, "The aura surrounding the " + me->short() +
		      " slowly diminishes, also the " + me->short() + 
		      " fades out of existence and it gets darker.\n");
	}
}
