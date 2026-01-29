
inherit "/std/object";
inherit "/d/Genesis/specials/spell_effect_object";

#include "../../guild.h"





#include <stdproperties.h>
#include <macros.h>

int Cancelled=0;
int Warning_alarm=0;

public int stop(string arg);

public void warn_fading();

public void create_object()
{
    set_name("_incognito_obj");
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Spell object for the incognito spell\n");

    set_spell_effect_desc("alter your appearance");
    set_no_show();

}


public int stop(string arg)
{
    if (this_player()!=query_effect_caster())
    {
        return 0;
    }
    if (Cancelled)
    {
        return 0;
    }
    if (arg==query_spell_effect_name() ||
        "v"+arg==query_spell_effect_name())
    {
        write("You stop focusing on your ability to "+
        query_spell_effect_desc()+".\n");
        Cancelled=1;
        set_alarm(0.1,0.0,&dispel_effect(this_player()));
        return 1;
    }
    return 0;
}


/*
 * Function name: set_dispel_time
 * Description;   Creates a timer that will dispel the effect
 * Arguments:     i - number of seconds before the effect vanishes                
 * Returns:       none
 */
public void set_dispel_time(int i)
{
    ::set_dispel_time(i);
    if (Warning_alarm)
    {
        remove_alarm(Warning_alarm);
        Warning_alarm=0;
    }
    if (i>240)
    {
        alarm_id=set_alarm(itof(i-240),0.0,warn_fading);
    }
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
