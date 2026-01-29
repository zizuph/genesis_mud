/*
 * /d/Gondor/common/guild/spells/heal.c
 *
 * The heal spell of the Rangers.
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 23-Dec-1996, Olorin: Revision.
 */
#pragma strict_types

#define SP_HEAL_MANA          75
#define SP_HEAL_INGR         ({ "_heal_spell_herb_" })
#define SP_HEAL_SKILL_LIST   ({ SKILL_AVG, TS_WIS, TS_INT, SKILL_END, \
                                SKILL_WEIGHT, 50, SS_SPELLCRAFT, \
                                SKILL_WEIGHT, 50, SS_FORM_CONJURATION, SS_ELEMENT_LIFE })

/*
 * Function name:   do_heal_spell
 * Decription:	    Cast the healing spell.
 * Returns:	    1 if spell was cast, fail message otherwise.
 */
mixed
do_heal_spell(string person)
{
    object  tp = this_player(), 
            env = environment(tp),
           *ob_arr,
           *ingr_arr,
            obj,
            patient;
    int     i, 
            power, 
            is_wiz = tp->query_wiz_level(), 
            success, 
            esf_roll, 
            no_ingr = 0, 
            fighting,
            align_adj,
            patient_al,
            al_before,
            al_diff,
            heal;
    string  fail,msg;

    if (!stringp(person) || !strlen(person))
	return "Heal whom?\n";

    person = lower_case(person);

    power = tp->query_ranger_rank()/2 +
            tp->query_skill(SS_FORM_CONJURATION) + 
            tp->query_skill(SS_ELEMENT_LIFE);

    if (objectp(tp->query_attack())) 
        fighting = 1;
    if ((person == "myself") || (person == "me")
	|| (person == tp->query_real_name())) 
    {
        if (!tp->query_company())
	    return "You feel unable to cast this spell on yourself.\n";
	patient = tp;
    }
    else if (!parse_command(person, all_inventory(ENV(tp)), "%l", ob_arr) ||
    !sizeof(ob_arr = NORMAL_ACCESS(ob_arr, 0, 0)))
        return "That person is not here.\n";
    else
	patient = ob_arr[0];

    if (!objectp(patient))
        patient = present(person, env);

    if (patient->query_hp() == patient->query_max_hp())
    {
        if (patient == tp) 
	    return "You don't need any healing.\n";
	else 
	    return "That person does not need healing.\n";
    }
    if (patient->query_ghost()) 
        return "That person is beyond your help now.\n";

    if (tp->query_mana() < SP_HEAL_MANA)
        return "You feel too weak to cast this spell.\n";

    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_HEAL_INGR, tp);
    if (sizeof(ingr_arr) < 1)
        no_ingr = 1;

    esf_roll = random(SP_HEAL_MANA/3 * (1 + no_ingr + fighting));
    if (esf_roll > power) 
    {
        esf(esf_roll - power, SP_HEAL_MANA, "heal", 
            "I" + sizeof(ingr_arr), "F" + fighting); 
	return 1;
    }
    /* Let's see if the player can cope with the task... */
    if (!is_wiz &&
	((success = tp->resolve_task(TASK_ROUTINE - 
            tp->query_ranger_rank() / 2, SP_HEAL_SKILL_LIST)) <= 0))
    {
        tp->catch_msg("You fail to cast the spell correctly.\n");
	tell_room(environment(tp), QCTNAME(tp) + " fails to cast a spell "
		+ "correctly.\n", tp);
	lose_random_ingr(ingr_arr);
	return 1;
    }
    if (no_ingr) 
        msg = "upon Este, the Valie of Healers";
    else 
        msg = "upon the virtues of lothore";
    if (patient != tp) 
    {
        tell_room(env, QCTNAME(tp)+" calls "+msg+", to heal " +
		  QTNAME(patient)+".\n", ({ tp, patient }));
	tp->catch_msg("You call "+msg+", for power to "+
		      "improve "+QTNAME(patient)+"'s health.\n" +
		      "You feel that someone answers your prayer.\n");
        patient->catch_msg("You feel healthier as "+QTNAME(tp)+" calls " + 
			   msg + " for power to heal you.\n");
    }
    else 
    {
        tell_room(env, QCTNAME(tp)+" calls "+msg+", for powers to heal "+
		  tp->query_objective()+"self.\n", TP);
	tp->catch_msg("You call "+msg+", for powers to heal yourself.\n" +
		      "You feel that someone answers your prayer.\n" +
		      "You feel healthier!\n");
    }
    /* Finally start casting the spell */
    patient->heal_hp(heal = 
		     (5 + F_PENMOD(success + 25, (tp->query_stat(SS_OCCUP) +
					     tp->query_skill(SS_ELEMENT_LIFE) +
					     tp->query_skill(SS_SPELLCRAFT))/3)));
    log_file("heal", tp->query_name() + " heals " + patient->query_name() +
	     " by " + heal + " hp on " + ctime(time()) + " (" +
	     success + ", " + tp->query_stat(SS_OCCUP) + ", " +
	     tp->query_skill(SS_ELEMENT_LIFE) + ", " + tp->query_skill(SS_SPELLCRAFT) +
	     ").\n");
    if (patient != tp)
    {
        if ((patient_al = patient->query_alignment()) < 0)
        {
            if (tp->query_skill(SS_MASTER_TASK) == 4)
                align_adj = patient_al/4;
            else
                align_adj = patient_al;
            al_before = tp->query_alignment();
            tp->adjust_alignment(align_adj);
            al_diff = tp->query_alignment() - al_before;
            log_file("alignadj",
                tp->query_name() + "'s alignment adjusted by "
              + al_diff + " for healing evil (" + patient_al
              + ") " + patient->query_name() + " "
              + ctime(time()) + ".\n");
        }
    }

    /* Make him/her pay for it and remove the ingredients */
    if (!is_wiz)
    {
      if (!tp->query_company() || (tp == patient)) 
	  remove_ingr(ingr_arr);
      else 
	  lose_random_ingr(ingr_arr);
    }
    if (!no_ingr) 
        i = SP_HEAL_MANA;
    else 
        i = SP_HEAL_MANA*2;
    tp->add_mana(-i);
    tell_room(env, QCTNAME(tp) + " casts a spell successfully.\n", tp);
    return 1;
}
