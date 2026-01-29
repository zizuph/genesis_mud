mapping fof = ([]);

/*
 * Function   : query_friend_or_foe
 * Description: Check if the specified player is a friend or foe on the Dark Lord
 * Arguments  : player - the player to check
 * Returns    : 0 when neutral, -1 when friend, 1 when foe
 */
public int query_friend_or_foe(mixed player)
{
    if (objectp(player)) player = player->query_real_name();
    if (member_array(player, m_indices(fof)) == -1) return 0;
    
    if (fof[player]["status"] == "foe") return 1;
    
    return -1;
}

/*
 * Function   : add_friend
 * Description: Add a new friend of Minas Morgul
 * Arguments  : player - the player to add
 *            : reason - the reason for adding the friend
 *            : nazgul - the nazgul that added the friend
 */
public void add_friend(mixed player, string reason, string nazgul) {
    if (objectp(player)) player = player->query_real_name();
    
    fof[player] = ([ 
        "status" : "friend",
        "reason" : reason,
        "nazgul" : nazgul,
        "time" : time(),
        "privileges" : ({ })
    ]);
    save_data();
}

/*
 * Function   : add_foe
 * Description: Add a new foe of Minas Morgul
 * Arguments  : player - the player to add
 *            : reason - the reason for adding the friend
 *            : nazgul - the nazgul that added the friend
 */
public void add_foe(mixed player, string reason, string nazgul) {
    if (objectp(player)) player = player->query_real_name();
    
    fof[player] = ([ 
        "status" : "foe",
        "reason" : reason,
        "nazgul" : nazgul,
        "time" : time(),
        "privileges" : ({ })
    ]);
    save_data();
}

/*
 * Function   : query_friends
 * Description: Returns those who are friends of the Tower
 */
public mapping query_friends_and_foes() {
    return fof;
}

/*
 * Function   : remove_friend_or_foe
 * Description: Removed a friend or foe from the list
 * Arguments  : player - the player to add
 */
public void remove_friend_or_foe(mixed player) {
    if (objectp(player)) player = player->query_real_name();
    m_delkey(fof, player);
    save_data();
}

/*
 * Function   : purge_nonexisting_friend_or_foe
 * Description: Purge any player no longer in the realms
 */
public void purge_nonexisting_friend_or_foe() {
    string *fofs = m_indices(fof);
    
    foreach(string player : fofs) 
    {
        if(!SECURITY->exist_player(player)) {
           write_file(MORGUL_REGULAR_RECORDS, "MORGUL MAGES: "
               + capitalize(player) + " is no longer in the realms "
               + "and was purged from the friend/foe list on " 
               + ctime(time()) + ".\n"); 
           write_file(MORGUL_NAZGUL_RECORDS, capitalize(player) 
               + " is no longer a " + fof[player]["status"]
               + " of Minas Morgul: Player does not exist. "
               + "(" + ctime(time()) + ").\n");
           remove_friend_or_foe(player);
       }
   }
}