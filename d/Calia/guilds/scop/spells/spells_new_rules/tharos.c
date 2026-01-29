
/*
 * tharos.c
 *
 * Tharos (Reduce Panic) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Navarre, October 8th, 2006
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER


string
query_spell_level()
{
    return "Master";
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
    if (caster == 0)
    {
        set_spell_name("tharos");
        set_spell_desc("Reduce Panic");
        set_spell_target(spell_target_one_present_living);
        set_spell_target_verify(spell_verify_present);
        set_spell_time(6);
        set_spell_mana(101);
        set_spell_vocal(0);
        set_spell_offensive(0);
        set_spell_peaceful(0);
        set_spell_task(TASK_ROUTINE);
        set_spell_resist_task(TASK_FORMIDABLE);
        set_spell_element(SS_ELEMENT_SPIRIT, 40);
        set_spell_form(SS_FORM_DIVINATION, 30);
        set_spell_ingredients(({"garnet", "rib"}));
        set_spell_object(SPIRIT_SPELLS + "tharos_obj");        

        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
    }
    else
    {
        if (caster->query_intoxicated())
        {
            caster->catch_tell("You cannot use Psuchae's gifts while intoxicated!\n");
            return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_tell("You cannot use Psuchae's gifts while you are not "+
                               "good aligned.\n");
            return 1;
        }
    }
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
    int success, hitresult, pen, gstat, wis;
    object spellob;
    object tar = targets[0];

    if (random(100) < resist[0])
    {
        if(tar == caster)
        {
            caster->catch_tell("You complete the spell, but you are unaffected.\n");
        }
        else
        {
            caster->catch_tell("You complete the spell, but your target is" +
                               " unaffected.\n");
        }
        return;
    }
    if(tar == caster)
    {
        tell_room(environment(caster), QCTNAME(caster)+" calls upon "+
                  "the spirits to ease and reassure "+HIM(caster)
                  +"self.\n", caster);
        caster->catch_tell("You call upon the spirits to ease and reassure yourself.\n");
    }
    else
    {
        tell_room(environment(caster), QCTNAME(caster)+" calls upon "+
                  "the spirits.\n", ({caster, tar}));
        caster->catch_msg("You call upon the spirits to ease and reassure "+QTNAME(tar)+".\n");
        tar->catch_msg(QCTNAME(caster)+" calls upon the spirits to ease and "+
                       "reassure you.\n");
    }

    if(tar->query_panic() == 0)
    {
        tar->catch_tell("You feel no effect.\n");
    }
    else
    {
        gstat = caster->query_stat(SS_OCCUP);
        wis = caster->query_stat(SS_WIS);

        tar->add_panic(-(gstat+random(wis/2)+random(gstat)));
        tar->catch_tell("You feel more secure.\n");
    }
}