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

#include "defs.h"

inherit "/d/Genesis/specials/std/spells/obj/spell_obj_base";


public int
query_variable_dispel_time()
{
    int result = 30;
    object caster = query_spell_effect_caster();
    if (caster)
    {
        if (caster->is_elemental_racial_cleric)
        {
            if (caster->query_prop(CONDUIT_PENALTY) == 3)
        		result = 20;
        	else
        		result = 40;
        }
        else
        {
            if (caster->query_prop(CONDUIT_PENALTY) == 3)
        		result = 15;
        	else
        		result = 30;
        }
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

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    string partner_name;
    object partner;
    
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    if (caster)
    {
        partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
        partner = find_player(partner_name);
    }
    
    if (objectp(target))
    {
        target->catch_tell("You feel a sharp pain in your eyes.\nYou have "+
            "been blinded!\n");
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " has been blinded!\n");
        partner->catch_msg(QCTNAME(target) + " has been blinded!\n");
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
    string partner_name;
    object partner;
    
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    
    if (caster)
    {
        partner_name = GUILD_MANAGER->query_current_syndyasmos_partner(caster);
        partner = find_player(partner_name);
    }

    if (objectp(target))
    {
        target->catch_tell("The pain in your eyes subside.\n");
    }

    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " blinks a few times and seems "
            + "to be able to see again.\n");
        partner->catch_msg(QCTNAME(target) + " blinks a few times and seems "
            + "to be able to see again.\n");
    }
}
