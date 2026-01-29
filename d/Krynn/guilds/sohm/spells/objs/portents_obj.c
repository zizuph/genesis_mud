/*
 * Standard Magical Evade Object
 *
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "evade_obj";

#define SOHM_PORTENTS_EFFECT "_sohm_portents_and_omens_effect"

// Prototypes
public void         hook_describe_evade_effect(object player, object attacker, int attack_id);

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_portents_object_");
    set_short("portents spell object");    
    set_long("This is the portents and omens spell's object. It allows casters to "
        + "divine and dodge a certain amount of hits.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the portents and omens spell.\n");
    set_spell_effect_desc("portents and omens");    
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your eyes open, overlayed with the future combat " +
            "events to happen before you.\n");
        tell_room(environment(target), QCTPNAME(target) + " eyes open, "
            + "calm and knowing, as if future events were displayed before " +
           HIM(target)+".\n", ({ target }));
    } 

    target->add_prop(SOHM_PORTENTS_EFFECT, 1);   
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

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("You blink, and the future is no longer as certain or clear as it " +
            "was before.\n");
    }

    target->remove_prop(SOHM_PORTENTS_EFFECT);
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
        target->catch_tell("You feel your portents and omens divination is about to wear off.\n");
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
        caster->catch_tell("You are mentally unable to maintain "
            + "the portents and omens spell.\n");
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
        return  "You are maintaining a divination providing you with portents " +
                "and omens about your enemies.\n";
    else
        return "";

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
    player->catch_msg("You divine " +QTPNAME(attacker) + " attack, easily " +
           "avoiding " +HIM(attacker)+ ".\n");
    attacker->catch_msg(QCTNAME(player)+" preternaturally anticipates your " +
           "attack, avoiding you easily.\n");
    tell_room(environment(player), QCTNAME(player) + " preternaturally anticipates "
            + QTPNAME(attacker) + " attack, easily avoiding " +HIM(attacker)+ ".\n", 
            ({ player, attacker }), player);
}
