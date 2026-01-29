/* Manager for Dragonarmy guild
 * Modif:
 *     Added function for easy promotions/demotions by hand. 19.12.2002 Torqual
 * Louie Dec 2005
 *
 * Navarre July 14th 2007, fixed the assume command code. It was totally buggy.
 *                         also lowered the idle time, to 14 days instead of 22.
 *                         more measures will be added.
 *
 * Navarre September 27 2007, added support for when the general dies, he can be replaced
 *                            if he is killed by a player.
 */

#pragma save_binary
#pragma strict_types
#pragma no_clone
#pragma no_shadow

#include "../guild.h"

#include <std.h>

#define MANAGER_SAVE        (DRAGONARMY_LOG + "manager")
#define MEMBER_SAVE         (DRAGONARMY_LOG + "members")
#define GUILDMASTER	    (DRAGONARMY_LOG + "guildmaster")

#define MEMBER_DIVISION	    0
#define MEMBER_PROMOTION    1
#define MEMBER_PROMOTER	    2
#define MEMBER_PROMOTED	    3
#define MAX_LEADER_IDLE     1209600     
            // 14 days * 60sec * 60min * 24 hours = 1209600 secs (14 days)

#define IS_INDEX(x, map)  (member_array(x, m_indices(map)) >= 0)

mapping banned = ([]);
mapping punished = ([]);
/*
  mapping member_count will have following items:
  "division" : ({ a, b, c, d, e })

  where:    "division"	- string - division of army
	    a,b,c,d,e	- int	 - number of members with promotion level
					0,1,2,3,4 respectively
*/
mapping member_count = ([]);

/*
  mapping members will have following items:
  "name" : ({ "division", promotion, "promoter", promoted })

  where:    "name"	- string - name of member
	    "division"	- string - division of army
	    promotion	- int	 - promotion level (0..4)
	    "promoter"	- string - name of member who did last promotion/demotion
	    promoted	- int	 - 1 if last promoted, 0 if demoted
*/
static mapping members = ([]);

/*
  mapping masters will have following items:
  "div" : ([ "title" : ({ "name1", "name2", ... }), ... ])

  where:    "title"	- string - master title
	    "name"	- string - name of member
	    "div"	- string - division of army
*/
mapping masters = ([]);

/*
  mapping fundrising will have following items:
  "div" : ([ "name" : pc_per_day, ... ])

  where:    "pc_per_day"- int	 - average plats collected per day
	    "name"	- string - name of member
	    "div"	- string - division of army
*/
mapping fundrising = ([]);

/* list of functions */
varargs int add_member(mixed who, string div, mixed recruiter);
int remove_member(mixed who);
int query_member(mixed who);
string query_division(mixed who);
int set_promotions(mixed who, int promo, object promoter);
int query_promotions(mixed who);
int query_promoted(mixed who);
string query_promoter(mixed who);
void remove_idle_leader(string div);

// this functions are for manual modifications in guild - wrapper to 
// set_promotion with proper arguments without present objects
int adm_level(string promoted, string promo);
int adm_load_members();

/*
 * Function:	update
 * Description:	This function checks for removed players or players that
 *		wizzed or jr characters and removes record of such players.
 */
private void
update()
{
    int i, s;
    string *names = m_indices(members);

    setuid();
    seteuid(getuid());
    s = sizeof(names);
    for(i = 0; i < s; i++)
    {
	if (!SECURITY->exist_player(names[i])
#ifndef DA_TESTING
	    || SECURITY->query_wiz_level(names[i])
	    || (extract(names[i], -2) == "jr")
#endif DA_TESTING
	   )
	{
	    member_count[query_division(names[i])][query_promotions(names[i])] += -1;
	    members = m_delete(members, names[i]);
	}
    }
}

/*
 * Function:	save
 * Description:	This function saves variables to savefiles.
 */
void
save()
{
    setuid();
    seteuid(getuid());
    save_object(MANAGER_SAVE);
    save_map(members, MEMBER_SAVE);
}

/*
 * Function:	create
 * Description:	This function is called when object is created.
 *		It restores variables form savefiles and updates them.
 */
void 
create()
{
    setuid();
    seteuid(getuid());

    restore_object(MANAGER_SAVE);
    members = restore_map(MEMBER_SAVE);

    update();
    save();
}

