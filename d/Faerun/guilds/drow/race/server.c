/*
 * drow/race/server.c
 *
 * This is the Guild Manager for the drow racial guild.
 */
/*
 * IMPORTANT NOTE
 *
 * The server does VERY little cross-checking of data
 * to see if things should be allowed or not.  This is
 * not the place to do it either, the server should be
 * kept as simple as possible, it is only meant to act
 * as a data repository.
 *
 * All checks need to be done in whatever code seeks
 * to manipulate this data.
 */
#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma save_binary
#pragma strict_types

#include "guild.h"

inherit (P_FAERUN_LIB + "log");

/*
 * mapping members = ([
 *    (string)name: ({ (int)type, (int)options,
 *                     (string)house, (string)city,
 *                     (string *)deities, (int)last active,
 *                   }),
 *    ])
 *
 * mapping houses = ([
 *    (string)house: ({ (string)city, (string *)members, (string *)applied,
 *                      ([ (string)Rank: (string)/(string *)member(s), ]), })
 *    ])
 *
 * mapping banished = ([ (string)name: (int)1, ])
 */
private mapping members = ([]), houses = ([]), banished = ([]);
#define MAX_BACKUPS  10
private int backups = 1;

/* Default values for new members/houses. */
#define NEW_MEMBER      ({ 1, 0, "", "", ({ }), 0 })
#define NEW_HOUSE(who, city)  ({ city, ({ who }), ({ }), \
                                 ([ HR_MATRON: who, ]), })
/* Convenience macro. */
#define MLC(name) if (objectp(name)) name = name->query_real_name(); \
		  else name = lower_case(name);

void cleanup_houses();
public int reorganize_house(string house, mixed who);


/*
 * Creates and restores the object file.
 */
private void
create(void)
{
    setuid();
    seteuid(getuid());

    catch(restore_object(GUILD_LOGS + "server"));
    set_alarm(300.0, 0.0, cleanup_houses);
}

/*
 * This saves the variables to an object file.
 */
private void
save_state(void)
{
    string file = (GUILD_LOGS + "server");

    catch(rename(file + ".o", file + ".o." + backups));
    /* Keep some backups in case of disaster. */
    if (++backups > MAX_BACKUPS)
	backups = 1;

    save_object(file);
}

/*
 * This updates the last active field of a member.
 */
public void
update_last_active(mixed name)
{
    MLC(name);

    if (!members[name])
	return;

    members[name][M_ACTIVE] = time();
    save_state();
}

/*
 * This queries the last active field of a member.
 */
public int
query_last_active(mixed name)
{
    MLC(name);
    if (!members[name])
	return 0;

    return members[name][M_ACTIVE];
}

/*
 * Adds a member to the guild server.
 * mixed name = name of member to add.
 */
public varargs int 
add_member(mixed name)
{
    MLC(name);
    members[name] = NEW_MEMBER;
    GLOG(JOINLOG, CAP(name) +" joined the Drow Racial.");
    save_state();
    return 1;
}

/*
 * Remove a member from the guild server.
 * mixed name = name of member to remove.
 */
public int
remove_member(mixed name)
{
    MLC(name);

    if (!members[name])
	return 0;

    GLOG(LEFTLOG, CAP(name) +" departed the Drow Racial guild.");
    m_delkey(members, name);
/* banishes player from ever joining again */
    banished[name] = time();
    save_state();
    return 1;
}

/*
 * Query a specific member of the guild.
 * mixed name = member to query against.
 * int type = (optional) binop type to check against member.
 */
public varargs mixed 
query_member(mixed name, int type) 
{
    MLC(name);

    if (!members[name])
	return 0;

    switch(type)
    {
    case -1:
	return members[name];
	break;
    case 0:
	return members[name][M_TYPE];
	break;
    default:
	return (members[name][M_TYPE] & type);
	break;
    }
}

/*
 * Removes a playername from the banished list
 * so they might rejoin the guild.
 * mixed name = playername to remove.
 */
public int
remove_banished(mixed name)
{
    MLC(name);

    if (!banished[name])
	return 0;

    GLOG(BANLOG, CAP(name) +" was unbanished from the Drow Racial.");
    m_delkey(banished, name);
    save_state();
    return 1;
}

/*
 * Query banished players from the guild.
 * mixed name = member to query against.
 */
public varargs mixed
query_banished(mixed name)
{
    if (!name)
	return m_indexes(banished);

    MLC(name);
    return banished[name];
}

