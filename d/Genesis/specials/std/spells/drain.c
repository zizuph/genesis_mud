/*
 * Filename: drain.c
 * Description: This is an adaptation of the harm spell to allow for an easy
 *              drain implementation. The drain is based on a % value of the
 *              total pen. So 1% drain = 0.5% of the total pen where as 100%
 *              drain = 50% of the pen. The healed value is taken out of the
 *              damage when returned after randomizing it.
 *              The formula for reducing the pen is:
 *                  pen - (pen * %heal) / 200
 *              The formula to recalculate the heal is:
 *                  damage * %heal / (200 - %heal)
 *              This makes sure that the heal is always accurate percentage
 *              of the damage done.
 *
 * Created by Carnak at 2018-01-24
 */
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/harm";

/* Global Variables */
static int drain_percentage;


/*
 * Function name:   query_drain_percentage
 * Description:     Returns the drain percentage.
 * Arguments:       None
 * Returns:         (int) - The percentage of the heal
 */
public int
query_drain_percentage()
{
    return drain_percentage;
} /* query_drain_percentage */

/*
 * Function name:   set_drain_percentage
 * Description:     Sets the drain percentage.
 * Arguments:       (int) drain - The percentage of the damage we wish to drain. 
 * Returns:         Nothing
 */
public void
set_drain_percentage(int drain)
{
    drain_percentage = min(100, max(1, drain));
} /* set_drain_percentage */

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public nomask void
desc_harm_damage(object caster, object target, mixed *result)
{
    /* Masked for the good of man-kind */
} /* desc_harm_damage */

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_drain_damage(object caster, object target, mixed *result, int healing)
{
    string how;

    switch (result[3])
    {
        case 0..20:
            how = "barely hurt";
            break;
        case 21..50:
            how = "slightly hurt";
            break;
        case 51..80:
            how = "somewhat hurt";
            break;
        case 81..110:
            how = "rather hurt";
            break;
        case 111..140:
            how = "hurt";
            break;
        case 141..170:
            how = "very hurt";
            break;
        default:
            how = "extremely hurt";
            break;
    }

    target->catch_tell("You feel " + how + ".\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
        how + ".\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how + ".\n",
        target, ({ caster, target }));
    
    if (healing)
    {
        target->catch_msg("Your health has been siphoned by " + QTNAME(caster)
        + ".\n");
        caster->catch_msg("You feel healthier.\n");
        caster->tell_watcher(QCTNAME(caster) + " looks healthier.\n",
        ({ target }));
    }
} /* desc_drain_damage */

/*
 * Function name:   query_drain_percentage
 * Description:     Returns the drain percentage.
 * Arguments:       None
 * Returns:         (int) - The percentage of the heal
 */
public mixed *
do_harm_damage(object caster, object target, int pen)
{
    mixed  *result;
    int     original_pen, healing,
            damage;
    
    original_pen = pen;
    /* Calculate the modified pen based on the % of the spell meant to deal
       damage */
    pen -= (pen * drain_percentage) / 200;
    
    /* Deal damage to get a result */
    result = target->hit_me(pen, MAGIC_DT, caster, -1);
    damage = result[3];
    
    if (damage > 0)
    {
        /* Modify the healing back to its correct percentage */
        healing = (result[3] * drain_percentage) / (200 - drain_percentage);
        healing = min(healing, caster->query_max_hp() - caster->query_hp());
        /* Heal the caster */
        caster->heal_hp(healing);
    }
    
    desc_drain_damage(caster, target, result, healing);
    send_debug_message("drain_spell", "Original Pen: " + original_pen
    + " Modified pen: " + pen + " Damage: " + damage + " Healing: " + healing);
    /* Return the result of the hit_me */
    return result;
} /* do_harm_damage */

/*
 * Function:    config_drain_spell
 * Description: Config function for the drain spell.
 */
public void
config_drain_spell()
{
} /* config_drain_spell */

/*
 * Function:    query_drain_ingredients
 * Description: This function defines what components are required for
 *              this drain spell.
 */
public string *
query_drain_ingredients(object caster)
{
    return ({ });
} /* query_drain_ingredients */

/*
 * Function:    config_harm_spell
 * Description: Config function for the harm spell.
 */
public nomask void
config_harm_spell()
{
    set_spell_name("drain");
    set_spell_desc("drain an enemies");

    set_spell_target(spell_target_one_other_present_living_or_enemy);

    set_spell_task(TASK_HARD);
    set_spell_ingredients(query_drain_ingredients);
    
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each drain spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(100.0);
    
    set_drain_percentage(100);
    
    // Call the specific configuration that is to be masked.
    config_drain_spell();    
} /* config_harm_spell */