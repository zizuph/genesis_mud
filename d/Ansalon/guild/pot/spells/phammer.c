/*
 * pHammer
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <cmdparse.h>
#include <tasks.h>  
#include <wa_types.h>

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 7;
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
    object ob, tar = targets[0];

    if (result < 5 || resist[0] >= min(result, 100) ||
        tar->query_phammer_object() == 1)
    {
        caster->catch_tell("You chant silently and around the " +
            tar->query_name() + " a glow briefly flickers only " +
            "to die out just as quick.\n");
        all_msgbb(QCTNAME(caster) + " chants silently and around " +
            "the " + tar->query_name() + " a glow briefly flickers " +
            "only to die out just as quick.\n", caster);
        return;
    }

    if (tar->query_phammer_object() == -1)
    {
        caster->catch_tell("You chant silently and around the " +
            tar->query_name() + " a faint glow begins to show, but " +
            "fades almost immediately.\n");
        all_msgbb(QCTNAME(caster) + " chants silently and around " +
            "the " + tar->query_name() + " faint glow begins to " +
            "show but fades almost immediately.\n", caster);
        return;
    }

    caster->catch_tell("You chant silently and around the " +
        tar->query_name() + " a faint glow begins to show, increasing in " +
        "strength to suddenly engulf the weapon in a spiritual swirling " +
        "glow.\n");
    all_msgbb(QCTNAME(caster) + " chants silently and around the " +
        tar->query_name() + " a faint glow begins to show, increasing in " +
        "strength to suddenly engulf the weapon in a spiritual swirling " +
        "glow.\n", caster);
        
    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(HAMMER_OBJ, caster, tar, resist, result);
    ob->set_time(1200 + (caster->query_priest_level() * 60 + result));
    ob->set_skill(((min(100, result) / 10) + 5) * caster->query_priest_level());
}

public object *
phammer_target(object caster, string str)
{
    object *arr;
    
    if (!stringp(str))
    {
        caster->catch_tell("You need a target.\n");
        return ({ });
    }
    
    arr = FIND_STR_IN_OBJECT(str, caster);
    if (!sizeof(arr))
    {
        caster->catch_tell("You need a target.\n");
        return ({ });
    }
    
    if (sizeof(arr) >= 2)
    {
        caster->catch_tell("Multiple targets would probably be a bad idea.\n");
        return ({ });
    }
    
    if (!arr[0]->query_weapon() && arr[0]->query_wt() != W_CLUB)
    {
        caster->catch_tell("The target must be a club.\n");
        return ({ });
    }

    return arr;
}

object
holy_water_ingr(object *possible, object *found)
{
    object *list;
    int i;
    
    list = possible - found;
    for (i = 0 ; i < sizeof(list) ; i++)
    {
        if (list[i]->query_is_takhisis_unholy_water())
            return list[i];
        if (member_array("holy water", list[i]->query_names()) >= 0)
            return list[i];
    }

    return 0;
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
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("phammer");
    set_spell_desc("Bless a bludgeon weapon");

    set_spell_time(6);
    set_spell_element(SS_ELEMENT_AIR,  38);
    set_spell_form(SS_FORM_ENCHANTMENT, 39);
    set_spell_mana(95);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(phammer_target);
    set_spell_target_verify(spell_verify_present);

#ifndef NO_INGREDIENTS
//    set_spell_ingredients(({"holy water","tuo"}));
    set_spell_ingredients(({holy_water_ingr,"tuo"}));
#endif

    return 0;
}
