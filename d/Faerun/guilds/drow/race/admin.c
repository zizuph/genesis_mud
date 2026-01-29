/*
 * admin.c
 *
 * This is a room for testing the drow racial guild stuff.
 * Matron Mother commands:
 * f_dismiss, f_accept, f_annex, f_appoint, f_dismiss
 *
 * Allowed by any drow:
 * f_apply, f_claim, f_desert, f_list
 */

 /*
 Lucius wizard-speaks: when you 'list <house>' it pulls the data manually, you'll just want to update it slightly.
You wizard-speak: ok. I'll look into that.
> 
Lucius wizard-speaks: oh me too.. I had just kinda planned to flush it out a tiny bit to have more rp-fleshiness to it I guess.
Lucius wizard-speaks: but however you prefer to do things is fine by me.
*/

#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma save_binaries
#pragma strict_types

#include "guild.h"
#include <const.h>
#include <mail.h>

inherit (P_FAERUN_STD + "faerun_room");

private void
create_faerun_room(void)
{
    setuid();
    seteuid(getuid());

    set_short("Drow Admin Testroom");
    set_long("Drow admin testroom.\n\nCurrently available commands are:\n\n"+
	"\taccept\n"+
	"\tannex\n"+
	"\tapply\n"+
	"\tappoint\n"+
	"\tclaim\n"+
	"\tdeny\n"+
	"\tdesert\n"+
	"\tdismiss\n"+
	"\tlist\n"+
	"\n");

    add_exit("join", "join");
}


/* Just a helper function to verify someones rank. */
private int
check_drow(mixed who, int rank)
{
    if (objectp(who))
	who = who->query_real_name();
    else
	who = lower_case(who);

    return GSERVER->query_member(who, rank);
}

/* Accepts or denies a house applicant. */
public int
f_accept(string str)
{
    string house;
    object player;

    if (!check_drow(TI, HOUSE_MATRON))
	return notify_fail("Only Matron Mothers may do this.\n", 0);

    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" who as a member of thy House?\n");
	return 0;
    }
    else
    {
	str = lower_case(str);
    }

    if (!check_drow(str, GUILD_MEMBER))
    {
	write("There does not seem to be any Drow with that name.\n");
	return 1;
    }

    house = GSERVER->query_member_house(TI);
    if (member_array(str, GSERVER->query_house_members(house, 1)) == -1)
    {
	write("But "+ CAP(str) +" has not applied to your House.\n");
	return 1;
    }

    if (query_verb() == "accept")
    {
	GSERVER->set_member_house(str, house, 0);
	write("You have accepted "+ CAP(str) +" into House "+ house +".\n");

	if (objectp(player = find_player(str)))
	{
	    player->update_member_info_race();
	    player->catch_tell("\nYou have been accepted into "+
		"the Drow House "+ house +"!\n\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(), str, "",
		"You have been accepted into the Drow House "+ house +"!\n");
	}
    }
    else
    { // query_verb() == "deny"
	GSERVER->set_member_house(str, "", 1);
	write("You have denied "+ CAP(str) +" entrance into House "+
	    house +".\n");

	if (objectp(player = find_player(str)))
	{
	    player->catch_tell("\nYou have been denied entrance into "+
		"the Drow House "+ house +"!\n\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(), str, "",
		"You have been denied entrance into the Drow "+
		"House "+ house +"!\n");
	}
    }

    return 1;
}

/* Annex leadership of a house. */
public int
f_annex(string str)
{
    if (!check_drow(TI, HOUSE_NOBLE) || (TI->query_gender() != G_FEMALE))
	return notify_fail("Only Female Noble may do this.\n", 0);

    if (!strlen(str))
    {
	notify_fail("State your House name for the record.\n");
	return 0;
    }

    if (str != GSERVER->query_member_house(TI))
    {
	write("But you are not a member of that House!\n");
	return 1;
    }

    switch(GSERVER->reorganize_house(str, TI))
    {
    case -2:
	write("The First Daughter is still active, "+
	    "therefore your request is denied.\n");
	break;
    case -1:
	write("The Matron Mother is still active, "+
	    "therefore your request is denied.\n");
	break;
    case 1:
	/* Fallthru */
    case 2:
	TI->update_member_info_race();
	write("Congratulations!  You are now the Matron Mother "+
	    "over House "+ str +"!\n");
	break;
    default:
	write("An unforseen error has occured, please contact "+
	    "the Guildmaster.\n");
	break;
    }

    return 1;
}

