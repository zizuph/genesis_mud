/*
 * Actor's Club Master
 *
 * This contains all the master/server/central functions for the Actors club.
 *
 * This code is all Mrpr with slight modifications by Lunatari 2006-2008.
 *
 * This hold all the mappings for members and so on, do not update this object
 * if you do not really have to.
 *
 * 2008-01-03 : Lunatari 
 * + Added offline invitation and such
 * 2008-02-18 : Lunatari
 * + Remove command fixed and not causing runtimes.
 * 2008-02-20 : Lunatari
 *0 + Confirmation log changed so it doesnt spam the actual club event log.
 * 2008-02-21 : Lunatari
 * + New members are added as Actor rank now.
 * + Old members who log in and are not Actor or Above wil be made Actors.
 */
#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include <macros.h>
#include <std.h>

#include "actor.h"

/*
 * Members, actual members of the club.
 * Removed, removed members (do_remove)
 * Expelled, expelled members aka uninvited members, old remove. 
 * Suggested, suggested players (do_suggest)
 * Invited, invited players, every month its purged.
 * Lauded, will contain laudings just like Invited.
 */
mapping gMembers,
        gRemoved,	
        gSuggested,
        gExpelled,
        gInvited;

static nomask string	dtstr(int tm);
static nomask void	check_vanished();
nomask string *list_suggest(int brief);
static nomask void      notify_manager(string mess);
void purge_invites();
void purge_expelled();
void save_central();

#define ONE_MONTH   (60 * 60 * 24 * 30)
#define ONE_WEEK    (24 * 7)

/*
 * Name:	Create
 * Desc:	Initialize parameters, read savefiles
 */
public nomask void
create()
{
    setuid();
    seteuid(getuid());

    gMembers   = restore_map(AC_MEMBERS);
    gRemoved   = restore_map(AC_REMOVED);
    gExpelled  = restore_map(AC_EXPELLED);
    gSuggested = restore_map(AC_SUGGESTED);
    gInvited   = restore_map(AC_INVITED);

    if (!mappingp(gInvited))
       gInvited = ([]);

    if (!mappingp(gMembers))
       gMembers = ([]);

    if (!mappingp(gRemoved))
       gRemoved = ([]);

    if (!mappingp(gExpelled))
       gExpelled = ([]);

    if (!mappingp(gSuggested))
       gSuggested = ([]);

    check_vanished();

    /* Reduce the lifetime of an invitation every hour */
    set_alarm(5.0, 3600.0, &purge_invites());
    set_alarm(5.0, 3600.0, &purge_expelled());
}


// Most of the below functions can only be called from the club,
// the inner sanctum or the actors symbol. Any other call is turned
// down, and in relevant cases -1 or "" or ({}) is returned.

/*
 * Name:	query_member
 * Desc:	Check if a named player is a member of the club
 * Args:	who - The player name
 * Returns:	1 - member, 0 - not
 */
nomask public int
query_member(string who)
{
    string pob = MASTER_OB(previous_object());

    /*
    find_player(WIZ_MANAGER)->catch_tell("[Actor's Debug: "+pob+" "+
        TP->query_real_name()+" ]\n");
    */
    if (previous_object() != this_object() &&
	pob != AC_CLUB &&
	pob != AC_INNER &&
	pob != AC_SYMBOL &&
        pob != AC_CENTRAL && 
        TP->query_real_name() != WIZ_MANAGER)
	return -1;

    check_vanished();

    return (sizeof(gMembers[who]) != 0);
}

/*
 * Name:	query_expelled
 * Desc:	Check if a named player has once been expelled from the club
 * Args:	who - The player name
 * Returns:	1 - previously expelled, 0 - not
 */
nomask public int
query_expelled(string who)
{
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_INNER2 &&
	pob != AC_SYMBOL)
	return -1;

    check_vanished();

    return (sizeof(gExpelled[who]) != 0);
}

/*
 * Name:	query_removed
 * Desc:	Check if a named player has once been removed from the club
 * Args:	who - The player name
 * Returns:	1 - previously removed, 0 - not
 */
nomask public int
query_removed(string who)
{
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return -1;

    check_vanished();

    return (sizeof(gRemoved[who]) != 0);
}

