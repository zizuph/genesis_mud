/*
 * Implementation of a general at-will damage spell. See inherit file for
 * details on harm spell.
 *
 * Inherit this and reconfigure it for your particular at-will spell.
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"

inherit SPELL_DIR + "harm";

#define MAX_ATWILL_CAID     60.0

/*
 * Function:    config_at_will_spell
 * Description: Config function for at will damage spells. Redefine this in your
 *              own at will spells to override the defaults.
 */
public varargs void
config_at_will_spell()
{
    set_spell_combat_aid(MAX_ATWILL_CAID);
}

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells.
 */
public nomask void
config_harm_spell()
{
    set_spell_name("atwill");
    set_spell_desc("At-Will Harm");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    //This will affect spell timings, and whitehit bonus.    
    set_spell_at_will(1);
    config_at_will_spell();
    
    // Reset this afterwards to prevent others from modifying it.
    set_spell_at_will(1);
    int max = ftoi(MAX_ATWILL_CAID);
    if (query_spell_apply_whitehit_aid())
    {
        max += query_white_hit_combat_aid();
    }
    if (ftoi(query_spell_combat_aid()) >= max)
    {
        // At Will Spells have a maximum combat aid of MAX_ATWILL_CAID. This will
        // be enforced in this code.
        set_spell_combat_aid(MAX_ATWILL_CAID);
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    hook_special_complete
 * Description: Override this to print out the message players will see
 *              when they can use their at will spell again.
 */
public void 
hook_special_complete()
{
    write("You feel ready to cast " + short() + " again.\n");
}

/*
 * Function:    hook_special_in_cooldown
 * Description: Override this to print out the message players will see
 *              when they cannot yet use their at will spell.
 */
public void
hook_special_in_cooldown()
{
    write("You are still gathering yourself from your last "
        + "casting of " + short() + "\n");
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
    ::resolve_harm_spell(caster, targets, resist, result);
}

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object *targets)
{
    ::desc_harm_cast(caster, targets);
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    ::desc_harm_damage(caster, target, result);
}

/*
 * Function:    recast_spell
 * Description: Called via alarm in restart_npc_special. Because it's
 *              an alarmed function, we need to set the this_player
 *              context correctly.
 */
public void
recast_spell(object player, string arg)
{
    object oldtp = this_player();
    set_this_player(player);
    do_ability(arg);
    set_this_player(oldtp);
}

/*
 * Function:    restart_npc_special
 * Description: At will harm spells are like fighter specials. When testing
 *              them, we want it to trigger as soon as it finishes.
 */
public void
restart_npc_special(object player, string arg)
{
    if (query_ability_time() > 0)
    {
        set_alarm(0.0, 0.0, &recast_spell(player, arg));
    }
}
