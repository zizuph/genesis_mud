#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "guild.h"

private mapping members = ([]);
private mapping clans   = ([]);
private mapping council = ([]);


public int
query_prevent_shadow()	{ return 1; }


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The save and function for the data.
 * This should always return 1.
 */
private varargs int
save(int no_save)
{
    if (!no_save)
        save_object(SAVE);

    return 1;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The clan administration functions.
 */
public varargs int
update_clans(int delete)
{
    int sz;
    string *tmp;

    /*
     * This simply adds in new clans into the server and synchs
     * up clan colours from the defined values in case they changed.
     */
    tmp = m_indexes(CLANS); sz = sizeof(tmp);
    while (--sz >= 0)
    {
        if (!clans[tmp[sz]])
            clans[tmp[sz]] = ([]);

        clans[tmp[sz]][CLAN_CLRS] = CLANS[tmp[sz]][CLAN_CLRS];
    }

    /*
     * This will remove clans that are no longer defined and
     * will make members of the defunct clan, clanless.
     * Use with extreme discretion.
     */
    if (delete)
    {
        tmp = m_indexes(clans); sz = sizeof(tmp);
        while (--sz >= 0)
        {
            if (!(CLANS[tmp[sz]]))
            {
                string *arr = m_indexes(clans[tmp[sz]]) - ({ CLAN_CLRS });
                int    size = sizeof(arr);

                while (--size >= 0)
                {
                    members[arr[size]][CNAME] = 0;
                }
                clans = m_delete(clans, tmp[size]);
            }
        }
    }
    return save();
}

public int
add_to_clan(string who, string clan, string by)
{
    if (!strlen(who) || !strlen(clan) || !strlen(by))
        return 0;

    MLC(who); MLC(by); CAP(clan);

    if (!members[who] || !members[by])
        return 0;

    if (!clans[clan])
        return 0;

    if ((who != by) && (members[by][CNAME] != clan))
        return 0;

    members[who][CNAME] = clan;
    clans[clan][who] = ({ time(), by });
    return save();
}

public int
remove_from_clan(string who, string by)
{
    string clan;

    if (!strlen(who) || !strlen(by))
        return 0;

    MLC(who); MLC(by);

    if (!members[who] || !members[by])
        return 0;

    clan = members[who][CNAME];

    if (members[by][CNAME] != clan)
        return 0;

    members[who][CNAME] = 0;
    clans[clan] = m_delete(clans[clan], who);
    return save();
}

public mixed
query_clan(string arg)
{
    if (!strlen(arg))
        return secure_var(clans);

    if (arg == "all")
    {
        if (!m_sizeof(clans))
            return ({});

        return secure_var(sort_array(m_indexes(clans)));
    }

    if (clans[CAP(arg)])
        return secure_var(clans[arg]);

    if (members[MLC(arg)])
        return members[arg][CNAME];
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The member administration functions.
 */
public int
add_member(string who, string surname)
{
    if (!strlen(who) || !strlen(surname))
        return 0;

    MLC(who); CAP(surname);

    if (members[who])
        return 0;

    if (member_array(surname, SURNAMES) == -1)
        return 0;

    members[who] = ({ time(), surname, 0, 0 });
    return save();
}

public int
remove_member(string who)
{
    if (!strlen(who))
        return 0;

    MLC(who);

    if (!members[who])
        return 0;

    remove_from_clan(who, who);
    members = m_delete(members, who);

    return save();
}

public mixed
query_member(string who)
{
    if (!strlen(who))
        return secure_var(members);

    MLC(who);

    if (who == "all")
    {
        if (!m_sizeof(members))
            return ({});

        return secure_var(sort_array(m_indexes(members)));
    }

    if (!members[who])
        return 0;

    return members[who];
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Query Council Member functions:
 */
public int 
query_council_member(string name) 
{ 
    return council[lower_case(name)];
}

public string *
query_council_members()
{
    return m_indices(council);
}

public mapping 
query_council_members_map()
{
    return secure_var(council);
}

public int 
add_council_member(string type, string name)
{
    council[lower_case(type)] = name;
    return save();
}

public int
remove_council_member(string name)
{
    if (member_array(MLC(name), m_indices(council)) < 0)
        return 0;

    council = m_delete(council, name);
    return save();
}

public string
query_clanchief(string arg)
{
    int sz, ix;
    string *arr;

    if (!strlen(arg))
	return 0;

    /* Check to see if Clanname was passed first. */
    if (council[MLC(arg)])
	return council[arg];

    arr = m_indices(council);
    sz  = sizeof(arr);

    /* Loop through mapping for a match */
    while(sz--)
    {
	/* Match found, argument is Chief of this clan. */
	if (council[arr[sz]] == arg)
	    return arr[sz];
    }

    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Kinslayer Check  (called from shadow)
 */
public void
notify_kinslayer(object killed, object killer)
{
    string who = killed->query_real_name(), by = killer->query_real_name();

    if (strlen(members[who][CNAME]) &&
      (members[who][CNAME] != members[by][CNAME]))
    {
        /* Not in same Clan */
        return;
    }

    /* Add or increment the KinSlayer count. */
    if (sizeof(members[by]) != 4)
        members[by] += ({ 1 });
    else
        members[by][KSLYR] += 1;

    save();
}

public int
query_kinslayer(string who)
{
    if (!strlen(who))
        return 0;

    if (!members[MLC(who)])
        return 0;

    if (sizeof(members[who]) == 4)
        return members[who][KSLYR];
    else
        return 0;
}

public int
remove_kinslayer(string who, string by, int all)
{
    if (!strlen(who) || !strlen(by))
        return 0;

    if (!members[MLC(by)] || !members[MLC(who)])
        return 0;

    if (members[who][CNAME] != members[by][CNAME])
        return 0;

    if ((sizeof(members[who]) != 4) || !members[who][KSLYR])
        return -1;

    if (all)
        members[who][KSLYR] = 0;
    else
        members[who][KSLYR] -= 1;

    return save();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The create function, to initialize variables upon load.
 */
public void
create()
{
    setuid(); seteuid(getuid());

    if (!restore_object(SAVE))
        update_clans();
}

