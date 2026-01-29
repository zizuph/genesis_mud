/*
 *  faerun/underdark/upper/menzo/sorcere/obj/acid_bolt.c
 *
 *  An Acid Bolt spell used by drows in Underdark
 *
 *  Created by Midnight, 18-2-2004
 */


inherit "/d/Genesis/newmagic/spells/bolt";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "/std/combat/combat.h"
#include "defs.h"
#include "/d/Faerun/defs.h"

#define MANA_COST 50
#define ACIDBOLT_BASE_PEN 400

// Prototypes
object *acidbolt_target(object caster, string str);
int spell_resist_acidbolt(object caster, object target, int element,
    int difficulty);

public void
create_bolt()
{
    set_spell_time(5);
    set_spell_mana(MANA_COST);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_WATER, 60);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_bolt_desc("acid");
    set_bolt_pen(ACIDBOLT_BASE_PEN);
    set_spell_name("acidbolt");
    set_spell_desc("Summon an acid bolt directed at target, " +
        "splashes hit nearby people.");

    // Use our own targeting routine
    set_spell_target(acidbolt_target);
    set_spell_resist(spell_resist_acidbolt);
}

object *acidbolt_target(object caster, string str)
{
    object *obs, *others;

    // If we give arguments, check for a living with that name
    if(stringp(str) && strlen(str))
    {
        // Find our intended target
        obs = spell_target_one_other_present_living(caster, str);
    }
    else
    {
        // Find our current enemy
        obs = spell_target_one_present_enemy(caster, str);
    }

    // Return our targets
    return obs;
}

