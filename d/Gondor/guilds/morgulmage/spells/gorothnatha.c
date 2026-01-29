#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "../morgulmage.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "delayedtrigger";

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public void
config_delayedtrigger_spell()
{
    set_spell_name("gorothnatha");
    set_spell_desc("Damage your enemy with the Dread Bite");

    set_spell_vocal(0);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_form(SS_FORM_ENCHANTMENT, 25);
    set_spell_element(SS_ELEMENT_DEATH, 30);

    set_spell_task(TASK_HARD);

    set_shadow_filename(MORGUL_SPELL_OBJ_DIR + "gorothnatha_sh");    
    set_spell_target(target_actor);

    set_morgul_rank(5);

    set_spell_time_factor(&adjust_time_by_rank(1.5));
}

public string *query_delayedtrigger_ingredients(object caster) 
{
    return ({ "_naicelum_charge", "leftover" });
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("Your deathly essence is already poised to strike!\n");
}