/*
 * Name:	query_level
 * Desc:	Check for the level of a named actor
 * Args:	who - the actor name
 * Returns:	The level
 */
nomask public int
query_level(string who)
{
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL &&
        TP->query_real_name() != WIZ_MANAGER)
	return -1;

    check_vanished();

    if (sizeof(gMembers[who]))
	return gMembers[who][AC_RANK];
    else
	return -1;
}

/*
 * Name:	add_member
 * Desc:	Add a member to the club
 * Args:	who - the player to add,
 *		nlist - the actors who invited him
 */
nomask public void
add_member(string who, string *nlist)
{
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_INNER2 &&
	pob != AC_SYMBOL)
	return;

    gMembers[who] = ({ time(), sort_array(nlist), 2, time(), time() });
    save_map(gMembers, AC_MEMBERS);
    if (sizeof(gExpelled[who]) != 0)
    {
	gExpelled = m_delete(gExpelled, who);
	save_map(gExpelled, AC_EXPELLED);
    }
    if (sizeof(gRemoved[who]) != 0)
    {
	gRemoved = m_delete(gRemoved, who);
	save_map(gRemoved, AC_REMOVED);
    }
    if (sizeof(gSuggested[who]) != 0)
    {
	gSuggested = m_delete(gSuggested, who);
	save_map(gSuggested, AC_SUGGESTED);
    }
    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (0) - Added by: " + implode(map(gMembers[who][AC_NLIST], capitalize), ", ") + "\n");
}

/*
 * Name:	attend_call
 * Desc:	Log a call for attention to a meeting
 * Args:	who - Who made the call
 *		mess - The attention message
 *		recips - Who heard the call
 */
nomask public void
attend_call(string who, string mess, string *recips)
{
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return;

    if (!strlen(mess))
	mess = "<No message>";

    write_file(ATTEND_LOG, ctime(time()) + " Called by: " + capitalize(who) + ": '" + capitalize(mess) + "' ["+ implode(map(recips, capitalize), ", ") + "]\n");
}

/*
 * Name:	do_remove_member
 * Desc:	Actually remove a member from the club
 * Args:	who - Whom to remove
 *		reason - the reason tag
 * Returns:
 */
nomask public void
do_remove_member(string who, int reason)
{
    object wizard;
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return;

    if(objectp(wizard = find_player(WIZ_MANAGER)))
	wizard->catch_msg("[Actor's Note: removed "+capitalize(who)+
			  " because of reason (int) "+reason+"]\n");

    if(gMembers[who])
    {

	switch (reason)
	{
        case REASON_RESIGN:
	    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Resigned.\n");
	    break;

        case REASON_WIZ:
	    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Wizzed.\n");
	    break;

        case REASON_VANISHED:
	    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Vanished from Genesis.\n");
	    break;

        case REASON_NONE:
	    /* FALLTHROUGH */
	    break;

        default:
	    break;
	}

	gMembers = m_delete(gMembers, who);
	save_map(gMembers, AC_MEMBERS);
    }
}

/*
 * Name:	promote_member
 * Desc:	Promote a member of the club
 * Args:	who - whom to promote
 *		nlist - the actors who did the promotion
 * Returns:	The new level
 *
nomask public int
promote_member(string who, string *nlist)
{
    object ob;
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return -1;

    gMembers[who][AC_RANK]++;
    gMembers[who][AC_RCH] = time();
    save_map(gMembers, AC_MEMBERS);

    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Promoted by: " + implode(map(sort_array(nlist), capitalize), ", ") + "\n");

    return gMembers[who][AC_RANK];
}
*/

/*
 * Name:	demote_member
 * Desc:	Demote a member of the club, possibly expelling him
 * Args:	who - whom to demote
 *		nlist - the actors who did the demoting
 * Returns:	The new level, -1 for expulsion
 *
nomask public int
demote_member(string who, string *nlist)
{
    object ob;
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return -1;

    gMembers[who][AC_RANK]--;
    gMembers[who][AC_RCH] = time();
    if (gMembers[who][AC_RANK] < 0)
    {
	gExpelled[who] = ({ time(), sort_array(nlist) });
	save_map(gExpelled, AC_EXPELLED);

	write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Expelled by: " + implode(map(gExpelled[who][AC_NLIST], capitalize), ", ") + "\n");

	do_remove_member(who, REASON_NONE);
	return -1;
    }

    save_map(gMembers, AC_MEMBERS);

    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Demoted by: " + implode(map(sort_array(nlist), capitalize), ", ") + "\n");

    return gMembers[who][AC_RANK];
}
*/

