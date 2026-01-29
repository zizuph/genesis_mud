/*
 * skiamorfi.c
 *
 * Skiamorfi (Shadow Form) spell for the Spirit Circle of Psuchae
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
        set_spell_name("skiamorfi");
        set_spell_desc("Shadow Form");
        set_spell_target(spell_target_caster);
        set_spell_time(6);
        set_spell_mana(50);
        set_spell_peaceful(1);
        set_spell_stationary(1);
        set_spell_visual(1);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_OCCUP)/2));
        set_spell_element(SS_ELEMENT_SPIRIT, 40);
        set_spell_form(SS_FORM_TRANSMUTATION, 25);
        set_spell_ingredients(({"_skiamorfi_component_", "_leftover_rib"}));
        set_spell_object(SPIRIT_SPELLS+"skiamorfi_obj");
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

/*  ALLOWED NOW, TO RESET THE EFFECT WITHOUT IT RUNNING OUT.
        if (present("_skiamorfi_object_",caster))
        {
            write("You are already in shadow form!\n");
            return 1;
        }
*/
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

    object shadowform_obj;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but for some reason "+
                           "it fails.\n");
        return;
    }

    shadowform_obj = present("_skiamorfi_object_",caster);

    if (shadowform_obj)
    {
        caster->catch_tell("Concentrating all of your efforts on the task, you "+
                           "succesfully call upon the gifts of Skiamorfi. " +
                           "You feel the shadows surrounding you strengten.\n");
        tell_room(environment(caster), "The shadows surrounding "+QTNAME(caster)+
                                       " shifts.\n", caster);
        shadowform_obj->reapply_spell_effect();
        return;
    }

    caster->catch_tell("Concentrating all of your efforts on the task, you "+
        "succesfully call upon the gifts of Skiamorfi. Your entire body "+
        "is surrounded by a blanket of shadow, enveloping you and "+
        "everything you are carrying from sight.\n");
    tell_room(environment(caster),QCTNAME(caster)+" is suddenly enveloped "+
        "by a blanket of shadows.\n",({caster}));
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, caster, resist,
                             result)->move(caster,1);
}
