
/*
 *  Created by Carnak, February 2017
 *  Modified by Mirandus to work as an alarm object shadow - Feb 2017
 */


inherit "/std/shadow";

#include <macros.h>

public object caster;

public int
query_is_shadowed_by_alarm()
{
    return 1;
}

public int
remove_alarm_shadow()
{
    remove_shadow();
}

public object
set_caster(object spellcaster)
{
    caster = spellcaster;
}    

void
alarm_disturbed(object ob)
{   
    if (ob != caster)
    { 
        if (interactive(ob))
        {        
            if (caster->query_met(ob))
            {
                caster->catch_tell(capitalize(ob->query_real_name())+
                    " has disturbed your alarm.\n");
            }
            else
            {
                caster->catch_tell(ob->query_Art_name(caster)+
                    " has disturbed your alarm!\n");
            }
        }
        else
        {
            string short = ob->query_Art_name(caster);
            if (!short)
                caster->catch_tell("Something has disturbed your alarm!\n");
            else
                caster->catch_tell(short+" has disturbed your alarm!\n");
        }
    }
}

public void
enter_inv(object ob, object from)
{
    shadow_who->enter_inv(ob, from);
    set_alarm(0.0, 0.0, &alarm_disturbed(ob));
}