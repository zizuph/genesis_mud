/*
 * Implementation of a general harm-type damage spell.  Harm spells do
 * damage to a target directly, simply reducing hit points.  Unlike
 * bolt damage spells, they cannot be dodged.  They use standard
 * resistance rather than basic, though (see resist.c).
 *
 * Inherit this and reconfigure it for your particular harm spell. This
 * harm spell was adapted from /d/Genesis/newmagic/spells/harm.c for
 * the ability-based spell system.
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

inherit SPELL_DIR + "centralized_spell";

#include "centralized_spell_restrictions.h"

// Prototypes
public void resolve_harm_spell(object caster, object *targets, int *resist, int result);

/*
 * Function:    config_harm_spell
 * Description: Config function for harm spells. Redefine this in your
 *              own harm spells to override the defaults.
 */
public void
config_harm_spell()
{
    set_spell_combat_aid(100.0);
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_ability_allow_hunting(1);
    set_spell_offensive(1);    
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({  });
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("harm");
    set_spell_desc("Harm someone");
    set_spell_target(spell_target_one_other_present_living_or_enemy);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_ingredients(query_harm_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(verify_change_enemy);
    
    // We set defaults for the spell element and form here. 
    // Each harm spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);

    set_spell_apply_whitehit_aid(1);
    
    // Call the specific configuration that is to be masked.
    config_harm_spell();
    
    // Call this after the config_harm_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
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

public mixed *
do_harm_damage(object caster, object target, int pen)
{
    return target->hit_me(pen, MAGIC_DT, caster, -1);
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
    string name;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }

    send_debug_message(short(), name + " hits with Pen of " + pen + ", "
      + "Damage of " + damage + " with Resist " + resist + ".");  
}

/* Temp routine to find out why Morgul Spells get no hitresult back
 * occasionally. /Mercade */
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

public void
hook_ability_penetration_modification(object actor, mixed *items, mixed
    *target, int *pen, int *hitloc, int *resist, int *result, int *pdiff)
{
    int* newpdiff = allocate(sizeof(target));
    for (int i = 0; i < sizeof(target); i++)
    {
        int expected = 100 - spell_resist_natural_only(actor, 
            target[i], query_spell_element());
        int actual = 100 - resist[i];
        if (expected == actual)
        {
            newpdiff[i] = 100;
        }
        else if (expected == 0) // 100% resist from AC should be impossible
        {
            newpdiff[i] = 200;
        }
        else
        {
            newpdiff[i] = 100 * (actual) / expected;
        }
    }    
    ::hook_ability_penetration_modification(actor, items, target,
        pen, hitloc, resist, result, newpdiff);
}


static nomask void
resolve_compound_combat_special(object actor, object *targets, int *hitlocs,
    int *random_hitlocs, int *pen, int *damage_types, mixed * items,
    int *resist, int *results)
{
    // Adding this for backwards compatibility, for now..
    if (!sizeof(filter(results, &operator(>)(,0))))
    {
        return ::resolve_compound_combat_special(actor, targets, hitlocs,
                 random_hitlocs, pen, damage_types, items, resist, results);
    }


    resolve_harm_spell(actor, targets, resist, 1);
    // Display the spell being cast

    object enhancer = get_best_spellpower_enhancer(actor);

    if (enhancer)
        hook_enhancer_modified_spell(actor, enhancer, targets);

    desc_harm_cast(actor, targets);    
    
    for(int i = 0; i < sizeof(targets); i++)
    {
        if (results[i] > 0)
        {
            mixed * hitresult = do_harm_damage(actor, targets[i], pen[i]);
        
            // Do some logging
            if (sizeof(hitresult) >= 4)
            {
                /* For some reason hit_me doesn't always come back with a hitresult array,
                * so put it inside this check for now. /Mercade. */
                desc_harm_damage(actor, targets[i], hitresult);
                
                if (enhancer)
                {
                    enhancer->did_spell_hit(-1, hitresult[0], targets[i],
                        query_spell_element(), query_spell_form_needed(), hitresult[2],
                        hitresult[3]);
                }
                
                if (targets[i]->query_hp() <= 0)
                {
                    targets[i]->do_die(actor);
                }

                report_resolve_spell(pen[i], resist[i], hitresult[3]);
            }
            else
            {
                report_no_hitresult("Pen " + pen[i] + " Hitresult " + variable2string(hitresult) +
                    " caster " + actor->query_real_name() + " " + variable2string(actor) +
                    " target " + variable2string(targets[i]));
                actor->catch_tell("The spell backfires.\n");
            }
        }
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
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}
