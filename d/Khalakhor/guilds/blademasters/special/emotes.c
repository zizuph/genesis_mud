/*
 * emotes.c
 *
 * This file contains the 'mundane' emotes of the Blademasters of
 * Khalakhor. It will not load by itself, it's meant to be included
 * into the main command soul, blade_soul.c in the same directory
 * as this file.
 *
 * Khail - April 15/97
 */

#define HIS_HER(x) x->query_possessive()
#define LIVE_I_VERIFY_CHAIN_BREAK "_live_i_verify_chain_break"

/*
 * Function name : cant_talk
 * Description   : Returns false if this_player can talk,
 *                 else a string with the failure message.
 * Arguments     : str - String describing the action to
 *                       be attempted, i.e. 'bwar'.
 * Returns       : As described.
 */
public string
cant_talk(string str)
{
    mixed fail;
    string ret;
    
    fail = TP->query_prop(LIVE_M_MOUTH_BLOCKED);

  /* Can't talk if gagged. */
    if (fail)
    {
        if (stringp(fail) && strlen(fail))
            ret = (string)fail;

        else
            ret = "You are somehow prevented from saying " +
                "anything!\n";
    }

  /* Can't talk if stunned. */
    if (TP->query_prop(LIVE_I_STUNNED))
    {
        ret = "You're too stunned and can't catch your breath " +
            "to say anything.\n";
    }

  /* Can't talk if under water. */
    fail = environment(TP)->query_prop(ROOM_I_TYPE);
    if (fail == ROOM_UNDER_WATER)
    {
        ret = "You can't say anything underwater.\n";
    }

    if (ret && strlen(ret))
        return ret;
    else
        return 0;
}

/*
 * Function name : do_bwar
 * Description   : Allows players to use the blademaster's warcry.
 * Arguments     : n/a
 * Returns       : 0 - Fail (i.e. gagged).
 *                 1 - Success.
 */
public int
do_bwar(string str)
{
    mixed *weapons;
    string fail;
    
    weapons = TP->query_weapon(-1);

  /* Can't warcry if we can't talk. */
    if (fail && strlen(fail = cant_talk("bwar")))
    {
        NF(fail);
        return 0;
    }

  /* Hard to stay hidden when you're waving a sword over */
  /* your head and screaming like a madman. */
    TP->reveal_me(1);

    if (!sizeof(weapons))
    {
        write("Raising a clenched fist above your head, you " +
            "bellow the ancient warcry of the Blademasters!\n");
        say("Raising a clenched fist above " + HIS_HER(TP) +
            " head, " + QTNAME(TP) + " roars an ancient warcry!\n");
    }
    else if (sizeof(weapons) == 1)
    {
        write("Raising your " + weapons[0]->short() +
            " above your head, you roar the ancient warcry of " +
            "the Blademasters!\n");
        say("Raising " + HIS_HER(TP) + " " + weapons[0]->short() +
            " above " + HIS_HER(TP) + " head, " + QTNAME(TP) +
            " roars an ancient warcry!\n");
    }
    else
    {
        write("Raising your " + weapons[0]->short() + " and " +
            weapons[1]->short() + " above your head, you roar " +
            "the ancient warcry of the Blademasters!\n");
        say("Raising " + HIS_HER(TP) + " " + weapons[0]->short() +
            " and " + weapons[1]->short() + " above " +
            HIS_HER(TP) + " head, " + QTNAME(TP) + " roars " +
            "an ancient warcry!\n");
    }
    TP->command("shout Gloir Bhur Lannen! Glory Thy Blade!");
  
  /* Is the player trying to attack someone? */
    if (str && strlen(str))
        TP->command("kill " + str);

    return 1;
}

/*
 * Function_name : do_flip
 * Description   : Allows a player to flip a weapon around in a 
 *                 circle.
 * Arguments     : str - Arguments supplied to 'bflip', but not
 *                       used anyway.
 * Returns       : 0 - Do nothing.
 *                 1 - Do emote.
 */
public int
do_flip(string str)
{
    mixed weplist;
    object weapon;

    NF("Bflip which weapon?\n");

    if (!str || !strlen(str))
        return 0;

    weplist = FIND_STR_IN_OBJECT(str, TP);

    if (!sizeof(weplist))
        return 0;

    if (sizeof(weplist) > 1)
    {
        NF("You can only bflip one weapon at a time.\n");
        return 0;
    }

    weapon = weplist[0];

    if (weapon->query_wt() != W_SWORD)
    {
        NF("You can only bflip a sword.\n");
        return 0;
    }

    if (!(weapon->query_wielded()) ||
        weapon->query_wielded() != TP)
    {
        NF("You are not wielding the " + weapon->short() + ".\n");
        return 0;
    }

    write("You gracefully flip your " + weapon->short() + " around " +
        "in your hand, testing the balance.\n");
    allbb(" gracefully flips " + TP->query_possessive() +
        " " + weapon->short() + " around in " + TP->query_possessive() +
        " hand a few times.");
    return 1;
}