/*
 * Set a guild members house affiliation.
 * mixed name - member to modify
 * string house - house to set.
 * int applicant - (optional)we are applying, not joining.
 */
public varargs int
set_member_house(mixed name, mixed house, int applicant)
{
    MLC(name);

    if (!strlen(house))
    {
	string old = members[name][M_HOUSE];
    int old_type = members[name][M_TYPE];

	members[name][M_HOUSE] = house;

	if (applicant)
	{
	    houses[old][H_APPLY] -= ({ name });
	    GLOG(HOUSELOG, CAP(name) + " withdrew application for "+
	       "House "+ old +".");
	} else {
	    houses[old][H_MEMBERS] -= ({ name });
	    members[name][M_TYPE]  = GUILD_MEMBER;
        if (old_type & HOUSE_NOBLE)
        {
            if (sizeof(houses[old][H_RANKS][HR_FNOBLES]))
            {
                houses[old][H_RANKS][HR_FNOBLES] -= ({ name });
            }
            if (sizeof(houses[old][H_RANKS][HR_MNOBLES]))
            {
                houses[old][H_RANKS][HR_MNOBLES] -= ({ name });
            }
        }
        if (old_type & HOUSE_PATRON)
        {
            m_delkey(houses[old][H_RANKS], HR_PATRON);
        }
        if (old_type & HOUSE_DAUGHTER)
        {
            m_delkey(houses[old][H_RANKS], HR_DAUGHTER);
        }
        if (old_type & HOUSE_WMASTER)
        {
            m_delkey(houses[old][H_RANKS], HR_WMASTER);
        }

	    GLOG(HOUSELOG, CAP(name) + " left House "+ old +".");
	}
    }
    else
    {
	members[name][M_HOUSE] = house;

	if (applicant)
	{
	    houses[house][H_APPLY] += ({ name });
	    GLOG(HOUSELOG, CAP(name) + " applied for House "+ house +".");
	} else {
	    houses[house][H_APPLY] -= ({ name });
	    houses[house][H_MEMBERS] += ({ name });
	    members[name][M_TYPE] |= HOUSE_MEMBER;
	    GLOG(HOUSELOG, CAP(name) + " joined House "+ house +".");
	}
    }

    save_state();
    return 1;
}

public void cleanup_houses()
{
    foreach (string house : m_indexes(houses))
    {
        string* house_members = houses[house][H_MEMBERS];
        foreach (string rank : ({ HR_WMASTER, HR_DAUGHTER, HR_PATRON }))
        {
            string name = houses[house][H_RANKS][rank];
            if (stringp(name) && member_array(name, house_members) == -1)
            {
                m_delkey(houses[house][H_RANKS], rank);
                GLOG(HOUSELOG, CAP(name) + " is not a member of " + CAP(house) + 
                    ", removing " + DROW_RANKS[rank][DR_TITLE]);
            }
        }
        foreach (string rank: ({ HR_FNOBLES, HR_MNOBLES }))
        {
            foreach (string name : houses[house][H_RANKS][rank])
            {
                if (member_array(name, house_members) == -1)
                {
                    houses[house][H_RANKS][rank] -= ({ name });
                    GLOG(HOUSELOG, CAP(name) + " is not a member of " + CAP(house) + 
                        ", removing " + DROW_RANKS[rank][DR_TITLE]);
                }
                
            }
        }
        
        string matron = houses[house][H_RANKS][HR_MATRON];
        int mtime = query_last_active(matron) + MAX_IDLE;
        int ctime = time();
	    if (mtime < ctime)
        {
        	reorganize_house(house, 0);
        }
    }
    save_state();
}

/*
 * Query a guild members house affiliation.
 * mixed name - member to check against.
 */
public string
query_member_house(mixed name)
{
    MLC(name);
    return members[name][M_HOUSE];
}

/*
 * Set a guild members city affiliation.
 * mixed name - member to modify
 * string city - city to set.
 */
public int
set_member_city(mixed name, string city)
{
    MLC(name);
    members[name][M_CITY] = city;
    save_state();
    return 1;
}

/*
 * Query a guild members city affiliation.
 * mixed name - member to check against.
 */
public string
query_member_city(mixed name)
{
    MLC(name);
    return members[name][M_CITY];
}

/*
 * Set a guild members deities.
 * mixed name - member to modify
 * string *gods - deities to set.
 */
public int
set_member_deity(mixed name, string *gods)
{
    MLC(name);
    members[name][M_DEITY] = gods;
    save_state();
    return 1;
}

