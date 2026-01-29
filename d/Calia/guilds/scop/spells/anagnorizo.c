/*
 * anagnorizo.c
 *
 * Anagnorizo (True Identity) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 30th, 2003
 *
 * Balance Review Done By Shiva - September 2003
 * 
 * Spell Redone in the fall of 2006 by Navarre.
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
    if(caster == 0)
    {
        set_spell_name("anagnorizo");
        set_spell_desc("True Identity");
        set_spell_target(spell_target_one_present_living);
        set_spell_time(3);
        set_spell_mana(51);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - caster->query_stat(SS_OCCUP));
        set_spell_element(SS_ELEMENT_SPIRIT, 50);
        set_spell_form(SS_FORM_DIVINATION, 40);
        set_spell_ingredients(({"moonstone_shard", "_leftover_eye"}));
        set_spell_target_verify(spell_verify_present);
        set_spell_peaceful(1);
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
    
        if(targets[0] == caster)
        {
            caster->catch_tell("A senile cleric! That's a first!\n");
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
    object tar = targets[0];

    if(tar->query_wiz_level())
    {
        caster->catch_tell("If the wizard wants you to know "+HIS(tar)+
                           " name, "+HE(tar)+" will let you know!\n");
        caster->catch_tell("The wizard has been notified of your attempt.\n");
        tar->catch_msg(QCTNAME(caster)+" tried to steal your name.\n");
        return;

    }

    if (random(100) < resist[0] || !interactive(tar))
    {
        caster->catch_tell("You complete the spell, but your target is" +
                           " unaffected.\n");
        return;
    }
    
    if(!interactive(tar) && find_living(tar->query_real_name()) != tar)
    {
        caster->catch_msg("You probe the mind of "+QTNAME(tar)+
                          ", but discover no name.\n");
        return;
    }

    tar->catch_tell(caster->query_The_name(tar)+" closes "+
        caster->query_possessive()+" eyes for a brief moment. Your mind "+
        "feels invaded and you somehow know that "+
        caster->query_the_name(tar)+" now knows your identity!\n"); 
    caster->catch_tell("You close your eyes, concentrating on "+
        tar->query_the_name(caster)+". After probing "+
        tar->query_possessive()+" mind, you come to the "+
        "realization that "+tar->query_possessive()+
        " name is "+capitalize(tar->query_real_name())+".\n");
    say(QCTNAME(caster)+" closes "+caster->query_possessive()+
        " eyes for a brief moment, while concentrating on " + 
        QTNAME(tar)+".\n", ({ caster, tar}));
    
    if(interactive(tar))
    {
        caster->add_introduced(tar->query_real_name());
    }
}
