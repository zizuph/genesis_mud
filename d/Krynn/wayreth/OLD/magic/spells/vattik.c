/*
 * Vattik
 *
 * Description: A simple combat spell, better known as 'Lightning Bolt'
 * Class: 3
 * Ingredients: A rib
 * Mana: 85
 * TaxL 4%?
 * Skills: SS_ELEMENT_AIR      14
 *         SS_FORM_ENCHANTMENT 10
 * Task:   TASK_EASY
 *
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>

public int
do_vattik(string str)
{
    return cast_spell();
}

public void
vattik_message(object caster, object enemy, mixed hr)
{
    string howhurt, howgood;

    log_file("vattik_log", sprintf("proc_hurt = %d, phit = %d, "+
	"dam = %d, caster = %s\n", hr[0], hr[2], hr[3],
	caster->query_real_name()));
    switch (hr[0])
      {
      case 0:
	howhurt = "unharmed";
	break;
      case 1..5:
	howhurt = "slightly shocked";
	break;
      case 6..15:
	howhurt = "shocked";
	break;
      case 16..30:
	howhurt = "heavily shocked";
	break;
      case 31..45:
	howhurt = "heavily shocked and burnt";
	break;
      case 46..65:
	howhurt = "heavily shocked and badly burnt";
	break;
      case 66..99:
	howhurt = "heavily shocked and horribly burnt";
	break;
      default:
	break;
      }

    switch (hr[3])
      {
      case 0..50:
	howgood = "jumps into";
	break;
      case 51..150:
	howgood = "strikes";
	break;
      case 151..400:
	howgood = "slams into";
	break;
      case 401..800:
	howgood = "explodes into";
	break;
      default:
	howgood = "devastatingly explodes into";
	break;
      }

	if(!howhurt)
	  {
    enemy->catch_msg(QCTNAME(caster) + " opens " + POSSESSIVE(caster) +
	" palm towards you and a bolt of lightning erupts from it and "+
	howgood + " your body, leaving what's left of your body crackling "+
	"and smouldering as you slump lifeless to the ground.\n");

    tell_room(E(caster), QCTNAME(caster) + " opens " + POSSESSIVE(caster) +
	" palm towards " + QTNAME(enemy) + " and a bolt of lightning "+
	"erupts from it and " + howgood + " the body of " + QTNAME(enemy) +
	" lifting " + OBJECTIVE(enemy) + " body into the air. Tendrils of "+
	"energy crackle from the body, causing the skin to smoulder, " +
	"then dissapating, letting the body lifelessly slump to the ground.\n",
	({ caster, enemy })); 

    caster->catch_msg("You open your palm towards " + QTNAME(enemy) +
	" and release a bolt of lightning that " + howgood + " " +
	 POSSESSIVE(enemy) + " body, lifting "+ OBJECTIVE(enemy) +
	" into the air. Tendrils of energy crackle from it, causing the "+
	"skin to smoulder, then dissapating, letting the body lifelessly "+
	"slump to the ground.\n");
	  }
	else
	  {
    enemy->catch_msg(QCTNAME(caster) + " opens " + POSSESSIVE(caster) +
	" palm towards you and a bolt of lightning erupts from it and "+
	howgood + " your body, leaving you " + howhurt + ".\n");

    tell_room(E(caster), QCTNAME(caster) + " opens " + POSSESSIVE(caster) +
	" palm towards " + QTNAME(enemy) + " and a bolt of lightning "+
	"erupts from it and " + howgood + " the body of " + QTNAME(enemy) +
	" leaving " + OBJECTIVE(enemy) + " " + howhurt + ".\n", ({ caster,
								    enemy })); 

    caster->catch_msg("You open your palm towards " + QTNAME(enemy) +
	" and release a bolt of lightning that " + howgood + " " +
	POSSESSIVE(enemy) + " body, leaving "+ OBJECTIVE(enemy) +
	" " + howhurt + ".\n");
	  }
}

public int
vattik_damage(object caster, object target, int result)
{
    int t, res;
    string lightningsize;

    if (!result)
        return 0;

    t = 100 + (300 * (caster->query_wohs_level() / 6)) +
	 (result * (caster->query_wohs_level() / 6));

    t = ((t > 1200) ? 1200 : t);

    log_file("vattik_log", sprintf("t = %d, result = %d\n", t, result));

    switch(t)
      {
      case 0..400:
	lightningsize = "small crackling ball of energy";
	break;
      case 401..700:
	lightningsize = "crackling ball of energy";
	break;
      case 701..1000:
	lightningsize = "large crackling ball of energy";
	break;
      case 1001..1100:
	lightningsize = "huge crackling ball of energy";
	break;
      case 1101..10000:
	lightningsize = "massive crackling ball of energy";
	break;
      }

    res = MAX(target->query_magic_res(MAGIC_I_RES_MAGIC),
	target->query_magic_res(MAGIC_I_RES_ELECTRICITY));

    t = ( t * (100 - res) / 100 );

    tell_room(E(caster), QCTNAME(caster) + " whispers words of power and " +
	"starts to shape a " + lightningsize + " between " +
	POSSESSIVE(caster) + " hands.\n", caster);

    caster->catch_msg("You whisper words of power and start to shape a " +
	lightningsize + " between your hands.\n");

    return ((t > 1500) ? 1500 : t);
}

public int
create_spell_vattik()
{
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_AIR, 14);
    set_spell_form(SS_FORM_ENCHANTMENT, 10);

    set_spell_time(2);

    set_spell_attack();
    set_damage_type(MAGIC_DT);

    set_spell_mana(85);
    set_spell_task(TASK_EASY);
    set_spell_ingredients("rib");
    set_spell_fail(spell_wohs_fail);

    set_find_target(find_one_living_target);
    set_spell_message(vattik_message);
    set_spell_damage(vattik_damage);
}
