/*
 * /d/Gondor/common/guild2/spells/palanquendo.h
 *
 * The tell line of the Morgul Mages
 * (palan-quendo = far-tell)
 * 
 * Class 0 spell
 * Element Air, Form Conjuration
 * Area of effect: location
 *
 * Ingredient: copper coin
 * Mana: 10, 20 for message to non-members
 * Skills: SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT
 * Description: Delivers a message to another living
 * Requirements: Morgul Mage, SS_OCCUP > 0
 *
 * Olorin, 14-jul-1994
 */

#define MS_PALAN_INGR     ({ "copper coin", })
#define MS_PALAN_MANA_IN   10
#define MS_PALAN_MANA_EX   20
#define MS_PALAN_TASK     TASK_SIMPLE
#define MS_PALAN_LIST     ({ SS_ELEMENT_AIR, SS_FORM_ENCHANTMENT, SS_SPELLCRAFT})

mixed
do_palanquendo(string str)
{
    int     mana_cost,
            is_wiz,
            result;
    mixed   fail;
    object  tp = this_player(),
            env = environment(tp),
            receiver,
           *ingr_arr;
    string  who,
            what,
            msg,
            msg_m,
            msg_n;

#if DEBUG
    is_wiz = 0;
#endif

    if (sizeof(tp->query_weapon(-1)))
        return "You cannot cast a spell while wielding a weapon!\n";
    if (!tp->query_npc() && objectp(tp->query_attack()))
        return "You cannot cast this spell while in combat!\n";

    if (ENV(tp)->query_prop(ROOM_I_NO_MAGIC))
        return MORGUL_S_SPELL_FAIL;

    if (!present(MORGUL_S_GUILD_OBJECT, tp))
        return "Without your robe, you cannot cast this spell!\n";

    if (!stringp(str))
        return "Whom do you tell what?\n";

    if (sscanf(str,"%s %s", who, what) != 2)
        return "Whom do you tell what?\n";

    who = lower_case(who);
    receiver = find_player(who);

    /*
     * Changed after discussion with Rastlin:
     * magic tell spells should permit to reach unknown players, too,
     * to distinguish them from messenger animals.
     * Olorin, January 1997
     */
    if (!objectp(receiver) ||
        receiver->query_linkdead())
    {
        return "Your message is lost in the void.\n";
    }

    /*
     * We permit tells to wizards only if the wizard is either a 
     * member of the Morgul mages or of the domain Gondor:
     */
    if (receiver->query_guild_name_occ() != GUILD_NAME)
    {
	if ((receiver->query_wiz_level()) &&
            (receiver->query_domain() != "Gondor"))
        {
            return "Your message is lost in the void.\n";
        }
        mana_cost = MS_PALAN_MANA_EX;
    }
    else
        mana_cost = MS_PALAN_MANA_IN;

    if (stringp(fail = check_player(tp, MS_PALAN_INGR, mana_cost,
        MS_PALAN_MIN)))
        return fail;

    ingr_arr = find_ingr(MS_PALAN_INGR, tp);

    if (!is_wiz &&
        (result = tp->resolve_task(MS_PALAN_TASK, MS_PALAN_LIST)) <= 0)
    {
#if DEBUG
    write("DEBUG: palanquendo failed with result: " + result + "\n");
#endif
        fail_cast(tp, ingr_arr);
        return 1;
    }
#if DEBUG
    write("DEBUG: palanquendo succeeded with result: " + result + "\n");
#endif

    msg_m = "Employing Dark Sorcery, " + tp->query_met_name() +
        " casts a spell.\n";
    msg_n = "Employing Dark Sorcery, the " + tp->query_nonmet_name() +
        " casts a spell.\n";
    say( ({ msg_m, msg_n, "" }) );

    /* If a wizard is invisible, the sender should not get a confirmation,
     * but the message should be sent.
     */
    if (receiver->query_wiz_level() && receiver->query_invis())
    {
        write("Your message is lost in the void.\n");
        is_wiz = 1;
    }
    else
    {
        if (tp->query_option(OPT_ECHO))
            write("With the power the Dark Lord has bestowed upon you, " +
                "you tell " + receiver->query_met_name() + ":\n" +
                break_string(what, 60, "   ") + "\n");
        else
            write("With the power the Dark Lord has bestowed upon you, " +
                "you send a message to " + receiver->query_met_name() + ".\n");
    }

    tell_object(receiver, "With the help of Dark Sorcery, " +
        tp->query_art_name(receiver) + " tells you:\n" +
        break_string(what, 60, "   ") + "\n");

    if (!is_wiz)
    {
        tp->add_mana(-mana_cost);
        remove_ingr(ingr_arr);
    }

    return 1;
}
