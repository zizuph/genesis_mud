/*
 * A harm-based spell that damages mana rather than health.
 *
 * Arman, October 2017
 */

#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_harm_mana_spell(object caster, object *targets, int *resist, int result);

#define DEBUG(x)	     find_player("arman")->catch_msg("[Mana drain] " + x + "\n")

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 */
public void
config_harm_mana_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(45.0);
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_offensive(1);    
}


/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_mana_ingredients(object caster)
{
    return ({  });
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("burn");
    set_spell_desc("Burn someone's mana");
    set_spell_target(spell_target_one_other_present_living_or_enemy);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_ingredients(query_harm_mana_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each harm spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
        
    // Call the specific configuration that is to be masked.
    config_harm_mana_spell();
    
    // Call this after the config_harm_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: desc_harm_mana_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                int damage - return value from damage call.
 */
public void
desc_harm_mana_damage(object caster, object target, int damage)
{
    string how;

    switch (damage)
    {
        case 0..10:
            how = "barely drained";
            break;
        case 11..15:
            how = "slightly drained";
            break;
        case 16..25:
            how = "somewhat drained";
            break;
        case 26..35:
            how = "rather drained";
            break;
        case 36..50:
            how = "drained";
            break;
        case 51..85:
            how = "very drained";
            break;
        default:
            how = "extremely drained";
            break;
    }

    target->catch_tell("You feel " + how + ".\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
        how + ".\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how + ".\n",
        target, ({ caster, target }));
}

/*
 * Function name: desc_harm_mana_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_mana_cast(object caster, object *targets)
{
    string msg;

    caster->catch_tell("You channel your power into " + 
        FO_COMPOSITE_ALL_LIVE(targets, caster) + ".\n");

    msg = " extends " + caster->query_possessive() + 
        " clenched fist toward you.\n";
        
    targets->catch_msg(
        ({
        caster->query_Met_name() +  msg, // met message
        capitalize(caster->query_nonmet_name()) + msg, // unmet message
        "" // unseen message
        }) );
                           
    targets->catch_tell("You feel a charge of magical energy surge " +
        "through your body.\n");

    caster->tell_watcher(QCTNAME(caster) + " extends " + 
        caster->query_possessive() + " clenched fist toward " +
        QCOMPLIVE + ".\n", targets, ({ caster }) + targets);
}

public nomask int
do_harm_mana_damage(object caster, object target, int pen)
{
    int phit = pen / 4; 
    phit += random(phit) + random(phit) + random(phit);

    // Because the mana pool is approximately 20-25% smaller 
    // than the health pool, the mana burn damage output
    // is reduced to reflect this, dropping to around quarter
    // of a standard damage harm output.

    int damage = F_NEW_DAMAGE(phit, 0, 0);
    int mana_damage = (damage * 10) / 45;

    DEBUG("Damage: " +damage+ ", Mana damage" +mana_damage);

    return mana_damage;
}

/*
 * Function name: report_resolve_spell
 * Description:   Function called when the ability executes to allow
 *                masking and reporting and logging. By default, it
 *                simply sends the info via send_debug_message
 * Arguments:     pen    - the pen of the hit
 *                resist - the amount of resistance the target has
 *                damage - the amount of damage dealt
 */
public void
report_resolve_spell(int pen, int resist, int damage)
{
    string name, logfile;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }

    logfile = implode(explode(MASTER_OB(this_object()), "/")[..-2], "/") + "/";
    logfile += short() + "_damage";
    logfile = implode(explode(logfile, " "), "");

    setuid();
    seteuid(getuid());
    
    send_debug_message(short(), name + " hits with Pen of " + pen + ", "
      + "Mana drain of " + damage + " with Resist " + resist + ".", logfile);  
}

public void
report_no_hitresult(string text)
{
    string name, logfile;
    
    if (interactive(this_player()))
        name = capitalize(this_player()->query_real_name());
    else
        name = MASTER_OB(this_player());

    logfile = implode(explode(MASTER_OB(this_object()), "/")[..-2], "/") + "/";
    logfile += short() + "_error";
    logfile = implode(explode(logfile, " "), "");

    setuid();
    seteuid(getuid());
    
    send_debug_message(short(), name + " " + text, logfile);
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, object * targets, int * resist, int result)
{
    resolve_harm_mana_spell(caster, targets, resist, result);

    // Display the spell being cast
    desc_harm_mana_cast(caster, targets);
    
    // Inflict the harm mana spell on each target
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        if (target->query_not_attack_me(caster, -1))
        {
            // query_not_attack_me is used by evade abilities such as the "blink" spell
            // AA's shield cover, and pirate's stagger.
            continue;
        }
        DEBUG("Target: " +target->short()+ ".");

        int pen = calculate_pen(resist[index]);
        DEBUG("Pen: " +pen+".");

        int mana_drain = do_harm_mana_damage(caster, target, pen);

        target->add_mana(-mana_drain);
        DEBUG("Drained " +mana_drain+".");
        desc_harm_mana_damage(caster, target, mana_drain);
        report_resolve_spell(pen, resist[index], mana_drain);

    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_mana_spell(object caster, object *targets, int *resist, int result)
{
}