/*
 * Query a guild members deities.
 * mixed name - member to check against.
 */
public string
query_member_deity(mixed name)
{
    MLC(name);
    return members[name][M_DEITY];
}

/*
 * Set a guild members 'type' field.
 * mixed name - member to modify
 * int opt - type to set.
 * int add - (optional)How to add the type.
 */
public varargs int
set_member_type(mixed name, int type, int add)
{
    MLC(name);

    switch(add)
    {
    case 1:
	members[name][M_TYPE] |= type;
	break;
    case -1:
	members[name][M_TYPE] ^= type;
	break;
    default:
	members[name][M_TYPE] = (GUILD_MEMBER | type);
	break;
    }

    save_state();
    return members[name][M_TYPE];
}

/*
 * Set a guild members options.
 * mixed name - member to modify
 * int opt - options to set.
 * int add - (optional)How to add the option.
 */
public varargs int
set_member_options(mixed name, int opt, int add)
{
    MLC(name);

    switch(add)
    {
    case 1:
	members[name][M_OPTIONS] |= opt;
	break;
    case -1:
	members[name][M_OPTIONS] ^= opt;
	break;
    default:
	members[name][M_OPTIONS] = opt;
	break;
    }

    save_state();
    return members[name][M_OPTIONS];
}

/*
 * Query a guild members options.
 * mixed name - member to check against.
 * int opt - (optional) binop options to check for.
 */
public varargs int
query_member_options(mixed name, int opt)
{
    MLC(name);

    if (!opt)
	return members[name][M_OPTIONS];
    else
	return (members[name][M_OPTIONS] & opt);
}

/*
 * Query the members of the guild.  By default returns a formatted list.
 * int arg = (optional) Just return an array of members.
 * int type = (optional) binop type to check against members.
 */
public varargs mixed
query_members(int arg, int type)
{
    if (arg)
    {
	if (!type)
	    return m_indices(members);
	else
	{
	    return m_indices(filter(members, &operator(!=)(0) @
		&operator(&)(, type) @ &operator([])(, M_TYPE)));
	}
    }

    if (!type)
	return sprintf("%#-75s", implode(m_indices(members), "\n"));
    else
    {
	return sprintf("%#-75s", implode(m_indices(filter(members,
		&operator(!=)(0) @ &operator(&)(, type) @
		&operator([])(, M_TYPE))), "\n"));
    }
}

/* 
 * Introduce a newly claimed house into the server.
 * mixed name - Member claiming the house.
 * string house - The house being claimed.
 * string city  - In which city is this house based?
 */
public int
claim_house(mixed name, string house, string city)
{
    if (houses[house])
	return 0;

    MLC(name);

    houses[house] = NEW_HOUSE(name, city);
    members[name][M_HOUSE] = house;
    members[name][M_TYPE] |= (HOUSE_MEMBER | HOUSE_NOBLE | HOUSE_MATRON);

    save_state();
    GLOG(HOUSELOG, CAP(name) +" claimed House "+ house +" of City "+
	city +" as her own.");
    return 1;
}

/* 
 * Obliterate a house from the server and remove its members.
 * string house - The house to remove.
 */
public int
destroy_house(string house)
{
    int size;
    string *arr;

    if (!houses[house])
	return 0;

    arr = houses[house][H_MEMBERS];
    size = sizeof(arr);

    while(size--)
    {
	object player;

    if (!members[arr[size]])
        continue;

   	members[arr[size]][M_HOUSE] = "";
   	members[arr[size]][M_TYPE]  = GUILD_MEMBER;
    
	if (objectp(player = find_player(arr[size])))
	{
	    player->update_member_info_race();
	    player->catch_tell("\nThe Drow House "+
		house +" has been disbanded!\n\n");
	}
    }

    arr = houses[house][H_APPLY];
    size = sizeof(arr);

    while(size--)
    {
	object player;

    if (!members[arr[size]])
        continue;
    
    members[arr[size]][M_HOUSE] = "";

    if (objectp(player = find_player(arr[size])))
    {
   	    player->update_member_info_race();
        player->catch_tell("\nThe Drow House "+
	    house +" has been disbanded!\n\n");
    }
    }
    

    GLOG(HOUSELOG, "House "+ house +" was obliterated.");
    m_delkey(houses, house);
    save_state();
    return 1;
}

/*
 * Sets the members rank within a House.
 * string house - The house to set.
 * string rank - What rank to give them?
 * mixed name - Who to set it to.
 */
