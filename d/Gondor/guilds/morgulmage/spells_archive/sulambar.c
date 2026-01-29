#pragma strict_types

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>
#include "../morgulmage.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"
#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public string *query_sulambar_ingredients(object caster);

public nomask void
config_spell()
{
    set_spell_name("sulambar");
    set_spell_desc("Summon the Wind of Doom");

    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_CONJURATION, 70);

    set_spell_task(TASK_DIFFICULT);

    set_spell_mana(300);
    set_spell_time(18);

    set_spell_target(spell_target_caster);
    set_spell_ingredients(query_sulambar_ingredients);
    set_spell_object(MORGUL_SPELL_OBJ_DIR + "sulambar");

    set_morgul_rank(23);
}

public string *query_sulambar_ingredients(object caster)
{
    return ({ "_nenamarth_charge" });
}

public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    object *_who_can_see = can_see_caster(caster);

    caster->catch_tell("With the power the Dark Lord has bestowed upon "
        + "you, you call the Wind of Doom.\n");
    _who_can_see->catch_msg("Employing Dark Sorcery, " + QTNAME(caster)
        + " calls the Wind of Doom.\n");

    setuid();
    seteuid(getuid());
    object cloud = make_spell_effect_object(query_spell_object(), caster,
            ({ environment(caster) }), resist, result);
    cloud->move(environment(caster), 1);

    add_maintained_spell_effect(caster, cloud);

    MORGUL_MASTER->increase_activity(caster, ACTIVITY_RARE_SPELL);

    if (!caster->query_npc())
    {
        // Decrease the number of charges
        MORGUL_MASTER->decrease_sulambar_charge(caster);
    }
}

public int
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }

    if(!caster->query_npc())
    {
        // Get the number of charges remaining
        int charges = MORGUL_MASTER->query_sulambar_charges(caster);

        // If we don't have any charges remaining, write a message and fail
        if(charges <= 0)
        {
            caster->catch_msg("Your attempt to call upon the Wind of Doom "
                + "fails.\n");
            return 0;
        }
    }


    return result;
}
