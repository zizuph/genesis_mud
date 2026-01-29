/*
 * Implementation of a multiple target / all enemy harm spell.
 * This spells infliect damage to the targets directly, reducing hit points
 * and cannot be dodged.
 * The spell uses standard resistance rather than basic, see resist.c.
 *
 * Created by Navarre, January 2010 - Based on Petros' harm spell.
 * 
 * Modifications:
 *
 * Rebalanced by limiting the damage and increasing mana cost based on the
 * amount of targets.
 * Functions set_spell_restrict_targets and set_spell_target_limit were added
 * to handle damage dispersion and mana cost.
 *
 */
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/harm";

static mapping  enemies = ([]);
static int      restrict_targets,
                target_limit;

/*
 * Function name:   query_spell_restrict_targets
 * Description:     Returns the restriction for targets.
 * Arguments:       None
 * Returns:         (int) - Restriction value for targets.
 */
public int
query_spell_restrict_targets()
{
    return restrict_targets;
} /* query_spell_restrict_targets */

/*
 * Function name:   set_spell_restrict_targets
 * Description:     Sets the amount of targets at which we stop the dispersion
 *                  of damage, this should probably not be set below the set
 *                  target_limit, unless set to 0. Setting this value to 0 means
 *                  that it spreads the damage over all the present targets.
 * Arguments:       (int) value - Number of restricted targets
 * Returns:         Nothing
 */
public void
set_spell_restrict_targets(int value)
{
    restrict_targets = value;
} /* set_spell_restrict_targets */

/*
 * Function name:   query_spell_target_limit
 * Description:     Returns the set target limit.
 * Arguments:       None
 * Returns:         (int) - Number of target_limit
 */
public int
query_spell_target_limit()
{
    return target_limit;
} /* query_spell_target_limit */

/*
 * Function name:   set_spell_target_limit
 * Description:     This is a multiplier for the pen value, which in turn is
 *                  then divided by the number of enemies and capped at pen.
 * Arguments:       (int) limit - The target limit
 * Returns:         Nothing
 */
public void
set_spell_target_limit(int limit)
{
    target_limit = limit;
} /* set_spell_target_limit */

/*
 * Function:    config_massharm_spell
 * Description: Config function for the mass harm spell.
 */
public void
config_massharm_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(100.0);
}

/*
 * Function:    query_massharm_ingredients
 * Description: This function defines what components are required for
 *              this massharm spell.
 */
public string *
query_massharm_ingredients(object caster)
{
    return ({ });
}

public nomask void
config_harm_spell()
{
    set_spell_name("massharm");
    set_spell_desc("Harm all enemies");

    set_spell_task(TASK_HARD);
    set_spell_ingredients(query_massharm_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each massharm spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    
    /* Limit spell targets */
    set_spell_target_limit(3);
    /* Restrict damage to only this amount of targets */
    set_spell_restrict_targets(5);
    
    // Call the specific configuration that is to be masked.
    config_massharm_spell();
    
    set_spell_target(spell_target_present_enemies);
    set_spell_mana_factor(0.4 + (itof(target_limit) * 0.8));
}

public void
hook_attack_object(object ob)
{
    // Masking this so that you won't see many attack messages
    // when it would attack multiple targets, if already attacking.
    if (IN_ARRAY(ob, this_player()->query_enemy(-1)))
    {
        return;
    }
    ::hook_attack_object(ob);
}

public void
hook_no_present_targets(object actor, string str)
{
    actor->catch_msg("You are not in combat and therefore have no enemies.\n");
}



public nomask object *
spell_target_present_enemies(object actor, string str)
{
    enemies[actor] = (object *)actor->query_enemy(-1) &
                     all_inventory(environment(actor));

    object * teammates = actor->query_team_others();

    if (sizeof(teammates) > 0)
    {
        foreach(object mate: teammates)
        {
            enemies[actor] += (object *)mate->query_enemy(-1) &
                     all_inventory(environment(mate));
        }
    }
    
    /* Restricting the targets based on preset values */
    if (restrict_targets && sizeof(enemies[actor]) > restrict_targets)
        enemies[actor] = exclude_array(enemies[actor],
                                       restrict_targets,
                                       sizeof(enemies[actor]) - 1);
    
    if (!sizeof(enemies[actor]))
    {
        hook_no_present_targets(actor, str);
        return ({});
    }
    
    return enemies[actor];
}

public mixed *
do_massharm_damage(object caster, object target, int pen)
{
    return target->hit_me(pen, MAGIC_DT, caster, -1);
}

public nomask mixed *
do_harm_damage(object caster, object target, int pen)
{
    send_debug_message("new_massharm", "Before Pen: " + pen);
    if (sizeof(enemies[caster]))
        pen = min(pen, (pen * target_limit) / sizeof(enemies[caster]));
    send_debug_message("new_massharm", "After Pen: " + pen);
    
    return do_massharm_damage(caster, target, pen);
}

