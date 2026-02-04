
#include "../../guild.h"

inherit "/std/object";
inherit SPELLOBJ_DIR+"spell_obj";

#include <stdproperties.h>
#include <macros.h>

int Dlevel;

public void create_object()
{
    
    set_name("_sight_obj");
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Object providing dark vision.\n");

    
    set_spell_effect_desc("see in the dark");
    set_no_show();

}

varargs public int
dispel_spell_effect(object dispeller)
{

    effect_target->catch_tell("The clarity of your vision fades.\n"); 

    if (effect_target!=effect_caster && effect_caster && effect_target &&
        ENV(effect_target)==ENV(effect_caster))
    {
        effect_caster->catch_msg("You sense a weakening in the vision "+
        "of "+QTNAME(effect_target)+".\n");
    }
	
    effect_target->change_prop(LIVE_I_SEE_DARK,
        effect_target->query_prop(LIVE_I_SEE_DARK) - Dlevel);
    
    remove_spell_effect_object();
    return 1;
}

public void warn_fading()
{
    effect_target->catch_tell("The clarity of your vision blurs "+
    "for a moment.\n");
}


public int
start()
{

    if (!::start() || move(effect_target,1))
    {
        remove_spell_effect_object();
        return 0;
    }

    int delay=max(240,effect_target->query_vamp_stat()*30);

    delay=min(1800,delay);

    if (effect_target!=effect_caster)
    {
        delay=min(1800,delay);
        //5-7 levels, 30 minute max
        Dlevel=5+random(3);
        effect_target->catch_msg(
            "You feel a presence penetrating your thoughts, delving deep "+
            "into your mind, followed by a feeling of blood rushing to "+
            "the back of "+
            "your eyes. You blink, and everything seems to be more in "+
            "focus.\n");
        effect_caster->catch_msg(
            "Using the mind gift, you focus the mind of "+
            QTNAME(effect_target)+", helping "+OBJ(effect_target)+
            " achieve further clarity of vision.\n");
    }
    else
    {
        //5-15 levels, 55 minute max
        Dlevel=5+random(11);
        effect_target->catch_msg(
            "You feel blood rush to the back of your "+
            "eyes as you reach further clarity of vision.\n");
    }
    effect_target->add_prop(LIVE_I_SEE_DARK,
        effect_target->query_prop(LIVE_I_SEE_DARK) + Dlevel);

    set_dispel_time(delay);
    return 1;
}

public void init()
{
    ::init();
    add_action(stop,"stop");
}

