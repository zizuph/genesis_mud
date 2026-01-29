/*
 *  /d/Gondor/guilds/morgulmage/master/member.c
 *
 *  This file is part of the Morgul Mage master object. It should
 *  not be loaded or called directly.
 *
 *  Created by Eowul, May 11th, 2009
 */
 
mapping member_information = ([]);

/*
 * Function   : get_mage_real_name
 * Description: Return the real name of the mage
 * Arguments  : mixed mage - the mage to get the name for
 * Returns    : The real name of the mage
 */
private string get_mage_real_name(mixed mage)
{
    if(objectp(mage)) return mage->query_real_name();
    return mage;
}

/*
 * Function   : initialize_member
 * Description: Setup the default member information is the mage
 *            : does not yet exist in the member_information mapping
 * Arguments  : name - the name of the mage
 */
private void initialize_member(string name)
{
    if(member_array(name, m_indices(member_information)) != -1) return;
    member_information[name] = ([ ]);
}

/*
 * Function   : set_mage_penalty
 * Description: Set the rank penalty for the mage to the specified value
 * Arguments  : object mage - the mage to set the penalty for
 *            : int penalty - the new penalty value
 */
public void set_mage_penalty(object mage, int penalty) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    member_information[magename]["penalty"] = penalty;
    
    mage->set_skill( SS_MORGUL_PENALTY, penalty );
    save_data();
}

/*
 * Function   : get_mage_penalty
 * Description: Retrieve the rank penalty for the specified mage
 * Arguments  : object mage - the mage to check the penalty for
 */
public int get_mage_penalty(object mage) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    if (member_array("penalty", m_indices(member_information[magename])) == -1)
    {
        member_information[magename]["penalty"] = 
            mage->query_skill(SS_MORGUL_PENALTY);
    }
    
    return member_information[magename]["penalty"];
}

/*
 * Function   : query_is_full_mage
 * Description: Check to see if the mage is no longer an apprentice
 * Arguments  : mixed mage - the mage to check for
 */
public int query_is_full_mage(mixed mage) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    
    return (member_array("magename", m_indices(member_information[magename])) != -1);
}

/*
 * Function   : query_mage_name
 * Description: Returns the name given to the mage on Rakasul
 * Arguments  : mixed mage - the mage to get the name for
 * Returns    : The name of the mage
 */
public string query_mage_name(mixed mage) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);

    if (member_array(magename, m_indices(MORGUL_MS_WIZARD_TITLES)) != -1)
    {
        return MORGUL_MS_WIZARD_TITLES[magename];
    }
    
    if (member_array("magename", m_indices(member_information[magename])) != -1)
    {
        return member_information[magename]["magename"];
    }
    
    return 0;
}

/*
 * Function   : remove_mage_name
 * Description: Remove the given name from a mage
 * Arguments  : mixed mage - the mage to remove the name for
 */
public void remove_mage_name(mixed mage)
{
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    m_delkey(member_information[magename], "magename");
    save_data();
}

/*
 * Function   : query_mage_names
 * Description: Returns a mapping listing all mages and their given names
 * Returns    : A mapping
 */
public mapping
query_mage_names()
{
    mapping result = ([]);
    foreach(string magename, mapping information : member_information)
    {
        if(member_array("magename", m_indices(information)) != -1)
        {
            result[magename] = information["magename"];
        }
    }
    
    return result;
}

/*
 * Function   : add_mage_name
 * Description: Store the name given to the mage on Rakasul
 * Arguments  : mixed mage - the mage to set the name for
 *            : string name - the name given to the mage
 */
public int
add_mage_name(mixed mage, string name)
{
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    member_information[magename]["magename"] = name;
    save_data();
}

/*
 * Function   : query_is_mage
 * Description: See if the specified name exists in our member list
 * Arguments  : string name - the name to check for
 */
public int
query_is_mage(string name)
{
    return (member_array(name, m_indices(member_information)) != -1);
}

/*
 * Function name: update_mage_rank
 * Description  : Store the latest rank information from a player
 * Arguments    : object mage - the mage to update the information for
 */
int update_mage_rank(object mage) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);

    if (!IS_MEMBER(mage)) return -1;
    
    if (member_array("rank", m_indices(member_information[magename])) != -1)
    {
        int original_rank = member_information[magename]["rank"][0];
        if (original_rank == mage->query_morgul_level()) return 1;
    }
    
    member_information[magename]["rank"] = ({ mage->query_morgul_level(),
        time(), mage->query_gender() });
    save_data();
    return 2;
}

/*
 * Function name: query_mages
 * Description  : Returns the names of all stored mages
 */
public string *query_mages()
{
    string *mages = ({});

    foreach(string name, mapping information : member_information)
    {
	if(member_array("expelled", m_indices(information)) == -1) {
            mages += ({ name });
        }
    }

    return mages;
}

/*
 * Function   : remove_mage_from_list
 * Description: Remove any information stored about a mage, should normally
 *            : not be called manually.
 * Arguments  : mage - the name of the mage
 */
public void remove_mage_from_list(mixed mage)
{
    string magename = get_mage_real_name(mage);
    m_delkey(member_information, magename);
    save_data();
}

/*
 * Function   : purge_nonexisting
 * Description: Remove non existing players from the mage list
 */
public void purge_nonexisting()
{
   string *mages = m_indices(member_information);
   foreach(string mage : mages) 
   {
       if(!SECURITY->exist_player(mage)) {
           find_living("eowul")->catch_msg("Player " + mage + " no longer exists.\n");
       }
   }
}
