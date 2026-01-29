/*
 * elefrinisi.c
 *
 * Elefrinisi (Relieve Encumberment) spell for the Spirit Circle of Psuchae
 *
 * A new spell added during the rework of all the spells of the spirit circle.
 * 
 * Navarre, October 8th, 2006
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
        set_spell_name("elefrinisi");
        set_spell_desc("Relieve Encumberment");
        set_spell_target(spell_target_one_present_living);
        set_spell_target_verify(spell_verify_present);
        set_spell_time(6);
        set_spell_mana(144);
        set_spell_vocal(0);
        set_spell_stationary(1);
        set_spell_peaceful(1);
        set_spell_task(TASK_ROUTINE);
        set_spell_resist_task(TASK_FORMIDABLE);
        set_spell_element(SS_ELEMENT_SPIRIT, 40);
        set_spell_form(SS_FORM_DIVINATION, 40);
        set_spell_ingredients(({"chalcedony", "thighbone"}));
        set_spell_object(SPIRIT_SPELLS + "elefrinisi_obj");        

        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
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

        if (present("_scop_elefrinisi_obj", targets[0]))
        {
            if(targets[0] == caster)
            {
              caster->catch_tell("You are already affected by " +
                                 "this prayer.\n");
            }
            else
            {
              caster->catch_msg(QCTNAME(targets[0])+" is already " +
                                "affected by this prayer.\n");
            }
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
concentrate_msg(object caster, object* targets, string arg)
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
resolve_spell(object caster, object* targets, int* resist, int result)
{
    int success, hitresult, pen;
    object spellob;
    object tar = targets[0];


    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
                           " unaffected.\n");
        return;
    }

    if(tar == caster)
    {
        caster->catch_tell("You call upon the spirits to alleviate you of "+
                           "the burdens of life.\n");

        tell_room(environment(caster), QCTNAME(caster)+" calls upon the " +
                  "spirits to aid "+HIM(caster)+".\n", caster);
    }
    else
    {
        caster->catch_msg("You call upon the spirits to alleviate "+
                           QTNAME(tar)+" of the burdens of life.\n");
        tar->catch_msg(QCTNAME(caster)+" calls upon the spirits to aid you "+
                       "with the burdens of life.\n");
        tell_room(environment(caster), QCTNAME(caster)+" calls upon the " +
                  "spirits to aid "+QTNAME(tar)+".\n", ({caster, tar}));
    }

    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, tar, 
                             resist[0], result)->move(tar,1);
}