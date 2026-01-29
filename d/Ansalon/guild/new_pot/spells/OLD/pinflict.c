/*
 * pInflict
 */
 
#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "../spells.h"
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

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
    object ob;
    
    caster->catch_tell("You clutch your medallion as you utter " +
        "a curse at " + QTNAME(tar) + ".\n" + QCTNAME(tar) +
        " hulks over as if struck.\n");
    tar->catch_tell("As " + QTNAME(caster) + " utters a curse " +
        "you hulk over in pain.\n");
    all_msg("As " + QTNAME(caster) + " utters a curse, " +
        QTNAME(tar) + " hulks over as if struck.\n", caster, tar);

    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(INFLICT_OBJ, caster, tar, resist, result);
    ob->set_pinflict_time(600 - (tar->query_stat(SS_DIS) * 2));
}

public object *
pinflict_target(object caster, string str)
{
    if (!stringp(str) || (str == ""))
        return spell_target_one_present_enemy(caster, str);
    else
        return spell_target_one_other_present_living(caster, str);
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
    set_spell_name("pinflict");
    set_spell_desc("Curse someone spiritually and physically");

    set_spell_time(5);
    set_spell_mana(150);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE, 60);
    set_spell_form(SS_FORM_ENCHANTMENT, 60);
    set_spell_ingredients(({ "diamond", "nail" }));
    set_spell_resist(spell_resist_basic);
    set_spell_target(pinflict_target);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_offensive(1);

    return 0;
}