/*******************************************************************/
/*******************************************************************/

/*
 * Function:	query_member_count
 * Description:	This function returns number of members for given division
 *		with a level of promotions up to given level.
 * Arguments:	int level  - (0..4) level of promotion
 *		string div - division we want the count for
 * Returns:	int - number of members
 */
int
query_member_count(int level, string div)
{
    int i,num = 0;
    
    if(!member_count[div])
    {
	return 0;
    }

    for(i=0; i<=level; i++)
    {
	num += member_count[div][i];
    }
    return num;
}

mixed
query_member_list(string div)
{
    int i, s;
    string *ind;
    string *recruits = ({});
    string *soldiers = ({});
    string *officers = ({});
    string *high_officers = ({});
    string *general = ({});

    if (!div)
    {
        return 0;
    }

    div = L(div);
    ind = m_indices(members);
    s = sizeof(ind);
    for(i=0; i<s; i++)
    {
	if (div != members[ind[i]][MEMBER_DIVISION])
	{
	    continue;
	}
	switch(members[ind[i]][MEMBER_PROMOTION])
	{
	case 4:
	    general += ({ C(ind[i]) });
	    break;
	case 3:
	    high_officers += ({ C(ind[i]) });
	    break;
	case 2:
	    officers += ({ C(ind[i]) });
	    break;
	case 1:
	    soldiers += ({ C(ind[i]) });
	    break;
	default:
	    recruits += ({ C(ind[i]) });
	}
    }
    return ({ recruits, soldiers, officers, high_officers, general });
}

/*
 * Function:	get_name
 * Description:	This function returns standardized name as used in records
 * Arguments:	mixed who - string containing name or object pointer.
 * Returns:	string - standardized name or 0 if wrong argument
 */
string
get_name(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }
    if (!stringp(who))
    {
        return 0;
    }
    return L(who);
}

/*
 * Function:	add_member
 * Description:	This function adds new member into the records
 * Arguments:	mixed who - objectpointer or name of new member
 *		string div - division it is added to
 *		mixed recruiter - objectpointer or name of recruiter
 * Returns:	int - 1 if added, 0 else
 */
varargs int
add_member(mixed who, string div, mixed recruiter)
{
    if (!(who = get_name(who)) || query_member(who))
    {
        return 0;
    }
    recruiter = get_name(recruiter);
    if ((!recruiter) || (div != query_division(recruiter)))
    {

	recruiter = 0;
    }
    members[who] = ({ div, 0, recruiter, 1 });
    if(!member_count[div])
    {
	member_count[div] = ({ 1,0,0,0,0 });
    }
    else
    {
	member_count[div][0] += 1;
    }
    punished = m_delete(punished, who);
    save();
    return 1;
}    
 
int
remove_member(mixed who)
{
    if (!(who = get_name(who)) || !query_member(who))
    {
        return 0;
    }
    member_count[query_division(who)][query_promotions(who)] += -1;
    members = m_delete(members, who);
    punished = m_delete(punished, who);
    save();
    return 1;
}

mixed
query_member(mixed who)
{
    if (!(who = get_name(who)))
    {
        return 0;
    }
    return members[who];
}

mixed
query_member_activity(mixed who)
{
    int i, s;
    string *ind, div;
    string *recruited = ({});
    string *promoted = ({});
    string *demoted = ({});

    if (!(who = get_name(who)) || !query_member(who))
    {
        return 0;
    }

    div = members[who][MEMBER_DIVISION];
    ind = m_indices(members);
    s = sizeof(ind);
    for(i=0; i<s; i++)
    {
	if (ind[i] == who || div != members[ind[i]][MEMBER_DIVISION] ||
	    who != members[ind[i]][MEMBER_PROMOTER])
	{
	    continue;
	}
	if(!members[ind[i]][MEMBER_PROMOTED])
	{
	    demoted += ({ capitalize(ind[i]) });
	}
	else if(members[ind[i]][MEMBER_PROMOTION])
	{
	    promoted += ({ capitalize(ind[i]) });
	}
	else
	{
	    recruited += ({ capitalize(ind[i]) });
	}
    }
    return ({ recruited, promoted, demoted });
}

