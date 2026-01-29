/* 
 * This is basic spell object for PoT. It is to be inherited by actual spells.
 * Created by Milan 15.11.2000
 */
#pragma strict_types

inherit "/d/Genesis/newmagic/spell";
inherit "/lib/commands";

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/dargaard/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include "../local.h"
#include <tasks.h>
#include <filter_funs.h>

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
    object old_tp = TP;

    set_this_player(caster);
    caster->catch_tell("You begin to concentrate on a spell.\n");
    allbb(" begins to concentrate on a spell.");
    set_this_player(old_tp);
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    int task = gSpell_task;

    /* Another change to better reflect how it should be
     * Statavg 100 again with maxed skills: TASK_ROUTINE; 95%,
     * TASK_DIFFICULT; 62%
     */
    return max(0, caster->resolve_task(task, ({
        SKILL_WEIGHT, 80, SS_SPELLCRAFT,
        SKILL_WEIGHT, 30, TS_INT,
        SKILL_WEIGHT, 30, TS_WIS, })));
}

/* Function name: all_msg
 * Description: Prints a message to those who wants it
 * Arguments: string str      - the string to print
 *            object caster   - the caster
 *            mixed exclude   - An array or object of those to exclude
 *            int only_vision - Only display it to those who can actually
 *                              see the caster.
 */
public varargs void
all_msg(string str, object caster, mixed exclude, int only_vision)
{
    object *who;
    
    who = FILTER_PLAYERS(all_inventory(environment(caster)) - ({ caster }));
    
    if (pointerp(exclude))
        who -= exclude;
    else if (objectp(exclude))
        who -= ({ exclude });
    
    if (only_vision)
        who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster, who));
    
    who->catch_msg(str);
}

/* Function name: all_msgbb
 * Description: An alias for all_msg(,,,1);
 * Arguments: See all_msg
 */
public varargs void
all_msgbb(string str, object caster, mixed exclude)
{
    all_msg(str, caster, exclude, 1);
}

/*
 * Function name: default_config_spell
 * Description:   Set the default values for the variables
 */
public void
default_config_spell()
{
    ::default_config_spell();
    set_spell_fail("You fail to pronouce the words correctly, and sharp "+
                   "pain shoots up your arm, as the energy gets "+
                   "trapped within you!\n");
}