/*
 * Name:	remove_member
 * Desc:	Remove a member from the club, soft 'expel'
 * Args:	who - whom to remove
 *		remover - the thespian who removed him
 *		reason - the reason for removal
 * Returns:	1 - success, -1 - fail
 */
nomask public int
remove_member(string who, string remover, string reason)
{
    object ob;
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return -1;

    gRemoved[who] = ({ time(), remover, reason });
    save_map(gRemoved, AC_REMOVED);

    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + 
      (gMembers[who][AC_RANK] + 1) + ") - Removed by: " + 
      capitalize(gRemoved[who][AC_NLIST]) + "\n");

    do_remove_member(who, REASON_NONE);
    return 1;
}

/*
 * Name:	list_members
 * Desc:	Print a list of certain members logs
 * Args:	who - who's doing the listing
 *		what - what to list
 */
nomask public void
list_members(object who, int what)
{
    string pob = MASTER_OB(previous_object());
    string *mem, *exl, *mem_list, *extra_list, name;
    int i, sz, num;

    check_vanished();

    mem = exl = ({});

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return;

    switch (what)
    {
    default:
    case 0:
    /* List Members */
#ifdef MET
	mem_list = filter(sort_array(m_indices(gMembers)), &who->query_met());
#else // MET
	mem_list = sort_array(m_indices(gMembers));
#endif // MET

	if (sizeof(mem_list))
	{
	    write(sprintf("  %-14s%-12s%-12s%s\n", "Member", "Acceptance", "Last visit", "Invited by"));
	    write(sprintf("  %-14s%-12s%-12s%s\n", "------", "----------", "----------", "----------"));
	    for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
	    {
#ifdef MET
		extra_list = filter(sort_array(gMembers[mem_list[i]][AC_NLIST]), &who->query_met());
#else // MET
		extra_list = gMembers[mem_list[i]][AC_NLIST];
#endif // MET
		if ((num = sizeof(gMembers[mem_list[i]][AC_NLIST]) - sizeof(extra_list)))
		    extra_list += ({ ("" + num + " unknown supporter" + (num > 1 ? "s" : "")) });
		write((objectp(find_player(mem_list[i])) ? "* " : 
                     ((time() - SECURITY->query_player_file_time(mem_list[i])) > ONE_MONTH) ? "- " : "  ") + 
                     sprintf("%-14s%10s  %10s  %s\n", capitalize(mem_list[i]), 
                     dtstr(gMembers[mem_list[i]][AC_TIME]), dtstr(gMembers[mem_list[i]][AC_LAST]), 
                     implode(map(extra_list, capitalize), ", ")));
	    }
	    if ((num = sizeof(m_indices(gMembers)) - sizeof(mem_list)) > 0)
		write("\n" + num + " unknown member" + (num > 1 ? "s" : "") + ".\n");
	}
	else
	    write("No members.\n");
	break;

    case 1:
    /* List Removed Members */
#ifdef MET
	mem_list = filter(sort_array(m_indices(gRemoved)), &who->query_met());
#else // MET
	mem_list = sort_array(m_indices(gRemoved));
#endif // MET

	if (sizeof(mem_list))
	{
	    write(sprintf("%-29s%-15s%-12s%s\n", "Removed", "Removal date", "Removed by", "Reason"));
	    write(sprintf("%-29s%-15s%-12s%s\n", "-------", "------------", "----------", "------"));
	    for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
	    {
#ifdef MET
		if (who->query_met(gRemoved[mem_list[i]][AC_NLIST]))
		    name = gRemoved[mem_list[i]][AC_NLIST];
		else
		    name = "unknown remover";

#else // MET
		name = gRemoved[mem_list[i]][AC_NLIST];
#endif // MET
		write(sprintf("%-29s%12s  %11s  %s\n", capitalize(mem_list[i]), dtstr(gRemoved[mem_list[i]][AC_TIME]), capitalize(name), capitalize(gRemoved[mem_list[i]][AC_RANK])));
	    }
	    if ((num = sizeof(m_indices(gRemoved)) - sizeof(mem_list)) > 0)
		write("\n" + num + " unknown removed member" + (num > 1 ? "s" : "") + ".\n");
	}
	else
	    write("No removed members.\n");
	break;
    }
}

