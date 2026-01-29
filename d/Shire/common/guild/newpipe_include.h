/*
 *   This file is included in the pipe.c file and uses functions and
 *   variables from that file.
 */

/*************************************************************************
 *
 *   Prototypes
 */

int is_founder(string str);
int is_member(mixed who);
int is_a_shire(object ob);
int set_silent();
int has_a_pipe(object obj);
static int add_soul_at_top(string soul, object who);


/************************* Identify procedures *********************/

/* Founders are either member of the HOMEDOMAIN or they are SPECIAL */

int
is_founder(string str)
{
    if (!str)
	return 0;
    str = lower_case(str);
    if (SECURITY->query_wiz_dom(str) == HOMEDOMAIN)
	return 1;
    return (member_array(str, IS_SPECIAL) != -1);
}

/*
 * Function name:   is_member
 * Description:     Test if the person is a member of the Hin Warrior guild
 * Arguments:       who: Either the name or the object of the person to check
 * Returns:         1 if a member, 0 otherwise
 */
int
is_member(mixed who)
{
    object ob;

    if (!who)
	return 0;
    if (stringp(who))
	ob = find_player(lower_case(who));
    else if (objectp(who))
	ob = who;
    else
	return 0;
    if (!ob || !interactive(ob))
	return 0;
    if (ob->test_bit(HOMEDOMAIN, SB_GROUP, SB_BIT))
	return 1;
    return 0;
}

/*
 * Function name:   is_a_shire
 * Description:     Test whether this person is also bearing a Hin Warrior
 *                  title (also known as a true Hin Warrior).
 * Arguments:       owner: The person to check.
 * Returns:         1 if the person is a true Hin Warrior, 0 otherwise.
 */
int
is_a_shire(object ob)
{
    string str;

    if (ob->query_wiz_level() > WIZLEV_LORD)
	return 1;
    if (is_founder(ob->query_real_name()))
        return 1;
    str = ob->query_title();
    if (str && sscanf(str, "%s Shires%s", str, str) == 2)
	return 1;
    return 0;
}

/*
 * Function name:   throw_out_of_guild
 * Description:     Expell someone from the Hin Warrior guild. The person's
 *		    guildbit is erased, and all Shire-stuff is removed. Also
 *                  the skills that can be trained in our guild are creamed
 *                  off.
 *                  This function does not include the removal of the pipe!
 * Arguments:       ob:    player to be thrown out.
 *                  check: TRUE if this_player() wants a checklist.
 * Returns:         1 if successful, 0 otherwise.
 */
