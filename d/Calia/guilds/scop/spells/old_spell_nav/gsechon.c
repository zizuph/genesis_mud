
/*
 * gsechon.c
 *
 * Gsechon (Name Forget) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 30th, 2003
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
    set_spell_name("gsechon");
    set_spell_desc("Name Forget");
    set_spell_target(spell_target_one_present_living);
    set_spell_time(5);
    set_spell_mana(25);
    set_spell_vocal(0);
    set_spell_task(TASK_SIMPLE - caster->query_casting_bonus());
    set_spell_element(SS_ELEMENT_SPIRIT, 35);
    set_spell_form(SS_FORM_DIVINATION, 35);
    set_spell_ingredients(({"bloodstone"}));
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
    int old_val, new_val;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
            " unaffected.");
        return;
    }

    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 2));
    caster->set_skill(SS_SPELLS_CASTED, new_val);

    targets[0]->catch_tell(caster->query_The_name(targets[0])+" closes "+
        caster->query_possessive()+" eyes. Your head begins to pound "+
        "with pain. The blood rushes against your skull rapidly. "+
        "Grasping your head, you close your eyes until the pain goes "+
        "away.\n");
    caster->catch_tell("You close your eyes, concentrating on "+
        targets[0]->query_the_name(caster)+". "+
        capitalize(targets[0]->query_pronoun())+" grasps "+
        targets[0]->query_possessive()+" head and winces as if "+
        targets[0]->query_pronoun()+" is in terrible pain. "+
        capitalize(targets[0]->query_pronoun())+" removes "+
        targets[0]->query_possessive()+" hands from "+
        targets[0]->query_possessive()+" head, and appears to be "+
        "in much less pain than "+targets[0]->query_pronoun()+
        " was a moment ago. You have successfully removed your "+
        "name from "+targets[0]->query_possessive()+" head.\n");
    say(QCTNAME(caster)+" closes "+caster->query_possessive()+
        " eyes.  Suddenly, "+QNAME(targets[0])+" grasps "+
        targets[0]->query_possessive()+" head and appears to "+
        "be in a great amount of pain. "+
        capitalize(targets[0]->query_pronoun())+" removes "+
        targets[0]->query_possessive()+" hands from "+
        targets[0]->query_possessive()+" head and appears "+
        "to be in much less pain than "+targets[0]->query_pronoun()+
        " was a moment ago.\n",({ caster, targets[0]}));
    targets[0]->remove_remembered(caster->query_real_name());
}