/*
 * Name:	update_last
 * Desc:	Update the last entry of the player
 * Args:	who - who the player is
 */
nomask void
update_last(string who)
{
    if (sizeof(gMembers[who]))
    {
	gMembers[who][AC_LAST] = time();
	save_map(gMembers, AC_MEMBERS);
    }
}

/*
 * Name:	check_vanished
 * Desc:	Check if any actors have vanished from the game,
 *		and if so, zap them from the records.
 */
static nomask void
check_vanished()
{
    string *mem_list, *exist_list;
    int i, sz, num;

    // Let's find those who simply has vanished since last check.
    mem_list = sort_array(m_indices(gMembers));
    exist_list = filter(mem_list, &SECURITY->exist_player());
    mem_list = mem_list - exist_list;

    for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
    {
	do_remove_member(mem_list[i], REASON_VANISHED);
    }
}

/*
 * Function name: query_suggest
 * Description:   Query the central if a certain player has been
 *                suggested, this is used by the invitation code.
 * Arguments:     Player name string.
 */
int
query_suggest(string player)
{
	if(!gSuggested[player]) return 0;

	return 1;
}

/*
 * Name:	add_suggest
 * Desc:	Add someone to the suggest log, inform everbody
 * Args:	who - whom to add
 * 		adder - who does the adding
 * Returns:	1 - success, 0 - not
 */
nomask int
add_suggest(string who, string adder)
{
    string pob = MASTER_OB(previous_object());
    string bstr;
    object *member_list;

    if (previous_object() != this_object() &&
	pob != AC_SYMBOL &&
        pob != AC_INNER)
	return 0;

    if (sizeof(gSuggested[who]) != 0)
	return notify_fail(capitalize(who) + " has already been suggested by " + capitalize(gSuggested[who][1]) + ".");

    gSuggested[who] = ({ time(), adder });
    save_map(gSuggested, AC_SUGGESTED);

    write("You just suggested " + capitalize(who) + " for membership in the Actor's Club.\n");

    bstr = "Your Actor's symbol suddenly starts vibrating and a soft voice can be heard:\n" +
	"  " + capitalize(adder) + " just suggested " + capitalize(who) + " for membership in the Actor's club.\n" +
	"  Keep an eye out for this player and make your recommendations\n" +
	"  known on the inner board in the club as soon as possible.\n";

    member_list = filter(map(m_indices(gMembers), find_player), &operator(!=)(0));
    member_list -= ({ find_player(adder) });

    member_list->catch_tell(bstr);

    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (-) - Suggested by: " + capitalize(adder) + "\n");

    return 1;
}

/*
 * Name:	list_suggest
 * Desc:	List all suggested members
 * Arg:         brief - return a brief list or print
 *		brief = 0 : print
 *		brief = 1 : return the entire list
 *              brief < 0 : return those older than (-brief) days
 */
nomask string *
list_suggest(int brief)
{
    string pob = MASTER_OB(previous_object());
    string *sugg_list, *tm_list;
    int i, sz, tm;

    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return ({});

    sugg_list = sort_array(m_indices(gSuggested));

    if (brief == 0)
    {
	if (sizeof(sugg_list))
	{
	    write(sprintf("%-29s%-17s%s\n", "Suggested", "Suggestion date", "Suggested by"));
	    write(sprintf("%-29s%-17s%s\n", "---------", "---------------", "------------"));
	    for (i = 0, sz = sizeof(sugg_list) ; i < sz ; i++)
		write(sprintf("%-29s%-17s%s\n", capitalize(sugg_list[i]), dtstr(gSuggested[sugg_list[i]][AC_TIME]), capitalize(gSuggested[sugg_list[i]][AC_NLIST])));
	}
	else
	    write("No suggested players.\n");
    }
    else if (brief == 1)
	return sugg_list;
    else
    {
	tm = time() - ((-brief) * 60 * 60 * 24);
	tm_list = ({ });

	for (i = 0, sz = sizeof(sugg_list) ; i < sz ; i++)
	    if (gSuggested[sugg_list[i]][AC_TIME] < tm)
		tm_list += ({ sugg_list[i] });

	return tm_list;
    }
}