/* Apply to join a house. */
public int
f_apply(string str)
{
    string tmp;

    if (check_drow(TI, HOUSE_MEMBER))
	return notify_fail("You already belong to a House.\n", 0);

    if (!strlen(str))
    {
	notify_fail("To which House are you applying?.\n");
	return 0;
    }

    if (strlen(tmp = GSERVER->query_member_house(TI)))
    {
	if (tmp != str)
	{
	    write("You already have an application pending with "+
		"House "+ tmp +".  Apply to it again to remove it.\n");
	}
	else
	{
	    write("You withdraw your application to House "+ tmp +".\n");
	    GSERVER->set_member_house(TI, "", 1);
	}
	return 1;
    }

    if (!strlen(tmp = GSERVER->query_house_rank(str, HR_MATRON)))
    {
	write("There is no House "+ str +" for you to apply to.\n");
    }
    else
    {
	object matron = find_player(tmp);

	GSERVER->set_member_house(TI, str, 1);
	write("You have applied to join the House "+ str +".\n");

	if (objectp(matron))
	{
	    tell_object(matron, "\nThe Drow "+ TI->query_name() +
		" has applied to join House "+ str +".\n\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
		tmp, "", "The Drow "+ TI->query_name() +
		" has applied to join House "+ str +".\n");
	}
    }

    return 1;
}

/* Promote/demote members of a house. */
public int
f_appoint(string str)
{
    mixed rank;
    mapping dranks;
    string *arr, house;

    if (!check_drow(TI, HOUSE_MATRON))
	return notify_fail("Only Matron Mothers may do this.\n", 0);

    if (!strlen(str))
	return notify_fail("Appoint whom to what position?\n");

    if (sizeof(arr = explode(lower_case(str), " ")) != 2)
	return notify_fail("Appoint whom to what position?\n");

    if (arr[0] == TI->query_real_name())
    {
	write("You are the Matron Mother, you may not demote yourself.\n"+
	    "If you wish to leave, you must 'desert' thine House.\n");
	return 1;
    }

    if (!check_drow(arr[0], HOUSE_MEMBER))
    {
	write("But "+ CAP(arr[0]) +" does not even belong to a House!\n");
	return 1;
    }

    house = GSERVER->query_member_house(TI);
    if (GSERVER->query_member_house(arr[0]) != house)
    {
	write("You may only alter appointments within thy own House.\n");
	return 1;
    }

    dranks = DROW_RANKS;
    if (!dranks[arr[1]])
    {
	write("That is not even a valid rank to appoint!\n");
	return 1;
    }

    rank = GSERVER->query_house_rank(house, "", arr[0]);
    if (strlen(rank))
    {
	if (rank != arr[1])
	{
	    write(CAP(arr[0]) +" already holds a rank within "+
		"House "+ house +"!\nYou must unappoint it by "+
		"giving their current rank first.\n");
	}
	else
	{
	    object player = find_player(arr[0]);

	    GSERVER->remove_house_rank(house, rank, arr[0]);
	    write(CAP(arr[0]) +" will no longer hold the rank "+
		"of "+ dranks[rank][DR_TITLE] +" within House "+
		house +".\n");

	    if (objectp(player))
	    {
		player->update_member_info_race();
		player->catch_tell("You no longer hold the rank "+
		    "of "+ dranks[rank][DR_TITLE] +" within House "+
		    house +".\n");
	    }
	    else
	    {
		CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
		    arr[0], "", "You no longer hold the rank"+
		    "of "+ dranks[rank][DR_TITLE] +" within House "+
		    house +".\n");
	    }
	}
    }
    else
    {
	int limit, gender;
	object player = find_player(arr[0]);

	if (objectp(player))
	{
	    gender = player->query_gender();
	}
	else
	{
	    player = ("/secure/master")->finger_player(arr[0]);
	    gender = player->query_gender();
	    player->remove_object();
	    player = 0;
	}

	rank = GSERVER->query_house_rank(house, arr[1]);
	limit = dranks[arr[1]][DR_LIMIT][gender];

	if (limit == 0)
	{
	    write("The position of "+ dranks[arr[1]][DR_TITLE] +
		" is unsuitable for "+ CAP(arr[0]) +".\n");
	    return 1;
	}
	else if ((limit == 1) && strlen(rank))
	{
	    write("The rank of "+ dranks[arr[1]][DR_TITLE] +
		" has already been filled.\n");
	    return 1;
	}
	else if (sizeof(rank) >= limit)
	{
	    write("There is a limit of "+ limit +" "+
		dranks[arr[1]][DR_TITLE] +"s and they "+
		"are all filled.\n");
	    return 1;
	}

	GSERVER->set_house_rank(house, arr[1], arr[0]);
	write("You grant "+ CAP(arr[0]) +" the rank of "+
	    dranks[arr[1]][DR_TITLE] +"!\n");

	if (objectp(player))
	{
	    player->update_member_info_race();
	    player->catch_tell("You have been granted "+
		"the rank of "+ dranks[arr[1]][DR_TITLE] +
		" within House "+ house +"!\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
		arr[0], "", "You have been granted "+
		"the rank of "+ dranks[arr[1]][DR_TITLE] +
		" within House "+ house +"!\n");
	}
    }

    return 1;
}

