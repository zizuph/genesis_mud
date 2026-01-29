/*
 *  /d/Gondor/guilds/morgulmage/master/nazgul.c
 *
 *  This file is part of the Morgul Mage master object. It should
 *  not be loaded or called directly.
 *
 *  Created by Eowul, July 2009
 */

private void set_nazgul(mixed mage, int nazgul)
{
    string magename = get_mage_real_name(mage);
    if (member_array(magename, m_indices(member_information)) == -1) return;
    member_information[magename]["nazgul"] = nazgul;
    save_data();
}
 
private void unset_nazgul(mixed mage)
{
    string magename = get_mage_real_name(mage);
    if (member_array(magename, m_indices(member_information)) == -1) return;
    m_delkey(member_information[magename], "nazgul");
    save_data();
}

public int query_is_nazgul(mixed mage) {
    string magename = get_mage_real_name(mage);
    if (member_array(magename, m_indices(member_information)) == -1) return 0;
    if (member_array("nazgul", m_indices(member_information[magename])) == -1) return 0;
    return member_information[magename]["nazgul"];
}

/*
 * Function   : set_player_as_lord_nazgul
 * Description: Sets everything needed to make a player the lord nazgul
 * Arguments  : mage - the player to promote
 */
void set_player_as_lord_nazgul(mixed mage)
{
    if (!query_is_nazgul(mage)) return;
    if (query_is_nazgul(mage) == 2) return;

    string name = get_mage_real_name(mage);    
    write_file(MORGUL_NAZGUL_RECORDS, "NAZGUL: " + capitalize(name)
        + " was promoted to Lord of the Nazgul. (" + ctime(time()) + ").\n");
    set_nazgul(name, 2);
    
    object player = find_player(name);
    if (objectp(player)) 
    {
        player->set_nazgul(2);
    }
}

/*
 * Function   : set_player_as_nazgul
 * Description: Promote a player to nazgul, promotion messages need to be 
 *            : written by the calling function.
 * Arguments  : mage - the player to promote
 */
void set_player_as_nazgul(mixed mage)
{
    if (query_is_nazgul(mage)) return;
    
    remove_as_archmage(mage);
    remove_from_position("lieutenant", mage);
    
    string name = get_mage_real_name(mage);    
    write_file(MORGUL_NAZGUL_RECORDS, "NAZGUL: " + capitalize(name)
        + " was transformed into a Nazgul. (" + ctime(time()) + ").\n");
    set_nazgul(name, 1);
    
    object player = find_player(name);
    if (objectp(player)) 
    {
        player->set_nazgul(1);
    }
    
    add_mage_to_activity_meter(mage);
}

/*
 * Function   : remove_player_as_lord_nazgul
 * Description: Remove the player as lord Nazgul
 * Arguments  : mage - the mage to remove
 *            : reason - why was the player removed
 */
void remove_player_as_lord_nazgul(mixed mage, string reason) {
    if (query_is_nazgul(mage) != 2) return;
    
    string name = get_mage_real_name(mage);    
    write_file(MORGUL_NAZGUL_RECORDS, "NAZGUL: " + capitalize(name)
        + " is no longer the Lord of Morgul, reason: " + reason
        + ". (" + ctime(time()) + ").\n");
    set_nazgul(name, 1);
    
    object player = find_player(name);
    if (objectp(player)) 
    {
        player->set_nazgul(1);
    }    
}

/*
 * Function name: query_lord_nazgul
 * Description  : Returns the name of the Lord Nazgul
 * Returns      : the name or 0 when no such lord exists
 */
public string query_lord_nazgul()
{
    foreach(string name, mapping data : member_information) {
        if (query_is_nazgul(name) == 2) return name;
    }
    return 0;
}

/*
 * Function name: query_nazgul_names
 * Description  : Returns the names of those holding a ring of power
 * Returns      : an array with names
 */
string *query_nazgul_names() {
    string *result = ({ });
    
    foreach(string name, mapping data : member_information) {
        if (query_is_nazgul(name) != 0) result += ({ name });
    }
    
    return result;
}