/*
 * Name:	remove_suggest
 * Desc:	Remove someone from the suggest list
 * Args:	who - whom to remove
 * Returns:	1 - success, 0 - not
 */
nomask int
remove_suggest(string who, string remover)
{
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_SYMBOL)
	return 0;

    if (sizeof(gSuggested[who]) == 0)
	return notify_fail("There is no suggested player with that name.\n");

    gSuggested = m_delete(gSuggested, who);
    save_map(gSuggested, AC_SUGGESTED);

    write("Ok.\n");

    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (-) - Suggestion removed by: " + capitalize(remover) + "\n");

    return 1;
}

/*
 * Name:	rank_check
 * Desc:	Check for rank changes within given time/rank
 * Args:	time - max time in days since last check
 * 		rank - the rank span to check
 * Returns:	list of members who's rank has not changed within parameters
 */
nomask string *
rank_check(int tmspan, int rank)
{
    string pob = MASTER_OB(previous_object());
    int tm, i, sz, secs;
    string *tm_list, *mem_list;

    if (previous_object() != this_object() &&
	pob != AC_SYMBOL)
	return ({});

    tm = time() - (tmspan * 60 * 60 * 24);
    tm_list = ({ });
    mem_list = sort_array(m_indices(gMembers));

    for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
    {
	if (gMembers[mem_list[i]][AC_RCH] < tm &&
	    gMembers[mem_list[i]][AC_RANK] < rank)
	    tm_list += ({ mem_list[i] });
    }

    return tm_list;
}

/*
 * Name:	rank_remain
 * Desc:	Update rank change time for a given member
 * Args:	who - whom to update
 *		cfer - confirm person
 * Returns:	1 - success, 0 - not
 */
nomask int
rank_remain(string who, string cfer)
{
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_SYMBOL)
	return 0;

    gMembers[who][AC_RCH] = time();
    save_map(gMembers, AC_MEMBERS);

    write_file(CONFIRM_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Rank confirmed by: " + capitalize(cfer) + "\n");

    return 1;
}

/*
 * Name:	query_last_visit
 * Desc:	Return the last logged visit timestamp
 * Args:	who - whom to query
 * Returns:	The timestamp
 */
nomask int
query_last_visit(string who)
{
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_SYMBOL)
	return 0;

    if (!CHECK_MEMBER_N(who))
	return 0;

    return gMembers[who][AC_LAST];
}

/*
 * Name:	dstr
 * Desc:	Turn the date string into something more palatable for logs
 * Args:	tm - the time to convert
 * Returns:	The converted date string
 */
static nomask string
dtstr(int tm)
{
    string rval, dt;

    if (tm == 0)
	return "         -";

    dt = ctime(tm);

    rval = dt[20..23] + " ";
    switch(dt[4..6])
    {
    case "Jan":
	rval += "01";
	break;

    case "Feb":
	rval += "02";
	break;

    case "Mar":
	rval += "03";
	break;

    case "Apr":
	rval += "04";
	break;

    case "May":
	rval += "05";
	break;

    case "Jun":
	rval += "06";
	break;

    case "Jul":
	rval += "07";
	break;

    case "Aug":
	rval += "08";
	break;

    case "Sep":
	rval += "09";
	break;

    case "Oct":
	rval += "10";
	break;

    case "Nov":
	rval += "11";
	break;

    case "Dec":
	rval += "12";
	break;

    default:
	rval += "**";
    }

    if (dt[8] == ' ')
	rval += " 0" + dt[9..9];
    else
	rval += " " + dt[8..9];

    return rval;
}

/*
 * Name:	login
 * Desc:	Someone logged in
 * Args:	who - who logged on
 * Returns:	None
 */
