/*
 * The heralds of the Valar engwagalad (poison cure) spell.
 *
 * re-worked and added poison resistance if spell wasn't strong enough
 * to cure the poison.
 * -Igneous-
 */

#pragma strict_types

#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"

#define SP_CURE_TASK       TASK_ROUTINE
#define SP_CURE_TASK_LIST  ({SKILL_AVG, SS_INT, SS_WIS, SKILL_END,\
			     SKILL_AVG, SS_FORM_ABJURATION, SS_ELEMENT_LIFE,\
			     SS_SPELLCRAFT, SKILL_END})
#define SP_CURE_MANA       90
#define SP_CURE_MIN        50

#define LOG_CURES

#ifdef  LOG_CURES
#define CURE_LOG(s)        write_file(HERALD_LOGS + "cure", s + "\n")
#else
#define CURE_LOG(s)
#endif

#ifndef POISON_OBJECT
#define POISON_OBJECT      "/std/poison_effect"
#endif


/*
 * Function name : Add_resistance
 * Arguments     : castor:  The castor of this spell
 *               : patient: The person recieving the aid of this spell
 *               : success: The sucess of the task that was performed 
 * Description   : If the spell is unable to cure the poison it adds
 *               : some poison resistance if they used the pawnrose herb
 *               : as well as athelas.
 */
nomask private void
add_resistance(object caster, object patient, int success)
{
    object ob;
    int time, power, oldres, newres;

    if (!success || !caster || !patient)
	return;
    time = 180 + success;


    // The % of resistance to be added.  If you add 10% to someone that is 
    // Already 10% resistant total resistance becomes 19% since a new object
    // uses this formula to add resistance (power * (100 - resistance)) / 100
    power = MIN(25, (MAX(10 , (success / 5))));
    oldres = patient->query_magic_res(MAGIC_I_RES_POISON);

    setuid(); seteuid(getuid());

    ob = clone_object("/std/resistance");
    ob->set_res_type(MAGIC_I_RES_POISON);
    ob->set_strength(power);
    ob->set_time(time);
    ob->move(patient);

    newres = patient->query_magic_res(MAGIC_I_RES_POISON);

    CURE_LOG("Changed poison resistance from "+oldres+" to "+newres+
      " in "+patient->query_name()+" for "+time+" seconds.");

    caster->catch_msg("You feel the spell has weakened the poison "+
      "somewhat.\n");
    if (caster != patient)
	patient->catch_msg("The poison in your veins seems to have weakened "+
	  "somewhat.\n");
}

/*
 * Function name : Find_poisons
 * Arguments     : player: the player we want to search for poisons
 * Description   : find any poisons in the player given
 * Returns       : an array of poison objects
 */
private object *
find_poisons(object player)
{
    object *poison;

    if (!objectp(player))
	return 0;
    poison = filter(all_inventory(player), &operator(==)(POISON_OBJECT) @ 
      &function_exists("create_object",));
    if (!sizeof(poison))
	return 0;    
    return poison;
}

/*
 * Function name : Find_cure_herb
 * Arguments     : ptype: poison type
 *               : player: the player we search for the herb.
 * Description   : finds the herb we are curing the poison with
 * Returns       : the curing herb.
 */
private object
find_cure_herb(string ptype, object player)
{
    object herb;

    if (objectp(herb = present("_herb_for_"+ptype+"_cleanse", player)) ||
      objectp(herb = present("_herb_athelas_", player)))
	return herb;
    return 0;
}

/*
 * Function name : Find_boosting_herb
 * Arguments     : player: The player we search.
 * Description   : Finds the pawnrose herb. used to "boost" the spell.
 * Returns       : the boosting herb.
 */
private object
find_boosting_herb(object player)
{
    object herb;

    if (objectp(herb = present("_cure_spell_ingr2_",player)))
	return herb;
    return 0;
}


/*
 * Function name : Do_cure_spell
 * Arguments     : str: a string given by this_player()
 * Description   : the actual cure spell.
 * Returns       : 0/1
 */