/* Claim a house. */
public int
f_claim(string str)
{
    string tmp;

    if (check_drow(TI, HOUSE_MEMBER))
	return notify_fail("You already belong to a House.\n", 0);

    if (!strlen(str))
    {
	notify_fail("Please name the House you are wanting to claim.\n");
	return 0;
    }

    if (TI->query_gender() != G_FEMALE)
    {
	write("Only Drow females may claim and rule a House.\n");
	return 1;
    }

    tmp = GSERVER->query_member_city(TI);
    if (member_array(str, DROW_CITIES[tmp][0]) == -1)
    {
	write("There is no such House from the City "+ tmp +".\n");
	return 1;
    }

    if (GSERVER->query_house_rank(str, HR_MATRON))
    {
	write("That House is already in possession of a Matron.\n");
	return 1;
    }

    if (GSERVER->claim_house(TI, str, tmp))
    {
	TI->update_member_info_race();
	write("Congratulations!  From this day forth you shall "+
	    "be known as the Matron Mother of House "+ str +"!\n");
    }
    else
    {
	write("There seems to be a problem claiming that House.\n"+
	    "Please contact a wizard.\n");
    }

    return 1;
}

/* Leave a house. */
public int
f_desert(string str)
{
    string tmp;

    if (!check_drow(TI, HOUSE_MEMBER))
    {
	write("How can you desert a House when you don't belong to one?\n");
	return 1;
    }

    if (!strlen(str))
	return notify_fail("Name your House for the records.\n");

    if (str != GSERVER->query_member_house(TI))
    {
	write("You do not belong to House "+ str +".\n");
	return 1;
    }

    if (!check_drow(TI, HOUSE_MATRON))
    {
	object matron;

	GSERVER->set_member_house(TI, "", 0);
	TI->update_member_info_race();
	tmp = GSERVER->query_house_rank(str, HR_MATRON);

	write("You have deserted House "+ str +"!\n");

	if (objectp(matron = find_player(tmp)))
	{
	    matron->catch_tell("\n"+ TI->query_name() +" has deserted "+
		"House "+ str +"!\n\n");
	}
	else
	{
	    CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
		tmp, "", "The Drow "+ TI->query_name() +
		" has deserted House "+ str +"!\n");
	}
    }
    else
    { // Matrons require special handling.
	GSERVER->remove_house_rank(str, HR_MATRON, TI);
	GSERVER->set_member_house(TI, "");
	GSERVER->reorganize_house(str, 0);
	TI->update_member_info_race();
	write("You have deserted House "+ str +"!\n");
    }

    return 1;
}

/* To kick a player from a House. */
public int
f_dismiss(string str)
{
    string house, rank;
    object player;

    if (!check_drow(TI, HOUSE_MATRON))
	return notify_fail("Only Matron Mothers may do this.\n", 0);

    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" who as a member of thy House?\n");
	return 0;
    }
    else
    {
	str = lower_case(str);
    }

    if (!check_drow(str, GUILD_MEMBER))
    {
	write("There does not seem to be any Drow with that name.\n");
	return 1;
    }

    house = GSERVER->query_member_house(TI);
    if (GSERVER->query_member_house(str) != house)
    {
	write("You may only alter appointments within thy own House.\n");
	return 1;
    }

    rank = GSERVER->query_house_rank(house, "", str);
    if (strlen(rank))
    {
	write("You must demote "+ CAP(str) +" before you remove "+
	    "them from thine House.\n");
	return 1;
    }

    write("You dismiss "+ CAP(str) +" from House "+ house +".\n");
    GSERVER->set_member_house(str, "", 0);

    if (objectp(player = find_player(str)))
    {
	player->update_member_info_race();
	player->catch_tell("\nYou have been dismissed from House "+
	    house +"!\n\n");
    }
    else
    {
	CREATE_MAIL("Drow Guild Update", TI->query_real_name(),
	    str, "", "You have been dismissed "+
	    "from House "+ house +"!\n");
    }

    return 1;
}