static int
throw_out_of_guild(object ob, int check)
{
    object pipe;
    string str, *list;
    int sk;

    seteuid(getuid());

    if (!ob->clear_bit(SB_GROUP, SB_BIT))
    {
	log_file("errors", ctime(time()) + " Could not clear guild bit in "
		 + capitalize(ob->query_real_name()) + ".\n");
	if (check)
	    write("-> Could not clear guild bit.\n");
    }
    else if (check)
	write("-> Successfully cleared the guild bit.\n");

    /* Fix the skills */
    if ((sk = ob->query_skill(SS_FORM_CONJURATION)) > 10)
        ob->set_skill(SS_FORM_CONJURATION, sk/2);
    
    if ((sk = ob->query_skill(SS_FORM_ABJURATION)) > 10)
        ob->set_skill(SS_FORM_ABJURATION, sk/2);
    
    if ((sk = ob->query_skill(SS_FORM_ENCHANTMENT)) > 10)
        ob->set_skill(SS_FORM_ENCHANTMENT, sk/2);
    
    if ((sk = ob->query_skill(SS_FORM_TRANSMUTATION)) > 10)
        ob->set_skill(SS_FORM_TRANSMUTATION, sk/2);
    
    if ((sk = ob->query_skill(SS_ELEMENT_LIFE)) > 10)
        ob->set_skill(SS_ELEMENT_EARTH, sk/2);
    
    if ((sk = ob->query_skill(SS_APPR_MON)) > 10)
        ob->set_skill(SS_APPR_MON, sk/2);
    
    if ((sk = ob->query_skill(SS_APPR_OBJ)) > 10)
        ob->set_skill(SS_APPR_OBJ, sk/2);
    
    if ((sk = ob->query_skill(SS_HERBALISM)) > 10)
        ob->set_skill(SS_HERBALISM, sk/2);
    
    if ((sk = ob->query_skill(SS_LANGUAGE)) > 10)
        ob->set_skill(SS_LANGUAGE, sk/2);
    
    if ((sk = ob->query_skill(SS_LOC_SENSE)) > 10)
        ob->set_skill(SS_LOC_SENSE, sk/2);
    
    if (ob->query_guild_member(GUILD_NAME))
    {
	ob->set_guild_pref(SS_LAYMAN, 0);
	if (check)
	    write("-> Relieved of the guildtax.\n");

        ob->clear_guild_stat();
        if (check)
            write("-> Cleared accumulated guild stat experience.\n");

	if (check)
	    write("-> Guild shadow found ");
	if (ob->remove_guild_lay() && check)
	    write("and removed.\n");
	else if (check)
	    write("but failed to remove.\n");
    }
    else if (check)
	write("-> Guild shadow not found.\n");

    list = ob->query_cmdsoul_list();
    if (member_array(OWN_SOUL, list) >= 0)
    {
	if (check)
	    write("-> Guild soul found ");
	if (ob->remove_cmdsoul(OWN_SOUL) && check)
	    write("and removed.\n");
	else if (check)
	    write("but failed to remove.\n");
    }
    else if (check)
	write("-> Guild soul not found.\n");
    return 1;
}

/*
 * Function name:   add_soul_at_top
 * Description:     add given soul at the top of the cmdsoul list
 * Arguments:       soul: filename of soul to be added
 *                  who:  player the soul must be added to
 * Returns:         1 if successful, 0 otherwise.
 */
static int
add_soul_at_top(string soul, object who)
{
    string *soul_arr;
    int i;

    seteuid(getuid());
    if (member_array(soul, who->query_cmdsoul_list()) >= 0)
	who->remove_cmdsoul(soul);
    if (!who->add_cmdsoul(soul))
	return 0;
    else
	who->remove_cmdsoul(soul);
    soul_arr = who->query_cmdsoul_list();
    for (i = 0; i < sizeof(soul_arr); i++)
	who->remove_cmdsoul(soul_arr[i]);
    who->add_cmdsoul(soul);
    for (i = 0; i < sizeof(soul_arr); i++)
	who->add_cmdsoul(soul_arr[i]);
    who->update_hooks();
    return 1;
}

/*
 * Function name:   join_to_guild
 * Description:     Join someone to the Hin Warrior guild. The person's
 *                  guildbit will be set, and necessary Shire-stuff will be
 *                  added. It will not add the pipe, tough.
 * Arguments:       ob: player to be joined
 * Returns:         1 if successful, 0 otherwise.
 */
