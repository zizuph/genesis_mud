/*
 * fos.c
 *
 * Fos (Light) spell for the Spirit Circle of Psuchae
 * This will give the player a halo as a light source
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Spell Redone in the fall of 2006 by Navarre
 *
 * Changed for balance to use coral instead of quartz and
 * changed mana to be correct.
 *
 * Navarre, October 28th, 2007: Removed resistance check if the target = the caster.
 *                              As they kept failing when in their shadow form.
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

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
    if (caster == 0)
    {
        set_spell_name("fos");
        set_spell_desc("Light");
        set_spell_target(spell_target_caster);
        set_spell_time(3);
        set_spell_mana(32);
        set_spell_visual(0);
        set_spell_vocal(0);
        set_spell_peaceful(0);
        set_spell_task(TASK_SIMPLE);
        set_spell_element(SS_ELEMENT_LIFE, 10);
        set_spell_form(SS_FORM_ENCHANTMENT, 15);
        set_spell_ingredients(({"pink_coral_shard"}));
        set_spell_resist(spell_resist_beneficial);
        set_spell_object(SPIRIT_SPELLS + "fos_obj");

        add_element_resistance(SS_ELEMENT_LIFE, MAGIC_I_RES_LIFE);
    }
    else
    {
        if (caster->query_intoxicated())
        {
            caster->catch_tell("You cannot use Psuchae's gifts " +
                               "while intoxicated!\n");
            return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_tell("You cannot use Psuchae's gifts " +
                               "while you are not good aligned.\n");
            return 1;
        }

        if (present("_fos_object_", caster))
        {
            caster->catch_tell("You already have a light halo.\n");
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
    caster->catch_tell("You summon the energies of Psuchae.\n");
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
    if (targets[0] != caster && random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but you do " +
                           "not receive a halo.\n");
        return;
    }
    caster->catch_tell("You channel the energies of Psuchae. A bright "+
                       "halo appears above your head.\n");
    say("A bright halo appears above "+QTPNAME(caster) + " head.\n", caster);
    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist[0], result)->move(targets[0],1);
}
