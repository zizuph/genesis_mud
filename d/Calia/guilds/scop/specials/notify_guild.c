public void
notify_departure(object member)
{
    object * members, * wizards;
    string name;
    
    name = member->query_real_name();
    members = filter(users(), &->is_spirit_member());
    members += filter(users(), &->is_elemental_cleric());
    members -= ({ member }); // don't notify self.
    wizards = filter(members, &->query_wiz_level());
    if (!sizeof(members))
        return;
    
    if (!member->query_wiz_level() 
        && !wildmatch("*jr", member->query_real_name()))    
    {
        // Don't announce juniors and wizards
        map(members, &->catch_msg("The voice of Psuchae echoes through your "
            + "mind announcing that "+capitalize(name)+" has retired to "
            + member->query_possessive() + " bunk, returning to the realm "
            + "of shadows and dreams.\n"));
    }
    else
    {
        // Wizards should always be notified.
        map(wizards, &->catch_msg("The voice of Psuchae echoes through your "
            + "mind announcing that "+capitalize(name)+" has retired to "
            + member->query_possessive() + " bunk, returning to the realm "
            + "of shadows and dreams.\n"));
    }
}

public void
notify_arrival(object member)
{
    object * members, * wizards;
    
    members = filter(users(), &->is_spirit_member());
    members += filter(users(), &->is_elemental_cleric());
    members -= ({ member }); // don't notify self.
    wizards = filter(members, &->query_wiz_level());
    if (!sizeof(members))
        return;
    
    if (!member->query_wiz_level() 
        && !wildmatch("*jr", member->query_real_name()))    
    {
        // Don't announce juniors and wizards
        map(members, &->catch_msg("The voice of Psuchae echoes through your "+
            "mind announcing that "+capitalize(member->query_real_name())+
            ", "+member->query_spirit_circle_title()+" has entered the realms.\n"));
    }
    else
    {
        // Wizards should always be notified.
        map(wizards, &->catch_msg("The voice of Psuchae echoes through your "+
            "mind announcing that "+capitalize(member->query_real_name())+
            ", "+member->query_spirit_circle_title()+" has entered the realms.\n"));
    }
}
