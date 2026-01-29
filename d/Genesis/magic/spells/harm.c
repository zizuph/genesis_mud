#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>

static int harm_pen;

public void harm(object caster, object *targets, int *resist,
    int result);
public int create_spell_harm(object caster, object *targets,
    string argument);

public void
add_spell_harm()
{
    this_object()->add_spell("harm", "Harm a living target",
         create_spell_harm, spell_target_one_other_present_living);
}

public void
set_harm_pen(int pen)
{
    harm_pen = pen;
}

/*
 * Function name: create_spelL_harm
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public int
create_spell_harm(object caster, object *targets, string argument)
{
    set_spell_time(4);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(harm);
    set_spell_stationary(1);
    set_spell_offensive(1);
    
    set_harm_pen(200);

    return 0;
}

public mixed *
do_harm_damage(object caster, object target, int pen)
{
    return target->hit_me(pen, MAGIC_DT, caster, -1);
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
        case 0..20:
            how = "barely hurt";
            break;
        case 21..50:
            how = "slightly hurt";
            break;
        case 51..80:
            how = "somewhat hurt";
            break;
        case 81..110:
            how = "rather hurt";
            break;
        case 111..140:
            how = "hurt";
            break;
        case 141..170:
            how = "very hurt";
            break;
        default:
            how = "extremely hurt";
            break;
    }

    target->catch_tell("You feel " + how + ".\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
        how + ".\n");
    caster->tell_watchers(QCTNAME(target) + " appears " + how + ".\n",
        target);
}

public void
desc_casting(object caster, object *targets)
{
    string msg;

    caster->catch_tell("You channel your power into " + 
        FO_COMPOSITE_ALL_LIVE(targets, caster) + ".\n");

    msg = " extends " + caster->query_possessive() + 
        " clenched fist toward you.\n";
    targets->catch_tell(({
        caster->query_Met_name() +  msg,
        capitalize(caster->query_nonmet_name()) + msg,
        "" }));
                           
    targets->catch_tell("You feel a charge of magical energy surge " +
        "through your body.\n");

    caster->tell_watcher(QCTNAME(caster) + " extends " + 
        caster->query_possessive() + " clenched fist toward " +
        QCOMPLIVE + ".\n", targets);
}

/*
 * Function name: harm
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
harm(object caster, object *targets, int *resist, int result)
{
    int i;
    mixed *hitresult;

    desc_casting(caster, targets);

    for (i = 0; i < sizeof(targets); i++)
    {
        hitresult = do_harm_damage(caster, targets[i], 
            harm_pen * (100 - resist[i]) / 100);
        desc_harm_damage(caster, targets[i], hitresult);
         
        if (targets[i]->query_hp() <= 0)
	{
            targets[i]->do_die(caster);
	}
    }
}
