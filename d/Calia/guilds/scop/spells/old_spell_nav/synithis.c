
/*
 * synithis.c
 *
 * Synithis (Summon Familiar) spell for the Spirit Circle of Psuchae
 * This will allow the player to summon a familiar to say/ask/whisper
 * through for quests
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 *
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
        set_spell_name("synithis");
        set_spell_desc("Summon Familiar");
        set_spell_target(spell_target_caster);
        set_spell_time(4);
        set_spell_mana(20);
        set_spell_visual(0);
        set_spell_vocal(0);
        set_spell_task(TASK_SIMPLE - caster->query_casting_bonus());
        set_spell_element(SS_ELEMENT_LIFE, 15);
        set_spell_form(SS_FORM_CONJURATION, 15);
        set_spell_ingredients(({"rib","intestine"}));
        set_spell_object(SPIRIT_SPELLS + "synithis_obj");
        add_element_resistance(SS_ELEMENT_LIFE, MAGIC_I_RES_LIFE);
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
        return 0;
    }
    else
    {
        if (present("_synithis_object_",caster))
        {
            write("You already have a familiar!\n");
            return 1;
        }
        return 0;
    }
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
    int old_val, new_val;

    if (present("_synithis_object_", caster))
    {
        caster->catch_tell("You have already summoned a familiar.\n");
        return;
    }

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but no familiar "+
            "appears.");
        return;
    }
    
    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 1));
    caster->set_skill(SS_SPELLS_CASTED, new_val);

    caster->catch_tell("Concentrating all of your energies, you pray "+
        "to Psuchae to call forth a familiar for which to speak through.\n");
    say(QCTNAME(caster) + "'s eyes flash brightly for a brief moment.\n",
        ({caster}));

    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist[0], result)->move(targets[0],1);
}