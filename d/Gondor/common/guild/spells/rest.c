/*
 * /d/Gondor/common/guild/spells/rest.c
 *
 * Included by the ranger spellbook and the rest spellobject.
 */
#pragma save_binary
#pragma strict_types

#define SP_REST_MANA                30
#define SP_REST_INGR                ({ "_rest_spell_herb_" })
#define SP_REST_TIRED_REDUCTION     30
#define SP_REST_EXTRA_REDUCTION     10
#define SP_REST_SKILL_LIST          ({ SKILL_AVG, TS_INT, TS_WIS, SKILL_END, \
                                       SKILL_AVG, SS_SPELLCRAFT, \
                                       SS_FORM_CONJURATION, SS_ELEMENT_LIFE, SKILL_END })

public mixed
do_rest_spell(string who)
{
    object  patient, 
            tp = this_player(), 
            env = environment(tp),
           *ob_arr,
           *ingr_arr;
    string  how, 
            tmp, 
            fail, 
            msg;
    int     i, 
            power, 
            esf_roll, 
            no_ingr, 
            is_wiz = tp->query_wiz_level(),
            success, 
            patient_al,
            al_before,
            al_diff,
            fighting;
  
    power = tp->query_skill(SS_FORM_CONJURATION) + 
            tp->query_skill(SS_ELEMENT_LIFE);

    if (objectp(tp->query_attack()))
        fighting = 1;

    if (!strlen(who))
        return "Cast the spell on whom?\n";
  
    if ((who == "me") || (who == tp->query_real_name()))
    {
        if (!tp->query_company()) 
	{
	    return "You cannot cast the spell on yourself!\n";
	}
	patient = tp;
    }
    else if (!parse_command(who, all_inventory(ENV(tp)), "%l", ob_arr) ||
    !sizeof(ob_arr = NORMAL_ACCESS(ob_arr, 0, 0)))
        return "That person is not here.\n";
    else
	patient = ob_arr[0];

    if (patient->query_fatigue() >= patient->query_max_fatigue())
    {
        if (patient == tp) 
	    return "You are fully rested already.\n";
	return "That person is fully rested already.\n";
    }
    if (tp->query_mana() < SP_REST_MANA)
        return "You feel too weak to cast this spell.\n";
    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_REST_INGR, tp);
    if (sizeof(ingr_arr) < 1) 
        no_ingr = 1;
    esf_roll = random(SP_REST_MANA/3 * (1 + no_ingr + fighting));
    if (esf_roll > power)
    {
        esf(esf_roll - power, SP_REST_MANA);
	return 1;
    }
    if (!is_wiz &&
        (success = tp->resolve_task(TASK_ROUTINE, SP_REST_SKILL_LIST)) <= 0)
    {
        tp->catch_msg("You fail to cast the spell correctly.\n");
	tell_room(env, QCTNAME(tp) + " fails to cast a spell correctly.\n", tp);
	lose_random_ingr(ingr_arr);
	return 1;
    }
    if (no_ingr) 
        msg = "upon Orome, the Vala of Hunters";
    else 
        msg = "upon the virtues of the redweed";

    if (patient != tp) 
    {
        tell_room(env,QCTNAME(tp) + " calls " + msg + ", and directs "
	  + "it towards " + QTNAME(patient) + ".\n",({ tp, patient }));  
	tp->catch_msg(BSN("You call "+msg+", and direct the spell "
	  + "towards " + QTNAME(patient) + "."));
	patient->catch_msg(BSN(QCTNAME(tp)+" calls "+msg+", "+
			 "and directs the powers towards you."));
	patient->catch_msg("You feel less tired.\n");
    }
    else 
    {
        tell_room(env,QCTNAME(tp)+" calls "+msg+" for power to rest "+
		tp->query_objective()+"self.\n", tp);
	tp->catch_msg("You call "+msg+" for power to rest your tired body.\n");
	tp->catch_msg("You feel less fatigued.\n");
    }
    patient->add_fatigue(SP_REST_TIRED_REDUCTION +
        (((tp->query_stat(SS_OCCUP) - 50) * SP_REST_EXTRA_REDUCTION) / 100));

    if (patient != tp)
    {
        if ((patient_al = patient->query_alignment()) < 0)
        {
            al_before = tp->query_alignment();
            tp->adjust_alignment(patient_al);
            al_diff = tp->query_alignment() - al_before;
            log_file("alignadj",
                tp->query_name() + "'s alignment adjusted by "
              + al_diff + " for resting evil (" + patient_al
              + ") " + patient->query_name() + " "
              + ctime(time()) + ".\n");
        }
    }

    /* Make him pay for it and remove the ingredients */
    if (!is_wiz)
    {
        tp->add_mana(-SP_REST_MANA);
	if (!tp->query_company() || patient == tp) 
	    remove_ingr(ingr_arr);
	else 
	    lose_random_ingr(ingr_arr);
    }
    return 1;
}