public nomask void
login(string who)
{
    string name = lower_case(who);
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_SYMBOL)
	return 0;

    if (!CHECK_MEMBER_N(name))
	return;

    /* Make sure people are atleast Actor Rank */
    if (QUERY_LEVEL_N(name) != MEMBER_RANK)
    {
        gMembers[name][AC_RANK] = MEMBER_RANK;
        save_map(gMembers, AC_MEMBERS);
    } 
       
    notify_manager("[Actor's club: " + capitalize(name) + " (" + AC_RANK_NAMES[QUERY_LEVEL_N(name)] + ") logged in.]\n");
}

/*
 * Name:	logout
 * Desc:	Someone logged out
 * Args:	who - who logged out
 * Returns:	None
 */
public nomask void
logout(string who)
{
    string name = lower_case(who);
    string pob = MASTER_OB(previous_object());

    if (previous_object() != this_object() &&
	pob != AC_SYMBOL)
	return 0;

    if (!CHECK_MEMBER_N(name))
	return;

    notify_manager("[Actor's club: " + capitalize(name) + " (" + AC_RANK_NAMES[QUERY_LEVEL_N(name)] + ") logged out.]\n");
}

/*
 * Name:	notify_manager
 * Desc:	Notify the club manager, if logged on
 * Args:	mess - message to the manager
 * Returns:	None
 */
static nomask void
notify_manager(string mess)
{
    object wiz;

    if (objectp((wiz = find_player(WIZ_MANAGER))))
	if (wiz->query_prop(WIZM_PROP) == 0)
	    wiz->catch_tell(mess);
}

/*
 * Function name: query_invites
 * Description:   Check the invites if any for a certain player.
 */
int
query_invites(mixed player)
{
    if (objectp(player))
        player = player->query_real_name();

    if (!gInvited[player] || !gInvited[player][0])
        return 0;

    return gInvited[player][0];
}

/*
 * Function name: query_inviters
 * Description:   Check the invites if any for a certain player.
 */
mixed
query_inviters(mixed player)
{
    if (objectp(player))
        player = player->query_real_name();

    if (!gInvited[player] || !gInvited[player][0])
        return 0;

    return gInvited[player][2];
}

/*
 * Function name: add_invite
 * Description:   Adds or sets the invitation status for a player.
 * Arguments:     player name, integer votes, inviter name
 */
void
add_invite(string player, int votes, string inviter)
{
  if(!player) return;

  if(votes >= 3) votes = 2;

  /* New entry */
  if(!gInvited[player])
  {
      /* Create an entry for the player */
      gInvited[player] = ({ votes, ONE_WEEK, ({ inviter, }), time(), });
  }
  else
  {
      /* User exists, check and add up */
      gInvited[player][0] = gInvited[player][0] + votes;
      gInvited[player][2] += ({inviter});
  }

  save_central();
}

/*
 * Function name: delete_invite
 * Description:   Deletes an invitation from the mapping.
 * Arguments:     player name as string.
 * Returns:       1 if successful and 0 if not (player not in list)
 */
int
delete_invite(string player)
{
    if(!gInvited[player]) return 0;

    if(gInvited = m_delete(gInvited, player)) return 1;

    return 0;
}

/*
 * Function name: list_invites
 * Description:   A debug list for wizards only.
 */
mixed
list_invites()
{
    string pob = MASTER_OB(previous_object());
    string *mem, *exl, *mem_list, *extra_list, name;
    int i, sz, num;

    mem = exl = ({});

    if (previous_object() != this_object() &&
        pob != AC_INNER &&
        pob != AC_SYMBOL)
        return;

    /* List Invited Players */
    mem_list = sort_array(m_indices(gInvited));

    if (sizeof(mem_list))
    {
       write(sprintf("%-22s%-7s%-11s%-5s%s\n", "Invited", "Votes","Invited   ","Days", "Invited by"));
       write(sprintf("%-22s%-7s%-11s%-5s%s\n", "-------", "-----","----------","----", "----------"));
       for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
       {
         extra_list = gInvited[mem_list[i]][2];

         write(sprintf("%-22s%- 7d%-11s%- 5d%s\n", capitalize(mem_list[i]), 
               gInvited[mem_list[i]][0],
               dtstr(gInvited[mem_list[i]][3]), 
               (gInvited[mem_list[i]][1])  / 24,
               implode(map(extra_list, capitalize), ", ")));
       }
    }
    else
    write("No invited players.\n");
}

