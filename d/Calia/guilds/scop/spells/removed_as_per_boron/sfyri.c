/*
 * sfyri.c
 *
 * Sfyri (Spiritual Hammer) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, August 4th, 2003
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spells/bolt";
 
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"
#include SPIRIT_HEADER
 
string
query_spell_level()
{
    return "Apprentice";
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{  
    set_spell_name("sfyri");
    set_spell_desc("Spiritual Hammer");
    set_spell_element(SS_ELEMENT_SPIRIT, 35);
    set_spell_form(SS_FORM_CONJURATION,35);
    set_spell_task(TASK_SIMPLE);
    set_spell_ingredients(({"_sfyri_component_"}));
    set_spell_target(spell_target_one_other_present_living);
    set_spell_mana(50);
    set_spell_vocal(0);
    set_bolt_pen(100);
    add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
    if (caster->query_intoxicated())
    {
        caster->catch_msg("You cannot use Psuchae's gifts while intoxicated!\n");
        return 1;
    }
    if (caster->query_alignment() < 0)
    {
        caster->catch_msg("You cannot use Psuchae's gifts while you are not "+
            "good aligned.\n");
        return 1;
    }
    ::config_spell(caster, targets, argument);
    return 0;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You concentrate on the powers of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
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
    int i, gstat, spirit, spellcraft, conjuration, total;
    mixed *hitresult;

    gstat = caster->query_stat(SS_OCCUP);
    spellcraft = caster->query_skill(SS_SPELLCRAFT);
    spirit = caster->query_skill(SS_ELEMENT_SPIRIT);
    conjuration = caster->query_skill(SS_FORM_CONJURATION);

    // Absolute maximum pen would be 325, minimum will be 75
    total = ((MIN(75,gstat)) + spellcraft + random(spirit) + conjuration)-
        (random(200));
    
    if (total < 100)
    {
        total = 100;
    }

    if (targets[0]->query_prop(LIVE_I_UNDEAD))
    {
        // 30% more damage for undeads (making maximum pen 423)
        total = (total * 130 / 100);   
    }
    
    set_bolt_pen(total);
    desc_bolt_cast(caster, targets);

    for (i = 0; i < sizeof(targets); i++)
    {
        if (!try_to_hit(caster, targets[i]))
        {
            desc_bolt_miss(caster, targets[i]);
            continue;
        }

        hitresult = do_bolt_damage(caster, targets[i], 
            bolt_pen * (100 - resist[i]) / 100);

        desc_bolt_damage(caster, targets[i], hitresult);
         
        if (targets[i]->query_hp() <= 0)
        {
            targets[i]->do_die(caster);
        }
    }
}

/*
 * Function name: desc_bolt_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
public void
desc_bolt_damage(object caster, object target, mixed *result)
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
    caster->tell_watchers(QCTNAME(target) + " appears " + how + ".\n",
        target);
}

/*
 * Function name: desc_bolt_miss
 * Description:   Write out some text describing the missed attack.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_miss(object caster, object target)
{
    string bolt = "The shadowy hammer misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher_miss(bolt + QCTNAME(target) + ".\n", target);
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
    string msg, his, bolt;

    his = caster->query_possessive();
    bolt = ", and a shadowy hammer shoots from %s palm.\n";

    caster->catch_tell("You extend your arm toward " +
        FO_COMPOSITE_ALL_LIVE(targets, caster) + sprintf(bolt, "your"));

    msg = " extends " + his + " arm toward you, and a shadowy hammer "+
        "shoots from " + his + " palm.\n";
    targets->catch_msg(({caster->query_Met_name() +  msg,
        capitalize(caster->query_nonmet_name()) + msg,
        "" }));
                           
    caster->tell_watcher(QCTNAME(caster) + " extends " + his + 
        " arm toward " + QCOMPLIVE + sprintf(bolt, his), targets);
}

