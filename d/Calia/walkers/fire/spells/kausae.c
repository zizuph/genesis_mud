
 /*
  *
  * Kausae (Combustion) spell for the Firewalkers of Thalassia
  * by Jaacar - November, 1997
  * Converted to the new spell system May 20th, 1998
  *
  * Revamped, Bishop, June 15th 1999.
  */

#pragma strict_types

inherit "/d/Genesis/magic/spells/bolt";

#include <ss_types.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "defs.h"
#include FIRE_HEADER

public int create_spell_kausae(object caster, object *targets, 
    string argument);
private void desc_kausae_casting(object caster, object *targets);
private void desc_kausae_damage(object caster, object target, 
    mixed *results);
private void desc_kausae_miss(object caster, object target);
public void kausae(object caster, object *targets, int *resist, int result);
public void set_damage(object caster);

public object *
kausae_target_present_enemies(object caster, string str)
{
    object *enemies = (object *)caster->query_enemy(-1) &
        all_inventory(environment(caster));


    /*
    if (!present("_kausae_potion_object_",caster))
    {
        caster->catch_tell("You are not under the effects of the "+
            "kausae potion!\n");
        return ({});
    }
    */

    if (!sizeof(enemies))
    {
        caster->catch_msg("There aren't any enemies present!\n");
        return ({});
    }

    return enemies;
}

public int
create_spell_kausae(object caster, object *targets, string argument)
{
    ::create_spell_bolt(caster, targets, argument);
    set_spell_time(1);
    set_spell_mana(250);
    set_spell_element(SS_ELEMENT_FIRE, 75);
    set_spell_form(SS_FORM_CONJURATION, 60);
    set_spell_offensive(1);
    set_spell_resist(spell_resist);
    set_spell_ingredients(({})); // Uses a potion
    set_spell_task(TASK_ROUTINE+100);
    set_bolt_damage_msg(desc_kausae_damage);
    set_bolt_casting_msg(desc_kausae_casting);
    set_bolt_miss_msg(desc_kausae_miss);
    set_spell_effect(kausae);
    set_damage(caster);
    return 0;
}


public void set_damage(object caster)
{
    int pen, task;

    task = caster->resolve_task(TASK_ROUTINE, ({ SKILL_WEIGHT,
        75, TS_OCC, SKILL_END, SKILL_WEIGHT, 25, TS_WIS, SKILL_END, SKILL_AVG,
        SS_FORM_CONJURATION, SS_ELEMENT_FIRE, SKILL_END}));
    pen = 150 + 4*caster->query_stat(SS_OCCUP) + 5*min(max(task, 0), 100);
    pen = min(pen, 1000); //Ceiling of 1000 pen for this bolt.
    set_bolt_pen(pen);
    if (caster->query_wiz_level())
    {
        caster->catch_msg("Bolt penetration is: " + pen + ".\n");
    }
}


private void
desc_kausae_casting(object caster, object *targets)
{
    caster->catch_msg("You complete the final words of the Kausae" +
        " incantation, and move your arm in a violent sweeping gesture." +
        " The air around you shimmers, then suddenly bursts into flames," +
        " much to the dismay of those who are fighting you.\n");
    caster->tell_watcher(QCTNAME(caster) + " completes the final words of" +
        " the spell, and moves " + caster->query_possessive() + " arm in a" +
        " violent sweeping gesture. The air around " 
        + caster->query_objective() + " shimmers, then suddenly bursts into" +
        " flames, much to the dismay of those who are fighting him.\n", 
        ({targets}));
    targets->catch_msg(QCTNAME(caster) + " completes the final words of" +
        " the spell, and moves " + caster->query_possessive() + " arm in a" +
        " violent sweeping gesture. The air around " 
        + caster->query_objective() + " shimmers, then suddenly bursts into" +
        " flames, much to your dismay.\n"); 

    if (caster->query_wiz_level())
    {
        caster->catch_msg("You will hit " + COMPOSITE_ALL_LIVE(targets) +
            ".\n");
    } 
}


private void
desc_kausae_damage(object caster, object target, mixed *result)
{
    string how;
    object ash;

    switch (result[0])
    {
        case 0..3:
            how = "singed";
            break;
        case 4..10:
            how = "slightly burned";
            break;
        case 11..20:
            how = "badly burned";
            break;
        case 21..35:
            how = "withered";
            break;
        case 36..53:
            how = "shrivelled";
            break;
        case 54..70:
            how = "roasted";
            break;
        default:
            how = "nearly consumed";
            break;
    }

    if (target->query_hp() <= 0)
    {
        caster->catch_msg(QCTNAME(target) + " is destroyed by the flames.\n");
        caster->tell_watcher(QCTNAME(target) + " is destroyed by the " +
            " flames.\n", target);
        target->catch_msg("Your body is completely consumed by the inferno," +
            " too quickly for you to feel much pain.\n");
        target->add_prop(LIVE_I_NO_CORPSE,1);
        seteuid(getuid());
        ash = clone_object("/d/Calia/walkers/fire/objects/ash");
        ash->move(environment(caster));
        target->do_die(caster);
    }
    else
    {
        caster->catch_msg(QCTNAME(target) + " is " + how +" by the flames.\n");
        caster->tell_watcher(QCTNAME(target) + " is " + how + " by the" +
            " flames.\n", target);
        target->catch_msg("You are " + how + " by the inferno around you.\n");
    }     
}

private void
desc_kausae_miss(object caster, object target)
{
    caster->catch_msg(QCTNAME(target) + " manages to avoid the flames" +
        " by doing some quick maneuvering.\n");
    caster->tell_watcher(QCTNAME(target) + " manages to avoid the flames" +
        " by doing some quick maneuvering.\n", target);
    target->catch_msg("You manage to avoid the flames by doing some quick" +
        " maneuvering.\n");
}

public void
kausae(object caster, object *targets, int *resist, int result)
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
	}
        else
        {
            hitresult = do_bolt_damage(caster, targets[i], 
                bolt_pen * (100 - resist[i]) / 100);

            damage_msg_func(caster, targets[i], hitresult);
        }
        
        if (targets[i]->query_hp() <= 0)
	{
            targets[i]->do_die(caster);
	}
    }
}

