/*
 * pImprecate
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
    return 4;
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

    if (tar->query_pimprecate_object())
    {
        caster->catch_tell(tar->query_The_name(caster) + " is already " +
            "cursed, and the spell has no additional effect.\n");
    }

    if (result < 5 || resist[0] > result)
    {
        caster->catch_msg("You clutch your medallion as you utter " +
            "a curse at " + QTNAME(tar) + ".\n");
        tar->catch_msg(QCTNAME(caster) + " utters a curse at you.\n");
        all_msg(QCTNAME(caster) + " utters a curse at " + QTNAME(tar) +
            ".\n", caster, tar);

        return;
    }

    caster->catch_msg("You clutch your medallion as you utter a curse " +
        "at " + QTNAME(tar) + ".\n" + QCTNAME(tar) + " hulks over as " +
        "if struck.\n");
    tar->catch_msg("As " + QTNAME(caster) + " utters a curse you " +
        "hulk over in pain.\n");
    all_msg("As " + QTNAME(caster) + " utters a curse, " + QTNAME(tar) +
        " hulks over as if struck.\n", caster, tar);

    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(IMPRECATE_OBJ, caster, tar, resist, result);
    ob->set_time(max(10 + random(caster->query_skill(PS_GUILD_LEVEL) / 3),
        10 + random(caster->query_skill(PS_GUILD_LEVEL) / 3)) * 2);
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
                                                                        
public object *
pimprecate_target(object caster, string str)
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
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("pimprecate");
    set_spell_desc("Curse your foe by making him insecure");

    set_spell_time(5);
    set_spell_element(SS_ELEMENT_LIFE, 45);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_mana(85);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist_basic);
    set_spell_target(pimprecate_target);
    set_spell_stationary(0);
    set_spell_target_verify(spell_verify_present);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"ear", "locoweed"}));
//    set_spell_ingredients(({"nail", holy_water_ingr}));
#endif

    set_spell_vocal(1);
    set_spell_offensive(1);

    return 0;
}
