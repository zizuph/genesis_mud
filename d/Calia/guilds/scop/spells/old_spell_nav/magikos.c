 
/*
 * magikos.c
 *
 * Magikos (Identify Magic) spell for the Spirit Circle of Psuchae
 * This is the identify magic info spell for the guild.
 *
 * Copyright (C): Jaacar, July 30th, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spells/identify.c";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER

object sp_caster;

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
    ::config_spell(caster, targets, argument);
    set_spell_name("magikos");
    set_spell_desc("Identify Magic");
    set_spell_time(6);
    set_spell_mana(20);
    set_spell_vocal(0);
    set_spell_task(TASK_SIMPLE - caster->query_casting_bonus());
    set_spell_ingredients(({"rib","thighbone"}));  
    set_spell_element(SS_ELEMENT_SPIRIT, 15);
    set_spell_form(SS_FORM_DIVINATION, 15);
    set_spell_stationary(1);
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
    caster->catch_tell("You mentally call upon Psuchae for power.\n");
    say(QCTNAME(caster) + " appears to concentrate deeply.\n");
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
    string msg, str;
    object target = targets[0];
    object *who;
    int old_val, new_val;

    result = result * (100 - resist[0]) / 100;

    msg = get_id_info(target, result);

    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 1));
    caster->set_skill(SS_SPELLS_CASTED, new_val);

    caster->catch_tell("You touch " + 
        FO_COMPOSITE_ALL_DEAD(targets, caster) + ".\n");

    who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
        all_inventory(environment(caster)) - ({ caster })));

    who->catch_msg(QCTNAME(caster) + " touches " + QCOMPDEAD + ".\n");

    if (strlen(msg))
    {
        caster->catch_tell(msg);
    }
    else
    {
        caster->catch_tell("You fail to divine any magical properties.\n");
    }

    target->appraise_object(caster->query_skill(SS_ELEMENT_SPIRIT) + result);
}