/*
 * Function name: do_oath
 * Description  : Allows players to make the blademaster's oath,
 *                basically just a way for them to 'swear allegiance'
 *                to someone in a flashy way.
 * Arguments    : str - Extra args to the 'boath' command.
 * Returns      : 0 - Keep threading. 
 *                1 - Stop threading.
 */
public int
do_oath(string str)
{
    object *who,
           *weapons;
    string wepstring,
           fail;

    NF("Make a Blademaster's oath of allegiance to whom?\n");

    if (!str || !strlen(str)) 
         return 0;

    who = parse_this(str, "[to] [the] %l");
    if (!sizeof(who)) 
        return 0;

    if (sizeof(who) > 1)
    {
        NF("You can only make a Blademaster's oath of allegiance " +
            "to one person at a time.\n");
        return 0;
    }

    if (strlen(fail = cant_talk("oath")))
    {
        NF(fail);
        return 0;
    }

    weapons = filter(TP->query_weapon(-1), &operator(==)(W_SWORD) @
        &->query_wt());
    if (!sizeof(weapons))
    {
        NF("You cannot make a Blademaster's oath of allegiance " +
            "without a sword.\n");
        return 0;
    }

    wepstring = COMPOSITE_WORDS(weapons->short());
    
    actor("You drop gracefully to one knee on the ground " +
        "before", who, ", lowering your eyes and raising your " +
        wepstring + " to your forehead. Solemnly, you intone " +
        "the oath: To thee I pledge my blade, my skill, and " +
        "my courage. To thy enemy, I pledge only my wrath, " +
        "and the justice which shall be thine."); 
    targetbb(" drops gracefully to one knee on the ground before " +
        "you, lowering " + TP->query_possessive() + " eyes and " +
        "raising " + TP->query_possessive() + " " + wepstring + 
        " to " + TP->query_possessive() + " forehead.", who);
    target(" intones to you the ancient oath of the Blademasters: " +
        "To thee I pledge my blade, my skill, and my courage. To " +
        "thy enemy, I pledge only my wrath, and the justice which " +
        "shall be thine.", who); 
    all2actbb(" drops gracefully to one knee on the ground before", 
        who,", lowering " + TP->query_possessive() + " eyes " +
        "and raising " + TP->query_possessive() + " " + wepstring +
        " to " + TP->query_possessive() + " forehead.", who);
    all2act(" intones to", who, " the ancient oath of the " +
        "Blademasters: To thee I pledge my blade, my skill, and my " +
        "courage. To thy enemy, I pledge only my wrath, and the " +
        "justice which shall be thine.", who);
    return 1;
}

/*
 * Function name: do_salute
 * Description  : Lets the player salute others with a sword.
 * Arguments    : str - Who the player is saluting.
 * Returns      : 0 - Do nothing.
 *                1 - Do emote.
 */
public int
do_salute(string str)
{
    object *oblist,
           *weplist;
    string wepshort;

    NF("Bsalute who?\n");

    if (!str || !strlen(str))
        return 0;

    weplist = filter(TP->query_weapon(-1), &operator(==)(W_SWORD) @
        &->query_wt());

    if (!sizeof(weplist))
    {
        NF("You must be wielding a sword to bsalute someone.\n");
        return 0;
    }

    wepshort = weplist[0]->short();

    oblist = parse_this(str, " %l");

    if (!sizeof(oblist))
        return 0;

    actor("You salute", oblist, " with a flourish of your " +
        wepshort + ".");
    targetbb(" salutes you with a flourish of " +
        TP->query_possessive() + " " + wepshort + ".", oblist);
    all2actbb(" salutes", oblist, " with a flourish of " +
        TP->query_possessive() + " " + wepshort + ".");
    return 1;
}

/*
 * Function name: do_smile
 * Description  : Special smile for the guild.
 * Arguments    : str - Argument to the command.
 * Returns      : 0 - Do nothing
 *                1 - Do emote.
 */
