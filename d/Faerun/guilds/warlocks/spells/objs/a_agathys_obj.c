/*
 * Warlock Evade Shield Spell Object 
 *
 * Originaly created by Petros, March 2010, used by Nerull 2017
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "../../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/evade_obj";

/*
* Function:    create_spell_object
* Description: Override this to customize properties for the spell object
*/
public void
create_spell_object()
{
    set_name("_agathys_shield_object");
    set_short("agathys shield object");
    set_long("This is the Armor of agathys shield object. It provides "
        + "the caster with an evade effect.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
        "created by the Armor of Agathys shield spell.\n");
        
        set_spell_effect_desc("Armor of Agathys");
}


/*
* Function:    hook_spell_effect_started
* Description: Override this to customize the message when this spell effect
*              is added to th target.
*/
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("A spectral frost forms and surround your body.\n");
        
        tell_room(environment(target), QCTNAME(target) + " is suddenly surrounded "
        + "by a layer of spectral frost.\n", ({ target }));
        
        target->add_prop(SHIELD_ON, 1);
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
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your Viehra dissipates.\n");  
        
        tell_room(environment(target), QCTNAME(target) + " is no longer " 
        +"covered by spectral frost.\n", ({ target }));
        
        target->remove_prop(SHIELD_ON);
    }
}


/*
* Function:    hook_spell_effect_warn_fading
* Description: Override this to customize the message for when
*              the effect has only a minute left.
*/
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel Viehra is starting "
        +"to fade.\n");
    }
}


/*
* Function:    hook_spell_effect_not_maintained
* Description: Override this to describe the effect when the caster
*              cannot maintain the effect.
*/
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();

    if (objectp(caster))
    {
        caster->catch_tell("Mentally drained, you lose control of "
            + "the viehra spell.\n");
    }
}


/*
* Function:    query_evade_subloc_description
* Description: When someone examines a person with this spell effect,
*              they will see whatever is returned by this function.
*/
public string
query_evade_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are surrounded by spectral frost.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrounded by "
        + "spectral frost.\n";
}


/*
* Function     : hook_describe_evade_effect
* Description  : Function to display messages that the attack was
*                blocked.
* Arguments    : player    - player who is being attacked
*                attacker  - the person doing the attacking
*                attack_id - attack id location
* Returns      : nothing
*/
public void
hook_describe_evade_effect(object player, object attacker, int attack_id)
{
    player->catch_msg(QCTNAME(attacker) + " misses you with "
        + attacker->query_possessive() + " attack as the spectral "
        +"frost surrounding your body mitigates the blow entirely.\n");
        
    attacker->catch_msg("You miss " + QTNAME(player) + " with your "
        + "attack as the spectral frost "
        + "surrounding " + player->query_objective() + " mitigates "
        +"the blow entirely.\n");
        
    tell_room(environment(player), QCTNAME(attacker) + " misses "
        + QTNAME(player) + " with " + attacker->query_possessive()
        + " attack as the spectral frost "
        + "surrounding " + QTNAME(player) + " mitigates the blow "
        +"entirely.\n",
        ({ player, attacker }), player);
}