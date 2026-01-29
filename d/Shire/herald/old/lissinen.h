/*
 * Old hin warrior tend speil that was modified for the Heralds of the Valar.
 *
 * Modified by Igneous May 18th 97
 * - Changed Heal to Mana ratio and added some general improvements.
 *
 * Currently this spell will heal someone with 50 SS_LIFE_SKILL and 
 * a 100 guild stat within the heralds 125 - 200 hps with modifers.
 * Healing is increased by 1/3 if casted on someone else besides
 * the caster.
 * -Igneous-
 */

#include <cmdparse.h>

#define SP_TEND_INGR	({ "_tend_spell_ingr_"})
#define SP_TEND_MANA	75
#define SP_TEND_MIN	20
#define SP_TEND_TASK	TASK_ROUTINE
#define SP_TEND_LIST	({ SKILL_AVG, SS_WIS, SS_INT, SKILL_END, \
		SKILL_AVG, SS_FORM_DIVINATION, SS_ELEMENT_LIFE, \
		SS_SPELLCRAFT, SKILL_END})

#define HEAL_AMOUNT     (TP->query_skill(SS_ELEMENT_LIFE)  + 25 + \
			 (TP->query_stat(SS_LAYMAN) / 2) + random(76))
#define HEAL_MAX         200

#define LOG_HEALS
#undef  LOG_HEALS

#ifdef  LOG_HEALS
#define HEAL_LOG(s)     write_file(HERALD_LOGS + "heal", s + "\n")
#else
#define HEAL_LOG(s)
#endif


/*
 * Function name:   do_tend_spell
 * Decription:	    Cast the tend spell.
 * Arguments:	    who: The person to tend
 * Returns:	    1 if spell was cast, 0 or the errorstring otherwise.
 */
mixed
do_tend_spell(string who)
{
    object target, *oblist, *ingr_arr;
    int i, success, is_wiz, before, after, amount, res;
    string fail;

    is_wiz = TP->query_wiz_level();

    if (!who)
	return "Tend who?\n";

    who = lower_case(who);
    if (who == "me" || who  == "myself"|| who == TP->query_real_name())
    {
	target = TP;
    }
    oblist = PARSE_THIS(who, "[the] %l");

    if (!objectp(target) && !sizeof(oblist))
    {
	write("You find no "+who+" to make your prayer for.\n");
	return 1;
    }

    if (sizeof(oblist) > 1)
    {
	write("You can only make your prayer for one person at a time.\n");
	return 1;
    }

    if (!objectp(target))
	target = oblist[0];

    if (TP->query_mana() < SP_TEND_MANA)
	return "You have not the strength to do that.\n";

    fail = check_player(TP, SP_TEND_INGR, SP_TEND_MANA, SP_TEND_MIN);

    if (fail && fail != "One of the ingredients is missing!\n")
	return fail;

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_TEND_INGR, this_player());

    /* Let's see how successful she is */
    if (!is_wiz && TP->resolve_task(SP_TEND_TASK, SP_TEND_LIST) <= 0)
    {
	fail_cast(TP,ingr_arr);
	return 1;
    }

    before = target->query_hp();

    if (sizeof(ingr_arr) < sizeof(SP_TEND_INGR))
    {
	TP->catch_msg("You do not have the required ingredients to "+
	  "cast this spell!\n");
	return 1;
    }
    amount = HEAL_AMOUNT;
    // Give a little bonus for thinking of others before ourselves
    if (target != TP)
	amount += amount / 3;
    amount = MIN(amount, HEAL_MAX);

    // This is a healing spell. reduce the amount do to the resistance prop
    res = 100 - target->query_magic_res("_magic_i_res_healing");
    res = MAX(res, 0);
    amount = (res * amount) / 100;

    target->heal_hp(amount);

    setuid(); seteuid(getuid());
    HEAL_LOG(ctime(time()) + " "+TP->query_name()+" heals "+
      target->query_name()+" for "+amount+" hit points.  "+
      "(ING: "+sizeof(ingr_arr)+" L_SKILL: "+
      TP->query_skill(SS_ELEMENT_LIFE)+" G_STAT: "+
      TP->query_stat(SS_LAYMAN)+")");

    after = target->query_hp();

    if (target == TP)
    {
	TP->catch_msg("You call upon Lorien to tend your wounds.\n"
	  + "You feel " + effectstr(before, after) + ".\n");
	say(QCTNAME(this_player()) + " invokes Lorien to tend "+
	  HIS_HER(TP)+ " wounds.\n"+ capitalize(HE_SHE(TP)) +
	  " looks "+ effectstr(before, after) +".\n");
    }
    else
    {
	TP->catch_msg("You invoke Lorien to tend to " + QCTNAME(target)+".\n"+
	  CAP(HE_SHE(TP))+ " looks "+ effectstr(before, after) + ".\n");
	say(QCTNAME(TP) + " invokes Lorien to tend to " + QCTNAME(target) +
	  ".\n"+CAP(HE_SHE(target))+ " looks "+effectstr(before, after) +
	  ".\n", ({TP,target}));
	target->catch_msg(QCTNAME(TP) + " invokes Lorien to tend your "+
	  "wounds.\nYou feel " + effectstr(before, after) + ".\n");
    }

    /* Remove the ingredients and make her pay for it */
    if (!is_wiz)
    {
	remove_ingr(ingr_arr);
	TP->add_mana(-SP_TEND_MANA);
    }
    return 1;
}
