/*
 * Implementation of a general bolt-type damage spell.  Bolt spells
 * conjure matter or energy and direct it at a target.  A bolt can
 * be dodged, but basic magic resistance is used, not standard (see
 * resist.c)
 *
 * Inherit this and reconfigure it for your particular type of bolt.
 * 
 * Example:
 * 
 * inherit "/d/Genesis/newmagic/spells/bolt";
 * 
 * #include <ss_types.h>
 * 
 * public varargs int
 * config_spell(object caster, object *targets, string argument)
 * {  
 *     ::config_spell(caster, targets, argument);
 * 
 *     set_spell_element(SS_ELEMENT_WATER, 60);
 *
 *     set_bolt_pen(800);
 *     set_bolt_desc("ice");
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
#include "/std/combat/combat.h"

static int bolt_pen;
static string bolt_desc;

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
    set_spell_name(desc + "bolt");
    set_spell_desc("Shoot a bolt of " + desc + " at a target.");
}

public void
create_bolt()
{
}

public void
create_spell()
{
    set_spell_time(4);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(1);
    set_spell_offensive(1);
    
    set_spell_target(spell_target_one_other_present_living);

    set_bolt_pen(200);
    set_bolt_desc("fire");

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();

    create_bolt();
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

    return target->hit_me(pen, MAGIC_DT, caster, -1, hit);
}

/*
 * Function name: desc_bolt_damage
 * Description:   Write out some text describing the damage done.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 *                mixed *result - return value from do_bolt_damage() call.
 */
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

/*
 * Function name: desc_bolt_miss
 * Description:   Write out some text describing the missed attack.  This can
 *                be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_miss(object caster, object target)
{
    string bolt = "The bolt of " + bolt_desc + " misses ";

    target->catch_tell(bolt + "you.\n");
    caster->catch_tell(bolt + target->query_the_name(caster) + ".\n");
    caster->tell_watcher_miss(bolt + QCTNAME(target) + ".\n", target);
}

/*
 * Function name: desc_bolt_cast
 * Description:   Describe casting of the spell, not including damage messages.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object target - the target
 */
public void
desc_bolt_cast(object caster, object *targets)
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

/*
 * Function name: try_to_hit
 * Description:   Test to see if the bolt hits a target.
 * Arguments:     object caster - the caster
 *                object target - the target
 * Returns:       1/0 - hit/missed
 */
public int
try_to_hit(object caster, object target)
{
    /* Should make a better formula */
    return (target->resolve_task(TASK_DIFFICULT, ({ TS_DEX, SS_DEFENSE })) > 0);
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

    desc_bolt_cast(caster, targets);

    for (i = 0; i < sizeof(targets); i++)
    {
        if (!try_to_hit(caster, targets[i]))
        {
            desc_bolt_miss(caster, targets[i]);
            continue;
        }

        hitresult = do_bolt_damage(caster, targets[i], 
            bolt_pen * (100 - resist[i]) / 100);

        desc_bolt_damage(caster, targets[i], hitresult);
         
        if (targets[i]->query_hp() <= 0)
        {
            targets[i]->do_die(caster);
        }
    }
}

