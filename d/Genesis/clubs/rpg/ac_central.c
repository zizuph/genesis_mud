/*
 * Actor's club central object.
 */

#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include <macros.h>
#include <std.h>

#include "actor.h"

mapping gMembers,	// Global mapping to contain the members
        gRemoved,	// Global mapping to contain removed members
        gExpelled;	// Global mapping to contain expelled members

static nomask string	dtstr(string dt);
static nomask void	check_vanished();

/*
 * Name:	Create
 * Desc:	Initialize parameters, read savefiles
 */
public nomask void
create()
{
    setuid();
    seteuid(getuid());

    gExpelled = gMembers = ([]);

    gMembers = restore_map(AC_MEMBERS);
    gRemoved = restore_map(AC_REMOVED);
    gExpelled = restore_map(AC_EXPELLED);

    if (!mappingp(gMembers))
	gMembers = ([]);

    if (!mappingp(gRemoved))
	gRemoved = ([]);

    if (!mappingp(gExpelled))
	gExpelled = ([]);

    check_vanished();
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
    
    if (previous_object() != this_object() &&
	pob != AC_CLUB &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
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
	pob != AC_SYMBOL)
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
	pob != AC_SYMBOL)
	return;

    gMembers[who] = ({ time(), sort_array(nlist), 0 });
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
    string pob = MASTER_OB(previous_object());
    
    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return;

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
    default:
	break;
    }

    gMembers = m_delete(gMembers, who);
    save_map(gMembers, AC_MEMBERS);
}

/*
 * Name:	promote_member
 * Desc:	Promote a member of the club
 * Args:	who - whom to promote
 *		nlist - the actors who did the promotion
 * Returns:	The new level
 */
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
    save_map(gMembers, AC_MEMBERS);

    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Promoted by: " + implode(map(sort_array(nlist), capitalize), ", ") + "\n");

    return gMembers[who][AC_RANK];
}

/*
 * Name:	demote_member
 * Desc:	Demote a member of the club, possibly expelling him
 * Args:	who - whom to demote
 *		nlist - the actors who did the demoting
 * Returns:	The new level, -1 for expulsion
 */
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

/*
 * Name:	remove_member
 * Desc:	Remove a member from the club, soft 'expel'
 * Args:	who - whom to remove
 *		remover - the thespian who removed him
 * Returns:	1 - success, -1 - fail
 */
