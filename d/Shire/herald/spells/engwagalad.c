/*
 * The heralds of the Valar engwagalad (poison cure) spell.
 *
 * re-worked and added poison resistance if spell wasn't strong enough
 * to cure the poison.
 * -Igneous-
 *
 *  Changed the find poison function so that it picks a random one
 * Igneous June 99
 
    Aprl 28, 2004 - Palmer:
    Removed logging for sucessful cast due to runtime errors.
    Hasn't seemed to work since 97 accordng to log file
    
 */

#pragma strict_types

#include "spells.h"

inherit SPELL_INHERIT;

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
 *               : success: The success of the task that was performed 
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
    power = MIN(25, (MAX(5 , (success / 5))));
    oldres = patient->query_magic_res(MAGIC_I_RES_POISON);

    setuid(); seteuid(getuid());

    ob = clone_object("/std/resistance");
    ob->set_res_type(MAGIC_I_RES_POISON);
    ob->set_strength(power);
    ob->set_time(time);
    ob->move(patient, 1);

    newres = patient->query_magic_res(MAGIC_I_RES_POISON);

    CURE_LOG("Changed poison resistance from "+oldres+" to "+newres+
      " in "+patient->query_cap_name()+" for "+time+" seconds.");

    caster->catch_tell("You feel the prayer has weakened the poison "+
      "somewhat.\n");
    if (caster != patient)
	patient->catch_tell("The poison in your veins seems to have "+
	  "weakened somewhat.\n");
}

/*
 * Function name : Find_poisons
 * Arguments     : player: the player we want to search for poisons
 * Description   : find any poisons in the player given
 * Returns       : an array of poison objects
 */
private object
find_poisons(object player)
{
    object *poison;

    if (!objectp(player))
	return 0;
    poison = filter(all_inventory(player), &operator(==)(POISON_OBJECT) @ 
      &function_exists("create_object",));
    if (!sizeof(poison))
	return 0;    
    return poison[random(sizeof(poison))];
}

void
do_engwagalad_spell(object caster, object *targets, int *resist, int success)
{
    object patient = targets[0], poison;

    // No healing naughty people!
    if ((patient->query_alignment() < -100))
    {
        caster->catch_msg("Your support of Melkor's servants has angered "+
                          "the Valar.\n");      
        caster->adjust_alignment(patient->query_alignment());
        return;
    }

    if (!objectp(poison = find_poisons(patient)))
    {
	if (patient == caster)
	    caster->catch_tell("You sense you are not poisoned.\n");
	else
	    caster->catch_tell("You sense that "+
	      patient->query_the_name(caster)+" is not poisoned.\n");
	return;
    }

    // Magic resistance to poison aids in the cleanse attempt.
    success += patient->query_magic_res(MAGIC_I_RES_POISON);
    // Resistance to this spell reduces the effectiveness of it.
    if (resist[0])
	success = (success * (100 - resist[0])) / 100;

    if (patient != caster)
    {
	if (poison->cure_poison(({poison->query->poison_type()}), success) != 1)
	{
	    caster->catch_tell("You sense your prayer was not powerful "+
	      "enough to cure.\n");
	    patient->catch_tell("You still feel poisoned.\n");

	    setuid(); seteuid(getuid());
	    CURE_LOG(ctime(time())+" "+caster->query_cap_name()+" failed "+
	      "to cleanse  (" +file_name(poison)+ ") of strength "+
	      poison->query_strength()+" in "+patient->query_cap_name()+
	      " with strength "+success+".");

	    if (sizeof(this_object()->query_found_optional_ingredients()))
		add_resistance(caster, patient, success);
	}
	else 
	{
	    caster->catch_tell("Your prayer seems to have some effect.\n");

	    setuid(); seteuid(getuid());
	    CURE_LOG(ctime(time())+" "+caster->query_cap_name()+
	      " cleansed ("+file_name(poison)+") of strength "+
	      poison->query_strength()+" in "+patient->query_cap_name()+
	      " with strength " + success + ".");
	}
    }
    else
    {
	if (poison->cure_poison(({poison->query_poison_type()}),success) != 1)
	{
	    caster->catch_tell("You sense your prayer was not powerful "+
	      "enough to cure the poison.\n");

	    setuid(); seteuid(getuid());
	    CURE_LOG(ctime(time())+" "+caster->query_cap_name()+" failed "+
	      "to cleanse (" +file_name(poison)+ ") of strength "+
	      poison->query_strength()+" in "+patient->query_cap_name()+
	      " with strength "+success+".");

	    if (sizeof(this_object()->query_found_optional_ingredients()))
		add_resistance(caster, patient, success);
	}
	else
	{
	    caster->catch_tell("Your prayer seems to have some effect.\n");
	    /*
	    Aprl 28, 2004 - Palmer:
  	    This causes runtimes and hasn't logged since 1997
	    setuid(); seteuid(getuid());
	    CURE_LOG(ctime(time())+" "+caster->query_cap_name()+
	      " cleansed ("+file_name(poison)+") of strength "+
	      poison->query_strength()+" in "+patient->query_cap_name()+
	      " with strength " + success + ".");
	      */
	}
    }
}

public int
create_engwagalad_spell(object caster, object *targets, string args)
{
    default_herald_spell_config();
    set_spell_mana(90);
    set_spell_time(12);
    set_spell_task((TASK_ROUTINE + 100) - (caster->query_stat(SS_LAYMAN) / 2));
    set_spell_ingredients(({"athelas"}));
    set_spell_optional_ingredients(({"pawnrose"}));
    set_spell_element(SS_ELEMENT_LIFE, 45);
    set_spell_form(SS_FORM_ABJURATION, 45);
    set_spell_effect(do_engwagalad_spell);
    set_spell_resist(spell_resist_beneficial);
    return 0;
}
