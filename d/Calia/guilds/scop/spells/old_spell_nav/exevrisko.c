
/*
 * exevrisko.c
 *
 * Exevrisko (Detect Alignment) spell for the Spirit Circle of Psuchae
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
    set_spell_name("exevrisko");
    set_spell_desc("Detect Alignment");
    set_spell_target(spell_target_one_present_living);
    set_spell_time(2);
    set_spell_mana(15);
    set_spell_vocal(0);
    set_spell_task(TASK_SIMPLE - caster->query_casting_bonus());
    set_spell_element(SS_ELEMENT_SPIRIT, 15);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_ingredients(({"skull"}));
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(1);
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
    int alignment, old_val, new_val;
    string desc_str;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but you cannot "+
            "divine the results.");
        return;
    }

    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 1));

    alignment = targets[0]->query_alignment();

    switch(alignment)
    {
        case 1200:
            desc_str = "glowing pure white in colour";
            break;
        case 1000..1199:
            desc_str = "brilliant white in colour";
            break;
        case 800..999:
            desc_str = "bright white in colour";
            break;
        case 600..799:
            desc_str = "hazy white in colour";
            break;
        case 400..599:
            desc_str = "airy white in colour";
            break;
        case 200..399:
            desc_str = "obscure white in colour";
            break;
        case 1..199:
            desc_str = "murky white in colour";
            break;
        case 0:
            desc_str = "clear crystalline in colour";
            break;
        case -199..-1:
            desc_str = "mist grey in colour";
            break;
        case -399..-200:
            desc_str = "smoke grey in colour";
            break;
        case -599..-400:
            desc_str = "dark grey in colour";
            break;
        case -799..-600:
            desc_str = "dusky grey in colour";
            break;
        case -999..-800:
            desc_str = "shadowy grey in colour";
            break;
        case -1199..-1000:
            desc_str = "absorbing coal-coloured";
            break;
        case -1200:
            desc_str = "midnight black in colour";
            break;
        default:
            desc_str = "an unknown colour";
            break;
    }

    caster->set_skill(SS_SPELLS_CASTED, new_val);
    caster->catch_tell("You close your eyes, concentrating on "+
        targets[0]->query_the_name(caster)+". You open your eyes "+
        "and inspect "+targets[0]->query_the_name(caster)+"'s inner "+
        "being carefully using the powers of vision granted to you "+
        "by Psuchae. You determine that the inner aura is "+desc_str+
        ".\n");

    targets[0]->catch_tell(caster->query_The_name(targets[0])+" closes "+
        caster->query_possessive()+" eyes. "+
        capitalize(caster->query_pronoun())+" opens "+
        caster->query_possessive()+" eyes and inspects you closely, "+
        "looking you up and down. After a few moments, "+
        caster->query_pronoun()+" looks away.\n");
    
    say(QCTNAME(caster)+" closes "+caster->query_possessive()+
        " eyes. "+capitalize(caster->query_pronoun())+" opens "+
        caster->query_possessive()+" eyes and inspects "+
        QNAME(targets[0])+" closely, looking "+targets[0]->query_objective()+
        " up and down. After a few moments, "+caster->query_pronoun()+
        " looks away.\n",({ caster, targets[0]}));

}
