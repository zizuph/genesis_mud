/*
 * LeddacOmat
 *
 * Description: A very weak direct damage combat spell.
 * Class: 2
 * Ingredients: A Silver Coin
 * Mana: 25
 * Tax: 0.25%?
 * Skills: SS_ELEMENT_FIRE      10
 *         SS_FORM_ABJURATION 6
 * Task:   TASK_SIMPLE + 75
 *
 * By Karath
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>

public int
do_ustilo(string str)
{
    return cast_spell();
}

public void
ustilo_message(object caster, object enemy, mixed hr)
{

    mixed howhurt;
    string howhard;

    switch(hr[0])
      {
      case 0:
	howhurt = ({"leaving", " undamaged"});
	break;
      case 1..5:
	howhurt = ({"blistering",""});
	break;
      case 6..15:
	howhurt = ({"welting",""});
	break;
      case 16..30:
	howhurt = ({"burning",""});
	break;
      case 31..50:
	howhurt = ({"burning"," rather fiercely"});
	break;
      case 51..80:
	howhurt = ({"leaving",", blistering and smouldering"});
	break;
      default:
	howhurt = ({"causing",", to ignite and burn"});
      }

    switch(hr[3])
      {
      case 0..50:
	howhard = "singe";
	break;
      case 51..100:
	howhard = "scorch";
	break;
      default:
	howhard = "burn";
	break;
      }

    if (hr[0] > 99)
      {
	/* Death message */
	enemy->catch_msg(QTNAME(caster) + " makes a fan with " +
	    POSSESSIVE(caster) + " fingers spread towards you, and jets "+
	    "of flame shoot from them towards you.\nThe flames buffet against "+
	    "your body, incinerating your skin and all goes black.\n");

        tell_room(E(caster), QCTNAME(caster) + " makes a fan with "+
	    POSSESSIVE(caster) + " fingers spread towards " + QTNAME(enemy) +
	    " and jets of flame shoot from them.\nThe flames buffet against "+
	    OBJECTIVE(enemy)+ ", incinerating the skin.\n", ({ caster, enemy }));
        caster->catch_msg("You make a fan with your fingertips spread "+
		"towards " +QTNAME(enemy)+ " and jets of flame shoot from "+
		"them.\nThe flames buffet against " +OBJECTIVE(enemy)+ ", "+
		"incinerating the skin.\n");

	if(!enemy->query_prop(LIVE_I_UNDEAD))
		enemy->command("$scream");

	} else {

    enemy->catch_msg(QTNAME(caster) + " makes a fan with " +
	POSSESSIVE(caster) + " fingers spread towards you, and jets "+
	"of flame shoot from them towards you.\nThe flames " + howhard +
	" you, " + howhurt[0] + " your skin" + howhurt[1] + ".\n");

    tell_room(E(caster), QCTNAME(caster) + " makes a fan with "+
	POSSESSIVE(caster) + " fingers spread towards " + QTNAME(enemy) +
	" and jets of flame shoot from them.\nThe flames " + howhard + " " +
	OBJECTIVE(enemy)+ ", " + howhurt[0] + " " +
	POSSESSIVE(enemy) + " skin" + howhurt[1] +
	".\n", ({ caster, enemy }));

    caster->catch_msg("You make a fan with your fingertips spread towards "+
	QTNAME(enemy) + ", and release jets of flame towards " +
	OBJECTIVE(enemy) + ".\nThe flames " +howhard+ " " +OBJECTIVE(enemy)+
	", " + howhurt[0] + " " + POSSESSIVE(enemy) + " skin" +
	howhurt[1] + ".\n");
	}
}

public int
ustilo_damage(object caster, object target, int result)
{
    int t, res;

    if (!result)
        return 0;

    res = MAX(target->query_magic_res(MAGIC_I_RES_MAGIC),
	target->query_magic_res(MAGIC_I_RES_FIRE));

    t = 15 + result + ((result * caster->query_wohs_level()) / 8);
    t = (t > 125 ? 125 : t);

    return (t * (100 - res) / 100);
}

public int
create_spell_ustilo()
{
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_FIRE, 5);
    set_spell_form(SS_FORM_ABJURATION, 6);

    set_spell_time(1);

    set_spell_attack();
    set_damage_type(MAGIC_DT);

    set_spell_mana(25);
    set_spell_task(TASK_SIMPLE + 35);
    set_spell_ingredients("silver coin");

    set_spell_fail(spell_wohs_fail);
    set_find_target(find_one_living_target);
    set_spell_message(ustilo_message);
    set_spell_damage(ustilo_damage);
}
