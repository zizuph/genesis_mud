/*
 * Vimmort
 *
 * Description: Death Spell
 * Class: 3
 * Ingredients: An Opal
 * Mana: 600
 * TaxL ??
 * Skills: SS_ELEMENT_DEATH    50
 *         SS_FORM_ENCHANTMENT 10
 * Task:   TASK_ROUTINE
 *
 * By Rastlin
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>

public int
do_vimmort(string str)
{
    return cast_spell();
}

public void
vimmort_message(object caster, object enemy, mixed hr)
{
    find_player("karath")->catch_msg(sprintf("Vimmort: %d\n", enemy->query_hp()));
    enemy->catch_msg(QCTNAME(caster) + " points at you whispers something " +
		     "unintelligable. Suddenly you feel your soul being "+
		     "wrenched violently as " + POSSESSIVE(caster) +
		     " eyes burn with a fierce hatred directed at you!\n");

    tell_room(E(caster), QCTNAME(caster) + " points at " + QTNAME(enemy) + 
              " and whispers something unintelligable. Suddenly " +
	      QTNAME(enemy) + " turns white and clutches " +
	      POSSESSIVE(enemy) + " chest!\n", ({ caster, enemy }));

    caster->catch_msg("You point at " + QTNAME(enemy) + " and whisper " +
		      POSSESSIVE(enemy) + " doom. " +
		      capitalize(OBJECTIVE(enemy)) +
		      " grabs " + POSSESSIVE(enemy) + " chest and looks "+
		      "at you in absolute horror!\n");
}

public int
vimmort_damage(object caster, object target, int result)
{
    int t;

    if (!result)
        return 0;

    /*
    t = ((result + random((25 * result) - target->query_stat(SS_CON)) +
	 (caster->query_skill(SS_ELEMENT_DEATH) -
	 target->query_stat(SS_CON)) * 5));
	 */

    if( ( target->query_stat(SS_CON) * 2 ) <
	( caster->query_skill(SS_ELEMENT_DEATH) + random(result) ) )
      { return 5000; }

    t = 3 * ( result + (10 * random(result) +
	 caster->query_skill(SS_ELEMENT_DEATH) ) );

    find_player("karath")->catch_msg(sprintf("Vimmort: t = %d result = %d targhp = %d targcon = %d\n", t, result, target->query_hp(), target->query_stat(SS_CON)));

    /* return (t < 0 ? 0 : t); */
    return t;
}

public int
create_spell_vimmort()
{
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_DEATH, 90);
    set_spell_form(SS_FORM_ENCHANTMENT, 70);

    set_spell_time(3);

    set_spell_attack();
    set_damage_type(MAGIC_DT);

    set_spell_mana(600);
    set_spell_task(TASK_ROUTINE);
    set_spell_ingredients("opal");
    set_spell_fail(spell_wohs_fail);

    set_find_target(find_one_living_target);
    set_spell_message(vimmort_message);
    set_spell_damage(vimmort_damage);
}
