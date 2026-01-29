/*
 * Merak object
 *
 * Give an object some light.
 */
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/shadow";

string gPrev_long, gNo_light = "";
int gLight;

public int
start()
{
    int vol;

    if (!shadow_me(spell_target))
    {
        remove_spell_effect_object();
        return 0;
    }
    
    vol = spell_target->query_prop(OBJ_I_VOLUME);

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
    
    spell_target->add_prop(OBJ_I_LIGHT, 
        spell_target->query_prop(OBJ_I_LIGHT) + gLight);
    return 1;
}

public varargs string
long(mixed for_obj)
{
    string str = shadow_who->long(for_obj);
    
    if (!stringp(str) || !strlen(str))
	str = "";

    str += "The " + shadow_who->short() + " has a soft glowing " +
        "aura surrounding it." + gNo_light + "\n";

    return str;
}

public varargs string
short(mixed for_obj)
{
    return shadow_who->short() + ", with a glowing aura";
}

varargs public int
dispel_spell_effect(object dispeler)
{
    object env = environment(shadow_who);
    
    shadow_who->add_prop(OBJ_I_LIGHT, shadow_who->query_prop(OBJ_I_LIGHT) - 
        gLight);
    shadow_who->set_long(gPrev_long);
    
    if (!gLight)
    {
        tell_room(env, "The aura surrounding the " + shadow_who->short() + 
            " slowly blinks and fades out, and so does the " +
            shadow_who->short() + ".\n");
	return 1;
    }

    if (living(env))
    {
        env->catch_msg("The aura surrounding the " + shadow_who->short() + 
            " slowly diminishes, also the " + shadow_who->short() +
            " fades out of existence and it gets darker.\n");
	tell_room(E(env), "The aura surrounding the " + shadow_who->short() +
            " that " + QCTNAME(env) + " is holding slowly " +
            "diminishes, also the " + shadow_who->short() + " fades out of " +
            " existence and it gets darker.\n", env);
    } 
    else if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "The aura surrounding the " + shadow_who->short() +
            " slowly diminishes, also the " + shadow_who->short() + 
            " fades out of existence and it gets darker.\n");
    }
    remove_spell_effect_object();
    return 1;
}

void
set_spell_duration(int t)
{
    set_alarm(itof(t), 0.0, &dispel_spell_effect());
}
