/*
 * Member List Utility
 * 
 * This is a utility object that combines the who lists from the Elemental
 * Worshippers with the Spirit Circle of Psuchae.
 * 
 * Created by Petros, August 2010
 * Fixed wizard title presentation (added - in the middle) - Jaacar, May 2016
 * Added Spirit Worshipper branch
 */
 
// We throw in some defines here from the actual guilds themselves.
#define COUNCIL_CODE "/d/Calia/guilds/scop/specials/council_code"
#define EW_GUILD_MANAGER "/d/Calia/guilds/elementalists/lib/guild_manager"
#define SS_PATRON_ELEMENTAL 114052

#define FIRE_FLAG 1
#define EARTH_FLAG 2
#define AIR_FLAG 4
#define WATER_FLAG 8
#define SPIRIT_FLAG 16
#define SEEKER_FLAG 32

/*
 * Function name: sort_ranks
 * Description  : Sorts the SCoP members list(swho).
 */
public int
sort_scop_ranks(object user1, object user2)
{
    string name1  = user1->query_name();
    string name2  = user2->query_name();
    int    value1 = user1->query_spirit_circle_level();
    int    value2 = user2->query_spirit_circle_level();

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
 * Function:    sort_worshippers
 * Description: Sort function used to just sort worshippers by name.
 */
private int
sort_worshippers(object user1, object user2)
{
    string name1 = user1->query_name();
    string name2 = user2->query_name();
    if (name1 > name2)
    {
        return 1;
    }
    else if (name1 < name2)
    {
        return -1;
    }
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
    if (user1->query_guild_name_occ() == "Spirit Circle of Psuchae"
        && user2->query_guild_name_occ() == "Spirit Circle of Psuchae")
    {
        return sort_scop_ranks(user1, user2);
    }
    return sort_worshippers(user1, user2);
}

/*
 * Function:    is_follower_of_elemental
 * Description: Given a player and an elemental name, it determines whether
 *              the player is a follower of that particular elemental.
 */
public int
is_follower_of_elemental(object player, string elemental)
{
    switch (elemental)
    {
    case "psuchae":
    	return (player->query_guild_name_occ() == "Spirit Circle of Psuchae");
        break;
      
    case "pyros":
        if (player->query_guild_name_lay() == "Elemental Worshippers of Calia"
            && (player->query_skill(SS_PATRON_ELEMENTAL) == FIRE_FLAG
                || EW_GUILD_MANAGER->query_primary_element(player) == "fire"))
        {
            return 1;
        }
        break;
        
    case "aeria":
        if (player->query_guild_name_lay() == "Elemental Worshippers of Calia"
            && (player->query_skill(SS_PATRON_ELEMENTAL) == AIR_FLAG
                || EW_GUILD_MANAGER->query_primary_element(player) == "air"))
        {
            return 1;
        }
        break;

    case "gu":
        if (player->query_guild_name_lay() == "Elemental Worshippers of Calia"
            && (player->query_skill(SS_PATRON_ELEMENTAL) == EARTH_FLAG
                || EW_GUILD_MANAGER->query_primary_element(player) == "earth"))
        {
            return 1;
        }
        break;

    case "diabrecho":
        if (player->query_guild_name_lay() == "Elemental Worshippers of Calia"
            && (player->query_skill(SS_PATRON_ELEMENTAL) == WATER_FLAG
                || EW_GUILD_MANAGER->query_primary_element(player) == "water"))
        {
            return 1;
        }
        break;

    case "w_psuchae":
        if (player->query_guild_name_lay() == "Elemental Worshippers of Calia"
            && (player->query_skill(SS_PATRON_ELEMENTAL) == SPIRIT_FLAG
                || EW_GUILD_MANAGER->query_primary_element(player) == "life"))
        {
            return 1;
        }
        break;

    case "seeker":
        if (player->query_guild_name_lay() == "Elemental Seekers of Calia"
            && (player->query_skill(SS_PATRON_ELEMENTAL) == SEEKER_FLAG
                || EW_GUILD_MANAGER->query_primary_element(player) == "seeker"))
        {
            return 1;
        }
        break;
    }
    return 0;
}

/*
 * Function:    format_members_presentation
 * Description: Given a list of members and the elemental, it formats the list
 *              to be printed out in the member list area.
 */
public string
format_members_presentation(object * members, string elemental)
{
    string presentation_list = "";
    if (sizeof(members) > 1)
    {
        members = sort_array(members, sort_members);
    }
    
    int bIsWiz = this_player()->query_wiz_level();
    foreach (object member : members)
    {
        string name = capitalize(member->query_real_name());
        if (member->query_wiz_level() && member->query_invis())
        {
            continue;
        }
        if (!bIsWiz && wildmatch("*jr", name) && this_player() != member)
        {
            // Juniors should not be seen by mortals
            continue;
        }    
        string title = member->query_presentation();
        if (elemental == "psuchae" && is_follower_of_elemental(this_player(), "psuchae") &&
        	(this_player()->query_guild_name_occ() == "Spirit Circle of Psuchae"))
        {                              
            if (COUNCIL_CODE->is_liberator(name))
                title += " (Liberator of Souls)";
            else if (COUNCIL_CODE->is_cultivator(name))
                title += " (Cultivator of Life)";
            else if (COUNCIL_CODE->is_beacon(name))
                title += " (Beacon of Spirits)";
            else if (COUNCIL_CODE->is_missionary(name))
                title += " (Missionary of the Spirit Circle)";
            else if (COUNCIL_CODE->is_emissary(name))
                title += " (The Emissary)";
            else if (COUNCIL_CODE->is_luminary(name))
                title += " (Luminary of the Spirit Circle)";
            else if (COUNCIL_CODE->is_conservator(name))
                title += " (Conservator of Armaments)";
            else if (COUNCIL_CODE->is_illuminati(name))
                title += " (The Illuminati)";
            else if (COUNCIL_CODE->is_intercessor(name))
                title += " (Intercessor of the Spirit Circle)";
            else if (member->query_wiz_level())
            {
                // Wizards have their guild titles hidden
                string occ_title = member->query_guild_title_occ();
                string lay_title = member->query_guild_title_lay();
                if (strlen(occ_title) || strlen(lay_title))
                {
                    title += " (" + (occ_title ? occ_title : "")
                           + " - " + (lay_title ? lay_title : "") + ")";
                }
            }              
        }        
        presentation_list += "- " + title + "\n";
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
    write("These servants of the Elementals currently walk the Realms:\n\n");
    object * psuchae = filter(awake_players, &is_follower_of_elemental(,"psuchae"));
    object * pyros = filter(awake_players, &is_follower_of_elemental(,"pyros"));
    object * diabrecho = filter(awake_players, &is_follower_of_elemental(,"diabrecho"));
    object * gu = filter(awake_players, &is_follower_of_elemental(,"gu"));
    object * aeria = filter(awake_players, &is_follower_of_elemental(,"aeria"));
    object * w_psuchae = filter(awake_players, &is_follower_of_elemental(,"w_psuchae"));
    object * seekers = filter(awake_players, &is_follower_of_elemental(,"seeker"));
    
    string psuchae_members = format_members_presentation(psuchae, "psuchae");
    if (strlen(psuchae_members))
    {
        write("Clerics of Psuchae:\n");
        write(psuchae_members + "\n");
    }
    string pyros_members = format_members_presentation(pyros, "pyros");
    if (strlen(pyros_members))
    {
        write("Followers of Pyros:\n");
        write(pyros_members + "\n");
    }
    string diabrecho_members = format_members_presentation(diabrecho, "diabrecho");
    if (strlen(diabrecho_members))
    {
        write("Followers of Diabrecho:\n");
        write(diabrecho_members + "\n");
    }
    string gu_members = format_members_presentation(gu, "gu");
    if (strlen(gu_members))
    {
        write("Followers of Gu:\n");
        write(gu_members + "\n");
    }
    string aeria_members = format_members_presentation(aeria, "aeria");
    if (strlen(aeria_members))
    {
        write("Followers of Aeria:\n");
        write(aeria_members + "\n");
    }
    string w_psuchae_members = format_members_presentation(w_psuchae, "w_psuchae");
    if (strlen(w_psuchae_members))
    {
        write("Followers of Psuchae:\n");
        write(w_psuchae_members + "\n");
    }
    string seeker_members = format_members_presentation(seekers, "seeker");
    if (strlen(seeker_members))
    {
        write("Elemental Seekers:\n");
        write(seeker_members + "\n");
    }


    object * ld_players = filter(all_inventory(find_object("/d/Genesis/obj/statue")), living);
    object * ld_members = filter(ld_players, &operator(==)("Spirit Circle of Psuchae") @ &->query_guild_name_occ())
                        + filter(ld_players, &operator(==)("Elemental Worshippers of Calia") @ &->query_guild_name_lay())
                        + filter(ld_players, &operator(==)("Elemental Seekers of Calia") @ &->query_guild_name_lay());
    ld_members = filter(ld_members, not @ &->query_wiz_level());
    if (!sizeof(ld_members))
    {
        return 1;
    }
    
    write("\nThese servants of the Five are currently within the Void:\n");
    write(format_members_presentation(ld_members, "") + "\n");
    return 1;
}
