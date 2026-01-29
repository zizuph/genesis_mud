/*
 * LeddacOmat
 *
 * Description: A simple combat spell, better known as 'magic missile'
 * Class: 3
 * Ingredients: A blade from a dagger or knife.
 * Mana: 24
 * Tax: 0.5%?
 * Skills: SS_ELEMENT_AIR      10
 *         SS_FORM_ENCHANTMENT 6
 * Task:   TASK_EASY
 *
 * By Rastlin
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>

public int
do_leddacomata(string str)
{
    return cast_spell();
}

public void
leddacomata_message(object caster, object enemy, mixed hr)
{

    mixed howhurt;
    string howhard;

    switch(hr[0])
      {
      case 0:
	howhurt = ({"leaving", " undamaged"});
	break;
      case 1..5:
	howhurt = ({"grazing",""});
	break;
      case 6..15:
	howhurt = ({"hurting",""});
	break;
      case 16..30:
	howhurt = ({"hurting"," rather badly"});
	break;
      case 31..50:
	howhurt = ({"tearing into"," very badly"});
	break;
      case 51..80:
	howhurt = ({"ripping into",", leaving a gaping wound"});
	break;
      default:
	howhurt = ({"shredding",", leaving a near mortal wound"});
      }

    switch(hr[3])
      {
      case 0..50:
	howhard = "lightly cutting";
	break;
      case 51..150:
	howhard = "cutting";
	break;
      case 151..250:
	howhard = "cutting";
	break;
      case 251..400:
	howhard = "stabbing";
	break;
      default:
	howhard = "stabbing deeply";
      }

    if (hr[0] > 99)
      {
	/* Death message */
	enemy->catch_msg(QCTNAME(caster) + " swings " + POSSESSIVE(caster) +
		" arm towards you and whispers a command. The glowing "+
		"blade above " + POSSESSIVE(caster) + " shoulder follows "+
		"as if thrown from an unseen hand, striking deeply into "+
		" your throat. You gurgle as blood foams out your mouth "+
		"and you drop to your knees as everything goes dark.\n");

    	tell_room(E(caster), QCTNAME(caster) + " swings " +
		POSSESSIVE(caster) + " arm towards " + QTNAME(enemy) +
		 " and "+ "whispers a command. The glowing blade above " +
		 POSSESSIVE(caster)+ " shoulder follows as if thrown " +
		"from an unseen hand, striking deeply into " +
		 QTNAME(enemy)+ "'s throat. " + capitalize(PRONOUN(enemy)) +
		" gurgles as blood foams from " + POSSESSIVE(enemy) +
		" throat, clutches vainly at the gaping wound, and "+
		"drops to " + POSSESSIVE(enemy) + " knees, falling "+
		"into a heap on the ground.\n", ({ caster, enemy}));

	caster->catch_msg("You swing your arm towards " + QTNAME(enemy) +
		" and whisper a command. The glowing blade above your " +
		"shoulder follows as if thrown from an unseen hand, " +
		"striking deeply into " + QTNAME(enemy) + "'s throat. "+
		capitalize(PRONOUN(enemy)) + " gurgles as blood foams "+
		"from " + POSSESSIVE(enemy) + " throat, clutches vainly "+
		"at the gaping wound, and drops to " + POSSESSIVE(enemy) +
		" knees, falling into a heap on the ground.\n");

	} else {

    enemy->catch_msg(QTNAME(caster) + " swings " + POSSESSIVE(caster) +
	" arm towards you and whispers a command. The glowing "+
	"blade above " + POSSESSIVE(caster) + " shoulder follows "+
	"as if thrown from an unseen hand, " + howhard + " into "+
	"your body, " + howhurt[0] + " you" + howhurt[1] + ".\n");

    tell_room(E(caster), QCTNAME(caster) + " swings " +
	POSSESSIVE(caster) + " arm towards " + QTNAME(enemy) + " and "+
	"whispers a command. The glowing blade above " + POSSESSIVE(caster)+
	" shoulder follows as if thrown from an unseen hand, " + howhard +
	" into " + QTNAME(enemy)+ "'s body, " + howhurt[0] + " " +
	OBJECTIVE(enemy) + howhurt[1] + ".\n", ({ caster, enemy }));

    caster->catch_msg("You swing your arm towards " + QTNAME(enemy) +
	" and whisper a command. The glowing blade above your shoulder "+
	"follows as if thrown from an unseen hand, " + howhard + " into " +
	POSSESSIVE(enemy) + " body, " + howhurt[0] + " " + OBJECTIVE(enemy) +
	howhurt[1] + ".\n");
	}
}

public int
leddacomata_damage(object caster, object target, int result)
{
    int t, resistance;
    string bladepower;

    if (!result)
        return 0;

    t = 75 + ( 75 * caster->query_wohs_level() / 5) +
	(result * caster->query_wohs_level() / 10);

    t = (t > 520 ? 520 : t);

    switch(t)
      {
      case 0..50:
	bladepower = "faint";
	break;
      case 51..100:
	bladepower = "softly flickering";
	break;
      case 101..175:
	bladepower = "flickering";
	break;
      case 176..250:
	bladepower = "brightly flickering";
	break;
      case 251..350:
	bladepower = "pulsing";
	break;
      default:
	bladepower = "strongly pulsing";
	break;
      }

    tell_room(E(caster), QCTNAME(caster) + " starts to mumble arcane "+
	"words, and the blade of a knife jumps above " + POSSESSIVE(caster) +
	" right shoulder, glowing in a " + bladepower + " light.\n",
	({ caster, }));
    caster->catch_msg("You mumble arcane words, and the blade of a knife "+
	"jumps above your right shoulder, glowing in a " + bladepower +
	" light.\n");

    resistance = MAX(target->query_magic_res(MAGIC_I_RES_MAGIC),
		target->query_magic_res(MAGIC_I_RES_AIR));
    return ( t * (100 - resistance) / 100 );
}

public int
create_spell_leddacomata()
{
    if (check_gagged())
        return 1;

    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 6);

    set_spell_time(2);

    set_spell_attack();
    set_damage_type(W_IMPALE);

    set_spell_mana(24);
    set_spell_task(TASK_EASY);
    set_spell_ingredients("knife");

    set_spell_fail(spell_wohs_fail);
    set_find_target(find_one_living_target);
    set_spell_message(leddacomata_message);
    set_spell_damage(leddacomata_damage);
}
