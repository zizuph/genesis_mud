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

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "blind_obj";

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_blind_begin(object caster, object target, object *effects)
{
    string partner_name;
    object partner;
    
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
hook_blind_ended(object caster, object target, object *effects)
{
    string partner_name;
    object partner;
    
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

public void 
hook_blind_failed(object actor, object target)
{
    actor->catch_msg(QCTNAME(target) + " does not seem to be affected.\n");
}

