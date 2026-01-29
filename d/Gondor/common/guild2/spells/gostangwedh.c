/*
 * /d/Gondor/common/guild2/spells/gostangwedh.c
 *
 * Decreases the combat speed of the target for a limited time
 * (gost-angwedh: terror-chain)
 * 
 * Class 2 duration spell
 * Element Death; Form Conjuration
 * Area of effect: target
 *
 * Ingredient: ungolestel, an iron armour (to be designated)
 * Mana:  50-100, depending on length of the effect
 * Skills: SS_ELEMENT_DEATH, SS_FORM_CONJURATION
 * Description: the property LIVE_I_QUICKNESS will be set to a negative
 *              value in the target. The value will be
 *              between 0 and -200, depending on SS_OCCUP and resolve_task result
 *              duration:  5 - 10 min, depending on resolve_task result
 * Requirements: Morgul Mage, guild level > 12
 *               mage robe must be present
 *               cannot be cast in combat
 *
 * Olorin, 08-nov-1995
 *
 * Maintenance:
 * ------------
 * March 26 2000, Morbeche - Added logging
 */

#define MS_GOSTA_INGR     ({ "gosta_ingr1", "gosta_ingr2" })
#define MS_GOSTA_MANA		 50
#define MS_GOSTA_TASK     TASK_FORMIDABLE
#define MS_GOSTA_TASK_DIFF	300
#define MS_GOSTA_LIST     ({ SS_ELEMENT_DEATH, SS_FORM_CONJURATION, SS_SPELLCRAFT})
#define MS_GOSTA_TARGET   ({ SS_ELEMENT_LIFE, SS_FORM_ABJURATION })

#undef DEBUG

mixed
do_gostangwedh(string str)
{
    object  tp = this_player(),
    env = environment(tp),
    *ingr_arr,
    *target,
    obj;
    int     is_wiz = tp->query_wiz_level(),
    size,
    diff,
    result;
    mixed   fail;
    string  he,
    his;

#if DEBUG
    is_wiz = 0;
#endif

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
	return "Without your robe, you cannot cast this spell!\n";

    if (!strlen(str))
	return "Cast the spell at whom?\n";

    str = LOW(str);
    target = parse_this(str, "[the] %l");
    if (!(size = sizeof(target)))
	return "Cast the spell at whom?\n";
    if (size > 1)
	return "You cannot cast the spell at more than one target at a time!\n";
    if (target[0] == tp)
	return "You cannot cast this spell on yourself!\n";

    /* magic check */
    if (NPMATTACK(target[0]))
	return MORGUL_S_SPELL_FAIL;

    if ((!F_DARE_ATTACK(tp, target[0])) && (tp->query_attack() != target[0]))
	return "You do not dare to cast the spell.\n";

    if (sizeof(tp->query_weapon(-1)) && interactive(tp))
	return "You cannot cast a spell while wielding a weapon!\n";
    if (objectp(tp->query_attack()) && interactive(tp))
	return "You cannot cast this spell during a fight!\n";
    if (stringp(fail = check_player(tp, 0, MS_GOSTA_MANA, MS_GOSTA_MIN)))
	return fail;

    ingr_arr = find_ingr(MS_GOSTA_INGR, tp);
    diff = MS_GOSTA_TASK - sizeof(ingr_arr) * MS_GOSTA_TASK_DIFF;
    if (tp->query_npc())
	diff = TASK_ROUTINE;
    if (diff < 0)
	diff = 0;

#if DEBUG
    write("DEBUG: gostangwedh diff: " + diff + "\n");
    dump_array(ingr_arr);
#endif
    if (!is_wiz &&
      (result = tp->resolve_task(diff, MS_GOSTA_LIST, target[0],
	  MS_GOSTA_TARGET)) <= 0)
    {
#if DEBUG
	write("DEBUG: gostangwedh result: " + result + "\n");
#endif
	tp->add_mana(-(MS_GOSTA_MANA/3));

	// Logging - Morbeche
	if (find_player(target[0]->query_real_name()))
	{
	    log_file("mm_player_fight", ctime(time())+" : "+tp->query_name()+
	      " failed gostangwedh on "+ target[0]->query_name() +
	      " result of " + result +".\n");
	}
	log_file("mm_slow", ctime(time()) + " : " +
	  tp->query_name() + " failed gostangwedh " +
	  "on " + target[0]->query_name() + 
	  " with a result of " + result + ".\n");

	fail_cast(tp, ingr_arr);
	if (target[0]->query_npc())
	    target[0]->command("$kill "+tp->query_real_name());
	return 1;
    }
#if DEBUG
    write("DEBUG: gostangwedh result: " + result + "\n");
#endif

    he = tp->query_pronoun();
    his = tp->query_possessive();

    tell_room(env,
      "Employing Dark Sorcery, "+QTNAME(tp)+" calls upon the Power of the "
      + "Dark Lord upon "+QTNAME(target[0])+".\n"
      + CAP(HE(tp))+" raises "+HIS(tp)+" arms at "+HIM(target[0])+" and "
      + "rasps a few menacing words.\n"
      + QCTNAME(target[0])+" grows pale and seems to move more slowly.\n",
      ({tp, target[0]}));
    target[0]->catch_msg("Employing Dark Sorcery, " + QTNAME(tp)
      + " calls the Power of the Dark Lord upon you!\n"
      + "Your heart is filled with terror and a heavy weight seems "
      + "to fall down upon your limbs like chains of iron.\n");
    tp->catch_msg("With the power the Dark Lord has bestowed upon you, "
      + "you cast the Chains of Terror onto "+QTNAME(target[0])+".\n"
      + "Raising your arms, you chant at your victim:\n"
      + "\t'Anto nin tur, gwedi kotumo-lya na engwidh o gost.'\n");

    if (result < 20)
	result = 20;
    else if (result > 100)
	result = 100;

    target[0]->add_panic(result);

    tell_room(env, QCTNAME(tp) + " casts a spell successfully.\n", tp);
    tp->catch_msg("You cast the spell successfully.\n");

    // Logging - Morbeche
    if (find_player(target[0]->query_real_name()))
    {
	log_file("mm_player_fight", ctime(time())+" : "+ tp->query_name() +
	  " gostangwedh " + target[0]->query_name() + " with " +
	  "result " + result + ".\n");
    }
    log_file("mm_slow", ctime(time()) + " : " + tp->query_name() +
      " cast gostangwedh on " + target[0]->query_name() + " with a " +
      " result of " + result + ".\n");

    FIX_EUID;
    obj = clone_object(MORGUL_SPELL_OBJS + "gostangwedh");
    obj->set_up_effect(target[0], 300 + result * 3, 
      (- result - MIN(tp->query_stat(SS_OCCUP), 100)));
    if (obj->move(target[0]))
	obj->move(target[0], 1);

#if DEBUG
    write("DEBUG: gostangwedh mana: " + (MS_GOSTA_MANA * (100 + result)) / 100 + ".\n"
      +  "                   time: " + (300 + result * 3) + ".\n"
      +  "               strength: " + (-result-MIN(tp->query_stat(SS_OCCUP), 100)) + ".\n");
#endif
    if (!is_wiz)
    {
	tp->add_mana(- (MS_GOSTA_MANA * (100 + result)) / 100);
	remove_ingr(ingr_arr);
    }
    return 1;
}
