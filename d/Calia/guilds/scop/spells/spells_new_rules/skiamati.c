
/*
 * skiamati.c
 *
 * Skiamati (Shadow Eyes) spell for the Spirit Circle of Psuchae
 * This will allow the player to see invisible people
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
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

object comp;

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
        set_spell_name("skiamati");
        set_spell_desc("Shadow Eyes");
        set_spell_target(spell_target_one_present_living);
        set_spell_time(6);
        set_spell_mana(252);
        set_spell_visual(0);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE);
        set_spell_element(SS_ELEMENT_SPIRIT, 55);
        set_spell_form(SS_FORM_DIVINATION, 30);
        set_spell_ingredients(({"amethyst", "eye"}));
        set_spell_resist(spell_resist_beneficial);
        set_spell_target_verify(spell_verify_present);
        set_spell_object(SPIRIT_SPELLS + "skiamati_obj");
        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
    }
    else
    {
        if (targets[0] != caster)
        {
            caster->catch_tell("This gift can only be used on yourself.\n");
            return 1;
        }

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

        if (present("_skiamati_object_", targets[0]))
        {
            caster->catch_tell("You already have enhanced vision.\n");
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
    object tar = targets[0];

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but for some reason "+
                           "it failed.\n");
        return;
    }
   
    if (tar == caster)
    {
        caster->catch_tell("You channel the energies of Psuchae into your "+
            "eyes, in the hope that you will be granted enhanced vision.\n");
        tell_room(environment(tar),QCTPNAME(tar)+" eyes flash "+
            "brightly for a brief moment.\n", tar);
        setuid();
        seteuid(getuid());
        make_spell_effect_object(query_spell_object(), caster, tar, 
            resist[0], result)->move(tar,1);
    }
}