nomask public int
remove_member(string who, string remover)
{
    object ob;
    string pob = MASTER_OB(previous_object());
    
    if (previous_object() != this_object() &&
	pob != AC_INNER &&
	pob != AC_SYMBOL)
	return -1;

    gRemoved[who] = ({ time(), remover });
    save_map(gRemoved, AC_REMOVED);

    write_file(AC_LOG, ctime(time()) + ": " + capitalize(who) + " (" + (gMembers[who][AC_RANK] + 1) + ") - Removed by: " + implode(map(gRemoved[who][AC_NLIST], capitalize), ", ") + "\n");

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
    string *mem, *exl, *mem_list, *extra_list;
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
#ifdef MET
	mem_list = filter(sort_array(m_indices(gMembers)), &who->query_met());
#else // MET
	mem_list = sort_array(m_indices(gMembers));
#endif // MET

	if (sizeof(mem_list))
	{
	    write(sprintf("  %-14s%-15s%-17s%s\n", "Member", "Rank", "Acceptance date", "Invited by"));
	    write(sprintf("  %-14s%-15s%-17s%s\n", "------", "----", "---------------", "----------"));
	    for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
	    {
#ifdef MET
		extra_list = filter(sort_array(gMembers[mem_list[i]][AC_NLIST]), &who->query_met());
#else // MET
		extra_list = gMembers[mem_list[i]][AC_NLIST];
#endif // MET
		if ((num = sizeof(gMembers[mem_list[i]][AC_NLIST]) - sizeof(extra_list)))
		    extra_list += ({ ("" + num + " unknown supporter" + (num > 1 ? "s" : "")) });
		write((objectp(find_player(mem_list[i])) ? "* " : ((time() - SECURITY->query_player_file_time(mem_list[i])) > (60 * 60 * 24 * 30)) ? "- " : "  ") + sprintf("%-14s%-15s%-17s%s\n", capitalize(mem_list[i]), AC_RANK_NAMES[gMembers[mem_list[i]][AC_RANK]], dtstr(ctime(gMembers[mem_list[i]][AC_NAME])), implode(map(extra_list, capitalize), ", ")));
	    }
	    if ((num = sizeof(m_indices(gMembers)) - sizeof(mem_list)) > 0)
		write("\n" + num + " unknown member" + (num > 1 ? "s" : "") + ".\n");
	}
	else
	    write("No members.\n");
	break;

    case 1:
#ifdef MET
	mem_list = filter(sort_array(m_indices(gRemoved)), &who->query_met());
#else // MET
	mem_list = sort_array(m_indices(gRemoved));
#endif // MET

	if (sizeof(mem_list))
	{
	    write(sprintf("  %-29s%-17s%s\n", "Removed", "Removal date", "Removed by"));
	    write(sprintf("  %-29s%-17s%s\n", "-------", "------------", "----------"));
	    for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
	    {
#ifdef MET    
		extra_list = filter(gRemoved[mem_list[i]][AC_NLIST], &who->query_met());
#else // MET
		extra_list = gRemoved[mem_list[i]][AC_NLIST];
#endif // MET
		if ((num = sizeof(gRemoved[mem_list[i]][AC_NLIST]) - sizeof(extra_list)))
		    extra_list += ({ ("" + num + " unknown remover" + (num > 1 ? "s" : "")) });
		write(sprintf("  %-29s%-17s%s\n", capitalize(mem_list[i]), dtstr(ctime(gRemoved[mem_list[i]][AC_NAME])), implode(map(extra_list, capitalize), ", ")));
	    }
	    if ((num = sizeof(m_indices(gRemoved)) - sizeof(mem_list)) > 0)
		write("\n" + num + " unknown removed member" + (num > 1 ? "s" : "") + ".\n");
	}
	else
	    write("No removed members.\n");
	break;

    case 2:
#ifdef MET
	mem_list = filter(sort_array(m_indices(gExpelled)), &who->query_met());
#else // MET
	mem_list = sort_array(m_indices(gExpelled));
#endif // MET

	if (sizeof(mem_list))
	{
	    write(sprintf("  %-29s%-17s%s\n", "Expelled", "Expulsion date", "Expelled by"));
	    write(sprintf("  %-29s%-17s%s\n", "--------", "--------------", "-----------"));
	    for (i = 0, sz = sizeof(mem_list) ; i < sz ; i++)
	    {
#ifdef MET    
		extra_list = filter(gExpelled[mem_list[i]][AC_NLIST], &who->query_met());
#else // MET
		extra_list = gExpelled[mem_list[i]][AC_NLIST];
#endif // MET
		if ((num = sizeof(gExpelled[mem_list[i]][AC_NLIST]) - sizeof(extra_list)))
		    extra_list += ({ ("" + num + " unknown expeller" + (num > 1 ? "s" : "")) });
		write(sprintf("  %-29s%-17s%s\n", capitalize(mem_list[i]), dtstr(ctime(gExpelled[mem_list[i]][AC_NAME])), implode(map(extra_list, capitalize), ", ")));
	    }
	    if ((num = sizeof(m_indices(gExpelled)) - sizeof(mem_list)) > 0)
		write("\n" + num + " unknown expelled member" + (num > 1 ? "s" : "") + ".\n");
	}
	else
	    write("No expelled members.\n");
	break;
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
 * Name:	dstr
 * Desc:	Turn the date string into something more palatable for logs
 * Args:	dt - the date string
 * Returns:	The converted date string
 */
static nomask string
dtstr(string dt)
{
    string rval;

    rval = dt[22..23] + " ";
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
    
    rval += " " + dt[8..9];

    return rval;
}

/*
 * Name:	
 * Desc:	
 * Args:	
 * Returns:	
 */
