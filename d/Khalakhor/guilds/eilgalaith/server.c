/**********************************************************************
 * - server.c                                                       - *
 * - Eil-Galaith, elven race guild server                           - *
 * - Original code Created by Lucius                                - *
 * - Recoded by Damaris 2/2002                                      - *
 **********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "guild.h"

private mapping members = ([]);
private mapping houses  = ([]);

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
 * The house administration functions.
 */
public varargs int
update_houses(int delete)
{
	int sz;
	string *tmp;
	
	/*
	* This simply adds in new houses into the server and synchs
	* up house colours from the defined values in case they changed.
	*/
        tmp = m_indexes(HOUSES); sz = sizeof(tmp);
        while (--sz >= 0)
        {
		if (!houses[tmp[sz]])
		{
			houses[tmp[sz]] = ([]);
		}
		houses[tmp[sz]][HOUSE_CLRS] = HOUSES[tmp[sz]][HOUSE_CLRS];
	}
	
	/*
	* This will remove houses that are no longer defined and
	* will make members of the defunct house, houseless.
	* Use with extreme discretion.
	*/
	
	if (delete)
	{
		tmp = m_indexes(houses); sz = sizeof(tmp);
		while (--sz >= 0)
		{
			if (!(HOUSES[tmp[sz]]))
			{
				string *arr = m_indexes(houses[tmp[sz]]) - ({ HOUSE_CLRS });
				int    size = sizeof(arr);
				while (--size >= 0)
				{
					members[arr[size]][HNAME] = 0;
				}
				houses = m_delete(houses, tmp[size]);
			}
		}
	}
	return save();
}

public int
add_to_house(string who, string house, string by)
{
	if (!strlen(who) || !strlen(house) || !strlen(by))
        return 0;
        
        MLC(who); MLC(by); CAP(house);
        
        if (!members[who] || !members[by])
        return 0;
        
        if (!houses[house])
        return 0;
        
        if ((who != by) && (members[by][HNAME] != house))
        return 0;
        
        members[who][HNAME] = house;
        houses[house][who] = ({ time(), by });
        return save();
}

public int
remove_from_house(string who, string by)
{
	string house;
	
	if (!strlen(who) || !strlen(by))
        return 0;
        
        MLC(who); MLC(by);
        
        if (!members[who] || !members[by])
        return 0;
        
        house = members[who][HNAME];
        
        if (members[by][HNAME] != house)
        return 0;
        
        members[who][HNAME] = 0;
        houses[house] = m_delete(houses[house], who);
        return save();
}

public mixed
query_house(string arg)
{
	if (!strlen(arg))
        return secure_var(houses);
        
        if (arg == "all")
        {
		if (!m_sizeof(houses))
		return ({});
		
		return secure_var(sort_array(m_indexes(houses)));
	}
	
	if (houses[CAP(arg)])
        return secure_var(houses[arg]);
        
        if (members[MLC(arg)])
        return members[arg][HNAME];
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * The member administration functions.
 */
public int
add_member(string who, string surname, int race)
{
	if (!strlen(who) || !strlen(surname))
        return 0;
        
        MLC(who); CAP(surname);
        
        if (members[who])
        return 0;
        
        if (member_array(surname, SURNAMES) == -1)
        return 0;
        
        members[who] = ({ time(), surname, race, 0 });
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
        
        remove_from_house(who, who);
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
 * The create function, to initialize variables upon load.
 */
public void
create()
{
	setuid(); seteuid(getuid());
	if (!restore_object(SAVE))
        update_houses();
}
