/*
 *	/d/Gondor/common/guild/lib/members.c
 *
 *	Function for the member lists of the ranger companies.
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 *	Coded by Olorin, February 1997
 *	using older code by Olorin.
 */
#pragma save_binary
#pragma strict_types

#include <std.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/titles.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

static string
ranger_title(string name)
{
    object player;
    int    avg_stat,
           mbit,
           is_finger;
    string r_title;

    if (SECURITY->query_wiz_level(name))
        return "";

    if (extract(name,-2) == "jr")
        return "";

    is_finger = 0;
    if (!(player = find_player(name)))
    {
        player = SECURITY->finger_player(name);
        is_finger = 1;
    }
    if (!player)
        return "";

    mbit = player->query_skill(SS_MASTER_TASK);
    if (mbit) 
	r_title = "the Master "+MASTER_TITLES[mbit];
    else 
    {
        if (!player->query_ghost())
        {
            avg_stat = ((player->query_stat(SS_OCCUP) / 4) +
                    player->query_skill(SS_REWARDED) -
                    player->query_skill(SS_PUNISHED));
            avg_stat = avg_stat/4;
            if (avg_stat >= sizeof(MALE_TITLE))
                avg_stat = sizeof(MALE_TITLE) - 1;
        }
        else
        {
            /* calling query_stat() in ghost gives illegal type errors */
            avg_stat = 0;
        }

	if (player->query_gender_string() == "female")
	    r_title = "the " + FEMALE_TITLE[avg_stat];
	else 
	    r_title = "the " + MALE_TITLE[avg_stat];
    }

    if (is_finger)
        player->remove_object();
    return r_title;
}

public string
print_member_list(int company_number = 0)
{
    string text, captain, deputy, sergeant, r_title;
    string *member_list;
    int    i;

    RANGER_GUILD->check_present_rangers();

    text = "These are presently the members" + STD_TITLE[company_number] +
	COMPANIES[company_number] + ":\n\n";

    member_list = RANGER_GUILD->query_company_members(company_number);

    seteuid(getuid());
    switch (company_number)
    {
    case 1: 
	captain  = COUNCIL->query_gondor(); 
	deputy   = COUNCIL->query_gondor_deputy();
	sergeant = COUNCIL->query_gondor_sergeant();
	break;
    case 2: 
	captain  = COUNCIL->query_ithilien(); 
	deputy   = COUNCIL->query_ithilien_deputy();
	sergeant = COUNCIL->query_ithilien_sergeant();
	break;
    default: 
	captain  = 0; 
	deputy   = 0;
	sergeant = 0;
	break;
    }

    if (captain)
	text += "- " + CAP(captain) + ", the Captain of the Rangers of " + 
	    COMPANIES[company_number] + "\n";
    else if (company_number)
	text += "- There is no Captain of the Rangers of " +
	    COMPANIES[company_number] + "\n";
    if (deputy)
	text += "- " + CAP(deputy) + ", the Lieutenant of the Rangers of " + 
	    COMPANIES[company_number] + "\n";
    else if (company_number)
	text += "- There is no Lieutenant of the Rangers of " +
	    COMPANIES[company_number] + "\n";
    if(sergeant)
	text += "- " + CAP(sergeant) + ", the Sergeant of the Rangers of " +
	    COMPANIES[company_number] + "\n";
    else if (company_number)
	text += "- There is no Sergeant of the Rangers of " +
	    COMPANIES[company_number] + "\n";
    
    i = -1;
    while (++i < sizeof(member_list))
    {
	if ( (member_list[i] != lower_case(captain)) && 
	     (member_list[i] != lower_case(deputy)) &&
	     (member_list[i] != lower_case(sergeant)) )
	{
	    if (member_list[i] != LOW(member_list[i]))
	    {
		log_file("members", "ERROR: Entry in company_rangers for " +
			 member_list[i] + " (" + company_number + ") corrupted! " +
			 ctime(time()) + ".\n");
		member_list[i] = LOW(member_list[i]);
	    }
	    r_title = ranger_title(member_list[i]);
	    if (r_title != "")
		text += "- " + CAP(member_list[i]) + "," +
		    STD_TITLE[company_number] + COMPANIES[company_number] + "\n";
	    else
	    {
		RANGER_GUILD->remove_from_list(member_list[i]);
		log_file("members", "MEMBERS BUG: no title for " +
			 member_list[i] + ". Will be removed from list. " +
			 ctime(time()) + ".\n");
	    }
	}
    }
    return text + "\n";
}