string
query_division(mixed who)
{
    string name = get_name(who);

    // Special case for bda recruiter.
    if (name == "bakaris")
    {
        return "blue";
    }

    // Special case for rda recruiter.
    if (name == "ariakas")
    {
        return "red";
    }

    if (!(who = get_name(who)) || !query_member(who))
    {
	return 0;
    }
    return (string)members[who][MEMBER_DIVISION];
}

int
set_promotions(mixed who, int promo, mixed promoter)
{
    int lp;
    string div, name = get_name(promoter), *temp_name;
    
    if (!(who = get_name(who)) || !query_member(who))
    {
	return 0;
    }
    
    lp = query_promotions(who);

    if(lp > promo)
    {
	members[who][MEMBER_PROMOTED] = 0;
    }
    else
    {
	members[who][MEMBER_PROMOTED] = 1;
    }
    
    div = query_division(who);

    member_count[div][lp] += -1;
    members[who][MEMBER_PROMOTION] = promo;
    member_count[div][promo] += 1;

    temp_name = explode(name, "_");

    if((query_division(name) == div)||
       (temp_name[0] == "wiz"))
    {
	members[who][MEMBER_PROMOTER] = name;
    }
    else 
    {
	members[who][MEMBER_PROMOTER] = 0;
    }

    save();
    return 1;
}

/* Function: adm_level
 * Args: string promoted - who to promote/demote
 * 	 string promo - level of promotion: general, high officer, officer
 * 	 		soldier, recruit
 * returns: 0 if fails
 *	    1 if success
 */
int adm_level(string promoted, string promo)
{
    int new_level;

    // wiz check 
/*
    if (!SECURITY->query_wiz_level(this_player()->query_real_name()))
            return 0;
    if (SECURITY->query_wiz_rank(this_player()->query_real_name()) < 5)
            return 0;
    if (SECURITY->query_wiz_dom(this_player()->query_real_name()) != "Krynn")
            return 0;


*/
	switch (promo)
	{
	case "general": 
		new_level = 4;
		break;
	case "high officer":
		new_level = 3;
		break;
	case "officer":
		new_level = 2;
		break;
	case "soldier":
		new_level = 1;
		break;
	case "recruit":
		new_level = 0;
		break;
	default: 
		new_level = 0;
	}

	return set_promotions(promoted, new_level, "wiz_" + this_player()->query_real_name());
}

/* Function: adm_load_members
 * Desc: This function allows to load up members from the file not only
 * 	during the creation of the object but also by hand
 * 	checks if wiz is allowed to do the changes
 * 	function does not save its values!!!!
 * args:
 * returns: 0 if no_wiz
 * 	    1 if no_steward or no_liege
 * 	    2 if no_Ansalon_domain
 * 	    3 if all done
 */
int adm_load_members()
{
    //wiz check
/*

    if (!SECURITY->query_wiz_level(this_player()->query_real_name()))
	    return 0;
    if (SECURITY->query_wiz_rank(this_player()->query_real_name()) < 5)
	    return 1;
    if (SECURITY->query_wiz_dom(this_player()->query_real_name()) != "Krynn")
	    return 2;

*/
    setuid();
    seteuid(getuid());

    members = restore_map(MEMBER_SAVE);

    update();

    return 3;
}


int
query_promotions(mixed who)
{
    if (!(who = get_name(who)) || !query_member(who))
    {
	return -1;
    }
    return (int)members[who][MEMBER_PROMOTION];
}

int
query_promoted(mixed who)
{
    if (!(who = get_name(who)) || !query_member(who))
    {
	return 0;
    }
    return (int)members[who][MEMBER_PROMOTED];
}

string
query_promoter(mixed who)
{
    if (!(who = get_name(who)) || !query_member(who))
    {
	return 0;
    }
    return (string)members[who][MEMBER_PROMOTER];
}

/*******************************************************************/
/*******************************************************************/

/*
  mapping masters will have following items:
  "div" : ([ "title" : ({ "name1", "name2", ... }), ... ])
*/
int
add_master_title(string title, string div)
{
    int i;
    string *titles;

    if (masters[div])
    {
	titles = m_indices(masters[div]);
    }
    else
    {
	masters[div] = ([]);
    }

    for (i=0; i<sizeof(titles); i++)
	if (L(titles[i]) == L(title))
	    return 0;

    masters[div][title] = ({ });
    save();
    return 1;
}

