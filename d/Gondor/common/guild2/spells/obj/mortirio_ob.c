/*
 *      /d/Gondor/common/guild2/spells/obj/mortirio_object.c
 *
 *      Copyright (c) 1997 by Christian Markus
 *
 *      Olorin, February 1997
 */
#pragma strict_types

inherit "/std/object.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

public string  wizinfo();

int     Strength = 5,
        Alarm_Id;

public void
create_object()
{
    set_name("Morgul_Mortirio_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(MAGIC_I_RES_POISON, 100);
    add_prop(MAGIC_I_RES_MAGIC,  100);
    add_prop(MAGIC_I_RES_MAGIC,   50);
    add_prop(OBJ_I_RES_POISON,   100);
    add_prop(OBJ_I_RES_MAGIC,    100);
    add_prop(OBJ_I_RES_MAGIC,     50);

    add_prop(OBJ_S_WIZINFO, wizinfo);

    set_no_show();
}

public void
set_strength(int i)
{
    Strength = i;
    if (Strength > 5)
        Strength = 5;
}

static void
end_mortirio()
{
    int     value;
    object  env;
    string  mess = " stop glowing like red coals.\n";

    // We check MORGUL_O_MORTIRIO_OBJECT to prevent double removal:
    if (objectp(env = ENV(TO)) && living(env) && 
        (env->query_prop(MORGUL_O_MORTIRIO_OBJECT) == TO))
    {
        env->catch_tell(
            "You feel that your vision becomes normal again.\n");

        tell_room(env, ({
            env->query_name()+"'s eyes" + mess,
            "The eyes of the "+env->query_nonmet_name()+mess, "" }),
            env, env);

        value = env->query_prop(LIVE_I_SEE_DARK) - Strength;
        if (value)
            env->change_prop(LIVE_I_SEE_DARK, value);
        else
            env->remove_prop(LIVE_I_SEE_DARK);
 
        value = env->query_prop(LIVE_I_SEE_INVIS) - 1;
        if (value)
            env->change_prop(LIVE_I_SEE_INVIS, value);
        else
            env->remove_prop(LIVE_I_SEE_INVIS);
 
       env->remove_prop(MORGUL_O_MORTIRIO_OBJECT);
    }
    set_alarm(1.0, 0.0, remove_object);
}

public void
set_duration(int i)
{
    object  env;

    if (!objectp(env = ENV(TO)) || !living(env))
        return;

    if (Alarm_Id)
        remove_alarm(Alarm_Id);
    Alarm_Id = set_alarm(itof(i), 0.0, end_mortirio);

    env->change_prop(LIVE_I_SEE_DARK,  env->query_prop(LIVE_I_SEE_DARK) + Strength);
    env->change_prop(LIVE_I_SEE_INVIS, env->query_prop(LIVE_I_SEE_INVIS) + 1);
    env->add_prop(MORGUL_O_MORTIRIO_OBJECT, TO);
}

static float
query_mortirio_time_left()
{
    mixed   arr;

    if (Alarm_Id && sizeof(arr = get_alarm(Alarm_Id)))
        return arr[2];
    return -1.0;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    set_alarm(1.0, 0.0, end_mortirio);
}

public string
wizinfo()
{
    return "The spellobject for the 'mortirio' spell of the Morgul Mages.\n" +
        "Permits seeing in darkness and seeing invisible objects.\n" +
        "LIVE_I_SEE_DARK  :  " + Strength + ",\n" +
        "LIVE_I_SEE_INVIS :  1,\n" +
        "The effect will end in " +query_mortirio_time_left()+ " seconds.\n";
}

