/*
 * Alarm Object - based on the Standard Blind Object
 *
 * This object notifies the caster if anyone enters the
 * room this is located in.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Jaacar, February 2017.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";

#define ALARM_SHADOW     ELEMENTALIST_SPELL_OBJS + "tromazo_shadow.c"

private string caster_name;
private object alarm_shadow;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_alarm_spell_object_");
    set_short("alarm spell object");    
    set_long("This is the standard alarm spell object.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the alarm spell.\n");
    set_spell_effect_desc("alarm");
        
    set_dispel_time(600);  
}

public void
set_caster_name(string str)
{
	caster_name = str;
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }
    
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }

    return 1;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object caster = query_spell_effect_caster();    
       
    alarm_shadow = clone_object(ALARM_SHADOW);
    alarm_shadow->set_caster(caster);
    alarm_shadow->shadow_me(environment(caster));
    
    if (objectp(caster))
    {
        caster->catch_msg("You have summoned an alarm to this location.\n");
    }       
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object caster = query_spell_effect_caster();
    
    alarm_shadow->remove_alarm_shadow();
    
    if (objectp(caster))
    {
        caster->catch_msg("The alarm you placed has faded.\n");
    }
}
