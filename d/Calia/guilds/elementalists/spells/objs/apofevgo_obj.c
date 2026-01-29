/*
 * Standard Magical Evade Object
 *
 * This is the spell object for the standard Genesis Magic System Evade
 * spell. When started, this spell object clones the evade
 * effect to essentially provide evade protection based on the combat aid
 * specified by the spell.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, March 2010
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <tasks.h>
#include "defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "evade_obj";

#define EC_EVADE_EFFECT "_ec_evade_effect"

// Prototypes
public void hook_describe_evade_effect(object player, object attacker, int attack_id);

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_evade_object_");
    set_short("evade spell object");    
    set_long("This is the standard evade spell's object. It allows casters to "
        + "dodge a certain amount of hits.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the evade spell.\n");
    set_spell_effect_desc("evade");    
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
        target->catch_tell("A thin layer of air begins to flow around you " +
            "making it more difficult for an opponent to hit you.\n");
        tell_room(environment(target), QCTNAME(target) + " is surrouned by "+
            "a thin layer of air.\n", ({ target }));
    } 

    target->add_prop(EC_EVADE_EFFECT, 1);   
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
        target->catch_tell("The thin layer of air surrounding you "+
            "dissipates.\n");
        tell_room(environment(target), "The thin layer of air surrounding "+
            QTNAME(target) + " dissipates.\n", ({ target }));
    }

    target->remove_prop(EC_EVADE_EFFECT);
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
        target->catch_tell("You feel the thin layer of air surrounding "+
            "you become weaker as the apofevgo prayer begins to wear off.\n");
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
            + "the apofevgo prayer.\n");
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
        return  "You are surrounded by a thin layer of air.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrouned "+
            "by a thin layer of air.\n";

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
        + attacker->query_possessive() + " attack as the thin layer of "+
        "air surrounding you pushes it away from you.\n");
    attacker->catch_msg("The thin layer of air surrounding "+QTNAME(player)+
        " causes you to miss your attack by pushing it away.\n");
    tell_room(environment(player), QCTNAME(attacker) + " tries to "
            + "attack " + QTNAME(player) + ", but the attack misses as "
            + "the thin layer of air surrounding "+QTNAME(player) + 
            " pushes it away.\n", 
            ({ player, attacker }), player);
}
