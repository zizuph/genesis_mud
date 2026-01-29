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
 * Navarre, October 28th, 2007: Removed resistance check if the target = the caster.
 *                              As they kept failing when in their shadow form.
 * Petros, November 17th, 2008: Fixed so that multiple castings do not stack
 *                              levels.
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
        set_spell_time(4);
        set_spell_mana(65);
        set_spell_visual(0);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - caster->query_stat(SS_OCCUP));
        set_spell_element(SS_ELEMENT_SPIRIT, 55);
        set_spell_form(SS_FORM_DIVINATION, 30);
        set_spell_ingredients(({"amethyst_shard", "_leftover_eye"}));
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
            caster->catch_tell("Already being blessed with the gift of skiamati, "
                + "you pray to Psuchae to prolong the gift.\n");
            return 0;
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
    caster->catch_tell("You silently lift up a prayer to Psuchae.\n");
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
    object skia_object;
    
    if (tar != caster && random(100) < resist[0])
    {
        caster->catch_tell("You complete the prayer, but for some reason "+
                           "your prayers are not answered.\n");
        return;
    }
   
    if (tar == caster)
    {
        skia_object = present("_skiamati_object_", targets[0]);
        if (skia_object)
        {
            caster->add_prop(SKIAMATI_IS_PRESENT, 1);
            skia_object->dispel_spell_effect();
        }

        setuid();
        seteuid(getuid());

        make_spell_effect_object(query_spell_object(), caster, tar, 
                                 resist[0], result)->move(tar,1);
    }
}
