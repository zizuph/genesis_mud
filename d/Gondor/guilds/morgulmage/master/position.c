mapping positions = ([ ]);

public int query_is_archmage(mixed mage) {
    string magename = get_mage_real_name(mage);
    if (!query_is_mage(magename)) return 0;
    if (member_array("archmage", 
        m_indices(member_information[magename])) == -1) return 0;
        
    return member_information[magename]["archmage"];
}

public void set_as_archmage(mixed mage) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
    member_information[magename]["archmage"] = 1;
    save_data();
}

public void remove_as_archmage(mixed mage) {
    string magename = get_mage_real_name(mage);
    if (!query_is_mage(magename)) return;
    m_delkey(member_information[magename], "archmage");
    save_data();
}

public string
query_position(string position)
{
    if(position == "herbalist") {
        return ("/d/Gondor/morgul/cellar/herb_shop")->query_herbalist();
    }
    
    if (member_array(position, m_indexes(positions)) == -1) return 0;
    return positions[position];
}

public int query_is_lieutenant(mixed mage) {
    string magename = get_mage_real_name(mage);
    return (query_position("lieutenant") == magename);
}

public void
assign_position(string position, mixed mage)
{
    if (position == "herbalist") {  
        ("/d/Gondor/morgul/cellar/herb_shop")->appoint_herbalist(mage);
        return;
    }
    
    string magename = get_mage_real_name(mage);
    positions[position] = magename;
    save_data();
}

public void
remove_from_position(string position, mixed mage)
{
    if (position == "herbalist") {
        ("/d/Gondor/morgul/cellar/herb_shop")->release_herbalist(mage);
        return;
    }
    
    string magename = get_mage_real_name(mage);
    if (positions[position] == magename) {
        m_delkey(positions, position);
        save_data();
    }
}

public void remove_player_from_positions(mixed mage) 
{
    string magename = get_mage_real_name(mage);
    
    foreach(string position, string name : positions) {
        if (name == magename) {
            write_file(MORGUL_NAZGUL_RECORDS,
                  capitalize(name) + " was removed from the "
               + "position of " + position  + ". " 
               + ctime(time()) + ".\n");         
            m_delkey(positions, position);
        }
    }
}

public void purge_positions() {
    foreach(string position, string name : positions) {
        if (!query_is_mage(name)) {
            write_file(MORGUL_NAZGUL_RECORDS, 
                 capitalize(name) + " is no longer a Morgul Mage "
               + "and was removed from the position of " + position
               + ". " + ctime(time()) + ".\n");         
            m_delkey(positions, position);
        }
    }
}
