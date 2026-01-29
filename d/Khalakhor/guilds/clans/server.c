/**********************************************************************
 * - server.c                                                       - *
 * - Clans, elven race guild server                                 - *
 * - Original code Created by Lucius                                - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
/*
 * Updated by Zhar, November 2012
 *
 * - fixed formatting
 * - added functions required for Blademaster title merging
 */

#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "guild.h"

private mapping members = ([]);
private mapping clans  = ([]);
private mapping blademasters = ([]);

/**********************************************************************
 * - The save and function for the data.                            - *
 * - This should always return 1.                                   - *
 **********************************************************************/
private varargs int
save(int no_save)
{
    if (!no_save)
    {
       	save_object(SAVE);
    }
        
    return 1;
}

/**********************************************************************
 * - The Clan administration functions.                             - *
 **********************************************************************/
public varargs int
update_clans(int delete)
{
    string *tmp = m_indexes(CLANS);
    int size = sizeof(tmp);

        
    /**************************************************************
     * - This adds new Clans into the server and synches up the - *
     * - Clan colours from the defined values in case they      - *
     * - changed.                                               - *
     **************************************************************/
            
    while (--size >= 0)
    {
        if (!clans[tmp[size]])
        {
            clans[tmp[size]] = ([]);
        }
                
        clans[tmp[size]][CLAN_CLRS] = CLANS[tmp[size]][CLAN_CLRS];
    }
        
    /**************************************************************
     * - This will remove Clans that are no longer defined and  - *
     * - will make members of the defunct Clan, Clanless. Use   - *
     * - with extreme discretion.                               - *
     **************************************************************/
        
    if (delete)
    {
        tmp = m_indexes(clans);
        size = sizeof(tmp);
                
        while (--size >= 0)
        {
            if (!(CLANS[tmp[size]]))
            {
                string *arr = m_indexes(clans[tmp[size]]) - ({CLAN_CLRS });
                int tmpsize = sizeof(arr);
                                
                while (--tmpsize >= 0)
                {
                    members[arr[tmpsize]][CNAME] = 0;
                }
                                
                clans = m_delete(clans, tmp[tmpsize]);
            }
        }
    }
        
    return save();
}

public int
add_to_clan(string who, string clan, string by)
{
    if (!strlen(who) || !strlen(clan) || !strlen(by))
    {
        return 0;
    }
        
    MLC(who); MLC(by); CAP(clan);
        
    if (!members[who] || !members[by])
    {
        return 0;
    }
        
    if (!clans[clan])
    {
        return 0;
    }
        
    if ((who != by) && (members[by][CNAME] != clan))
    {
        return 0;
    }
        
    members[who][CNAME] = clan;
    clans[clan][who] = ({ time(), by });
        
    return save();
}

public int
remove_from_clan(string who, string by)
{
    string clan;
        
    if (!strlen(who) || !strlen(by))
    {
        return 0;
    }
        
    MLC(who); MLC(by);
        
    if (!members[who] || !members[by])
    {
        return 0;
    }
        
    clan = members[who][CNAME];
        
    if (members[by][CNAME] != clan)
    {
        return 0;
    }
        
    members[who][CNAME] = 0;
    clans[clan] = m_delete(clans[clan], who);
        
    return save();
}

public mixed
query_clan(string arg)
{
    if (!strlen(arg))
    {
        return secure_var(clans);
    }
        
    if (arg == "all")
    {
        if (!m_sizeof(clans))
        {
            return ({});
        }
        
        return secure_var(sort_array(m_indexes(clans)));
    }
        
    if (clans[arg])
    {
        return secure_var(clans[arg]);
    }
        
    if (members[MLC(arg)])
    {
        return members[arg][CNAME];
    }
}

/**********************************************************************
 * -  The member administration functions.                          - *
 **********************************************************************/

public int
add_member(string who, string surname, int race)
{
    if (!strlen(who) || !strlen(surname))
    {
        return 1;
    }
        
    MLC(who); CAP(surname);
        
    if (members[who])
    {
        return 2;
    }
        
    if (member_array(surname, SURNAMES) == -1)
    {
        return 3;
    }
        
    members[who] = ({ time(), surname, race, 0 });
        
    return save();
}

public int
remove_member(string who)
{
    if (!strlen(who))
    {
        return 0;
    }
        
    MLC(who);
        
    if (!members[who])
    {
        return 0;
    }
        
    remove_from_clan(who, who);
    members = m_delete(members, who);
        
    return save();
}

public mixed
query_member(string who)
{
    if (!strlen(who))
    {
        return secure_var(members);
    }
        
    MLC(who);
        
    if (who == "all")
    {
        if (!m_sizeof(members))
        {
            return ({});
        }
                
        return secure_var(sort_array(m_indexes(members)));
    }
        
    if (!members[who])
    {
        return 0;
    }
        
    return members[who];
}

/*
 * Handling of Blademaster lists and titles
 */
public void
update_blademasters()
{
    blademasters = restore_map(BMASTER_MAP);
	
    if (!mappingp(blademasters))
    {
        blademasters = ([ ]);
    }
}

public mixed
query_blademaster(string who)
{
    if (!blademasters[who])
    {
    	return 0;
    }
        
    return blademasters[who];
}

public string
query_blademaster_title(object who)
{
    return who->query_blademaster_title();
}

/**********************************************************************
 * - The create function, to initialize variables upon load.        - *
 **********************************************************************/

public void
create()
{
    setuid();
    seteuid(getuid());
        
    if (!restore_object(SAVE))
    {
        update_clans();
        update_blademasters();
    }
}
