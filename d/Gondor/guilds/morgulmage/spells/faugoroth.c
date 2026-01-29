#pragma strict_types

#include "../morgulmage.h"
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "stun";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public void
config_stun_spell()
{
    set_spell_name("faugoroth");
    set_spell_desc("Make your enemy pause fighting in fear");

    // 20 charges per potion.
    set_spell_component_factor(COMPONENT_AID_LOW);
    set_spell_combat_aid(40.0);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_form(SS_FORM_ENCHANTMENT, 34);
    set_spell_element(SS_ELEMENT_DEATH, 38);

    set_spell_class(SPELL_CLASS_3);
    set_spell_task(TASK_ROUTINE);
    
    set_spell_object(MORGUL_SPELL_OBJ_DIR + "faugoroth");    

    set_morgul_rank(17);

    set_spell_time_factor(adjust_time_by_rank);
}

public string *
query_stun_ingredients(object caster)
{
    return ({ "_taltambar_charge" });
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_stun_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_stun_spell(object caster, mixed * targets, int * resist, int result)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
}

/*
 * Function:    hook_describe_cast_stun
 * Description: Function that gets called to display the caster casting the
 *              spell towards his intended targets.
 */
public void
hook_describe_cast_stun(object caster, object * targets)
{
    caster->catch_tell("Mustering your will, you rise up and turn your fell "
        + "gaze fall upon " + targets[0]->query_the_name(caster) + ".\n");
    targets->catch_msg(QCTNAME(caster) + " rises up and you freeze for a "
        + "moment in mindless panic.\n");
    caster->tell_watcher(QCTNAME(caster) + " rises up and " 
        + QTNAME(targets[0]) + " seems to freeze almost immediately in "
        + "sheer terror.\n", targets[0], ({ targets[0], caster }));
}

/*
 * Function:    hook_target_stun_resisted
 * Description: Called to show the messages of the targets that were not
 *              stunned because they resisted the spell.
 */
public void
hook_target_stun_resisted(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("A brief look of terror passes across the face of " 
        + targets[0]->query_the_name(caster) + ", yet " 
        + targets[0]->query_pronoun() + " seems ultimately unfazed and "
        + "continues " + targets[0]->query_possessive() + " attack upon "
        + "you!\n");
    targets->catch_tell("A dread feeling of blind terror momentarily grips "
        + "your heart, but you fight it off and continue your assault "
        + "upon " + caster->query_the_name(targets[0]) + ".\n"); 
    caster->tell_watcher("You see " + QTNAME(targets[0]) + " pause for a "
        + "moment as a fearful look falls across " 
        + targets[0]->query_possessive() + " face. However, a moment last, "
        + "a look of steely resolve appears and " 
        + targets[0]->query_pronoun() + " continues " 
        + targets[0]->query_possessive() + " assault upon " 
        + QTNAME(caster) + ".\n");
}

/*
 * Function:    hook_target_stun_succeeded
 * Description: Called to show the messages of the targets that were
 *              affected by the stun. Part of the stun messages
 *              will also be described by the stun object itself. Note
 *              that it's entirely possible the stun spell may hit,
 *              but because of a cooldown period, the stun may not
 *              actually have any effect.
 */
public void
hook_target_stun_succeeded(object caster, object * targets)
{
    if (!sizeof(targets))
    {
        return;
    }
    
    caster->catch_tell("Your fell gaze falls upon " 
        + targets[0]->query_the_name(caster) + ", as you watch the worm "
        + "freeze in the terror of your dread presence.\n");
    targets->catch_tell("You are unable to move as an unreasoning avalanche "
        + "of pure terror grips your heart and overwhelms you.\n");
}