/*
 * Function name: spell_resist_acidbolt
 * Description:   Determines a target's base resistance to a spell.  This
 *                can be used for spells for which stat/skill-based
 *                resistance checks don't make sense.
 * Arguments:     object caster - the caster of the spell
 *                object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_acidbolt(object caster, object target, int element,
    int difficulty)
{
    // Based on the basic resistance check
    return combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_ACID, resistance_map[element] }));
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
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int     i;
    mixed   *hitresult;

    // Write the casting message
    desc_bolt_cast(caster, ({ targets[0] }) );

    // Try hitting our target
    if (!try_to_hit(caster, targets[0]))
    {
        // Write a miss message and stop the rest of the function (the splash)
        desc_bolt_miss(caster, targets[0]);
        return;
    }

    // Determine the hit result
    hitresult = do_bolt_damage(caster, targets[i],
        bolt_pen * (100 - resist[0]) / 100);

    // Write the hit message
    desc_bolt_damage(caster, targets[0], hitresult);

    // See if our target turned into a dead-form, if so, kill it
    if (targets[0]->query_hp() <= 0)
        targets[0]->do_die(caster);

    // See if the acid did enough damage to actually 'splash'
    // Hitresult ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    if(hitresult[2] >= 20)
    {
        // Write message
        tell_room(environment(caster),
            "As the acid sphere hits " + QTNAME(targets[0]) + "'s " +
            hitresult[1] + " it explodes, and is scattered into " +
            "large, flying drops.\n",targets[0]);
        targets[0]->catch_msg("As the acid sphere hits your " +
            hitresult[1] + " it explodes and scatters into " +
            "large, flying drops.\n");

        // Find everyone in our environment except the caster and the primary
        // target
        targets = FILTER_LIVE(all_inventory(environment(targets[0]))) -
            ({ caster, targets[0] });
        resist = map(targets, &spell_resist_acidbolt(caster, ,
            query_spell_element(), gSpell_resist_task));

        // Loop through all the targets
        for(i=0;i<sizeof(targets);i++)
        {
            // Try hitting our target
            if (!try_to_hit(caster, targets[i]))
            {
                // Write a message here that the splash misses the target
                targets[i]->catch_msg("You manage to evade the drops " +
                "of acid.\n");
                tell_room(environment(targets[i]), QCTNAME(targets[i]) +
                    " evades the drops of acid.\n", targets[i]);
                continue;
            }

            // Determine the hit result, we do half the damage as on the
            // primary target
            hitresult = do_bolt_damage(caster, targets[i],
                (bolt_pen /2) * (100 - resist[i]) / 100);

            // TODO: Write the hit message
            targets[i]->catch_msg("You are struck by flying drops of acid. Your skin sizzles painfully.\n");
            tell_room(environment(targets[i]),
                QCTNAME(targets[i]) + " is struck by flying drops of acid.\n", targets[i]);

            // See if our target turned into a dead-form, if so, kill it
            if (targets[i]->query_hp() <= 0)
                targets[i]->do_die(caster);
        }
    }
}

/*
 * Function name: desc_bolt_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_cast(object caster, object *targets)
{
    caster->catch_msg( "You chant some ancient, arcane words and draw a " +
         "drowish rune in the air with one finger. With a fluid motion, you aim for " + QTNAME(targets[0]) + ". Your eyes burn with a rage, and stream of liquid emerges from your palm.\n");
    targets[0]->catch_msg(QCTNAME(caster)+ " chants some ancient, arcane words " +
         "and draw a drowish rune in the air with one finger. With a fluid motion " + QTNAME(caster) + " aims for you, " +  caster->query_possessive() + " eyes burn with rage, and a stream of liquid flies from "  + caster->query_possessive() +
         " palm towards you.\n");
    caster->tell_watcher(QCTNAME(caster)+ " chants some ancient, arcane words " +
         "and draw a drowish rune in the air with one finger. With a fluid motion " + QTNAME(caster) + " aims for " +
         QTNAME(targets[0]) + ". " + caster->query_possessive() +
         " eyes burn with rage. A stream of liquid flies from "
         + caster->query_possessive() + " palm towards " + QTNAME(targets[0]) + ".\n",targets[0]);
}

void
desc_bolt_damage(object caster, object target, mixed *result)
{
    switch(result[0])
    {
        case 0:
            caster->catch_msg("Your thin stream of acid does not reach "
                + QTNAME(target) + ". ");
            target->catch_msg(QCTPNAME(caster) + " thin stream of acid " +
                "does not reach you.");
            caster->tell_watcher(QCTPNAME(caster) + " thin stream of " +
                "acid does not reach " + QTNAME(target) + ". ", target);
            break;
        case 1..3:
            caster->catch_msg("Your stream of acid hits " + QTNAME(target) + 
                ", spraying " + HIM_HER(target) + " with acid.");
            target->catch_msg("The stream of acid hits you, spraying you with acid.");
            caster->tell_watcher("The stream of acid hits " + QTNAME(target) + 
                ", spraying  " + HIM_HER(target) + " with acid.");
            break;
        case 4..6:
            caster->catch_msg("Your stream of acid brutally hits " + 
                QTNAME(target) + ", showering " + HIM_HER(target) + " with acid.");
            target->catch_msg("The stream of acid brutally hits you, " +
                "showering you with acid.\n");
            caster->tell_watcher("The stream of acid brutally hits " + 
                QTNAME(target) + ", showering " + HIM_HER(target) + " with acid.");
            break;
        case 7..9:
            caster->catch_msg("Your stream of acid powerfully hits " + 
                QTNAME(target) + ", covering " + HIM_HER(target) + " with acid.");
            target->catch_msg("The stream of acid powerfully hits you, " +
                "covering you with acid.");
            caster->tell_watcher("The stream of acid powerfully hits " + 
                QTNAME(target) + ", covering  " + HIM_HER(target) + " with acid.");
            break;
        case 10..12:
            caster->catch_msg("Your stream of acid hammers " + QTNAME(target) + 
                ", drenching " + HIM_HER(target) + " with acid.");
            target->catch_msg("The stream of acid hammers you, drenching " + 
                "you with acid.");
            caster->tell_watcher("The stream of acid hammers " + 
                QTNAME(target) + ", drenching " + HIM_HER(target) + " with acid.");
            break;
        default:
            caster->catch_msg("Your stream of acid slams into " + 
                QTNAME(target) + ", soaking " + HIM_HER(target) + " with acid.");
            target->catch_msg("The stream of acid slams into you, " +
                "soaking you with acid.");
            caster->tell_watcher("The stream of acid slams into " + 
                QTNAME(target) + ", soaking  " + HIM_HER(target) + " with acid.");
            break;
    }

    caster->catch_msg("\n");
    target->catch_msg("\n");
    caster->tell_watcher("\n", target);
}
