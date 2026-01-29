/*
 * Standard Blind Object
 *
 * This is the spell object for the standard Genesis Magic System's
 * blind spell. It blinds the target for a limited duration.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Navarre, March 2010.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <time.h>

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";


public int
query_variable_dispel_time()
{
    int result = 25;
    object caster = query_spell_effect_caster();
    if (caster)
    {
        if (caster->query_prop(CONDUIT_PENALTY) == 3)
        	result = 12;
    	else
    		result = 25;
    }
    
    return result;
}

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_blind_object_");
    set_short("blind spell object");    
    set_long("This is the standard blind spell object. " +
             "It blinds the target.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the blind spell.\n");
    set_spell_effect_desc("blind");
    
    set_dispel_time(query_variable_dispel_time());
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

    query_effect_target()->inc_prop(LIVE_I_BLIND);
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
    
    query_effect_target()->dec_prop(LIVE_I_BLIND);
    return 1;
}

public void
remove_perika_alarm(object caster)
{
	int cooldown = caster->query_prop(LIVE_I_PERIKA_CAST);
    if (cooldown) 
    {
    	if (cooldown < time())
    	{
	    	caster->catch_msg("You feel ready to use the powers of "+
	    		"Perika again.\n");
	    }
    }
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    int cooldown = time() + 60;    
    
    if (objectp(target))
    {
        target->catch_tell("Your eyes begin to burn profusely.\nYou have "+
            "been blinded!\n");
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " has been blinded!\n");
        set_alarm(60.0, 0.0, &remove_perika_alarm(caster));
    	caster->add_prop(LIVE_I_PERIKA_CAST, cooldown);
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
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    
    if (objectp(target))
    {
        target->catch_tell("Your eyes stop burning and you can see again.\n");
    }

    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " blinks a few times and seems "
            + "to be able to see again.\n");
    }
}
