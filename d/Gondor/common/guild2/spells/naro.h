/*
 * /d/Gondor/common/guild2/spells/naro.h
 *
 * Word of Command
 * (naro - tell
 *  drego nin! - flee me!
 *  libo makil! - drop sword!
 *  maetho! - fight!)
 * 
 * Class 1, 3, 4 instant spell
 * Element Air; Form Enchantment
 * Area of effect: victim
 *
 * Mana:     30..60 per level, depending on the discipline of the target
 * Skills:     SS_ELEMENT_DEATH, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT, TS_INT
 *         victim: SS_ELEMENT_LIFE, SS_FORM_ABJURATION, TS_DIS
 * Ingredients:     skull (leftover), sumac, knife
 *         Every ingredient that is present will reduce the difficulty of the
 *         task by MS_NARO_TASK_DIFF. The difficulty of the task will be
 *         MS_NARO_TASK + level * MS_NARO_TASK_DIFF
 * Description:  drego nin! - victim runs away, wimpy is raised, combat is stopped.
 *               libo makil! - weapon is dropped.
 *               maetho <victim2>! - victim attacks victim2.
 * Requirements: Morgul Mage, Level >= 3, 13, 23
 *               mage robe must be present
 *
 * Olorin, 08-aug-1995
 *
 * Maintenance:
 * ------------
 * March 26 2000, Morbeche - Added logging
 * 2000.04.07, Chmee - naro libo makil will force the target _player_
 * to attack a mage.
 */
#define MS_NARO_INGR     ({ "skull", "naro_ingr2", "naro_ingr3", })
#define MS_NARO_MANA_BASE    30
#define MS_NARO_TASK_BASE    TASK_ROUTINE
#define MS_NARO_TASK_DIFF    300
#define MS_NARO_LIST     ({ SS_ELEMENT_DEATH, SS_FORM_ENCHANTMENT, \
                            SS_SPELLCRAFT, TS_INT })
#define MS_NARO_VICTIM   ({ SS_ELEMENT_LIFE, SS_FORM_ABJURATION, TS_DIS})
#define MS_NARO_DREGO_OBJ    (MORGUL_SPELL_OBJS + "naro_drego_ob")

#undef DEBUG

mixed   do_drego(object target, int res);
mixed   do_libo(object target, int res);
mixed   do_maetho(object target, object victim, int res);

