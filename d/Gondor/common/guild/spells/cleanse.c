/*
 * /d/Gondor/common/guild/spells/cleanse.c
 *
 * The cleanse spell of the Rangers
 * Gondor company offers spellcraft to 40 and life spells to 30.
 * Thus the effective max skill/stat bonus for resolve_task will be:
 * SKILL_AVG, TS_INT, TS_WIS, SKILL_END, SKILL_WEIGHT, 50, SS_SPELLCRAFT, 
 *               100     100                                          40
 * SKILL_WEIGHT, 50, SKILL_AVG, SS_FORM_ABJURATION, SS_ELEMENT_LIFE, SKILL_END
 *                                               0               30
 * 100 + 1/2 40 + 1/2 (0 + 30)/2 = 100 + 20 + 7 = 127.
 * For a routine task, this gives a mean success value of (0 + 2 * 127)/5 = 50,
 * and min/max values of -49/150, with 1/8 of all castings with success > 100. 
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 28-Nov-1996, Olorin: Major revision
 * Feb 2000, Morbeche:  Added a random(10) decrease in the strength
 *                      of the poison if the ranger casts the spell
 *                     successfully but fails to cleanse the poison.
 * March 26 2000, Morbeche:  Fixed logging.
 */
#pragma strict_types

#define SP_CLEANSE_MANA 	 80
#define SP_CLEANSE_POWER 	 30
#define SP_CLEANSE_INGR 	({ "_cleanse_spell_herb_" })
#define SP_CLEANSE_SKILL_LIST	({ SKILL_AVG, TS_INT, TS_WIS, SKILL_END, \
                                   SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                                   SKILL_WEIGHT, 50, SKILL_AVG, SS_FORM_ABJURATION, SS_ELEMENT_LIFE, SKILL_END })

private int
filter_poison(object ob)
{
    if (function_exists("create_object", ob) == POISON_OBJECT)
	return 1;
    return 0;
}

private object *
test_for_poison(object pl)
{
    object *poison;

    if (!objectp(pl))
	return 0;
    poison = filter(all_inventory(pl), filter_poison);
    if (sizeof(poison))
	return poison;
    return 0;
}

/*
 * Function name: test_for_herb
 * Description:   Check if the necessary herbs are present.
 * Argument:      Pointer to poison object in patient.
 * Returns:       Pointer to herb object in healer.
 */
private object
test_for_herb(string ptype, object tp)
{
    object  herb; 

    if (objectp(herb = present("_herb_for_"+ptype+"_cleanse",tp)) ||
      objectp(herb = present("_herb_athelas_",tp)))
	return herb;
    return 0;
}

