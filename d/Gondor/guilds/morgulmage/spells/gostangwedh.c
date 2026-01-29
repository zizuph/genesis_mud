#pragma strict_types

#include "../morgulmage.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "slow";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public void
config_slow_spell()
{
    set_spell_name("gostangwedh");
    set_spell_desc("Slow someone with the Chains of Terror");

    set_spell_object(MORGUL_SPELL_OBJ_DIR + "gostangwedh");    
    
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_element(SS_ELEMENT_DEATH, 50);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_class(SPELL_CLASS_4);
    set_spell_task(TASK_HARD);
    set_spell_time_factor(&adjust_time_by_rank(1.5)); // 4s * 1.5 = 6s

    set_slow_interval(3.5);

    set_morgul_rank(20);
}

// HOOKS TO BE DEFINED

/*
 * Function:    query_slow_ingredients
 * Description: This function defines what components are required for
 *              this slow spell.
 */
public string *
query_slow_ingredients(object caster)
{
    return ({ "_nwalyavanta_charge" });
}

/*
 * Function:    resolve_slow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_slow_spell(object caster, mixed * targets, int * resist, int result)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_RARE_SPELL);
}

public int
is_servant(object ob) 
{
    if (IS_MEMBER(ob)) return 1;
    return (ob->query_anghoth_level());
}
/*
 * Function:    hook_describe_cast_slow
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_slow(object caster, object * targets)
{
    caster->catch_tell("Your eyes narrow in anticipation as you reveal the "
        + "true power and might of the Dark Lord unto " 
        + COMPOSITE_LIVE(targets) + ".\n");

    object *livings = FILTER_LIVE(all_inventory(environment(caster))) - targets
        - ({ caster });

    object *servants = filter(livings, is_servant);
    object *non_servants = livings - servants;

    targets->catch_msg("A dread feeling of hopelessness sinks deep into your "
        + "heart as " + QTNAME(caster) + " displays " + caster->query_possessive()
        + " contempt for you!\n");

    non_servants->catch_msg("A dread feeling of hopelessness sinks deep into "
        + "your heart as you watch " + QTNAME(caster) + " displays "
        + caster->query_possessive() + " contempt for " + QTNAME(targets[0]) 
        + "!\n");

    servants->catch_msg(QCTNAME(caster) + " reaches deep into the shadows, "
        + "and overwhelms " + QTNAME(targets[0]) + " with the true might and "
        + "power of the Dark Lord.\n");
}

/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " is already under the effects of "
        + "the Chains of Terror!\n");
}
