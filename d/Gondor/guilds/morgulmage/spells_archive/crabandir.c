#pragma strict_types

#include "../morgulmage.h"
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <files.h>

inherit "/d/Genesis/specials/std/spells/summon";

#define _NO_DEFAULT_CONCENTRATE_MESSAGE

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

object * spell_target_craban(object caster, string str);
public string *query_crabandir_ingredients(object caster);

public void
config_summon_spell()
{
    set_spell_name("crabandir");
    set_spell_desc("Summon the crabain to spy on someone");

    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);

    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_element(SS_ELEMENT_DEATH, 50);

    set_spell_task(TASK_ROUTINE);
    set_spell_time_factor(3.5); // 4s * 3.5 = 14s
    set_spell_mana_factor(6.67); // 30 * 6.67 = 200

    set_spell_target(spell_target_craban);
    set_ability_target_verify(0);

    set_summon_file(MORGUL_SPELL_OBJ_DIR + "crabandir_npc");
    set_summon_into_inventory(0);
    
    set_spell_object(MORGUL_SPELL_OBJ_DIR + "crabandir_obj");

    set_spell_ingredients(query_crabandir_ingredients);
    set_morgul_rank(10);

    set_spell_time_factor(adjust_time_by_rank);
}

public string *
query_crabandir_ingredients(object caster)
{
    return ({ "_corcosunk_charge" });
}

/*
 * Function:    resolve_summon_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_summon_spell(object caster, mixed * targets, int * resist, int result, mapping input)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
}

object *
spell_target_craban(object caster, string str)
{
    if (!strlen(str))
    {
        caster->catch_tell("Target whom?\n");
        return ({ });
    }

    if (environment(caster)->query_prop(ROOM_I_INSIDE))
    {
        caster->catch_tell("You are not outdoors. Your craban may find "
            + "it hard to find a way out.\n");
        return ({ });
    }

    object living = find_living(str);

    if (!objectp(living) || living->query_invis())
    {
        caster->catch_tell("You do not sense " + LANG_POSS(str)
            + " presence in the realms.\n");
        return ({ });
    }

    if (living->query_wiz_level() && !caster->query_wiz_level())
    {
        caster->catch_tell("You don't dare spy on " + living->query_name() 
            + ".\n");
        return ({ });
    }
    
    return ({ living });
}

void concentrate_msg(object caster, object *targets, string args)
{
    tell_room(environment(caster), QCTNAME(caster) + " extends"
        + caster->query_possessive() + " clenched fist skyward,"
        + " slowly unfurling gnarled fingers as if to beckon some"
        + " unknown thing.\n", caster);

    caster->catch_tell("Using the power the Dark Lord has bestowed upon "
        + "you, you summon the crebain to spy on " 
        + targets[0]->query_name() + " for you. Extending your"
        + " right hand slowly skyward, you beckon your "
        + "servants with the words \"Yalanlye craban! Gimo nin kweth a "
        + "telo!\"\n");
}