/* General list ability. */
public int
f_list(string str)
{
    if (!strlen(str))
    {
	notify_fail("List what?  Choose amongst: houses/cities, "+
	    "<house>, ranks.\n", 0);
	return 0;
    }

    switch(str)
    {
    case "cities":
	/* Fallthru */
    case "houses":
    {
	mapping cities = DROW_CITIES;
	string *arr = sort_array(m_indices(cities));
	int ix, size = sizeof(arr);

	/* Woo!  Print print the list */
	write("The known Cities and Houses of the Drow:\n\n");
	for (ix = 0; ix < size; ix++)
	{
	    string *arr2 = sort_array(cities[arr[ix]][0]);
	    int ix2, size2 = sizeof(arr2);

	    write("  City of "+ arr[ix] +":\n\n");
	    for (ix2 = 0; ix2 < size2; ix2++)
	    {
		write(sprintf("    House %-15s %s\n", arr2[ix2],
			(GSERVER->query_house_rank(arr2[ix2], HR_MATRON) ?
			    "(claimed)" : "(available)")));
	    }
	    write("\n");
	}
    }
        break;
    case "ranks":
    {
	int size, length;
	string *arr, *darr;
	mapping dmap, drank = DROW_RANKS;

	dmap = map(filter(drank, &operator([])(, DR_APPNT)),
	                         &operator([])(, DR_TITLE));

	darr = m_indices(dmap);
	size = m_sizeof(dmap);
	arr = allocate(size);

	while(size--)
	{
	    arr[size] = sprintf("%20s  --->  %-s",
		darr[size], dmap[darr[size]]);
	}

	write("These are the appointable ranks within a Drow House:\n\n");
	write(sprintf("%-=75s\n\n", implode(sort_array(arr), "\n")));
    }
	break;
    default:
	if (!GSERVER->query_house_rank(str, HR_MATRON))
	{
	    mapping cities = DROW_CITIES;

	    if (!cities[str])
	    {
		write("There is no Drow House or Drow City available "+
		    "by that name to query.\n");
		return 1;
	    }

	    TI->more(read_file(sprintf("%scities/%s",
			GUILD_HELP, cities[str][1])), 0);
	}
	else
	{
	    mixed *ranks = allocate(6);
	    mixed *hdata = GSERVER->query_house_data(str);
	    string *members = hdata[H_MEMBERS];

	    ranks[0] = hdata[H_RANKS][HR_MATRON]   ?: "(none)";
	    ranks[1] = hdata[H_RANKS][HR_DAUGHTER] ?: "(none)";
	    ranks[2] = hdata[H_RANKS][HR_PATRON]   ?: "(none)";
	    ranks[3] = hdata[H_RANKS][HR_WMASTER]  ?: "(none)";

	    ranks[4] = hdata[H_RANKS][HR_FNOBLES] ?
		sort_array(hdata[H_RANKS][HR_FNOBLES]) : ({ "(none)" });

	    ranks[5] = hdata[H_RANKS][HR_MNOBLES] ?
	        sort_array(hdata[H_RANKS][HR_MNOBLES]) : ({ "(none)" });

	    members = sizeof(members -= ranks[0..3] + ranks[4] + ranks[5]) ?
		sort_array(members) : ({ "(none)" });

	    write(sprintf("\n  House %s from the City of %s\n\n"+
		    "    Matron Mother:  %s\n"+
		    "   First Daughter:  %s\n"+
		    "     House Patron:  %s\n"+
		    "   Weapons Master:  %s\n\n"+
		    "  Noble Daughters:%2s%-#75s\n"+
		    "       Noble Sons:%2s%-#75s\n"+
		    "        Commoners:%2s%-#75s\n\n",
		str, GSERVER->query_house_city(str),
		CAP(ranks[0]), CAP(ranks[1]), CAP(ranks[2]), CAP(ranks[3]),
		sizeof(ranks[4]) > 4 ? "\n" : "",
		implode(map(ranks[4], capitalize), "\n"),
		sizeof(ranks[5]) > 4 ? "\n" : "",
		implode(map(ranks[5], capitalize), "\n"),
		sizeof(members)  > 4 ? "\n" : "",
		implode(map(members, capitalize), "\n")));
	}
        break;
    }
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(  f_accept, "accept"  );
    add_action(   f_annex, "annex"   );
    add_action( f_appoint, "appoint" );
    add_action(  f_accept, "deny"    );
    add_action( f_dismiss, "dismiss" );
    add_action(    f_list, "list"    );
}