mixed
do_naro(string str)
{
    object  tp = this_player(),
    env = environment(tp),
    *ingr_arr,
    *target,
    *victim,
    robe;
    int     is_wiz = tp->query_wiz_level(),
    min_level,
    diff,
    level,
    s,
    mana_cost,
    fail;
    mixed   result;
    string  level_word,
    rest,
    fail_msg = 0;

#if DEBUG
    is_wiz = 0;
#endif

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
    return "Without your robe, you cannot cast this spell!\n";

    str = LOW(str);

    if (!strlen(str) || !parse_command(str, env,
    " [the] %l %w %s", target, level_word, rest))
    {
    return "Cast the spell at whom?\n";
    }

    target = NORMAL_ACCESS(target, 0, 0);

    if (!(s = sizeof(target)))
    return "Cast the spell at whom?\n";
    if (s > 1)
    return "You cannot command more than one victim at a time!\n";
    if (target[0] == tp)
    return "You cannot command yourself!\n";
    if (IS_MORGUL_MAGE(target[0]))
    return "You cannot cast this spell on a fellow mage!\n";

    /*
     * Checks due to this spell being an attack spell
     * no attacks or no magic attacks on this target or in this room
     */
    if (NPMATTACK(target[0]))
    return MORGUL_S_SPELL_FAIL;

    if ((!F_DARE_ATTACK(tp, target[0])) && (tp->query_attack() != target[0]))
    return "You do not dare to cast the spell.\n";

    switch (level_word)
    {
    case "drego":
    if (rest == "nin" || rest == "nin!")
        level = 1;
    break;
    case "libo":
    if (rest == "makil" || rest == "makil!")
        level = 2;
    break;
    case "maetho":
    if (!strlen(rest))
        fail_msg = "Command your victim to attack whom?\n";
    else
    {
        victim = parse_this(rest, "[the] %l");
        victim -= target;
        if (sizeof(victim) != 1)
        fail_msg = "Command your victim to attack whom?\n";
        else
        level = 3;
    }
    break;
    default:
    level = 0;
    break;
    }

    if (!level)
    {
    if (strlen(fail_msg))
        return fail_msg;
    return "Tell your victim to do what?\n";
    }

    if ((level > 1) && (interactive(tp)))
    {
    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (objectp(tp->query_attack()))
        return "You cannot cast this spell during a fight!\n";
    }

    ingr_arr = find_ingr(MS_NARO_INGR, tp);

    mana_cost = level * MS_NARO_MANA_BASE;
    mana_cost = (mana_cost * (100 + MIN(100, target[0]->query_stat(SS_DIS)))) / 100;

    if ((level == 2) && (interactive(tp)) && objectp(target[0]->query_attack()))
    mana_cost += MS_NARO_MANA_BASE;
    diff = MS_NARO_TASK_BASE + (level - sizeof(ingr_arr)) * MS_NARO_TASK_DIFF;
    if (tp->query_npc())
    diff = MS_NARO_TASK_BASE;
    if (diff < 0)
    diff = 0;

    switch (level)
    {
    case 1: min_level = MS_NARO1_MIN; break;
    case 2: min_level = MS_NARO2_MIN; break;
    case 3: min_level = MS_NARO3_MIN; break;
    }

#if DEBUG
    write("Mana cost = "+mana_cost+"; difficulty = "+diff+"; level = "+min_level+"!\nIngredient array:\n");
    dump_array(ingr_arr);
#endif

    if (stringp(fail_msg = check_player(tp,
      ({}), mana_cost, min_level)))
    return fail_msg;

    tell_object(target[0], tp->query_The_name(target[0]) +
      " looks at you with burning eyes, trying to control your will.\n");
    write("You look deep into the eyes of " + target[0]->query_the_name(tp) +
      " trying to control " + HIS(target[0]) + " will with the power " +
      "that the Dark Lord has bestowed upon you!\n");

    if ((!is_wiz) && ((result = tp->resolve_task(
        diff, MS_NARO_LIST, target[0], MS_NARO_VICTIM)) <=
    target[0]->query_magic_res(MAGIC_I_RES_DEATH)))
    {
#if DEBUG
    write("DEBUG: naro failed with result = "+result+"!\n");
#endif
    tp->add_mana(-(mana_cost/3));

    // Logging - Morbeche
    if (find_player(target[0]->query_real_name()))
    {
        log_file("mm_player_fight", ctime(time())+" : "+tp->query_name()+
          " failed naro level " + level + " on " +
          target[0]->query_name() + " with result " + result + ".\n");
    }
    log_file("mm_command", ctime(time()) + " : " + tp->query_name() +
      " failed naro level " + level + " on " +
      target[0]->query_name() + " with result " + result +".\n");

    fail_cast(tp, ingr_arr);
    if (level == 1)
    {
        if (target[0]->query_npc())
        target[0]->command("$kill " + tp->query_real_name());
    }
    return 1;
    }

#if DEBUG
    write("Spell succeeds for level "+level+" with result = "+result+"!\n");
#endif

    // Logging - Morbeche
    if (find_player(target[0]->query_real_name()))
    {
    log_file("mm_player_fight", ctime(time())+" : "+tp->query_name()+
      " cast naro level " + level +" on " +
      target[0]->query_name() + " with result " + result + ".\n");
    }
    log_file("mm_command", ctime(time()) + " : " + tp->query_name() +
      " cast naro level " + level + " on " +
      target[0]->query_name() + " with result " + result +".\n");

    switch (level)
    {
    case 1:
    result = do_drego(target[0], result);
    break;
    case 2:
    result = do_libo(target[0], result);
    break;
    case 3:
    result = do_maetho(target[0], victim[0], result);
    break;
    }

    tp->add_mana(-mana_cost);
#if DEBUG
#else
    remove_ingr(ingr_arr);
#endif

    return result;
}

mixed
do_drego(object target, int res)
{
    int     i;
    object  tp = TP,
    naro_ob,
    room,
    *doors,
    cobj;
    string *wdir;

    write("Peering deeply into the eyes of " + target->query_the_name(tp) +
      " you command: Drego nin!\nTrembling in fear and panic, " +
      HE(target)+" runs away!\n");
    tell_object(target, "Staring deeply into your eyes with eyes burning " +
      "like red coals, " + tp->query_the_name(target) + " tells you: " +
      "Drego nin!\nYou do not understand what the words mean, but you " +
      "are filled with fear and panic and try to run away.\n");
    tell_room(ENV(tp), QCTNAME(tp) + " stares threateningly into the eyes " +
      "of " + QTNAME(target) + ", rasping the words: Drego nin!\n" +
      QCTNAME(target) + " starts to tremble and then runs away in panic.\n",
      ({ tp, target, }) );

    target->run_away();
    target->set_whimpy(MIN(MAX(25, target->query_whimpy() * 150 / 100), 100));
    target->add_panic(res + tp->query_stat(SS_OCCUP));
    // Did it work?
    if (ENV(tp) == (room = ENV(target)))
    {
    wdir = room->query_exit_cmds();
    if (sizeof(doors = filter(all_inventory(room), 
          &operator(==)(DOOR_OBJECT) @ &function_exists("create_object", ))))
        for (i = 0; i < sizeof(doors); i++)
        wdir += doors[i]->query_pass_command();
    cobj = target->query_combat_object();
    if (objectp(cobj))
        cobj->cb_run_away(ONE_OF_LIST(wdir));
    }

    if (target->query_npc())
    {
    FIX_EUID
    naro_ob = clone_object(MS_NARO_DREGO_OBJ);
    naro_ob->set_from_room(ENV(tp));
    naro_ob->move_back_with_delay(tp, res);
    naro_ob->move(target, 1);
    }
    return 1;
}

