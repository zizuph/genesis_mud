#pragma strict_types

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../morgulmage.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"
#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public object *narusse_target(object caster, string str);
public string *query_narusse_ingredients(object caster);

public nomask void
config_spell()
{
    set_spell_name("narusse");
    set_spell_desc("Summon the fires of Orodruin");
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_form(SS_FORM_ENCHANTMENT, 20);
    set_spell_element(SS_ELEMENT_FIRE, 20);
    
    set_spell_task(TASK_HARD);
   
    set_spell_mana(30);
    set_spell_time(4);
     
    set_spell_target(narusse_target);
    set_spell_ingredients(query_narusse_ingredients);
    set_spell_object(MORGUL_SPELL_OBJ_DIR + "narusse");

    set_morgul_rank(3);

    set_spell_time_factor(adjust_time_by_rank);
}

object find_narusse_object(object ob) 
{
    object *effects = ob->query_magic_effects();
    foreach(object effect : effects) 
    {
        if (MASTER_OB(effect) == query_spell_object()) return effect;
    }
    return 0;
}

public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    caster->catch_msg("You shout in a rasping voice: Tulo lacho Orodruin! "
        + "Minno russenna!\n");
    tell_room(environment(caster), QCTNAME(caster)+ " calls out in "
        + "a dark rasping voice: Tulo lacho Orodruin! Minno russenna!\n", caster);

    // Remove narusse effects applied before
    foreach (object target : targets)
    {
        object existing_effect = find_narusse_object(target);
        if (objectp(existing_effect)) existing_effect->dispel_effect(caster);
    }
    
    add_maintained_spell_effect(caster,
        make_spell_effect_object(query_spell_object(), caster, targets, resist, result));

    MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    // Make sure narusse is not already applied for this caster
    foreach (object target : targets)
    {
        object enhancement = find_narusse_object(target);
        if (objectp(enhancement)) {
            if (enhancement->query_spell_effect_caster() == caster) 
            {
                caster->catch_tell("The " + target->short() + " is already "
                     + "under the effect of the narusse spell\n");
                return 0;
            }
        }
    }
    
    return result;    
}

public object *narusse_target(object caster, string str) 
{
    object *weapons = caster->query_weapon(-1);
    if (!sizeof(weapons)) {
        caster->catch_tell("You don't have a weapon wielded.\n");
        return ({ });
    }
    
    object *enhanced_weapons = filter(weapons, objectp @ find_narusse_object);
    if (sizeof(enhanced_weapons)) return enhanced_weapons;
    
    weapons = filter(weapons, &operator(==)(W_SWORD) @ &->query_wt());
    if (sizeof(weapons)) return ({ weapons[0] });
    
    caster->catch_tell("You can only summon the fires of Oroduin on a sword.\n");
    return ({ });
}

public string *
query_narusse_ingredients(object caster)
{
    return ({ "_nennaur_charge" });
}
