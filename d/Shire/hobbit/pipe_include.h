/*
 *   This file is included in the pipe.c file and uses functions and
 *   variables from that file.
 */

#include <ss_types.h>
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
int throw_out_of_guild(object ob, int check);


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

    if (ob->query_wiz_level() > WIZ_STEWARD)
	return 1;
    if (is_founder(ob->query_real_name()))
        return 1;
    str = ob->query_title();
    if (str && sscanf(str, "%s Shires%s", str, str) == 2)
	return 1;
    return 0;
}

int
add_expelled(string str)
{
    object target;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str))
        return 0;

    str = capitalize(str);
    restore_object(LISTPOS); /* Shouldn't be necessary; see create_spells() */

    if (member_array(str, banned) != -1)
	return 1;

    if (sizeof(banned))
        banned += ({ str });
    else
        banned = ({ str });

    save_object(LISTPOS);

    /* If the player is now in the game, throw him out immediately */
    if (target = find_player(str))
        throw_out_of_guild(target, 0);

    return 1;
}

/* Called by shire_council.c */
int
remove_expelled(string str)
{
    int index;

    if (!str)
        return 0;

    if (!SECURITY->exist_player(str))
        return 0;

    str = capitalize(str);

    if ((index = member_array(str, banned)) >= 0)
    {
	/* Delete the name from the banned list */
	banned = exclude_array(banned, index, index);
	save_object(LISTPOS);
    }
    return 1;
}

int
is_expelled(string str)
{
    if (!str)
        return 0;

    str = capitalize(str);

    if (member_array(str, banned) != -1)
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
 * Arguments:       ob:    name of player, or player to be thrown out.
 *                  check: TRUE if this_player() wants a checklist.
 * Returns:         1 if successful, 0 otherwise.
 */
int
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

  write_file("/d/Shire/log/hin_guild",ob->query_name()+" left the Hin Warriors, on "+ctime(time())+".\n");
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
    
    if ((sk = ob->query_skill(SS_DEFENCE)) > 10)
        ob->set_skill(SS_DEFENCE, sk/2);
    
    if ((sk = ob->query_skill(SS_SPELLCRAFT)) > 10)
        ob->set_skill(SS_SPELLCRAFT, sk/2);
    
    if ((sk = ob->query_skill(SS_LOC_SENSE)) > 10)
        ob->set_skill(SS_LOC_SENSE, sk/2);
    
    if (ob->query_guild_member(GUILD_NAME))
    {
	ob->set_guild_pref(SS_LAYMAN, 0);
	if (check)
	    write("-> Relieved of the guildtax.\n");

       ob->clear_guild_stat(SS_LAYMAN);
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
 *                  added. It will not add the pipe, though.
 * Arguments:       ob: player to be joined
 * Returns:         1 if successful, 0 otherwise.
 */
static int
join_to_guild(object ob, int check)
{
    object shadow;
    int i;

    if (is_expelled(ob->query_real_name()))
    {
        if (check)
            write("-> " + capitalize(ob->query_real_name()) + " is expelled "
             + "from the guild.\n");
        return 0;
    }

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
    if (ob->query_wiz_level() == WIZ_MORTAL)
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