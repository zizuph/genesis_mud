/*
 * Implementation of a general harm-type damage spell.  Harm spells do
 * damage to a target directly, simply reducing hit points.  Unlike
 * bolt damage spells, they cannot be dodged.  They use standard
 * resistance rather than basic, though (see resist.c).
 *
 * Inherit this and reconfigure it for your particular harm spell.
 * 
 * Example:
 * 
 * inherit "/d/Genesis/newmagic/spells/harm";
 * 
 * #include <ss_types.h>
 * 
 * public varargs int
 * config_spell(object caster, object *targets, string argument)
 * {  
 *     ::config_spell(caster, targets, argument);
 * 
 *     set_spell_element(SS_ELEMENT_DEATH, 60);
 *
 *     set_harm_pen(800);
 *
 *     return 0;
 * }
 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>

static int harm_pen;

public void
set_harm_pen(int pen)
{
    harm_pen = pen;
}

public void
create_spell()
{
    set_spell_time(4);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(1);
    set_spell_offensive(1);

    set_spell_target(spell_target_one_other_present_living);
    
    set_harm_pen(200);

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();
}

public mixed *
do_harm_damage(object caster, object target, int pen)
{
    return target->hit_me(pen, MAGIC_DT, caster, -1);
}

/*
 * Function name: desc_harm_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
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

/*
 * Function name: desc_harm_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_harm_cast(object caster, object *targets)
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
    int i;
    mixed *hitresult;

    desc_harm_cast(caster, targets);

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
