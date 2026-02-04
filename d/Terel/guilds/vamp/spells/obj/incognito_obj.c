
#include "../../guild.h"

inherit "/std/object";
inherit SPELLOBJ_DIR+"spell_obj";

#include <stdproperties.h>
#include <macros.h>

public void create_object()
{
    set_name("_incognito_obj");
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Spell object for the incognito spell\n");

    set_spell_effect_desc("alter your appearance");
    set_no_show();

}

varargs public int
dispel_spell_effect(object dispeller)
{
	
	if (query_effect_target()->query_incognito())
    {
	
	    query_effect_target()->set_incognito(0);
	
        query_effect_target()->catch_tell("The illusion is broken, and "+
        "your true form is once again revealed.\n");

        object * watchers=WATCHERS(query_effect_caster())-
            ({ query_effect_caster() });
    
        watchers->catch_msg(QCTNAME(query_effect_caster()) + " looks a " 
            + "little hazy for a moment.\n");
    }

    remove_spell_effect_object();
    return 1;
}

public void warn_fading()
{
    query_effect_caster()->catch_tell("Your true form starts to show.\n");
}


public int
start()
{

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }
    
    move(query_effect_target(),1);

    query_effect_target()->catch_msg("You focus your mind on masking "+
    "your identity, changing the look of your various features.\n");

    object * watchers=WATCHERS(query_effect_caster())-
            ({ query_effect_caster() });
    
    watchers->catch_msg(QCTNAME(query_effect_caster()) + " looks a " 
        + "little hazy for a moment.\n");
    
    query_effect_target()->set_incognito(1);

    int delay=max(1500,query_effect_target()->query_vamp_stat()*45);
    
    //Lasts 25-120 minutes
    delay=min(delay,60*120);

    set_dispel_time(delay);


    return 1;
}

public void init()
{
    ::init();
    add_action(stop,"stop");
}