/*
 * Function   : validate_reign_of_lord_nazgul
 * Description: Check if there are sufficient Nazgul to support a Lord
 */
void validate_reign_of_lord_nazgul()
{    
    string lord = query_lord_nazgul();
    string *nazgul = query_nazgul_names();
    
    if ((sizeof(nazgul) < 3) && (lord != 0))
    {
        send_message(lord, "Since there are not enough ringwraiths "
            + "to support your reign you lost your crown!\n");
        remove_player_as_lord_nazgul(lord, "not enough ringwraiths");
    }
}

/*
 * Function   : remove_player_as_nazgul
 * Description: Remove the player as nazgul
 * Arguments  : nazgul - the player to remove as nazgul
 */
void remove_player_as_nazgul(mixed nazgul, string reason = 0) {
    int is_nazgul = query_is_nazgul(nazgul);
    if (!is_nazgul) return;

    if (is_nazgul  == 2) remove_player_as_lord_nazgul(nazgul, reason);
    
    string name = get_mage_real_name(nazgul);    
    write_file(MORGUL_NAZGUL_RECORDS, "NAZGUL: "+ capitalize(name)
        + " was demoted, reason: " + reason+ " (" + ctime(time())+ ").\n");
    unset_nazgul(name);
    
    object player = find_player(name);
    if (objectp(player)) 
    {
        player->set_nazgul(0);
    }
    
    validate_reign_of_lord_nazgul();
    remove_mage_from_activity_meter(name);
}

/*
 * Function   : validate_nazgul
 * Description: Check if the nazgul are all still valid
 */
void validate_nazgul()
{
    string *nazgul_names = query_nazgul_names();
    foreach(string name : nazgul_names)
    {
        if (SECURITY->query_wiz_rank(name))
            remove_player_as_nazgul(name, "wizard");
    }    
}

/*
 * Function   : query_ring_information
 * Description: Retrieve the information stored about the nazgul ring for 
 *            : this mage
 * Arguments  : mage - the name of the mage we want the ring details for
 */
mixed query_ring_information(mixed mage)
{
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    return member_information[magename]["ring"];
}

/*
 * Function   : set_ring_information
 * Description: Set the information about the nazgul ring
 * Arguments  : mage - the mage to store the info for
 *            : information - the ring information to store
 */
void set_ring_information(mixed mage, mixed information)
{
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    member_information[magename]["ring"] = information;
    save_data();
}

private void add_vote(mixed nazgul, mixed mage, string key)
{
    string nazgul_name = get_mage_real_name(nazgul);
    string mage_name = get_mage_real_name(mage);
    if (!query_is_mage(mage_name)) return;
    member_information[nazgul_name][key] = mage_name;
    save_data();
}

/*
 * Function   : add_vote_for_nazgul
 * Description: Cast a vote for the given nazgul to promote a fellow mage
 * Arguments  : nazgul - the nazgul for which to store the vote
 *            : mage - the mage being voted for
 */
void add_vote_for_nazgul(mixed nazgul, mixed mage)
{
    add_vote(nazgul, mage, "nazgul_vote");
}

/*
 * Function   : add_vote_for_lord_nazgul
 * Description: Cast a vote for the given nazgul to promote a fellow mage
 * Arguments  : nazgul - the nazgul for which to store the vote
 *            : mage - the mage being voted for
 */
void add_vote_for_lord_nazgul(mixed nazgul, mixed mage)
{
    add_vote(nazgul, mage, "nazgul_lord_vote");
}

private void remove_vote(mixed nazgul, string key)
{
    string nazgul_name = get_mage_real_name(nazgul);
    if (!query_is_mage(nazgul_name)) return;
    m_delkey(member_information[nazgul_name], key);
    save_data();
}

/*
 * Function   : remove_vote_for_nazgul
 * Description: Removes the vote cast by the nazgul
 * Arguments  : nazgul - the nazgul for which to remove the vote
 */
void remove_vote_for_nazgul(mixed nazgul)
{
    remove_vote(nazgul, "nazgul_vote");
}