static int
join_to_guild(object ob, int check)
{
    object shadow;
    int i;

    seteuid(getuid());

    if (!ob->set_bit(SB_GROUP, SB_BIT))
    {
	log_file("errors", ctime(time()) + " Could not set guild bit in "
		 + capitalize(ob->query_real_name()) + ".\n");
	if (check)
	{
	    write("-> Could not set guild bit.\n");
	    write("-> Aborting...\n");
	}
	return 0;
    }
    else if (check)
	write("-> Successfully set the guild bit.\n");

    ob->set_guild_pref(SS_LAYMAN, GUILD_TAX);
    if (check)
	write("-> Set guild-tax.\n");

    if (ob->query_guild_member(GUILD_NAME))
    {
	if (check)
	    write("-> Player already has a guild shadow.\n");
    }
    else
    {
	shadow = clone_object(SHIRE_SHADOW);
	i = shadow->shadow_me(ob, GUILD_TYPE, GUILD_STYLE, GUILD_NAME);
	if (i == 1)
	{
	    if (check)
		write("-> Successfully added the guild shadow.\n");
	}
	else
	{
	    if (check)
	    {
		write("-> Failed to add the guild shadow.\n");
		write("-> Aborting...\n");
	    }
	    shadow->remove_object();
	    return 0;
	}
    }
    if (ob->query_wiz_level() == WIZLEV_MORTAL)
    {
	if (add_soul_at_top(SHIRE_SOUL, ob))
	{
	    if (check)
		write("-> Successfully added the guild soul.\n");
	}
	else
	{
	    if (check)
	    {
		write("-> Failed to add the guild soul.\n");
		write("-> Aborting...\n");
	    }
	    return 0;
	}
    }
    else if (check)
	write("-> Skipped addition of the guild soul.\n");
    return 1;
}

/*
 * Function name:   join_to_guild_from_statue
 * Description:     Is called from statue.c and joins someone who typed
 *                  'pledge allegiance'.
 * Arguments:       -
 * Returns:         1 if successful, 0 otherwise.
 */
int
join_to_guild_from_statue()
{
    if (MASTER_OB(previous_object()) != STATUEPOS)
	return 0;
    if (is_member(this_player()))
    {
	if (!present(MY_UNIQUE_ID, this_player()))
	{
	    write("You receive a brand new pipe of the Shires.\n");
	    this_object()->move(this_player());
	}
	else
	{
	    write("You already are a member of our guild.\n");
	    this_object()->remove_object();
	}
	return 0;
    }
    if (join_to_guild(this_player(), 0))
	return 1;
    throw_out_of_guild(this_player(), 0);
    write("Something went wrong, but I don't have clue what...\n");
    write("Please contact a Shire wizard.\n");
    this_object()->remove_object();
    return 0;
}

/*****************   "Founders only"-functions    **********************
 ********                                                       ********
 ********  Some memberlist editing procedures                   ********
 ********  Of course these should be static, to prevent forcing ********/

/*
 * Function name:   do_expell
 * Description:     Expell someone from the Hin Warrior guild. The person's
 *		    guildbit is erased, and all Shire-stuff is removed.
 * Arguments:       str: Name of the person to be expelled.
 * Returns:         1 if successful, 0 otherwise.
 */
static int
do_expell(string str)
{
    object ob, pipe;

    if (!str || !is_founder(this_player()->query_real_name()))
	return 0;
    ob = find_player(str);
    if (!ob)
    {
	notify_fail("No player with that name.\n");
	return 0;
    }
    if (ob == this_player())
    {
	notify_fail("You can't expell yourself.\n");
	return 0;
    }
    if (is_founder(ob->query_real_name()))
    {
	notify_fail("Nob Nar is very fond of " + ob->query_name() + " and won't "
		    + "let you do it.\n");
	return 0;
    }
    if (!this_object()->throw_out_of_guild(ob, 1))
    {
	write("Failed to expell " + ob->query_name() + " from the Hin Warrior "
	      + "guild.\n");
	return 1;
    }
    write("You have expelled " + ob->query_name() + " from the Hin Warrior "
	  + "guild.\n");
    ob->catch_msg(QCTNAME(this_player()) + " has expelled you from the Hin "
		  + "Warrior guild.\n");
    if (pipe = present(MY_UNIQUE_ID, ob))
    {
	pipe->remove_object();
	ob->catch_msg("Your pipe desintegrates in a flash.\n");
    }
    return 1;
}

/*
 * Function name:   do_enlight
 * Description:     allows shire-wizards to recrute others to the Shire guild
 * Arguments:       name of player
 * Returns:         1 for successful, else 0
 */
