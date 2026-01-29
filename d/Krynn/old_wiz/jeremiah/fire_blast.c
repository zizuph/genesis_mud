/*
 * Fire blast
 *
 * by jeremiah 950728
 */


#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>


public object *fireblast_target(string arg);
public void fireblast_message(object caster, object target, mixed hitresults);
public void fireblast_fail();
public int fireblast_damage(object caster, object target, int result);
public int fireblast_resist(object target);


public void
create_spell_fireblast()
{
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_CONJURATION, 20);

    set_spell_time(3);
    set_spell_attack();
    set_damage_type(MAGIC_DT);

    /* set_ingredients("red dragonscale"); */

    set_spell_mana(10); /* low mana cost for test purposes ONLY */
    set_find_target(fireblast_target);

    set_spell_message(fireblast_message);
    set_spell_fail(fireblast_fail);
    set_spell_damage(fireblast_damage);
    set_spell_resist(fireblast_resist);
}


public int
fire_blast(string str)
{
    return cast_spell();
}


public object *
fireblast_target(string str)
{
    object target;

    if (!str)
    {
       write("You need to specify a target.\n");
       return 0;
    }

    target = present(str,E(query_caster()));
 
    if(target == query_caster())
    {
       write("Are you mad ? Fireblast yourself ?\n");
       return 0;
    }

    if (!target)
    {
       write("There is no such ting here.\n");
       return 0;
    }

    if (!living(target))
    {
       write("You can only fireblast a living being.\n");
       return 0;
    }

    return ({ target });
}


public void
fireblast_message(object caster, object target, mixed hitresults)
{
    object *nomsg;
    string how;

    nomsg = ({ target }) + ({ caster });

    how = "unharmed";
    if (hitresults[0] > 0)
       how = "barely burned";
    if (hitresults[0] > 10)
       how = "slightly burned";
    if (hitresults[0] > 20)
       how = "burned quite badly";
    if (hitresults[0] > 40)
       how = "burned very badly";
    if (hitresults[0] > 60)
       how = "badly incinerated";

    target->catch_msg(QCTNAME(caster) + " stretches " + 
        POSSESSIVE(caster) + " hand towards you. A cone of fire burst " +
        "from " + POSSESSIVE(caster) + " palm and fingertips. You " +
        "stagger backwards as you are engulfed in an inferno of blazing " +
        "fire.\n" +
        "You are " + how + " by the fire.\n");

    tell_room(environment(target), QCTNAME(caster) + " stretches " +
        POSSESSIVE(caster) + " hand towards " + QCTNAME(target) + 
        ". A cone of fire bursts from " + POSSESSIVE(caster) + 
        " palm and fingertips. " + QCTNAME(target) + " reels backwards " +
        "and is engulfed in an inferno of blazing fire.\n" +
        QCTNAME(target) + " is " + how + " by the fire.\n", nomsg);

    caster->catch_msg("You stretch your hand towards " + 
        QCTNAME(target) + " and a cone of fire bursts from your " +
        "palm and fingertips. " + QCTNAME(target) + " reels backwards " +
        "and is engulfed in an inferno of blazing fire.\n" +
        QCTNAME(target) + " is " + how + " by your fire.\n");
}


int
fireblast_damage(object caster, object target, int result)
{
    return F_PENMOD(75 + result/4, caster->query_skill(SS_SPELLCRAFT) + result);
}


public void
fireblast_fail()
{
    tell_room(environment(query_caster()), QCTNAME(query_caster()) + 
       " looks confused.\n");
    write("Something went wrong! You feel your energies flow into " +
       "nothingness. Your spell failed.\n"); 
}

public int
fireblast_resist(object target)
{
    return target->query_magic_res(MAGIC_I_RES_FIRE);
}