/*
 * Function   : remove_vote_for_lord_nazgul
 * Description: Removes the vote cast by the nazgul
 * Arguments  : nazgul - the nazgul for which to remove the vote
 */
void remove_vote_for_lord_nazgul(mixed nazgul)
{
    remove_vote(nazgul, "nazgul_lord_vote");
}

/*
 * Function   : validate_votes
 * Description: Loop through all the votes and make sure they are still valid.
 * Arguments  : the promotion key to check
 */
void validate_votes(string key)
{
    foreach(string member, mapping data : member_information) 
    {
        string reason = 0;
        
        if (member_array(key, m_indices(data)) == -1) 
            continue;
        
        if (!query_is_nazgul(member)) 
            reason = "not a nazgul";
        
        if (!query_is_mage(data[key])) 
            reason = capitalize(data[key]) + " is not a mage";
            
        if (SECURITY->query_wiz_rank(data[key]))
            reason = capitalize(data[key]) + " is a wizard";
            
        if (reason)
        {
            write_file(MORGUL_REGULAR_RECORDS, "VOTES: Removed "
               + key + " for " + capitalize(member) + ": "
               + reason + " (" + ctime(time()) + ").\n"); 
            m_delkey(member_information[member], key);
            save_data();
        }
    }    
}

private int query_valid_promotion(mixed mage, string key) 
{
    validate_votes(key);
    
    string mage_name = get_mage_real_name(mage);
    if (!query_is_mage(mage_name)) return 0;
    
    string *nazgul_names = query_nazgul_names();
    int vote_count = 0;
    foreach(string nazgul_name : nazgul_names) {
        if (member_array(key, 
            m_indices(member_information[nazgul_name])) == -1) continue;
        
        if (member_information[nazgul_name][key] ==
            mage_name) vote_count++;
    }
    
    return (vote_count > (sizeof(nazgul_names) / 2));
}

/*
 * Function   : query_valid_promotion_to_nazgul
 * Description: Check to see if it's valid to promote a mage to nazgulhood
 * Arguments  : mage - the name of the mage to check for
 * Returns    : 0 when not valid, 1 when valid
 */
int query_valid_promotion_to_nazgul(mixed mage)
{
    return query_valid_promotion(mage, "nazgul_vote");
}

/*
 * Function   : query_valid_promotion_to_lord_nazgul
 * Description: Check to see if it's valid to promote a nazgul to lord
 * Arguments  : nazgul - the name of the nazgul to check for
 * Returns    : 0 when not valid, 1 when valid
 */
int query_valid_promotion_to_lord_nazgul(mixed nazgul)
{
    return query_valid_promotion(nazgul, "nazgul_lord_vote");
}

/*
 * Function   : clear_votes_for_nazgul
 * Description: Remove all nazgul votes
 */
void clear_votes_for_nazgul() 
{
    foreach(string nazgul_name : query_nazgul_names()) {
        m_delkey(member_information[nazgul_name], "nazgul_vote");
    }
    save_data();
}

/*
 * Function   : clear_votes_for_lord_nazgul
 * Description: Remove all lord nazgul votes
 */
void clear_votes_for_lord_nazgul() 
{
    foreach(string nazgul_name : query_nazgul_names()) {
        m_delkey(member_information[nazgul_name], "nazgul_lord_vote");
    }
    save_data();
}

private mapping query_votes(string key)
{
    mapping result = ([]);
    
    foreach(string nazgul_name : query_nazgul_names()) {
        if (member_array(key, 
            m_indices(member_information[nazgul_name])) == -1) continue;
            
        result[nazgul_name] = member_information[nazgul_name][key];
    }
    
    return result;
}

/*
 * Function   : query_nazgul_votes
 * Description: Returns a mapping listing who voted for whom
 */
mapping query_nazgul_votes()
{
    return query_votes("nazgul_vote");
}

/*
 * Function   : query_lord_nazgul_votes
 * Description: Returns a mapping listing who voted for whom
 */
mapping query_lord_nazgul_votes()
{
    return query_votes("nazgul_lord_vote");
}