static int
do_enlight(string str)
{
    object ob;

    if (!str)
	return 0;
    if (!is_a_shire(this_player()) ||
	this_player()->query_wiz_level() <= WIZLEV_APPRENTICE)
    {
	notify_fail("You must be a wizard of the Shires to do that.\n");
	return 0;
    }
    if (is_founder(this_player()->query_real_name()))
	ob = find_player(str);
    else
	ob = present(str, environment(this_player()));

    if (!ob || !interactive(ob))
    {
	notify_fail("No player with that name.\n");
	return 0;
    }
    if (ob == this_player())
    {
	notify_fail("Sharing Shirehood with oneself is too deep.\n");
	return 0;
    }
    if (!join_to_guild(ob, 1))
    {
	write("Failed to enlight " + ob->query_name() + ".\n");
	return 1;
    }
    clone_object(MASTER)->move(ob);
    write("You quickly duplicate your pipe and let " + ob->query_name() + " "
	  + "share the joy of it!\n");
    ob->catch_msg(QCTNAME(this_player()) + " gives you a wonderful pipe!\n");
    ob->catch_msg("You are now a member of the Hin Warrior guild.\n");
    return 1;
}

static int
do_remove_list(string str)
{
    int index;

    if (!is_founder(this_player()->query_real_name()))
	return 0;

    if (!str || str == "?")
    {
	write("Usage: " + query_verb() + " <playername>\n"
	+ "This will remove <playername> from the list of banned people.\n");
    }

    str = capitalize(lower_case(str));
    restore_object(LISTPOS);

    if ((index = member_array(str, banned)) != -1)
    {
	/* Delete the name from the members list */
	banned = exclude_array(banned, index, index);
	save_object(LISTPOS);
	write("Removed " + str + " from the banish-list.\n");
	return 1;
    }
    write("Could not find " + str + " in the banish-list.\n");
    return 1;
}

static int
do_add_list(string str)
{
    if (!is_founder(this_player()->query_real_name()))
	return 0;

    if (!str || str == "?")
    {
	write("Usage: " + query_verb() + " <playername>\n"
	    + "This will add <playername> to the list of banned people.\n");
    }

    str = capitalize(lower_case(str));
    restore_object(LISTPOS);

    if (member_array(str, banned) != -1)
    {
	write(str + " already is in the banish-list.\n");
	return 1;
    }
    banned += (
	       {
	str
    });
    save_object(LISTPOS);
    write("Added " + str + " to the banish-list.\n");
    return 1;
}

static int
do_show_list(string str)
{
    string *tmp_array;

/*
 *       Showlist command syntax:
 *            showlist [partial_name]
 */
    if (!is_founder(this_player()->query_real_name()))
	return 0;

    /* Analyse the input-string */
    if (!str)
	str = "";

    str = lower_case(str);

    if (str == "?")
    {
	write("\nCOMMAND:   Showlist\n\n"
	      + "FORMAT:\n   showlist [name]\n\n"
	      + "SYNOPSIS:\n");
	write("   Showlist shows all members of the Hin warrior guild who are\n"
	      + "   registered in the file " + LISTPOS + ".o .\n"
	      + "   In that file all banished Hin Warriors are kept.\n"
	      + "     name    Show, if present the members whose name starts with\n");
	write("             with the string 'name'. If you do not specify a name,\n"
	      + "             all names will be shown.\n"
	      + "EXAMPLES:\n");
	write("   showlist          Show all banished members.\n"
	  + "   showlist t        Will show all banned members whose name\n"
	      + "                     starts with 'T'\n");
	return 1;
    }

    restore_object(LISTPOS);
    if (str != "")
	filter_str = capitalize(str);
    else
	filter_str = "";

    tmp_array = filter_array(banned, "partial_name_filter", this_object());

    write("\nTotal number of banished members: " + sizeof(banned) + ".\n");
    write("Banished members of the Hin Warriors are:\n");

    more_array = sort_array(tmp_array, "less_eq_func", this_object());
    more_pos = 0;
    more_list();
    return 1;
}