public int
set_house_rank(string house, string rank, mixed name)
{
    string old;
    mapping ranks = DROW_RANKS;

    if (!houses[house])
	return 0;

    MLC(name);
    switch(rank)
    {
    /* The nobles are in arrays as there can be more than
     * one generic noble, hence the special handling. */
    case HR_FNOBLES:
    case HR_MNOBLES:
	if (!houses[house][H_RANKS][rank])
	    houses[house][H_RANKS][rank]  = ({ name });
	else
	    houses[house][H_RANKS][rank] += ({ name });

	members[name][M_TYPE] |= ranks[rank][DR_TYPE];
	GLOG(HOUSELOG, CAP(name) +" added as a new "+
	    ranks[rank][DR_TITLE] +" of House "+ house +".");
	break;
    default:
	if (strlen(old = houses[house][H_RANKS][rank]))
	{
	    members[old][M_TYPE] ^= (ranks[rank][DR_TYPE] | HOUSE_NOBLE);
	    GLOG(HOUSELOG, CAP(old) +" forcibly removed as "+
	       ranks[rank][DR_TITLE] +" of House "+ house +".");
	}

	houses[house][H_RANKS][rank] = name;
	members[name][M_TYPE] |= (ranks[rank][DR_TYPE] | HOUSE_NOBLE);
	GLOG(HOUSELOG, CAP(name) +" instated as the new "+
	    ranks[rank][DR_TITLE] +" of House "+ house +".");
	break;
    }

    save_state();
    return 1;
}

/*
 * Removes the members rank within a House.
 * string house - The house to set.
 * string rank - What rank to give them?
 * mixed name - Who to set it to.
 */
public int
remove_house_rank(string house, string rank, mixed name)
{
    string old;
    mapping ranks = DROW_RANKS;

    if (!houses[house])
	return 0;

    MLC(name);
    switch(rank)
    {
    /* The nobles are in arrays as there can be more than
     * one generic noble, hence the special handling. */
    case HR_FNOBLES:
    case HR_MNOBLES:
	if (!sizeof(houses[house][H_RANKS][rank]))
	    return 0;

	if (!sizeof(houses[house][H_RANKS][rank] -= ({ name })))
	    m_delkey(houses[house][H_RANKS], rank);

	members[name][M_TYPE] ^= ranks[rank][DR_TYPE];
	GLOG(HOUSELOG, CAP(name) +" removed as a new "+
	    ranks[rank][DR_TITLE] +" of House "+ house +".");
	break;
    default:
	m_delkey(houses[house][H_RANKS], rank);
	members[name][M_TYPE] ^= (ranks[rank][DR_TYPE] | HOUSE_NOBLE);
	GLOG(HOUSELOG, CAP(name) +" removed as "+
	    ranks[rank][DR_TITLE] +" of House "+ house +".");
	break;
    }

    save_state();
    return 1;
}

/*
 * Query the rank of a House member.
 * string house - The house to check.
 * string rank - The rank to check.
 * mixed name - (optional)See if this person is that rank.
 */
public mixed
query_house_rank(string house, string rank, mixed name)
{
    mixed hrank;

    if (!houses[house])
	return 0;
    else
	hrank = houses[house][H_RANKS][rank];

    if (!name)
	return hrank;

    MLC(name);
    switch(rank)
    {
    /* The nobles are in arrays as there can be more than
     * one generic noble, hence the special handling. */
    case HR_FNOBLES:
    case HR_MNOBLES:
	if (!sizeof(hrank))
	    return 0;
	else
	    return (member_array(name, hrank) >= 0);
	break;
    case "":
	/* Special case to pass through this switch. */
	break;
    default:
	return (hrank == name);
	break;
    }
    /* Special bit to determine what rank a player has. */
    {
	int size;
	string *arr;

	hrank = houses[house][H_RANKS];
	size  = m_sizeof(hrank);
	arr   = m_indices(hrank);

	while(size--)
	{
	    if (pointerp(hrank[arr[size]]) &&
		 member_array(name, hrank[arr[size]]) >= 0)
	    {
		return arr[size];
	    }
	    else if (hrank[arr[size]] == name)
	    {
		return arr[size];
	    }
	}
	return 0;
    }
}

/*
 * Query the members of a house.
 * string house - the house to check.
 * int applicant - (optional)return applicants, not members.
 */
public varargs string *
query_house_members(string house, int applicant)
{
    if (!houses[house])
	return ({ });

    if (applicant)
	return secure_var(houses[house][H_APPLY]);
    else
	return secure_var(houses[house][H_MEMBERS]);
}

