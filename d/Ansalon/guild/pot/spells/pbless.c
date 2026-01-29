/*
 * pBless
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
    return 9;
}

void
do_bless(object caster, object target, int resist, int result)
{
    setuid();
    seteuid(getuid());
    make_spell_effect_object(BLESS_OBJ, caster, target, resist, result);
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
    object *onlookers;
    string s;

    if (caster == tar)
    {
    	if (present(BLESS_ID,tar))
    	{
    	    caster->catch_tell("You are already blessed by Takhisis, and " +
    	    "the spell has no effect.\n");
    	    return;
    	}
        caster->catch_tell("You invoke Takhisis' blessing against the " +
        "forces of good. You feel a warm touch over your body and you " +
        "know you are less vulnerable to attacks by the goodaligned.\n");

        all_msgbb(QCTNAME(caster) + " blesses " + HIM(caster) + "self in " +
        "the name of Takhisis, Queen of Darkness.\n", caster);

        do_bless(caster, caster, resist[0], result);
        
        return;
    }

    if (present(BLESS_ID,tar))
    {
        caster->catch_tell(tar->query_The_name(caster) + " is already " +
        "blessed, so the spell has no effect.\n");
        return;
    }

    caster->catch_tell("You bless " + tar->query_the_name(caster) + " in " +
    "the name of Takhisis, Queen of Darkness.\n");

    tar->catch_tell(caster->query_The_name(tar) + " blesses you in the " +
    "name of Takhisis, Queen of Darkness. You feel a warm touch over your " +
    "body and you know you are less vulnerable to attacks by the forces " +
    "of good.\n");

    all_msgbb(QCTNAME(caster) + " blesses " + QTNAME(tar) + " in the name " +
    "of Takhisis, Queen of Darkness.\n", caster, tar);

    do_bless(caster, tar, resist[0], result);
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
    set_spell_name("pbless");
    set_spell_desc("Invoke the Dark Queen's blessing");

    set_spell_time(10);

    if (caster && targets && targets[0] != caster)
        set_spell_mana(125);
    else
        set_spell_mana(85);

    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE,  60);
    set_spell_form(SS_FORM_ENCHANTMENT, 60);
#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"onoclea"}));
#endif
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(spell_target_one_present_living);

    set_spell_target_verify(spell_verify_present);
    set_spell_vocal(1);
    set_spell_peaceful(1);
    set_spell_stationary(1);

    return 0;
}
