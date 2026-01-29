/* /d/Gondor/guilds/defenders/souls/member_list_util.c
*
* Member List Utility
*
* This is a utility object that combines the who lists. Originally
* for the Elementalists, but we will use it here since it's so nifty.
* 
* Nerull 2016.
*
* Originally created by Petros, August 2010
*/

#include "../defs.h";
#include "../guild.h";


/*
* Function name: sort_ranks
* Description  : Sorts members list.
*/
public int
sort_def_ranks(object user1, object user2)
{
	string name1 = user1->query_name();
	string name2 = user2->query_name();

	//int    value1 = DEF_MASTER->query_guild_rank(user1->query_name());
	//int    value2 = DEF_MASTER->query_guild_rank(user2->query_name());

	int value1 = user1->query_guild_level_occ();
	int value2 = user2->query_guild_level_occ();

	if (value1 != value2)
	{
		/* sort by ranks */
		return value2 - value1;
	}

	// the ranks are same, sort by name

	if (name1 > name2)
	{
		return 1;
	}

	if (name1 < name2)
	{
		return -1;
	}

	// the names are same
	return 0;
}


/*
* Function:    sort_members
* Description: Sorts the members and calls the appropriate helper sort
*              function depending on which guild they're in.
*/
private int
sort_members(object user1, object user2)
{
     return sort_def_ranks(user1, user2);
}


public int
non_spec(object player, string spec)
{
	switch (spec)
	{
	    case "checkmember":
		if (player->query_guild_name_occ() == GUILDNAME_OCC)
		{
			return 1;
		}
	}

	return 0;
}


/*
* Function:    format_members_presentation
* Description: Given a list of members, it formats the list
*              to be printed out in the member list area.
*/
public string
format_members_presentation(object * members, string spec)
{
	string presentation_list = "";

	if (sizeof(members) > 1)
	{
		members = sort_array(members, sort_members);
	}

	foreach(object member : members)
	{
		string name = capitalize(member->query_real_name());

		string title = member->query_guild_title_occ_on();

		presentation_list += name +" - " + title +"\n";
		
	}

	return presentation_list;
}



/*
* Function:    list_members
* Description: The actual function called by the souls of the two guilds
*              to execute the who command.
*/
public int
list_members()
{
	object * awake_players = users();

	write("These Defenders walk the Realms:\n");
	write("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


	object * spec0 = filter(awake_players, &non_spec(, "checkmember"));

	string spec0_members = format_members_presentation(spec0, "checkmember");

	write(spec0_members + "");
	


	object * ld_players = filter(all_inventory(find_object("/d/Genesis/obj/statue")),
		living);

	object * ld_members = filter(ld_players, &operator( == )("defenders") @ &->query_guild_name_occ());

	ld_members = filter(ld_members, not @ &->query_wiz_level());


	if (!sizeof(ld_members))
	{
		return 1;
	}


	write("\nThese defenders are lost in the realms:\n");

	write(format_members_presentation(ld_members, "") + "\n");
	return 1;
}
