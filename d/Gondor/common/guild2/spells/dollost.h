/*
 * /d/Gondor/common/guild2/spells/dollost.h
 *
 * Drains mana from opponent
 * (dol-lost = head-empty)
 * 
 * Class 3 instant spell
 * Element Death; Form Conjuration
 * Area of effect: living target
 *
 * Ingredient: garlic
 * Mana: 60, 1/3 on failure
 * Skills: SS_ELEMENT_DEATH, SS_FORM_CONJURATION
 * Description: If the caster is poisoned by dollost poison, he or she
 *              will drain up to 50% of the victim's present mana.
 *              Half of the mana will be lost, the other half will be 
 *              added to the caster's mana.
 *              If the caster's INT is lower than the victim's INT, the
 *              caster will lose up to 25% of his or her present mana,
 *              though.
 * Requirements: Morgul Mage, guild level >= 11
 *               mage robe must be present
 *               the caster must be poisoned by dollost poison
 *
 * Olorin, 20-may-1994
 *
 * Maintenance:
 * ------------
 * March 26 2000, Morbeche - Added logging
 */

#include <comb_mag.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define MS_DOLLO_INGR     ({ "dollost_ingr", })
#define MS_DOLLO_MANA      60
#define MS_DOLLO_TASK     TASK_ROUTINE
#define MS_DOLLO_LIST     ({ SS_ELEMENT_DEATH, SS_FORM_CONJURATION, SS_SPELLCRAFT})
#define MS_DOLLO_VICTIM   ({ SS_ELEMENT_LIFE, SS_FORM_ABJURATION })
#define MS_DOLLO_DRAIN     50