int
do_cure_spell(string str)
{
    object patient, tp, cure_herb, boost_herb;
    object *poison, *herb_arr, *oblist;
    string ptype, herbstr;
    int success, res;

    if (!str)
    {
	write("Cast engwagalad on whom?\n");
	return 1;
    }
    tp = TP;
    str = lower_case(str);
    if (str == "me" || str  == "myself"|| str == tp->query_real_name())
    {
	patient = tp;
    }
    else
	oblist = PARSE_THIS(str, "[the] %l");

    if (!objectp(patient) && !sizeof(oblist))
    {
	tp->catch_msg(CAP(str)+" is nowhere to be seen.\n");
	return 1;
    }
    if (sizeof(oblist) > 1)
    {
	write("You can only make your prayer for one person at a time!\n");
	return 1;
    }

    if (!objectp(patient))
	patient = oblist[0];

    if (!sizeof(poison = find_poisons(patient)))
    {
	if (patient == tp)
	    tp->catch_msg("You sense you are not poisoned.\n");
	else
	    tp->catch_msg("You sense that "+QTNAME(patient)+
	      " is not poisoned.\n");
	return 1;
    }
    ptype = poison[0]->query_poison_type();
    if (!objectp(cure_herb = find_cure_herb(ptype, tp)))
    {
	tp->catch_msg("You do not have the herbs nessacery to perform the "+
	  "engwagalad prayer.\n");
	return 1;
    }    
    if (tp->query_mana() < SP_CURE_MANA)
    {
	tp->catch_msg("You feel to weak to cast this spell.\n");
	return 1;
    }
    boost_herb = find_boosting_herb(tp);
    if (boost_herb)
	herb_arr = (({boost_herb}) + ({cure_herb}));
    else
	herb_arr = (({cure_herb}));

    // Okie all the checks are done and herbs have been found.

    //  Success of this task with 100 Stats and 50 skills (highest trainable 
    //  in the guild) is MIN -39 AVG 60 MAX 159.
    success = tp->resolve_task(SP_CURE_TASK, SP_CURE_TASK_LIST);

    if (success <= 0)
    {
	tp->catch_msg("Your tongue fails to phrase the prayer, and the "+
	  "spell goes astray!\n");
	say(QCTNAME(tp)+" fails to phrase "+HIS_HER(tp)+" chant correctly.\n");
	lose_random_ingr(herb_arr);
	return 1;
    }

    // Magic resistance to poison aids in the cleanse attempt.
    success += patient->query_magic_res(MAGIC_I_RES_POISON);

    // This is a healing spell.
    res = 100 - patient->query_magic_res("_magic_i_res_healing");
    res = MAX(res, 0);
    success = (res * success) / 100;

    if (!cure_herb) 
	herbstr = "Vala Lorien";
    else 
	herbstr = cure_herb->short();

    if (patient != tp)
    {
	say(QCTNAME(tp)+" uses the virtues of the "+herbstr+
	  " to try to cleanse the poison from "+QTNAME(patient)+
	  "'s blood.\n",({patient}));
	patient->catch_msg(QCTNAME(tp)+" calls for the virtues of the "+
	  herbstr+" to try to cleanse the poison from "+
	  "your blood.\n");
	tp->catch_msg("You call upon the virtues of the "+herbstr+"\n"+
	  " to try to cleanse the poison from "+QTNAME(patient)+
	  "'s blood.\n");

	if (poison[0]->cure_poison(({ptype}),success) != 1)
	{
	    tp->catch_msg("You sense your prayer was not powerful "+
	      "enough to cure.\n");
	    patient->catch_msg("You still feel poisoned.\n");
	    setuid(); seteuid(getuid());
	    CURE_LOG(ctime(time())+" "+tp->query_name()+" failed to cleanse "+
	      ptype+ " poison (" +file_name(poison[0])+ ") of strength "+
	      poison[0]->query_strength()+" in "+patient->query_name()+
	      " with strength "+success+".");

	    if (boost_herb)
		add_resistance(tp, patient, success);
	}
	else 
	{
	    setuid(); seteuid(getuid());
	    CURE_LOG(ctime(time())+" "+tp->query_name()+" cleansed "+    
	      ptype+" poison ("+file_name(poison[0])+") of strength "+
	      poison[0]->query_strength()+" in "+patient->query_name()+
	      " with strength " + success + ".");
	    tp->catch_msg("The spell seems to have some effect.\n");
	}
    }
    else
    {
	tp->catch_msg("You call upon the virtues of the "+
	  herbstr+" to cleanse your blood from the poison.\n");
	say(QCTNAME(tp)+" uses the powers of the "+herbstr+" to try "+
	  "to cleanse "+HIS_HER(tp)+" blood from the poison.\n",tp);
	if (poison[0]->cure_poison(({ptype}),success) != 1)
	{
	    tp->catch_msg("You sense your prayer was not powerful enough "+
	      "to cure the poison.\n");
	    setuid(); seteuid(getuid());
	    CURE_LOG(ctime(time())+" "+tp->query_name()+" failed to cleanse "+
	      ptype+ " poison (" +file_name(poison[0])+ ") of strength "+
	      poison[0]->query_strength()+" in "+patient->query_name()+
	      " with strength "+success+".");
	    if (boost_herb)
		add_resistance(tp, patient, success);
	}
	else
	{
	    setuid(); seteuid(getuid());
	    CURE_LOG(ctime(time())+" "+tp->query_name()+" cleansed "+    
	      ptype+" poison ("+file_name(poison[0])+") of strength "+
	      poison[0]->query_strength()+" in "+patient->query_name()+
	      " with strength " + success + ".");
	}
    }
    tp->add_mana(-SP_CURE_MANA);
    remove_ingr(herb_arr);
    return 1;
}
