/*
 * Blast
 *
 * by Rastlin 950624
 */

#include <ss_types.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <macros.h>
#include <tasks.h>
#include <formulas.h>
#include <stdproperties.h>

public object *blast_target(string arg);
public void blast_message(object caster, object target, mixed hitresults);
public mixed blast_success(object caster, object *targets);
public void blast_fail();
public int blast_damage(object caster, object target, int result);
public int blast_resist(object target);

public void
create_spell_blast()
{
    set_element(SS_ELEMENT_FIRE, 34);
    set_form(SS_FORM_CONJURATION, 20);

    set_spell_time(5);
    set_spell_attack();
    set_damage_type(W_IMPALE);

/*    set_ingredients("cotton wool"); */

    set_mana_spell(5);
    set_find_target(blast_target);

    set_spell_message(blast_message);
    set_spell_success(blast_success);
    set_spell_fail(blast_fail);
    set_spell_damage(blast_damage);
    set_spell_resist(blast_resist);
}

public int
blast(string str)
{
    tell_room(environment(query_caster()), "Suddenly it starts to blow " +
	      "very hot winds and you can see a few flames above your " +
	      "head.\n");
    return cast_spell();
}

public object *
blast_target(string str)
{
    object *enemies;

    if (!str || !strlen(str))
    {
        enemies = query_caster()->query_enemy(-1);
        enemies = (all_inventory(environment(query_caster())) & enemies);

        if (enemies)
	    return enemies;

	write("You are not fighting anyone.\n");
	return 0;
    }
    else
    {
	enemies = CMDPARSE_ONE_ITEM(str, "kill_access", "kill_access");

	if (enemies)
	    return enemies;

	write("No such thing here.\n");
	return 0;
    }
}

public void
blast_message(object caster, object target, mixed hitresults)
{
    string how, blast;
    int dam = hitresults[3];

    switch(hitresults[0])
    {
        case 0:
            how = "doesn't harm "; break;
	case 1..5:
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
	blast = "huge fire blast ";
    else
	blast = ((dam > 300) ? "fire blast " : "small fire blast ");

    caster->catch_msg("You point at " + QTNAME(target) + " and a " +
		      blast + how + "its target.\n");

    target->catch_msg(QCTNAME(caster) + " points at you and a " +
		      blast + how + "you.\n");

    tell_room(environment(caster), QCTNAME(caster) + " points at " +
	      QTNAME(target) + " and a " + blast + how + 
	      target->query_objective() + ".\n", ({caster, target}));
}

public int
blast_damage(object caster, object target, int result)
{
    if (!result)
        return 0;
    return F_PENMOD(75 + result/4, caster->query_skill(SS_SPELLCRAFT) + result);
}

public mixed
blast_success(object caster, object *targets)
{
    int *result = ({}), i = -1, size, tmp;

    size = sizeof(targets);

    while (++i < size)
    {
        if ((tmp = caster->resolve_task(TASK_ROUTINE,
            ({ TS_WIS, SKILL_AVG, SS_SPELLCRAFT, SS_ELEMENT_FIRE,
               SS_FORM_CONJURATION, SKILL_END }) )) <= 0)
            tmp = 0;
        result += ({ tmp });
    }
    return result;
}

public void
blast_fail()
{
    tell_room(environment(query_caster()), QCTNAME(query_caster()) + " frowns.\n");
    write("A small flame appears in your hand. " +
	"Your spell failed.\n");
}

public int
blast_resist(object target)
{
    return target->query_magic_res(MAGIC_I_RES_FIRE);
}

