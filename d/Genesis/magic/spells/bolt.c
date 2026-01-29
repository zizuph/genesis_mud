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
#include "/std/combat/combat.h"

static int bolt_pen;
static string bolt_desc;
static function casting_msg_func, damage_msg_func, miss_msg_func;

public void bolt(object caster, object *targets, int *resist, int result);
public int create_spell_bolt(object caster, object *targets, string argument);
public void desc_bolt_damage(object caster, object target, mixed *result);
public void desc_bolt_miss(object caster, object target);
public void desc_bolt_casting(object caster, object *targets);


public void
add_spell_bolt()
{
    this_object()->add_spell("bolt", "Shoot a bolt of magical energy",
         create_spell_bolt, spell_target_one_other_present_living);
}

/*
 * Function name: set_bolt_pen
 * Description:   Set the "pen" for the attack.  Damage is calculated
 *                from this value.
 * Arguments:     int pen - the pen value
 */
public void
set_bolt_pen(int pen)
{
    bolt_pen = pen;
}

/*
 * Function name: set_bolt_desc
 * Description:   Set the description or type of the bolt (ice, water,
 *                fire, etc.)
 * Arguments:     string desc - the bolt description
 */
public void
set_bolt_desc(string desc)
{
    bolt_desc = desc;
}

/*
 * Function name: set_bolt_casting_msg
 * Description:   Designate a function to be called when the
 *                spell is cast but before the bolt hits.  This should
 *                be used to give an appropriate casting message.
 * Arguments:     function f - the function to call
 */
public void
set_bolt_casting_msg(function f)
{
    casting_msg_func = f;
}

/*
 * Function name: set_bolt_damage_msg
 * Description:   Designate a function to be called to produce damage
 *                messages
 * Arguments:     function f - the function to call
 */
public void
set_bolt_damage_msg(function f)
{
    damage_msg_func = f;
}

/*
 * Function name: set_bolt_miss_msg
 * Description:   Designate a function to be called to produce messages
 *                when a bolt misses the target.
 * Arguments:     function f - the function to call
 */
public void
set_bolt_miss_msg(function f)
{
    miss_msg_func = f;
}

/*
 * Function name: create_spell_bolt
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public int
create_spell_bolt(object caster, object *targets, string argument)
{
    set_spell_time(4);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(bolt);
    set_spell_stationary(1);
    set_spell_offensive(1);
    
    set_bolt_pen(200);
    set_bolt_desc("fire");
    set_bolt_casting_msg(desc_bolt_casting);
    set_bolt_damage_msg(desc_bolt_damage);
    set_bolt_miss_msg(desc_bolt_miss);


    return 0;
}

public mixed *
do_bolt_damage(object caster, object target, int pen)
{
    int ran, i, j, hit, *hloc_ids, ac;
    object cob;
    mixed *hloc;

    /* Pick a hitlocation and apply armour mod to pen */
    ran = random(100);

    cob = target->query_combat_object();
    hloc_ids = cob->query_hitloc_id();
    hit = -1;
    j = 0;
    
    for (i = 0; i < sizeof(hloc_ids); i++)
    {
        hloc = cob->query_hitloc(hloc_ids[i]);
    
        j += hloc[HIT_PHIT];
        if (j >= ran)
	{
            hit = hloc_ids[i];
            ac = (intp(hloc[HIT_AC]) ? 
                hloc[HIT_AC] : hloc[HIT_AC][random(sizeof(hloc[HIT_AC]))]);
            pen -= random(ac / 2);
            break;
	}
    }

    return target->hit_me(pen, MAGIC_DT, caster, hit);
}

public void
desc_bolt_damage(object caster, object target, mixed *result)
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
desc_bolt_miss(object caster, object target)
{
    string bolt = "The bolt of " + bolt_desc + " misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher_miss(bolt + QCTNAME(target) + ".\n", target);
}

public void
desc_bolt_casting(object caster, object *targets)
{
    string msg, pos, bolt;

    pos = caster->query_possessive();
    bolt = ", and " + ((sizeof(targets) > 1) ? "bolts" : "a bolt") +
        " of " + bolt_desc + ((sizeof(targets) > 1) ? " shoot" : " shoots") +
        " from %s palm.\n";

    caster->catch_tell("You extend your arm toward " +
        FO_COMPOSITE_ALL_LIVE(targets, caster) + sprintf(bolt, "your"));

    msg = " extends " + pos + " arm toward you, and a bolt of " + 
        bolt_desc + " shoots from " + pos + " palm.\n";
    targets->catch_msg(({
        caster->query_Met_name() +  msg,
        capitalize(caster->query_nonmet_name()) + msg,
        "" }));
                           
    caster->tell_watcher(QCTNAME(caster) + " extends " + pos + 
        " arm toward " + QCOMPLIVE + sprintf(bolt, pos), targets);
}

public int
try_to_hit(object caster, object target)
{
    /* Should make a better formula */
    return (target->resolve_task(TASK_DIFFICULT, ({ TS_DEX, SS_DEFENSE })) > 0);
}

/*
 * Function name: bolt
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
bolt(object caster, object *targets, int *resist, int result)
{
    int i;
    mixed *hitresult;

    if (casting_msg_func)
    {
        casting_msg_func(caster, targets);
    }

    for (i = 0; i < sizeof(targets); i++)
    {
        if (!try_to_hit(caster, targets[i]))
	{
            if (miss_msg_func)
	    {
                miss_msg_func(caster, targets[i]);
	    }

            return;
	}

        hitresult = do_bolt_damage(caster, targets[i], 
            bolt_pen * (100 - resist[i]) / 100);

        if (damage_msg_func)
	{
            damage_msg_func(caster, targets[i], hitresult);
	}
         
        if (targets[i]->query_hp() <= 0)
	{
            targets[i]->do_die(caster);
	}
    }
}