public int
do_smile(string str)
{
    object *oblist;

    NF("Bsmile at who?\n");

    if (!str || !strlen(str))
    {
        write("You smile confidently, secure in your abilities " +
            "with a sword.\n");
        allbb(" smiles confidently, secure in " +
            TP->query_possessive() + " abilities with a sword.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
        return 0;

    actor("You smile confidently at",oblist,", secure in your " +
        "abilities with a sword.");
    targetbb(" smiles confidently at you, secure in " +
        TP->query_possessive() + " abilities with a sword.", oblist);
    all2actbb(" smiles confidently at",oblist,", secure in " +
        TP->query_possessive() + " abilities with a sword.");
    return 1;
}

/*
 * Function name: do_break
 * Description  : Lets the player destroy Blademaster equipment.
 * Arguments    : str - String, what the player wants to break.
 * Returns      : 0 - Do nothing.
 *                1 - Broke something.
 */
public int
do_break(string str)
{
    object *ob;
    string desc;

    notify_fail("Break what?\n");

    if (!str || !strlen(str))
        return 0;

    ob = FIND_STR_IN_OBJECT(str, TP);

    if (!sizeof(ob))
    {
        notify_fail("You find no such item to destroy.\n");
        return 0;
    }

    if (sizeof(ob) > 1)
    {
        notify_fail("You can only break one thing at a time.\n");
        return 0;
    }

    if (!ob[0]->is_blademaster_equipment())
    {
        notify_fail("You find no such piece of Blademaster " +
            "equipment to destroy.\n");
        return 0;
    }

    desc = ob[0]->short();

    if (ob[0]->check_weapon())
    {
        write("Bracing the blade of the " + desc +
            " on the ground, you strike it at a practiced " +
            "angle, breaking it!\n");
        say(QCTNAME(TP) + " braces the blade of " +
            LANG_ADDART(desc) + " on the ground, " +
            "and strikes it with a skillful blow, breaking " +
            "it!\n");
        ob[0]->remove_broken();
        return 1;
    }

    if (ob[0]->check_armour())
    {
        write("Grasping the " + desc + " by the seams, " +
            "you effortlessly rend it to tatters.\n");
        say(QCTNAME(TP) + " grasps " + LANG_ADDART(desc) +
            " by the seams, and effortlessly rends it to " +
            "tatters!\n");
        ob[0]->remove_broken();
        return 1;
    }

    if (ob[0]->query_prop(OBJ_I_BLADEMASTER_ARM))
    {
        ob[0]->remove_me();
        write("Grasping the " + desc + " by the seams, " +
            "you effortlessly rend it to tatters.\n");
        say(QCTNAME(TP) + " grasps " + LANG_ADDART(desc) +
            " by the seams, and effortlessly rends it to " +
            "tatters!\n");
        ob[0]->remove_object();
        return 1;
    }

    if (ob[0]->query_prop(OBJ_I_BLADEMASTER_GOBJ))
    {
        if(!IS_BLADEMASTER(TP))
        {
        notify_fail("You cannot break that.\n");
        return 0;
        }

  /* Allow a break that does nothing if this_player() is */
  /* not the 'owner' of this chain, as determined by the */
  /* first Blademaster who carries it after cloning. */
        if (ob[0]->query_owner() != TP)
        {
        write("Grasping the " + desc + " tightly, you give it " +
            "the expert twist required to shatter the links.\n");
        say(QCTNAME(TP) + " grasps " + LANG_ADDART(desc) + 
            " tightly, and gives it a quick twist that shatters " +
            "all the links.\n");
        ob[0]->remove_object();
        return 1;
        }

  /* If this_player() is the owner of this chain, see if he */
  /* really wants to leave the Blademasters. Confirmation is */
  /* done by checking for a verify prop in the player. */
    if (!TP->query_prop(LIVE_I_VERIFY_CHAIN_BREAK))
    {
        write("Breaking the chain will result in forfeit " +
            "of your claim to your rightful title as Blademaster. " +
            "Once forfeited, it can never be reclaimed. Break " +
            "the chain again, if you are sure this is what you " +
            "want to do.\n");
        TP->add_prop(LIVE_I_VERIFY_CHAIN_BREAK, 1);
        return 1;
    }

  /* Ok, this_player() is the Blademaster who owns this chain, */
  /* and has attempted to break the chain once already. */
  /* This player will soon be an ex-Blademaster. */
    write("Grasping the " + desc + " tightly, you give it " +
        "the expert twist required to shatter the links.\n");
    say(QCTNAME(TP) + " grasps " + LANG_ADDART(desc) + 
        " tightly, and gives it a quick twist that shatters " +
        "all the links.\n");
    write("You give up your title as Blademaster, and leave " +
        "their ways behind.\n");
    ob[0]->leave_blademaster_guild();
    return 1;
    }

    notify_fail("You cannot break that.\n");
    return 0;
}