mixed
do_dollost(string str)
{
    object  tp = this_player(),
    env = environment(tp),
    *ingr_arr,
    *target,
    robe,
    obj;
    int     is_wiz = tp->query_wiz_level(),
    strength,
    mana,
    fail,
    result;
    string  success,
    msg_m,
    msg_n;

#if DEBUG
    is_wiz = 0;
#endif

    str = LOW(str);
    if (str == "me" || str == tp->query_real_name())
	return "You do not want to cast this spell on yourself!\n";
    else
	target = parse_this(str, "[the] %l");
    if (!sizeof(target))
	return "Cast the spell at whom?\n";
    if (sizeof(target) > 1)
	return "You cannot cast the spell at more than one person!\n"; 
    if (target[0] == tp)
	return "You do not want to cast this spell on yourself!\n";
    /*
     * Checks due to this spell being an attack spell
     * no attacks or no magic attacks on this target or in this room
     */
    if (NPMATTACK(target[0]))
	return "A power greater than the Dark Lord prevents you from casting the spell.\n";
    /*
     * Spell starts combat, so we'd better not cast it if we don't dare to attack the target.
     */
    if (!F_DARE_ATTACK(tp, target[0]))
	return "You don't dare to cast the spell on " + QTNAME(target[0]) + "\n";

    if (sizeof(tp->query_weapon(-1)))
	return "You cannot cast a spell while wielding a weapon!\n";
    if (stringp(fail = check_player(tp,
	  MS_DOLLO_INGR, MS_DOLLO_MANA, MS_DOLLO_MIN)))
	return fail;

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
	return "Without your robe, you cannot cast this spell!\n";

    if ((!objectp(obj = present(MORGUL_S_DOLLOST_POISON_NAME, tp))) &&
      (!tp->query_npc()))
	return "You are not properly prepared to cast this spell!\n";
    strength = obj->query_strength();

    ingr_arr = find_ingr(MS_DOLLO_INGR, tp);

    if (!is_wiz && (result = tp->resolve_task(
	  MS_DOLLO_TASK, MS_DOLLO_LIST, target[0], MS_DOLLO_VICTIM)) <= 0)
    {
#if DEBUG
	write("DEBUG: dollost fail result: " + result + "\n");
#endif
	tp->add_mana(-(MS_DOLLO_MANA/3));

	// Logging - Morbeche
	if (find_player(target[0]->query_real_name()))
	{
	    log_file("mm_player_fight", ctime(time()) + " : "+tp->query_name() +
	      " failed dollost on " + target[0]->query_name() +
	      " with a result of " + result +".\n");

	}
	log_file("mm_mana_drain", ctime(time()) + " : "+ tp->query_name() +
	  " failed to cast dollost on " + target[0]->query_name() +
	  " with a result of " + result +".\n");

	fail_cast(tp, ingr_arr);
	return 1;
    }
#if DEBUG
    write("DEBUG: dollost result: " + result + ", poison strength: " + strength + "\n");
#endif

    tell_object(target[0], tp->query_The_name(target[0]) +
      " starts chewing something and mumbles strange words.\n" +
      "Suddenly, " + tp->query_pronoun() +
      " breathes a cloud of garlic stench into your face.\n");
    /* Intentionally we do give a message to players when invisible. */
    tell_room(env, QCTNAME(tp) + " starts chewing something and mumbles " +
      "strange words.\nSuddenly, " + tp->query_pronoun() +
      " breathes a cloud of garlic stench into the face of " +
      QTNAME(target[0]) + ".\n", ({ tp, target[0] }) );
    write("You start chewing the garlic bulb.\nWith the power the Dark " +
      "Lord has bestowed upon you, you call Emptyhead,\n\tpraying " +
      "silently: Anno ruth a losso dol, Belegir Morui!\nThen you breathe " +
      "into the face of " + target[0]->query_the_name(tp) + ".\n");

    if (result < 100)
	result = 100;
    else if (result > 200)
	result = 200;

    result /= 2;
    strength += result;
    strength /= 2;

    strength -= (strength * target[0]->query_magic_res(MAGIC_I_RES_DEATH)) / 100;
    mana = ((target[0]->query_mana() * MS_DOLLO_DRAIN)/100 * strength)/100;

#if DEBUG
    write("DEBUG: dollost strength: " + strength + ", mana drain: " + mana + "\n");
#endif

    if (!is_wiz)
    {
	tp->add_mana(-MS_DOLLO_MANA);
	remove_ingr(ingr_arr);
    }

    if (tp->query_stat(SS_INT) > target[0]->query_stat(SS_INT))
    {
	tell_object(target[0], "You feel sick.\n");
	target[0]->command("puke");
	target[0]->add_mana(-mana);
	tp->add_mana(mana/2);
	switch(mana)
	{
	default:
	case 0..50:
	    success = "You feel no effect.\n"; break;
	case 51..100:
	    success = "You feel mentally a little strengthened.\n"; break;
	case 101..150:
	    success = "You feel mentally a somewhat strengthened.\n"; break;
	case 151..200:
	    success = "You feel mentally a strengthened.\n"; break;
	case 201..250:
	    success = "You feel mentally stronger.\n"; break;
	case 251..1000:
	    success = "You feel mentally a lot stronger.\n"; break;
	}

	msg_m = tp->query_met_name() + " casts a spell successfully.\n";
	msg_n = "The " + tp->query_nonmet_name() +
	" casts a spell successfully.\n";
	tell_room(env, ({ msg_m, msg_n }), tp);
	write("You cast the spell successfully.\n" + success);

	// Logging - Morbeche
	if (find_player(target[0]->query_real_name()))
	{
	    log_file("mm_player_fight", ctime(time()) + " : " +tp->query_name()+
	      " dollost "+target[0]->query_name() +
	      " with success of " + mana + ".\n");
	}
	log_file("mm_mana_drain", ctime(time()) + " : " + tp->query_name() +
	  " cast dollost on " + target[0]->query_name() +
	  " with success of " + mana + ".\n");
    }
    else
    {
	write("You feel sick.\n");
	tp->command("puke");
	tp->add_mana(-mana/2);
	msg_m = tp->query_met_name() + " casts a spell.\n";
	msg_n = "The " + tp->query_nonmet_name() + " casts a spell.\n";
	tell_room(env, ({ msg_m, msg_n }), tp);
	write(target[0]->query_The_name(tp) + " is too strong and resists " +
	  "the effects of the spell.\nThe power of Sauron turns against " +
	  "you, you feel mentally drained.\n");

	// Logging - Morbeche
	if (find_player(target[0]->query_real_name()))
	{
	    log_file("mm_player_fight", ctime(time())+" : "+tp->query_name() +
	      " tried to dollost "+target[0]->query_name() +
	      " but has too little INT.\n");
	}
	log_file("mm_mana_drain", ctime(time()) + " : " + tp->query_name() +
	  " tried to cast dollost on " + target[0]->query_name() +
	  " but has too little INT.\n");
    }

    if (!objectp(target[0]->query_attack()))
    {
	write(target[0]->query_The_name(tp) + " attacks you!\n");
	tp->attack_object(target[0]);
    }

    return 1;
}
