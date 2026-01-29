/*
 * pCurse
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 3;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;

    set_this_player(caster);
    caster->catch_tell("You take a deep breath and concentrate.\n");
    all_msg(QCTNAME(caster) + " takes a deep breath and concentrates.\n",
        caster);
    set_this_player(old_tp);
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
    object tar = targets[0];
    string s;

    if (caster == tar)
    {
        caster->catch_tell("You curse yourself for being stupid.\n");
        return;
    }

    if (P(PARA_ID,tar))
    {
        caster->catch_tell(tar->query_The_name(caster) + " is already " +
        "cursed, and the spell has no additional effect.\n");
    }

    s = "In the name of Takhisis, Queen of Darkness, by Zeboim of the " +
    "Deep Seas and Chemosh the Lord of Death, by Sargonnas the Dark " +
    "Vengeance, be you cursed!";

    caster->catch_tell("You point at " + tar->query_the_name(caster) +
    " and utter in a cold voice: " + s + "\n");

    tar->catch_tell(caster->query_The_name(tar) + " points at you and " +
    "utters in a cold voice: " + s + "\n");

    all_msg(QCTNAME(caster) + " points at " + QTNAME(tar) + " and utters " +
    "in a cold voice: " + s + "\n", caster, tar);

    if (resist[0] > result)
        return;

    setuid();
    seteuid(getuid());
    make_spell_effect_object(PARA_OBJ,
        caster, tar, resist, result);
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
    set_spell_name("pcurse");
    set_spell_desc("Curse your foe");

    set_spell_element(SS_ELEMENT_LIFE,  10);
    set_spell_form(SS_FORM_ENCHANTMENT, 15);

    set_spell_time(2);
    set_spell_mana(28);

    set_spell_task(TASK_SIMPLE);

    set_spell_resist(spell_resist);
    set_spell_target(spell_target_one_present_living);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    set_spell_vocal(1);
    
    return 0;
}
