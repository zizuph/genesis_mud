/*
 * A general healing spell.  Inherit this and reconfigure it for your own
 * specific purposes.
 *
 * Example:
 *
 * inherit "/d/Genesis/newmagic/spells/heal";
 *
 * public varargs int
 * config_spell(object caster, object *targets, string argument)
 * {
 *     if (::config_spell(caster, targets, argument))
 *     {
 *         return 1;
 *     }
 *
 *     set_spell_ingredients({ "quartz gem" });
 *     set_spell_mana(50);
 *     set_heal_amount(400);
 * }
 */
#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <ss_types.h>
#include <composite.h>

public int healing;

/*
 * Function name: set_heal_amount
 * Description:   Indicate how many hps this spell should heal.
 * Arguments:     int amnt - healing amount in hps
 */
public void
set_heal_amount(int amnt)
{
    healing = amnt;
}

/*
 * Function name: query_heal_amount
 * Description:   Returns the base hps this spell heals.  This can be
 *                redefined if you want to calculate hps on an individual
 *                basis.
 * Arguments:     object caster - the caster
 *                object target - the target
 * Returns:       Base healing amount in hps.
 */
public int
query_heal_amount(object caster, object target)
{
    return healing;
}

public void
create_heal()
{
}

public void
create_spell()
{
    set_spell_name("heal");
    set_spell_desc("Heal injuries.");
    set_spell_target(spell_target_one_present_living);

    set_spell_time(8);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_LIFE, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_ingredients(({}));
    set_spell_resist(spell_resist_healing);
    set_spell_target_verify(spell_verify_present);

    set_heal_amount(600);

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();

    create_heal();
}

/*
 * Function name: desc_heal
 * Description:   Describe the spell casting and effect.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object *targets - the targets
 *                int *heal - Healing in hps for each target
 */
public void
desc_heal(object caster, object *targets, int *heal)
{
    int i, index;
    string who;

    if ((index = member_array(caster, targets)) >= 0)
    {
        who = COMPOSITE_WORDS (map(targets - ({ caster }),
            &->query_the_name(caster)) + ({ "yourself" }));
    }
    else
    {
        who = FO_COMPOSITE_ALL_LIVE(targets, caster);
    }

    caster->catch_tell("You aid " + who + " with your healing powers.\n");

    for (i = 0; i < sizeof(targets); i++)
    {
        if ((heal[i] < 1) ||
            (targets[i]->query_hp() >= targets[i]->query_max_hp()))
        {
	    targets[i]->catch_tell("A pleasant warmth briefly overcomes " +
                "you and quickly fades.\n");
	}
	else
	{
	    targets[i]->catch_tell("A pleasant warmth briefly overcomes " +
                "you as you feel your injuries healing.\n");
	}
    }
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
    int i, *heal = allocate(sizeof(targets));

    for (i = 0; i < sizeof(heal); i++)
    {
        heal[i] = (100 - resist[i]) *
            query_heal_amount(caster, targets[i]) / 100;
        targets[i]->heal_hp(heal[i]);
    }

    desc_heal(caster, targets, heal);
}
