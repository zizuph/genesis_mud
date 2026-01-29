/*
 * /d/Gondor/common/guild/spells/elbereth.c
 *
 * Modification log:
 * 17-Jun-1997, Olorin: Check value of LIVE_I_UNDEAD to modify strength of effect.
 */
#pragma save_binary
#pragma strict_types

#define SP_ELBERETH_MANA  75
#define SP_ELBERETH_INGR ({ "torch" })

/*
 * Function name:   do_elbereth_spell
 * Decription:	    Cast the elbereth spell.
 * Returns:	    1 if spell was cast, 0 otherwise.
 */
mixed
do_elbereth_spell(string person)
{
    object  tp, 
            env, 
           *ob_arr, 
           *ingr_arr, 
            obj, 
            target;
    int     i, 
            is_wiz, 
            undead,
            diff,
            success, 
            fighting;
    string  fail,msg;

    if (!strlen(person)) 
    {
        return "Whom do you want to scare away?\n";
    }

    person = lower_case(person);
    tp = this_player();
    env = environment(tp);
    is_wiz = tp->query_wiz_level();

    if (!parse_command(person, all_inventory(ENV(tp)), "%l", ob_arr) ||
    !sizeof(ob_arr = NORMAL_ACCESS(ob_arr, 0, 0)))
    {
	return "That person is not here.\n";
    }
    target = ob_arr[0];
    
    if (tp->query_mana() < SP_ELBERETH_MANA) 
    { 
        return "You feel too weak to ask for Elbereth's aid.\n";
    }
    /* Get the object array of all ingredients */
    ingr_arr = find_ingr(SP_ELBERETH_INGR, tp);
    if (sizeof(ingr_arr) < 1)
    {
        return BSN("You need a torch to attempt this prayer!");
    }
    if (ingr_arr[0]->query_prop(OBJ_I_HAS_FIRE) == 0)
    {
        return BSN("You need a burning torch to even have a chance "
            + "at turning an Undead being away!");
    }

    /*
     * The difficulty changes with with the value of the LIVE_I_UNDEAD property.
     * With a value of 1, the task is simple, with a value of 100, the task is
     * difficult.
     */
    if ((undead = target->query_prop(LIVE_I_UNDEAD)) < 1)
    {
        return "That person is not an undead!\n";
    }

    if (undead > 100)
        undead = 100;

    diff = TASK_SIMPLE/2 + undead * (TASK_DIFFICULT - TASK_ROUTINE) / 100;
    if (tp->query_guild_name_race() == "Dunedain")
        diff -= tp->query_dunedain_level() / 2;
    if (tp->query_race() == "elf")
        diff -= tp->query_average_stat() / 2;

    /* Let's see if the player can cope with the task... */
    success = tp->resolve_task(diff,
        ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
           SKILL_WEIGHT, 90, SKILL_AVG, TS_WIS, TS_INT, SKILL_END,
           SKILL_WEIGHT, 30, SS_FORM_CONJURATION, 
           SKILL_WEIGHT, 30, SS_ELEMENT_LIFE }), 
        target, 
        ({ SKILL_WEIGHT, 30, SS_FORM_ABJURATION,
           SKILL_WEIGHT, 70, SS_ELEMENT_LIFE,
           SKILL_AVG, TS_WIS, TS_DIS, SKILL_END, }) );
    log_file("elbereth", tp->query_name() + " casts Elbereth with success: "
      + success + " against " + target->query_name() + ", undead level: "
      + undead + ". " + ctime(time()) + "\n");
    if (!is_wiz && (success <= 0))
    {
        tp->catch_msg("You desperately wave the burning torch before "
            + QTNAME(target)+".\n");
        tell_room(environment(tp), QCTNAME(tp) + " desperately waves a "
            + "burning torch before "+QTNAME(target)+".\n", tp);
        if (!random(4))
        {
            tp->catch_msg("Your torch flames up briefly, then burns out.\n");
            ingr_arr[0]->remove_object();
        }
        tp->catch_msg("Your foe looks unscathed.\n");
        tp->add_mana(-(SP_ELBERETH_MANA/3));
        return 1;
    }
    else if (success < 25)
    {
        say(QCTNAME(tp) + " waves a burning torch before " + QTNAME(target)
          + ", crying: O Elbereth! Gilthoniel!\n", ({ tp, target }));
        tp->catch_msg("You wave the burning torch before the evil "
          + QNAME(target) + ", crying:\n\tO Elbereth! Gilthoniel!\n");

        target->catch_msg(QCTNAME(tp)+" waves a burning torch before you, "+
          "crying out loudly: ");
        target->add_panic(success + (tp->query_stat(SS_OCCUP) / 2));
        target->catch_msg("O Elbereth! Gilthoniel!\n"+
          "You feel fear seizing your mind for a moment!\n");
        target->command("$back " + tp->query_real_name());
        if (IS_MORGUL_MAGE(target))
            target->command("mshriek");

    }
    else
    {
        say(QCTNAME(tp) + " waves a burning torch before " + QTNAME(target)
          + ", crying: O Elbereth! Gilthoniel!\n", ({ tp, target }));
        tp->catch_msg("You wave the burning torch before the evil "
          + QNAME(target) + ", crying:\n\tO Elbereth! Gilthoniel!\n");

        target->catch_msg(QCTNAME(tp)+" waves a burning torch before you, "+
          "crying out loudly: ");
        target->add_panic(success + tp->query_stat(SS_OCCUP));
        target->catch_msg("O Elbereth! Gilthoniel!\n"+
          "You feel fear seizing your mind for a moment!\n");
        if (IS_MORGUL_MAGE(target))
            target->command("mshriek");
        target->run_away();
        if (!is_wiz)
        {
            tp->catch_msg("Your torch flames up brightly for a moment, and is "
              + "consumed as your prayer takes effect!\n");
            ingr_arr[0]->remove_object();
        }
        tp->add_mana(-SP_ELBERETH_MANA);
    }
    return 1;
}