int
remove_master_title(string title, string div)
{
    int i;
    string *titles;

    if (!masters[div])
	return 0;

    titles = m_indices(masters[div]);

    for (i=0; i<sizeof(titles); i++)
	if (L(titles[i]) == L(title))
	{
	    masters[div] = m_delete(masters[div], titles[i]);
	    save();
	    return 1;
	}

    return 0;
}

string
query_master_title(mixed who, string div)
{
    int i;
    string *titles;

    if (!(who = get_name(who)) || !query_member(who))
	return 0;

    if (div != query_division(who) || !masters[div])
	return 0;

    titles = m_indices(masters[div]);

    for (i=0; i<sizeof(titles); i++)
	if (member_array(who, masters[div][titles[i]]) > -1)
	    return titles[i];

    return 0;
}

/*
 * Function name:	set_master
 * Arguments:		who - mixed - player name or object
 *			title - title string
 *			div - division of the army
 * Returns:	int	0 - all fine else errorcode
 *			1 - wrong player argument
 *			2 - player is not member
 *			3 - player not member of this division
 *			4 - no master titles for this division
 *			5 - wrong title
 *			6 - player already is a master
 */
int
set_master(mixed who, string title, string div)
{
    int i;
    string *titles;

    if (!(who = get_name(who)))
	return 1;
    if (!query_member(who))
	return 2;
    if (div != query_division(who))
	return 3;
    if (!masters[div])
	return 4;
    if (query_master_title(who, div))
	return 6;

    titles = m_indices(masters[div]);
    for (i=0; i<sizeof(titles); i++)
	if (L(titles[i]) == L(title))
	{
	    masters[div][titles[i]] += ({ who });
	    save();
	    return 0;
	}
    return 5;
}

/*
 * Function name:	remove_master
 * Arguments:		who - mixed - player name or object
 *			title - title string
 *			div - division of the army
 * Returns:	int	0 - all fine else errorcode
 *			1 - wrong player argument
 *			4 - no master titles for this division
 *			5 - wrong title
 */
int
remove_master(mixed who, string title, string div)
{
    int i;
    string *titles;

    if (!(who = get_name(who)))
	return 1;
    if (!masters[div])
	return 4;

    titles = m_indices(masters[div]);
    for (i=0; i<sizeof(titles); i++)
	if (L(titles[i]) == L(title))
	{
	    masters[div][titles[i]] -= ({ who });
	    save();
	    return 0;
	}
    return 5;
}

mapping
query_masters(string div)
{
    if (!masters[div])
	return ([]);
    return masters[div] + ([]);
}

/*******************************************************************/
/*******************************************************************/

int
add_punishment(mixed who, int punishment)
{
    if (!(who = get_name(who)))
    {
	return 0;
    }

    punished[who] = punished[who] | punishment;
    save();
    return 1;
}

int
remove_punishment(mixed who, int punishment)
{
    int previous_pun;

    if (!(who = get_name(who)))
    {
        return 0;
    }

    previous_pun = punished[who];
  
    if (!(previous_pun & punishment))
    {
        return 1;
    }
  
    punished[who] = previous_pun ^ punishment;
    if (!punished[who])
    {
	punished = m_delete(punished, who);
    }
    save();
    return 1;
}

int
set_punishment(mixed who, int punishment)
{
    if (!(who = get_name(who)))
    {
        return 0;
    }

    if (!punishment)
    {
	punished = m_delete(punished, who);
    }
    else
    {
	punished[who] = punishment;
    }
    save();
    return 1;
}

varargs mixed *
query_punished(int punishment)
{
    if (!punishment)
    {
        return m_indices(punished);
    }

    return m_indices(filter(punished,
        &operator(!=)(0) @ &operator(&)(punishment)));
}

varargs int
query_punishment(mixed who, int punishment )
{
    if (!(who = get_name(who)))
    {
        return 0;
    }

    if (!punishment)
    {
        return punished[who];
    }
   
    return punished[who] & punishment;
}

