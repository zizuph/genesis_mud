/*
 *  /d/Gondor/guilds/morgulmage/master/messages.c
 *
 *  This file is part of the Morgul Mage master object. It should
 *  not be loaded or called directly.
 *
 *  Created by Eowul, August 23rd, 2009
 */

public int send_message(mixed mage, string message)
{
    object player = objectp(mage) ? mage : find_player(mage);
    if (objectp(player)) {
        player->catch_msg(message);
        return 1;
    }
    
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    
    if (member_array("messages", m_indices(member_information[magename])) == -1) {
        member_information[magename]["messages"] = ({ message });
    } else {
        member_information[magename]["messages"] += ({ message });
    }
    
    save_data();
    return 1;
}

public void deliver_pending_messages(object player) {
    string magename = get_mage_real_name(player);
    
    if (member_array(magename, m_indices(member_information)) == -1)
        return;
    
    if (member_array("messages", m_indices(member_information[magename])) == -1)
        return;
        
    foreach(string message : member_information[magename]["messages"]) {
        player->catch_msg(message);
    }
    
    m_delkey(member_information[magename], "messages");
    save_data();
}