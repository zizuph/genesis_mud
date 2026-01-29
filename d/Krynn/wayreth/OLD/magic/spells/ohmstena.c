/*
 * OhmStena
 *
 * Description: A very weak direct damage combat spell.
 * Class: 2
 * Ingredients: A Silver Coin
 * Mana: 25
 * Tax: 0.25%?
 * Skills: SS_ELEMENT_AIR      10
 *         SS_FORM_ENCHANTMENT 6
 * Task:   TASK_SIMPLE + 75
 *
 * By Karath
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>

public int
do_ohmstena(string str)
{
    return cast_spell();
}

public void
ohmstena_message(object caster, object enemy, mixed hr)
{

    mixed howhurt;
    string howhard;

    switch(hr[0])
      {
      case 0:
	howhurt = ({"leaving", " undamaged"});
	break;
      case 1..5:
	howhurt = ({"sparking",""});
	break;
      case 6..15:
	howhurt = ({"shocking",""});
	break;
      case 16..30:
	howhurt = ({"burning",""});
	break;
      case 31..50:
	howhurt = ({"shocking"," rather fiercely"});
	break;
      case 51..80:
	howhurt = ({"leaving",", blistering and smouldering"});
	break;
      default:
	howhurt = ({"causing",", to crackle and smoke"});
      }

    switch(hr[3])
      {
      case 0..50:
	howhard = "sting";
	break;
      case 51..100:
	howhard = "shock";
	break;
      default:
	howhard = "electrocute";
	break;
      }

    if (hr[0] > 99)
      {
	/* Death message */
	enemy->catch_msg(QTNAME(caster) + " reaches towards you and clamps " +
	    POSSESSIVE(caster) + " fingers around your throat. Coils of "+
	    "electricity run from " +POSSESSIVE(caster)+ " fingertips "+
	    "and explode into your veins.\nYour throat chars and "+
	    "your lungs crackle and your breath fails you.\n");

        tell_room(E(caster), QCTNAME(caster) + " reaches towards " +
	    QTNAME(enemy)+ " and clamps " +POSSESSIVE(caster)+
	    " fingers around " + QTNAME(enemy) + "'s throat. Coils of "+
	    "electricity run from " +POSSESSIVE(caster)+ " fingertips "+
	    " and explode into " +QTNAME(enemy)+ "'s veins.\n"+
	    capitalize(PRONOUN(enemy))+" chokes as "+POSSESSIVE(enemy)+
	    " throat chars, and lungs crackle.\n", ({ caster, enemy }));

        caster->catch_msg("You reach towards "+QTNAME(enemy)+ " and "+
	    "clamp your fingers around "+POSSESSIVE(enemy)+" throat. "+
	    "Coils of electricity run from your fingertips and explode "+
	    "into "+POSSESSIVE(enemy)+"'s veins.\n"+
	    capitalize(PRONOUN(enemy))+" chokes as "+POSSESSIVE(enemy)+
	    " throat chars, and lungs crackls.\n");

	if(!enemy->query_prop(LIVE_I_UNDEAD))
		enemy->command("$choke");

	} else {

    enemy->catch_msg(QTNAME(caster) + " reaches " +POSSESSIVE(caster)+
	" hand towards you and grabs hold.\nCoils of energy from "+
	POSSESSIVE(caster)+" fingers "+howhard+", " + howhurt[0] +
	" your skin" + howhurt[1] + ".\n");

    tell_room(E(caster), QCTNAME(caster) + " reaches "+
	POSSESSIVE(caster) + " hand towards " + QTNAME(enemy) +
	" and grabs hold.\nCoils of energy from " +POSSESSIVE(caster)+
	" fingers " +howhard+ ", " +howhurt[0]+ " " +POSSESSIVE(enemy)+
	" skin" + howhurt[1] + ".\n", ({ caster, enemy }));

    caster->catch_msg("You reach your hand towards "+ QTNAME(enemy) +
	", and grab hold.\nCoils of energy from your fingers " +howhard+
	", " + howhurt[0] + " " + POSSESSIVE(enemy) + " skin" +
	howhurt[1] + ".\n");
	}
}

public int
ohmstena_damage(object caster, object target, int result)
{
    int t, res;

    if (!result)
        return 0;

    res = MAX(target->query_magic_res(MAGIC_I_RES_MAGIC),
	target->query_magic_res(MAGIC_I_RES_AIR));

    t = 15 + result + ((result * caster->query_wohs_level()) / 8);
    t = (t > 125 ? 125 : t);

    t = (random(101) < random(res));

    return t;
}

public int
create_spell_ohmstena()
{
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_AIR, 5);
    set_spell_form(SS_FORM_ENCHANTMENT, 6);

    set_spell_time(1);

    set_spell_attack();
    set_damage_type(MAGIC_DT);

    set_spell_mana(25);
    set_spell_task(TASK_SIMPLE + 35);
    set_spell_ingredients("nail");

    set_spell_fail(spell_wohs_fail);
    set_find_target(find_one_living_target);
    set_spell_message(ohmstena_message);
    set_spell_damage(ohmstena_damage);
}