mixed
do_libo(object target, int result)
{
    int     i, j,
    *mag_arr,
    resist;
    object  tp = TP,
    *weapon;

    write("You raise your hand, menacing " + target->query_the_name(tp) +
      ", and command: Libo makil!\n" + target->query_The_name(tp) +
      " seems striken dumb, " + HIS(target) + " chest heaving heavily.\n");
    tell_object(target, tp->query_The_name(target) + " raises " + HIS(tp) +
      " hand, menacing you, and commands: Libo makil!\nYou fail to " +
      "understand the words, but you are striken dumb.\nYou feel your " +
      "tongue cleave to your mouth, and your heart labouring.\n");
    tell_room(ENV(tp), QCTNAME(tp) + " raises " + HIS(tp) + " hand, " +
      "menacing " + QTNAME(target) + ", and commands: Libo makil!\n" +
      QCTNAME(target) + " seems striken dumb, " + HIS(target) +
      " chest heaving heavily.\n", ({ tp, target, }) );
    weapon = target->query_weapon(-1);
    if (!sizeof(weapon))
    return 1;
    i = random(sizeof(weapon));

    // the spell should be less effective against magical weapons
    if (weapon[i]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
    mag_arr = weapon[i]->query_prop(MAGIC_AM_MAGIC);
    if (((j = member_array("enchantment", mag_arr)) > -1) &&
      intp(mag_arr[j-1]))
        resist += mag_arr[j-1];
    if (((j = member_array("death", mag_arr)) > -1) &&
      intp(mag_arr[j-1]))
        resist += mag_arr[j-1];
    resist += weapon[i]->query_prop(MAGIC_I_RES_DEATH);
    if (resist < result)
        weapon[i]->remove_broken();
    }
    else
    weapon[i]->remove_broken();
    target->command("$drop " + OB_NAME(weapon[i]));
    target->add_panic(result);
                                /*If a mage breaks player's weapon, that
                                  player will attack a mage.               */
    if (!(target->query_npc()))
    {
        if (this_player()->check_seen( target ))
        {
            tell_object( target, "Filled with grief and blinded by "+
                "the anger you rush toward " +
                this_player()->query_the_name( target ) + ".\n");
            tell_room( environment( this_player() ), QCTNAME( target ) +
                " suddenly rushes toward " + QCNAME( this_player() ) +
                ".\n", ({this_player(), target}) );
        }
        else
        {
            tell_object( target, "Filled with grief and blinded by "+
                "the anger you rush toward the source of voice.\n");
            tell_room( environment( this_player() ), QCTNAME( target ) +
                " suddenly rushes toward the source of voice.\n",
                ({this_player(), target}) );
        }
        tell_object( this_player(),
            target->query_The_name( this_player() ) +
            " suddenly rushes in your direction.\n" );
        target->attack_object( this_player() );
    }

    return 1;
}

mixed
do_maetho(object target, object victim, int res)
{
    object  tp = TP;

    write("You peer deeply into the eyes of " + target->query_the_name(tp) +
      " and pointing at " + victim->query_the_name(tp) + ", you command: " +
      "Maetho!\nActing like a possessed creature, " +
      target->query_the_name(tp) + " turns to attack " +
      victim->query_the_name(tp) + "!\n");
    tell_object(target, "Staring deeply into your eyes with eyes burning " +
      "like red coals, " + tp->query_the_name(target) + " points at " +
      victim->query_the_name(target) + " and tells you: Maetho!\nYou do " +
      "not understand what the word means, but feeling as if you are " +
      "possessed and you turn to attack " + victim->query_the_name(target) +
      "!\n");
    tell_object(victim, tp->query_The_name(victim) + " stares threateningly " +
      "into the eyes of " + target->query_the_name(victim) + ", and " +
      "pointing at you rasps the word: Maetho!\nActing like a possessed " +
      "creature, " + target->query_the_name(victim) + " turns to attack " +
      "you!\n");
    tell_room(ENV(tp), QCTNAME(tp) + " stares threateningly into the eyes " +
      "of " + QTNAME(target) + ", and pointing at " + QTNAME(victim) +
      " rasps the word: Maetho!\nActing like a possessed creature, " +
      QTNAME(target) + " turns to attack " + QTNAME(victim) + "!\n",
      ({ tp, target, victim, }) );
    if (interactive(target))
    target->add_prop(LIVE_O_LAST_KILL, victim);
    target->command("$kill " + OB_NAME(victim));
    return 1;
}

#undef DEBUG