mixed
do_cleanse_spell(string person)
{
    object  tp = this_player(),
    env = environment(tp),
    *ob_arr, 
    *ingr_arr, 
    patient, 
    *poisons,
    herb;
    int     i, 
    power, 
    esf_roll, 
    is_wiz = tp->query_wiz_level(),
    success, 
    strength, 
    mana_cost,
    patient_al,
    al_before,
    al_diff,
    fighting;
    string  fail, 
    herbstr, 
    ptype,
    log_poison_strength;
    string log_herb_loss = "_not_ lost",
    log_poison_name;

    if (objectp(tp->query_attack()))
	fighting = 1;
    if (tp->query_ghost())
    {
	return "You are unable to do that in your present condition.\n";
    }

    power = tp->query_skill(SS_FORM_CONJURATION) + 
    tp->query_skill(SS_ELEMENT_LIFE);

    if (!strlen(person))
    {
	return "Cleanse whom?\n";
    }

    person = lower_case(person);

    if ((person == "myself") || (person == "me") ||
      person == tp->query_real_name())
    {
	if (!strlen(tp->query_company()))
	{
	    return "You are strong not enough to cast this spell on yourself.\n";
	}
	patient = tp;
    }
    else if (!parse_command(person, all_inventory(ENV(tp)), "%l", ob_arr) ||
      !sizeof(ob_arr = NORMAL_ACCESS(ob_arr, 0, 0)))
    {
	return "That person is not here.\n";
    }
    else
	patient = ob_arr[0];

    if (patient->query_ghost())
    {
	return "That person is beyond your help now.\n";
    }

    poisons = test_for_poison(patient);
    if (!sizeof(poisons))
    {
	if (patient == tp)
	    return "But you are not poisoned!\n";

	return "That person is not poisoned!\n";
    }

    if (!objectp(herb = test_for_herb(ptype = poisons[0]->query_poison_type(), tp)))
    {
	return "You lack the herbs needed for cleansing that poison!\n";
    }

    // SP_CLEANSE_MANA is the minimum value, so we need to be careful:
    if (tp->query_mana() < (2 * SP_CLEANSE_MANA))
	return "You feel too weak to cast this spell.\n";

    ingr_arr = ({ herb });
    esf_roll = random(SP_CLEANSE_POWER * (1 + fighting));
    if (esf_roll > power)
    {
	esf(esf_roll - power, SP_CLEANSE_MANA, "cleanse");
	lose_random_ingr(ingr_arr);
	log_herb_loss = "lost";
	return 1;
    }

    if ((success = tp->resolve_task(TASK_ROUTINE -
	  tp->query_ranger_rank() / 2, SP_REST_SKILL_LIST)) <= 0)
    {
	tp->catch_msg("Your tongue fails to phrase the prayer, and the spell goes astray!\n");
	tell_room(env,QCTNAME(tp)+" fails to phrase "+tp->query_possessive()+
	  " chant correctly.\n",tp);
	lose_random_ingr(ingr_arr);
	log_herb_loss = "lost";
	return 1;
    }

    if (!objectp(herb)) 
	herbstr = "Vala Este, the Healer";
    else 
	herbstr = herb->short();

    // Store the poison info in a variable so that we'll still have
    // a record of what the poison was after it gets removed, rather
    // than trying to reference a poison that no longer exists - Morbeche

    log_poison_name = file_name(poisons[0]);
    log_poison_strength = poisons[0]->query_strength();

    if (patient != tp)
    {
	tell_room(env,BSN(QCTNAME(tp)+" uses the virtues of the "+herbstr+
	    " to try to cleanse the poison from "+QTNAME(patient)+"'s blood."),
	  ({ tp, patient }));
	patient->catch_msg(BSN(QCTNAME(tp)+" calls for the virtues of the "+
	    herbstr+" to try to cleanse the poison from your blood."));
	tp->catch_msg("You call upon the virtues of the "+herbstr+"\n"+
	  " to try to cleanse the poison from "+QTNAME(patient)+"'s blood.\n");
	if (is_wiz) 
	    tp->catch_msg("The spell's strength was "+success+".\n");
	if ((patient_al = patient->query_alignment()) < 0)
	{
	    al_before = tp->query_alignment();
	    tp->adjust_alignment(patient_al);
	    al_diff = tp->query_alignment() - al_before;
	    log_file("alignadj",
	      tp->query_name() + "'s alignment adjusted by "
	      + al_diff + " for cleansing evil (" + patient_al
	      + ") " + patient->query_name() + " "
	      + ctime(time()) + ".\n");
	}
	if (poisons[0]->cure_poison(({ poisons[0]->query_poison_type() }),success) != 1)
	{
	    tp->catch_msg("You fear the poison was stronger than your spell.\n");
	    patient->catch_msg("You fear the poison was too strong for the cure.\n");
	    log_file("cleanse", ctime(time()) + ": " + tp->query_name()
	      + " failed to cleanse "    
	      + ptype + " poison (" + log_poison_name + ") of strength "
	      + log_poison_strength + " in " + patient->query_name()
	      + " with strength " + success + ".  Component was "+log_herb_loss+".\n");
	    poisons[0]->set_strength(poisons[0]->query_strength() - random(10));
	}
	else
	{
	    tp->catch_msg("The spell seems to have some effect.\n");
	    log_file("cleanse", ctime(time()) + ": " + tp->query_name() + " cleansed "    
	      + ptype + " poison (" + log_poison_name + ") of strength "
	      + log_poison_strength + " in " + patient->query_name()
	      + " with strength " + success + ".  Component was "+log_herb_loss+".\n");
	}
    }
    else
    {
	tp->catch_msg(BSN("You call upon the virtues of the "+
	    herbstr+" to cleanse your blood from the poison."));
	tell_room(env,BSN(QCTNAME(tp)+" uses the powers of the "+herbstr+" to try "+
	    "to cleanse "+tp->query_possessive()+" blood from the poison."),tp);
	if (is_wiz) 
	    tp->catch_msg("The spells strength was "+success+".\n");
	if (poisons[0]->cure_poison(({ poisons[0]->query_poison_type() }),success) != 1)
	{
	    tp->catch_msg("You fear the spell was not strong enough to cure the poison.\n");
	    log_file("cleanse", ctime(time()) + ": " + tp->query_name()
	      + " fails to cleanse "
	      + ptype + " poison (" + log_poison_name + ") of strength "
	      + log_poison_strength + " with strength " + success + 
	      ".  Component was "+log_herb_loss+".\n");
	    poisons[0]->set_strength(poisons[0]->query_strength() - random(10));
	}
	else
	{
	    log_file("cleanse", ctime(time()) + ": " + tp->query_name() + " cleanses "
	      + ptype + " poison (" + log_poison_name + ") of strength "
	      + log_poison_strength + " with strength " + success + 
	      ".  Component was "+log_herb_loss+".\n");
	}
    }
    if (!is_wiz)
    {
	mana_cost = SP_CLEANSE_MANA * success / 100;
	if (mana_cost < SP_CLEANSE_MANA)
	    mana_cost = SP_CLEANSE_MANA;
	tp->add_mana(- mana_cost);
	remove_ingr(ingr_arr);
    }
    return 1;
}