/*
 * Query what City a particular house belongs to.
 * string house - the house to check.
 */
public string
query_house_city(string house)
{
    if (!houses[house])
	return "";
    else
	return houses[house][H_CITY];
}

/*
 * Query the houses mapping for various information.
 * string city - (optional) Only query houses from this city.
 */
public varargs string *
query_houses(string city)
{
    if (strlen(city))
    {
	return m_indices(filter(houses,
	    &operator(==)(, city) @ &operator([])(, H_CITY)));
    }
    else
	return m_indices(houses);
}

/*
 * Query the raw data for a particular House.
 * string house - the houses data to get.
 */
public mixed *
query_house_data(string house)
{
    if (!houses[house])
	return ({ });
    else
	return secure_var(houses[house]);
}

/*
 * See if we need to update the Leadership of a given house.
 * string house - the house to verify.
 * mixed who - who/what is initiating this change.
 */
public int
reorganize_house(string house, mixed who)
{
    string tmp;
    int mtime, ctime = time();

    if (!houses[house])
	return 0;

    MLC(who);

    /* A noble is initiating this change request. */
    if (who)
    {
	/* See if the Matron is really idle. */
	tmp = houses[house][H_RANKS][HR_MATRON];
	mtime = members[tmp][M_ACTIVE];
	mtime += MAX_IDLE;

	if (mtime >= ctime)
	    return -1;

	/* We are the First Daughter, make us the Matron. */
	if (members[who][M_TYPE] & HOUSE_DAUGHTER)
	{
	    remove_house_rank(house, HR_DAUGHTER, who);
	    set_house_rank(house, HR_MATRON, who);
	    return 1;
	}

	/* Just a Noble, see if the First Daughter is active. */
	if (tmp = houses[house][H_RANKS][HR_DAUGHTER])
	{
	    mtime = members[tmp][M_ACTIVE];
	    mtime += MAX_IDLE;

	    if (mtime >= ctime)
		return -2;

	    /* Matron and Dauther are inactive, we are now the Matron. */
	    remove_house_rank(house, HR_FNOBLES, who);
	    set_house_rank(house, HR_MATRON, who);
	}

	return 2;
    } else {
	object player;

	/* Find the First Daughter and Promote if active enough. */
	if (tmp = houses[house][H_RANKS][HR_DAUGHTER])
	{
	    mtime = members[tmp][M_ACTIVE];
	    mtime += MAX_IDLE;
	}

	if (mtime >= ctime)
	{
	    /* First Daughter is active, make her the Matron. */
	    remove_house_rank(house, HR_DAUGHTER, tmp);
	    set_house_rank(house, HR_MATRON, tmp);

	    if (objectp(player = find_player(tmp)))
	    {
		player->update_member_info_race();
		player->catch_tell("\nYou are now the "+
		    "Matron Mother of House "+ house +"!\n\n");
	    }
	}
	else
	{
	    /* Okay, they are both inactive, check for active nobles. */
	    string *arr = houses[house][H_RANKS][HR_FNOBLES];

	    if (sizeof(arr))
	    {
		arr = filter(houses[house][H_RANKS][HR_FNOBLES],
		    &operator(>=)(, ctime) @
		    &operator(+)(, MAX_IDLE) @
		    &operator([])(, M_ACTIVE) @
		    &operator([])(members, ));
	    }

	    if (sizeof(arr))
	    {
		/* Found some, make one of them the Matron. */
		who = one_of_list(arr);
		remove_house_rank(house, HR_FNOBLES, who);
		set_house_rank(house, HR_MATRON, who);

		if (objectp(player = find_player(who)))
		{
		    player->update_member_info_race();
		    player->catch_tell("\nYou are now the "+
			"Matron Mother of House "+ house +"!\n\n");
		}
	    }
	    else
	    {
		/* None could be located, disband the House entirely. */
		destroy_house(house);
	    }
	}
	return 1;
    }
}

/*
 * Called from /d/Faerun/domain_link.c when a player
 * is purged or deleted.  This will let us clean up
 * various things.  Also may be called when a player
 * of Matron rank leaves Her House.
 */
public void
check_deleted_player(mixed name)
{
    string house;

    MLC(name);
    if (!members[name])
	return;

    house = members[name][M_HOUSE];

    if (members[name][M_TYPE] & HOUSE_MATRON)
	reorganize_house(house, 0);

    /* House might no longer exist.. */
    if (houses[house])
	set_member_house(name, 0);

    remove_member(name);
}
