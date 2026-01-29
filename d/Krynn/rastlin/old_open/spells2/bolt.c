/*
 * Bolt
 *
 * by Rastlin 950610
 */

#include <ss_types.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>

public object *bolt_target(string arg);
public void bolt_message(object caster, object target, mixed hitresults);
public void bolt_fail();
public int bolt_damage(object caster, object target, int result);
public int bolt_resist(object target);

public void
create_spell_bolt()
{
    set_spell_element(SS_ELEMENT_FIRE, 34);
    set_spell_form(SS_FORM_CONJURATION, 20);

    set_spell_time(5);
    set_spell_attack();
    set_damage_type(W_IMPALE);

/*    set_ingredients("cotton wool"); */

    set_spell_mana(5);
    set_find_target(bolt_target);
    set_spell_task(TASK_SIMPLE);
    
    set_spell_message(bolt_message);
    set_spell_fail(bolt_fail);
    set_spell_damage(bolt_damage);
    set_spell_resist(bolt_resist);
}

public int
bolt(string str)
{
    return cast_spell();
}

public object *
bolt_target(string str)
{
    object ob;

    if (!str || !strlen(str))
    {
	ob = query_caster()->query_attack();
        if (ob)
	    return ({ ob });

	write("You are not fighting anyone.\n");
	return 0;
    }
    else
    {
	ob = present(str, environment(query_caster()));

	if (ob)
	{
	    if (ob == query_caster())
	    {
		write("Cast the Bolt on yourself?\n");
		return 0;
	    }
	    if (!living(ob))
	    {
		write("No such living here.\n");
		return 0;
	    }
            return ({ ob });
	}
	write("No such thing here.\n");
	return 0;
    }
}

public void
bolt_message(object caster, object target, mixed hitresults)
{
    string how, bolt;
    int dam = hitresults[3];

    switch(hitresults[0])
    {
	case 0..5:
	    how = "licks "; break;
	case 6..15:
	    how = "scorches "; break;
	case 16..30:
	    how = "burns "; break;
	case 31..50:
	    how = "whithers "; break;
	case 51..90:
	    how = "shrivels "; break;
	default:
	    how = "consumes "; break;
    }

    if (dam > 600)
	bolt = "big white bolt ";
    else
	if (dam > 300)
	    bolt = "white bolt ";
	else
	    bolt = "small bolt ";

    caster->catch_msg("You point at " + QTNAME(target) + " and a " +
		      bolt + "shoots out from your finger tips, it " +
		      how + "its target.\n");

    target->catch_msg(QCTNAME(caster) + " points at you and a " +
		      bolt + "shoots out from " + caster->query_pronoun() +
		      " finger tips, the fire ball " + how + "you.\n");

    tell_room(environment(caster), QCTNAME(caster) + " points at " +
	      QTNAME(target) + " and a " + bolt + "shoots out from " +
	      caster->query_pronoun() + " finger tips, the fire ball " +
	      how + QTNAME(target) + ".\n", ({caster, target}));
}

public int
bolt_damage(object caster, object target, int result)
{
    return F_PENMOD(75 + result/4, caster->query_skill(SS_SPELLCRAFT) + result);
}

public void
bolt_fail()
{
    tell_room(environment(query_caster()), "Rastlin frowns.\n");
    write("A small flame appears in your hand. " +
	"Your spell failed.\n");
}

public int
bolt_resist(object target)
{
    return target->query_magic_res(MAGIC_I_RES_FIRE);
}