int
less_eq_func(string str1, string str2)
{
    return str1 <= str2;
}

int
partial_name_filter(string str)
{
    string var3, var2, var1;

    var3 = "#" + str + "#";
    var2 = "#" + filter_str + "%s";
    if (sscanf(var3, var2, var1))
	return 1;
    return 0;
}

static int
do_news(string str)
{
    if (!is_founder(this_player()->query_real_name()))
	return 0;
    cat("/d/Shire/common/doc/NEWS");
    return 1;
}

static int
do_newsoul(string str)
{
    object *ul;
    string *souls;
    int i, silence;

    if (!is_founder(this_player()->query_real_name()))
	return 0;

    if (str == "-s")
	silence = 1;
    else
	silence = 0;

    seteuid(getuid());
    ul = users();

    for (i = 0; i < sizeof(ul); i++)
    {
	if (ul[i] == this_player())
	    continue;

	souls = ul[i]->query_cmdsoul_list();
	if (member_array(OWN_SOUL, souls) == -1)
	    continue;

	if (!silence)
	    tell_object(ul[i], "Your awareness of the ways of the Hin "
			+ "Warrior has changed.\n");
	ul[i]->update_hooks();
	write("Gave " + capitalize(ul[i]->query_real_name())
	      + " a new soul.\n");
    }
    write("Ok.\n");
    return 1;
}

/* Inserted this function for a certain, obese person. *grin*
*/
static int
do_goto_board(string str)
{
    if (this_player()->query_wiz_level() < WIZLEV_APPRENTICE)
	return 0;
    this_player()->move_living("to another interesting board", MYPATH
		             + "hguild2");
    return 1;
}

/*
 * Function name:   do_replace
 * Description:     Replace all pipes in the game. This can be used to give
 *                  everyone in the game a new pipe after an update has been
 *                  made.
 * Arguments:       str: If the argument was "-s", change the pipes without
 *                       any noise, so the change will pass unnoticed.
 * Returns:         0 if the owner is no founder, 1 otherwise
 */
static int
do_replace(string str)
{
    object pipe, player_ob;
    object *list;
    int i, silence, test, was_online;

    if (!is_founder(this_player()->query_real_name()))
	return 0;
    if (!str)
	silence = 0;
    else if (str == "-s")
	silence = 1;

    list = filter_array(users(), "has_a_pipe", this_object());
    i = 0;
    for (i = 0; i < sizeof(list); i++)
    {
	/* Do not remove the pipe of the owner... He probably already did it. */
	if ((player_ob = list[i]) != this_player())
	{
	    pipe = present(MY_UNIQUE_ID, player_ob);
	    was_online = pipe->query_online();
	    pipe->remove_object();
	    pipe = clone_object(MASTER);
	    if (silence)
		pipe->set_silent();
	    if (!was_online)
		pipe->set_offline();
	    pipe->move(player_ob);

	    if (!silence)
		tell_object(player_ob, this_player()->query_name()
			    + " gives you a brand new pipe.\n");

	    write("Replaced the pipe of "
		  + capitalize(player_ob->query_real_name()));
	    if (silence)
		write(" silently");

#if DEBUG
	    if (was_online)
		write(", " + player_ob->query_pronoun() + " was online");
	    else
		write(", " + player_ob->query_pronoun() + " was offline");
#endif

	    write(".\n");
	}
    }
    return 1;
}


/*
 * Function name:   has_a_pipe
 * Description:     Check if the object has a pipe
 * Arguments:       obj: Object to check
 */
int
has_a_pipe(object obj)
{
    return present(MY_UNIQUE_ID, obj) ? 1 : 0;
}

/*
 * Function name:   set_silent
 * Description:     Make sure the pipe makes no sounds when replaced
 */
int
set_silent()
{
    no_noise = 1;
}
