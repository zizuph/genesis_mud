/*
 * A fireball spell
 * It is called from Rastlin's magic book.
 * 1994 by Rastlin.
 */
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>

void
create_spell_fireball(string arg)
{
    set_spell_element(SS_ELEMENT_FIRE, 20);
    set_spell_time(2);
    set_spell_mana_needed(10);
    set_spell_form(SS_FORM_ABJURATION, 10);
    set_spell_attack();
    set_spell_message("fireball_message");
    set_spell_damage("fireball_damage");
    set_spell_dt(W_IMPALE);
}

mixed
do_fireball(string arg)
{
    if (spell_attack)
    { 
	caster->add_prop(LIVE_O_SPELL_ATTACK, this_object());
	caster->attack_object(targets[0]);
    }
    return 1;
}

int
fireball_damage(object attacker)
{
    return F_PENMOD(30, 
        MIN(attacker->query_stat(SS_OCCUP) +
            attacker->query_skill(query_spell_element()) +
            attacker->query_skill(query_spell_form()), 80));
}

public void
fireball_message(object attacker, object enemy, int result)
{
    attacker->catch_msg("You hit " + QTNAME(enemy) + " with a fireball.\n");
    enemy->catch_msg(QCTNAME(attacker) + " points at you.\n" +
		      "You are hit by a fireball.\n");
    say(QCTNAME(attacker) + " points at " + QTNAME(enemy) + "\n" 
    + QTNAME(enemy) + " is hit by a fireball.\n", ({attacker, enemy}));
}