/*******************************************************************/
/*******************************************************************/

int
set_banned(mixed who, string div)
{
    if (!(who = get_name(who)))
    {
        return 0;
    }

    if (pointerp(banned[who]))
    {
        banned[who] |= ({ div });
    }
    else
    {
        banned[who] = ({ div });
    }

    save();
    return 1;
}

int
remove_banned(mixed who, string div)
{
    if (!(who = get_name(who)))
    {
        return 0;
    }

    if (!pointerp(banned[who]))
    {
        return 0;
    }

    banned[who] -= ({ div });
    if (!sizeof(banned[who]))
    {
	banned = m_delete(banned, who);
    }
    save();
    return 1;
}

varargs mixed
query_banned(mixed who = -1, mixed div = -1)
{
    if (who == -1)
    {
        if (div == -1)
 	{
            return banned + ([]);
	}
        return filter(banned, &operator(>=)(, 0) @ &member_array(div));
    }

    if (!(who = get_name(who)))
    {
        return 0;
    }

    if (div == -1)
    {
        return banned[who];
    }

    if (!banned[who])
    {
        return 0;
    }

    return (member_array(div, (mixed *)banned[who]) >= 0);
}

/* 
 * Function: check_replace_leader
 * Description: Try to become the leader if the spot is open
 */
int
check_replace_leader(object who)
{
    if(!who)
	return 0;
    string player = who->query_real_name();

    who = find_player(player);

    if (!objectp(who))
    {
	return 0;
    }

    string div = who->query_dragonarmy_division();

    if (!strlen(div))
        return 0;

    remove_idle_leader(div);

    //See if we even have a general

    string* ind = m_indices(members);
    int s = sizeof(ind);
    int count = 0;
    for(int i = 0; i < s; i++)
    {
	if (div != lower_case(members[ind[i]][MEMBER_DIVISION]))
	{
	    continue;
	}
	if(members[ind[i]][MEMBER_PROMOTION] == 4)
	{
	    count++;
	}
    }
    if (count > 0)
        return 0;

    if (set_promotions(who->query_real_name(), 4, "the Dark Queen"))
    {
        return 1;
    }
    return 0;
}

/*
 * Function : remove_idle_leader
 * Description: Remove a leader that hasn't logged in for X days
 */
void
remove_idle_leader(string div)
{
    string general;

    if (!strlen(div))
    {
        return;
    }
    
    string* ind = m_indices(members);
    int s = sizeof(ind);
    int count = 0;

    for(int i = 0; i < s; i++)
    {
	if (div != lower_case(members[ind[i]][MEMBER_DIVISION]))
	{
	    continue;
	}
	if(members[ind[i]][MEMBER_PROMOTION] == 4)
	{
	    general = ind[i];
	    count++;
	}
    }

    //See if we even have a general
    if (count < 1)
        return;
    
    //Check if any (of our div) General is idle, remove if so
    int t = time() - MAX_LEADER_IDLE;
    
    if (find_player(general))
        return;

    int j = file_time(PLAYER_FILE(general) + ".o");

	    
   if (j < t)
   {
        //Demote inactive Generals to Officer (2)
       set_promotions(general, 2, "the Dark Queen");
   }    
}

/*
 * Function : remove_idle_leader
 * Description: Remove a leader that hasn't logged in for X days
 */
void
remove_killed_leader(object dead_soldier, object killer)
{
    string general;

    if (!dead_soldier)
    {
        return;
    }

    string div = dead_soldier->query_dragonarmy_division();

    if(!div)
    {
	return;
    }
    string* ind = m_indices(members);
    int s = sizeof(ind);
    int count = 0;
    for(int i = 0; i < s; i++)
    {
	if (div != lower_case(members[ind[i]][MEMBER_DIVISION]))
	{
	    continue;
	}
	if(members[ind[i]][MEMBER_PROMOTION] == 4)
	{
	    general = ind[i];
	    count++;
	}
    }
    //See if we even have a general
    if (count < 1)
    {
	return;
    }

    if(lower_case(general) == lower_case(dead_soldier->query_real_name()) &&
       interactive(killer))
    {
	//Demote dead Generals to Officer (2)
	set_promotions(general, 2, "the Dark Queen");
    }
}