/* DEBUG INVITE LIST */
mixed
query_invited()
{
    int k, i;
    mixed list, tmp;

    k = m_sizeof(gInvited);
    i = -1;
    list = ({ });
    tmp  = m_indexes(gInvited);

    while(++i < k)
    {
		list += ({capitalize(tmp[i])});
    }

    return list;
}

/*
 * Function name: purge_invites
 * Description:   This will purge the invite mappings so that
 *                persons wont have decades to join in, this to
 *                prevent very odd joinings.
 *                Example: Miclo gets invited by Nellnight 2008-01-01
 *                 Miclo lacks one vote, none votes until 2008-12-24 when
 *                 Lunatari enters the guild and votes for Miclo who then
 *                 gets in because he had a 2 point vote from Nellnight.
 *
 *                This will reduce the Age variable in the invite mapping
 *                every hour the server is awake and after 48 hours it will
 *                be reduced to 0 and then the member will be removed from
 *                the mapping.
 *
 * Creation:      2008-01-03 by Lunatari
 */
void
purge_invites()
{
    int k, i;
    mixed list, tmp;

    k = m_sizeof(gInvited);
    i = -1;
    list = ({ });
    tmp  = m_indexes(gInvited);

    /*
     * Go through the list and decrease their age by 1,
     * if the age is 0 then delete them from the mapping.
     */
    while(++i < k)
    {
	if(gInvited[tmp[i]][1] >= 1)
	  gInvited[tmp[i]][1] = gInvited[tmp[i]][1] - 1;
	else
          gInvited = m_delete(gInvited, tmp[i]);
    }

    save_central();
}

/*
 * Function name: list_removal
 * Description:   A list of people pending removal/expelled.
 */
mixed
list_removal()
{
    string pob = MASTER_OB(previous_object());
    string *mem, *exl, *mem_list, *extra_list, name;
    int i, sz, num;

    mem = exl = ({});

    if (previous_object() != this_object() &&
        pob != AC_INNER &&
        pob != AC_SYMBOL)
        return;

    /* List Expelled Players */
    mem_list = sort_array(m_indices(gExpelled));

    if (sizeof(mem_list))
    {
       write(sprintf("%-22s%-7s%-11s%-5s%s\n", "Pending", "Votes","Added Date","Days", "Expellers "));
       write(sprintf("%-22s%-7s%-11s%-5s%s\n", "-------", "-----","----------","----", "----------"));
       for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
       {
         extra_list = gExpelled[mem_list[i]][2];

         write(sprintf("%-22s%- 7d%-11s%- 5d%s\n", capitalize(mem_list[i]), 
               gExpelled[mem_list[i]][0],
               dtstr(gExpelled[mem_list[i]][3]), 
               (gExpelled[mem_list[i]][1])  / 24,
               implode(map(extra_list, capitalize), ", ")));
       }
    }
    else
    write("No players has been suggested for removal.\n");
}

/*
 * Purge expelled pendings
 */
void
purge_expelled()
{
    int k, i;
    mixed list, tmp;

    k = m_sizeof(gExpelled);
    i = -1;
    list = ({ });
    tmp  = m_indexes(gExpelled);

    /*
     * Go through the list and decrease their age by 1,
     * if the age is 0 then delete them from the mapping.
     */
    while(++i < k)
    {
	if(gExpelled[tmp[i]][1] >= 1)
	  gExpelled[tmp[i]][1] = gExpelled[tmp[i]][1] - 1;
	else
          gExpelled = m_delete(gExpelled, tmp[i]);
    }

    save_central();
}

/*
 * Function name: save_central
 * Description:   Saves the central mappings, well
 *                those who Lunatari added.
 */
void save_central()
{
    setuid();
    seteuid(getuid());

    save_map(gInvited, AC_INVITED);
    save_map(gExpelled, AC_EXPELLED);
}

/*
 * Function name: armageddon
 * Description:   Armageddon is calling this to destruct.
 */
void
armageddon()
{
    /* Let us save */
    save_central();
}

/*
 * Name:
 * Desc:
 * Args:
 * Returns:
 */
