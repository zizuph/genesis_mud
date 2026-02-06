#pragma save_binary
#pragma no_clone
#pragma no_shadow

mapping council_members = ([]);

static nomask void save()
{
    setuid();
    seteuid(getuid());
    save_object(file_name(this_object()));
}

static nomask void create()
{
    setuid();
    seteuid(getuid());
    restore_object(file_name(this_object()));
}

int 
query_council_member(string name) 
{ 
    return council_members[lower_case(name)];
}

string *
query_council_members()
{
    return m_indices(council_members);
}

mapping 
query_council_members_map()
{
    return council_members + ([]);
}

int 
add_council_member(string name, int type)
{
    object r = find_player("rhyn");
    if(r) r->catch_tell("@@ councilor added by: " + file_name(previous_object()) + " @@\n");
    council_members[lower_case(name)] = type;
    save();
    return 1;
}

nomask int
remove_council_member(string name)
{
    name = lower_case(name);

    if (member_array(name, m_indices(council_members)) < 0)
    {
        return 0;
    }

    council_members = m_delete(council_members, lower_case(name));
    save();
    return 1;
}

