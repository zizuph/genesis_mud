/*
* Vampires Evade Shield Spell Object 
*
*
* Originaly created by Petros, March 2010, used by Nerull 2021
*/
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/evade_obj";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "../../guild.h"

/*
* Function:    create_spell_object
* Description: Override this to customize properties for the spell object
*/
public void
create_spell_object()
{
    set_name("_elusiveness_object");
    set_short("elusiveness object");
    set_long("This is the elusiveness object. It provides "
        + "the caster with an evade effect.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
        "created by the elusiveness spell.\n");
        
    set_spell_effect_desc("Elusiveness");
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
        target->catch_tell("The blood infuses you with enhanced level "
        +"of evasion.\n");
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
        target->catch_tell("You feel your enhancement of additional "
        +"evasion fades away.\n");  
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
        target->catch_tell("You feel Elusiveness is starting "
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
            + "the Elusiveness spell.\n");
    }
}


/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person has a beating heart now
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (interactive(to))
    {
        //to->add_subloc(EVADE_SUBLOC, this_object());        
    }
}


/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    
    if (interactive(old))
    {
        //old->remove_subloc(EVADE_SUBLOC);
    }
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
        + attacker->query_possessive() + " attack due to your "
        +"preternatural speed.\n");
        
    attacker->catch_msg("You miss " + QTNAME(player) + " with your "
        + "attack as " + player->query_pronoun() + " quickly evades "
        +"it due to "+ player->query_possessive() +" preternatural speed.\n");
        
    tell_room(environment(player), QCTNAME(attacker) + " misses "
        + QTNAME(player) + " with " + attacker->query_possessive()
        + " attack as " + QTNAME(player) + " quickly evades it due to "
        + player->query_possessive() +" preternatural speed.\n",
        ({ player, attacker }), player);
}