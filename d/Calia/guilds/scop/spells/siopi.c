/*
 * siopi.c
 *
 * Siopi (Silence) spell for the Spirit Circle of Psuchae
 * This is the silence spell for the guild.
 *
 * Copyright (C): Jaacar, July 30th, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

#ifndef LIVE_M_NO_SILENCE
#define LIVE_M_NO_SILENCE "_live_m_no_silence"
#endif

object comp;

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
        set_spell_name("siopi");
        set_spell_desc("Silence");
        set_spell_target(spell_target_one_present_living);
        set_spell_time(3);
        set_spell_mana(70);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_OCCUP)/2));
        set_spell_element(SS_ELEMENT_SPIRIT, 35);
        set_spell_form(SS_FORM_ENCHANTMENT, 25);
        set_spell_ingredients(({"lapis_lazuli_shard", "_leftover_tooth"}));
        set_spell_target_verify(spell_verify_present);
        set_spell_object(SPIRIT_SPELLS + "siopi_obj");
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

        if (present("_siopi_object_", targets[0]))
        {
            caster->catch_tell("Your have already silenced that target!\n");
            targets[0]->catch_tell(caster->query_The_name(targets[0])+
                " attempts to silence you again, but you have already been "+
                "muted so it does not work.\n");
            return 1;
        }

        if(targets[0] == caster)
        {
            caster->catch_tell("If you don't want to speak, just don't say anything.\n");
            return 1;
        }

        if (targets[0]->query_prop(LIVE_M_MOUTH_BLOCKED))
        {
            caster->catch_tell("That target already cannot speak.\n");
            return 1;
        }

        if(targets[0]->query_wiz_level())
        {
            caster->catch_tell("Psuchae doesn't have enough power to shut up a wizard!\n");
            return 1;
        }

        if (targets[0]->query_prop(LIVE_M_NO_SILENCE))
        {
            caster->catch_tell("That target cannot be silenced.\n");
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
    object tar = targets[0];

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
                           " unaffected.\n");
        return;
    }

    if(time() - tar->query_prop("_silenced_by_scop_at") < 300)
    {
        caster->catch_tell("You complete the spell, but your target is "+
                           "unaffected.\n");
        tar->catch_msg(QCTNAME(caster)+" casts a spell on you, but you " +
                       "are unaffected.\n");
        tell_room(environment(caster), QCTNAME(caster)+ " casts a spell on "+
                  QTNAME(tar)+".\n", ({tar, caster}));
        return;
    }
    
    caster->catch_tell("You point at "+tar->query_the_name(caster)+
                       ", removing "+tar->query_possessive() + " ability to "+
                       "speak.\n");
    tar->catch_tell(caster->query_The_name(tar) + 
                    " points at you, glaring into your eyes as "+
                    caster->query_pronoun()+" does so. You feel your mouth "+
                    "tightening up. You cannot speak!\n");
    say(QCTNAME(caster) + " points at " + QTNAME(tar) +
        ".\n", ({caster, tar}));
    say("It looks as if "+QTNAME(tar) + " attempts to speak but fails.\n", ({caster, tar}));

    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, tar, 
                             resist[0], result)->move(tar,1);
}
