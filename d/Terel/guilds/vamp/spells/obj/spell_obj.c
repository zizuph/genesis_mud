
#include "../../defs.h"

inherit CORELIB_DIR+"spell_effect_object";

int Cancelled=0;
int Warning_alarm=0;

public int stop(string arg);


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

public void warn_fading()
{
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
