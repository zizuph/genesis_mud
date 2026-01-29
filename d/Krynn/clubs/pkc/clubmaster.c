/* created by Aridor 12/02/93 
 *
 *
 * Cotillion did performance improvments in 2002-08-
 */
#pragma save_binary

inherit "/std/room";

#include "/d/Krynn/common/defs.h"
#include "clubdefs.h"

#include <std.h>
#include <stdproperties.h>
#include <macros.h>

/* OK, this is a tough one! I want to know how much older a player got
 * within the last twentyone days. 
 * According to this (and the alignment of the player), a ranking list is produced.
 *
 * Here goes:
 * members contains the names of the members of the club. There are
 * (currently) only 30 members allowed. 'members' holds
 * the integer how many 30min intervals the player was in the game within the last 21 days.
 * The value contains only the last calculated one and is updated as needed.
 * The login/logout times are drawn from the creation and remove of the
 * club object, the scabbard.
 * In a file for each player, every login and logout is recorded. Old entries
 * in this file are erased again (older than 21 days).
 * 
 */

/*
 * The index is the player name.
 *
 * The first element is the players last recorded age, second alignment,
 * third is the login array. 
 */

mapping members = ([ ]);

#define M_AGE   0
#define M_ALIGN 1
#define M_LOGIN 2
#define M_SIZE  3

/*
 * Simple flags 
 */
#define F_LOGIN  1
#define F_LOGOUT 2


/* Prototypes */
public int query_supporter_login_time(mixed player);
int query_restore_scabbard(object player);
int restore_scabbard(object player);


/*
* Function name: initialize_the_club
* Description:   reinitializes the club after a reboot
* Arguments:     none
* Returns:       void
*/
void
initialize_the_club()
{
    setuid();
    seteuid(getuid());
    
    members = ([ ]);
    members = restore_map(MEMBER_FILE);

    KRLINK->register_restorable("pkc_scabbard", 
        "The Prestigious Knights' Club Scabbard", 
        query_restore_scabbard, restore_scabbard);
}

public void
save()
{
    save_map(members, MEMBER_FILE);
}


/*
* Function name: create_room
* Description:   creates the room
* Arguments:     none
* Returns:       void
*/
void
create_room()
{
    int tm;

    set_short("Club Master Room");
    set_long("This is the knights club master room. This room handles calculations " +
	"of alignment and logintimes for the clubmembers. You can do " +
	"'qclub' and 'rank' " +
	"for infos on the club. To update all scabbards after a modification, " +
	"'update club_obj', 'load club_obj' to check if it works and then " +
	"'Call here update_club'. 'clubexpel <name> <reason>' expels a member from the club.\n");;

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(CLUB + "club3","down");

    add_prop(ROOM_I_NO_CLEANUP, 1);
    initialize_the_club();
}

/*
 * NEVER CALL THIS UNLESS YOU KNOW WHAT YOU ARE DOING
 */
public void
import_old_data()
{
    mapping map;
    string *idx;
    string str, *row;
    int i, k, y, z, tmp, bar;

    map = restore_map("/d/Krynn/solamn/palan/club/log/_member_file");
    idx = m_indexes(map["members"]);

    k = sizeof(idx);
    i = -1;

    while (++i < k)
    {
	members[idx[i]] = ({ map["members"][idx[i]], 
				 map["align"][idx[i]], ({ }) });
	
	str = read_file("/d/Krynn/solamn/palan/club/log/" + idx[i]);
	row = explode(str, "\n");

	z = sizeof(row);
	y = -1;

	while (++y < z)
	{
	    if (sscanf(row[y], "LIN,%d,%d", tmp, bar) == 2)
	    {
		members[idx[i]][M_LOGIN] += ({ F_LOGIN, tmp, bar });
	    }
	    if (sscanf(row[y], "OUT,%d,%d", tmp, bar) == 2)
	    {
		members[idx[i]][M_LOGIN] += ({ F_LOGOUT, tmp, bar });
	    }
	}
	write("Imported: " + idx[i] + "\n");
    }
}

/*
* Function name: init
* Description:   define the club commands for wizards.
*/
void
init()
{
    ::init();
    ADA("clubexpel");
    ADD("query_club","qclub");
    ADD("display_ranking_list","rank");
}

public void
mark_supporter_login(object who)
{
    string name;
    if (who->query_wiz_level())
	return;


    name = who->query_real_name();

    /* If you are not in the members array you are a fraud ;) */
    if (!members[name])
	return;

    members[name][M_AGE] = who->query_age();
    members[name][M_ALIGN] = who->query_alignment() / 50;
    members[name][M_LOGIN] += ({ F_LOGIN, time(), who->query_age() });
}

public void
mark_supporter_logout(object who)
{
    string name;

    name = who->query_real_name();

    if (!members[name])
	return;
    
    members[name][M_LOGIN] += ({ F_LOGOUT, time(), who->query_age() });
    
    save();
}

/*
 * Function name: query_the_player_alignment
 * Description:   get the alingment of who
 * Arguments:     object who - the player to get the
 *                alignment from.
 * Returns:       alignment of 'who' (int)
 */
int
query_supporter_alignment(mixed who)
{
    if (!who)
	return 0;
    
    if (objectp(who))
	return (who->query_alignment()) / 50;
    
    if (stringp(who) && members[who])
	return members[who][M_ALIGN];
    
    return 0;
}

/*
 * Function name: query_master_value
 * Description:   calculate the clubvalue for the player
 * Arguments:     object player
 * Returns:       the clubvalue (int)
 */
public int
query_master_value(mixed player)
{
    /* the login value is much more important than the alignment...*/
    return (query_supporter_login_time(player) / 2) * 
	query_supporter_alignment(player);
}


/*
* Function name: query_supporter_login_value
* Description:   calculate the total login time of player 
*                within the last TWENTY_ONE_DAYS.
* Arguments:     string player, mixed who - player object if
*                player is logged in.
* Returns:       the login time (int)
*/
public int
query_supporter_login_time(mixed player)
{
    string name;
    mixed arr;
    int i, k, interval;
    int last_age, first_age; 

    if (objectp(player))
    {
	name = player->query_real_name();
	if (!members[name])
	    return 0;

	members[name][M_AGE] = player->query_age();
	members[name][M_ALIGN] = player->query_alignment() / 50;
    }
    else if (stringp(player))
    {
	name = player;
	if (!members[name])
	    return 0;
    }
    
    last_age = members[name][M_AGE];

    arr = members[name][M_LOGIN];
    k = sizeof(arr);
    
    if (!k)
	return 0;
    
    while (k)
    {
	/* Is the login info up-to-date enough? */
	if (arr[1] > (time() - TWENTY_ONE_DAYS))
	{
	    if (arr[0] == F_LOGIN)
	    {
		first_age = arr[2];
		break;
	    }
	    
	    if (arr[0] == F_LOGOUT)
	    {
		/* This is a bit special, we count partial time before 
		 * the logout */
		interval = (arr[1] - (time() - TWENTY_ONE_DAYS));
		/* No logins can be more than two days
		 * This really indicates that the login part is missing */
		if (interval > (86400*2))
		    interval = 0;
		
		first_age = arr[2] - (interval / 2);
		
		break;
	    }
	} else {
	    arr = arr[3..];
	    k -= 3;
	}
    }
    
    /* Player might have been in long enough to expire his login entry */
    if (!objectp(player) && !first_age)
	first_age = last_age - (TWENTY_ONE_DAYS / 2);
    
    members[name][M_LOGIN] = arr;
    
    if (first_age <= 0 || first_age > last_age)
	first_age = last_age;
    
    return (last_age - first_age) * 2 / SEC_PER_30_MIN;
}

/*
 *
 */
public void
modify_member_age(string name, int i)
{
    int size;

    if (!members[name])
        return;
    
    size = sizeof(members[name][M_LOGIN]);
    if (size < 3) 
        return 0;
    
    members[name][M_LOGIN][2] = i;
    
    write_file(CLUBLOG, name + " " + ctime(time())[4..15] + ": " + 
        this_interactive()->query_real_name() + " Patched " +
        " to " + members[name][M_AGE]  + "\n");
}

/*
 * Function name: expel_from_club
 * Description:   expels player from the club for <reason> reason.
 * Arguments:     mixed player, string reason
 * Returns:       void
 */
public void
expel_from_club(mixed player, string reason)
{
    string name;
    object scab;

    if (!player)
	return;

    if (objectp(player))
    {
	name = player->query_real_name();
    } 

    if (stringp(player))
    {
	name = player;
	player = find_player(name);
    } 

    /* We only give messages if the player actually has a scabbard */
    if (objectp(player) && (scab = IS_CLUB_MEMBER(player)))
    {
	if (!reason)
	    player->catch_msg("You haven't followed the ways of Paladine " + 
		"for too long! You are expelled from the Prestigious " + 
		"Knights' Club.\n");
	else
	    player->catch_msg(reason);	
	scab->remove_object();
    }
    
    members = m_delete(members, name);
    write_file(CLUBLOG, name + " " + ctime(time())[4..15] + " Expelled.\n");
}
    
/*
* Function name: clubexpel
* Description:   allows a (Krynn) wizard or any Liege or higher 
*                to expel a member from the club manually.
* Arguments:     string name - name of the player AND reason, divided by a space
* Returns:       1 if successfull, 0 if not.
*/
int
clubexpel(string str)
{
    string name, reason; 


    if ((SECURITY)->query_wiz_dom(TP->query_real_name()) != "Krynn" &&
	(SECURITY)->query_wiz_rank(TP->query_real_name()) < WIZ_LORD)
	return 0;

    notify_fail("Expel <whom> <why>?\n");

    if (!stringp(str))
	return 0;

    if (sscanf(str, "%s %s", name, reason) == 2)
    {
	write("Attempting to expel: " + name + " due to '" + reason + "'\n");
	expel_from_club(name, reason);
    }
    return 1;
}

/*
* Function name: is_able_to_join
* Description:   determines whether it is possible for a player
*                to join or not. If so performs the joining.
* Arguments:     object player - player who wants to join.
* Returns:       error message if failure or 0 if success.
*/
string
is_not_able_to_join(object player)
{
    int i, k;
    string name, str, dummy;
    object scab;

    if (!objectp(player))
	return "Very strange bug.";

    setuid();
    seteuid(getuid(TO));

    if (IS_CLUB_MEMBER(player))
	return "You are already a member!";

    name = player->query_real_name();

    if (members[name])
    {
        return "You are already a member. Use 'rejoin club' if you have " + 
            "lost the scabbard/holster.";
    }

    if (player->query_wiz_level())
    {
	(SCABBARD)->load_me();
	scab = clone_object(SCABBARD);
	if (scab->move(player))
	    return "Hmm, strange. You were not able to join.";
	write_file(CLUBLOG, name + " " + 
	    ctime(time())[4..15] + " Joined.\n");
	return "You have joined as an honorary member.";
    }
    
    if (player->query_average_stat() < 40)
	return "You need to get much better still to be able to join this " + 
	    "club.";
    if (player->query_average_stat() < 60)
	return "You need to get a little better still to be able to join " + 
	    "this club.";
    if (player->query_alignment() < 300)
	return "You need to follow the ways of Paladine further to be able " + 
	    "to join this club.";

    if (m_sizeof(members) >= CLUB_LIMIT)
	for(i = 0, k = m_sizeof(members); i < k; i++)
	{
	    dummy = (m_indices(members))[i];
	    if (!find_player(dummy) && 
		query_supporter_login_time(dummy) <= MIN_REQUIRE)
	    {
		members = m_delete(members, dummy);
		write_file(CLUBLOG, dummy + " " + ctime(time())[4..15] + 
		    " Expelled (Join).\n");
		break;
	    }
	}

    if (m_sizeof(members) >= CLUB_LIMIT)
	return "I'm sorry, but the club is full. Every now and then a " + 
	    "spot may become vacated, though.";

    (SCABBARD)->load_me();
    scab = clone_object(SCABBARD);
    
    members[name] = allocate(M_SIZE);
    members[name][M_AGE] = player->query_age();
    members[name][M_ALIGN] = player->query_alignment() / 50;
    members[name][M_LOGIN] = ({ });

    if (scab->move(player))
	return "You unsuccessfully tried to join the club. " + 
	    "Please leave a bug report.";
    
    write_file(CLUBLOG, name + " " + 
	ctime(time())[4..15] + " Joined.\n");
    save();
    return 0;
}


/*
* Function name: update_club
* Description:   find every active supporter of the club and update his/her scabbard.
* Arguments:     none
* Returns:       void
*/
void
update_club()
{
    int i;
    object dummy;
    for(i = 0; i < m_sizeof(members); i++)
    {
	tell_room(TO, (m_indices(members))[i]);
	dummy = find_living((m_indices(members))[i]);
	if (dummy)
	    (IS_CLUB_MEMBER(dummy))->update_me();
    }
}

/*
* Function name: query_club
* Description:   lets wizzes check on the state of the club members. 
*                Displays a list with numbers for each member.
* Arguments:     none
* Returns:       void
*/
void
query_club()
{
    int i,j;
    mixed k;
    object who;
    string the_name;
    write("Stored list of member values:\n" + 
	"NAME                          VALUE          ALIGN\n\n");
    for(i = 0; i < m_sizeof(members); i++)
    {
	the_name = (m_indices(members))[i];
	who = find_player(the_name);
	j = query_supporter_login_time(who);
	if (who)
	    k = "* " + query_supporter_alignment(who);
	else
	    k = query_supporter_alignment(the_name);
	write(sprintf("%-20s%15d%15s\n", the_name, j, "" + k));
    }
  
}

/*
* Function name: lex_greater_than
* Description:   used to sort the member array from best to least member
* Arguments:     string str1 and str2.
* Returns:       1 if str1<str2; 0 if str1==str2; -1 otherwise
*/
int
lex_greater_than(string str1, string str2)
{
    if (str1 < str2)
	return 1;
    if (str1 == str2)
	return 0;
    return -1;
}

/* Function name: get_supporter_title
 * Description:   gives the club title of the supporter
 * Arguments:     the player object
 * Returns:       string - the title
 */
string
get_supporter_title(mixed player)
{
    int value;
    string how;

    if (!player)
	return "";
    if (objectp(player) && player->query_wiz_level())
	how = "Honorary ";
    else
    { 
	how = "";
	value = query_master_value(player);
	if (value > 5300)
	    how += "Incredibly Prestigious ";
	else if (value > 5200)
	    how += "Most Prestigious ";
	else if (value > 5000)
	    how += "Highly Prestigious ";
	else if (value > 4800)
	    how += "Very Prestigious ";
	else if (value > 4600)
	    how += "Prestigious ";
	else if (value > 4200)
	    how += "Most Exalted ";
	else if (value > 3800)
	    how += "Exalted ";
	else if (value > 3400)
	    how += "Most Glorified ";
	else if (value > 3000)
	    how += "Highly Glorified ";
	else if (value > 2600)
	    how += "Glorified ";
	else if (value > 2200)
	    how += "Most Respectable ";
	else if (value > 1800)
	    how += "Very Respectable ";
	else if (value > 1400)
	    how += "Respectable ";
	else if (value > 900)
	    how += "Most Recognized ";
	else if (value > 400)
	    how += "Recognized ";
	else if (value > 5)
	    how += "";
	else if (value > -1)
	    how += "Unworthy ";
	else
	    how += "Damned ";
    }
  
    how += "Supporter ";
    return how;
}

int
member_sort(string m1, string m2, mapping map)
{
    if (map[m1] < map[m2])
	return 1;
    else if (map[m1] > map[m2])
	return -1;
    return 0;
}

/*
* Function name: get_ranking_list_display
* Description:   compiles the list the players see on the surface in the
*                private club room. Supporters are ranked according to 
*                their title and clubvalues
* Arguments:     none
* Returns:       string - the list of the ranking.
*/
string
get_ranking_list_display()
{
    int i, k;
    string *idx, ret;
    object player;
    mapping m;

    ret = "";

    /* Sort real good */    
    idx = m_indexes(members);
    m = mkmapping(idx, map(idx, query_master_value));

    idx = sort_array(m_indexes(members), &member_sort(, , m));

    k = sizeof(idx);
    i = -1;
    while (++i < k)
    {
	player = find_player(idx[i]);
	if (objectp(player))
	    query_master_value(player);
	ret += sprintf("%15s the %s\n", 
	    capitalize(idx[i]) + (objectp(player) ? "*" : ""), 
	    get_supporter_title(idx[i]));
	
    }

    if (!k)
	ret = "The Club currently has no Supporters.";
    return ret;
}


/*
* Function name: break_faith_with_the_club
* Description:   performs the leaving of the club.
* Arguments:     object player - who wants to leave
* Returns:       string - errormessage if failed to leave the club,
                          0 if successfully left the club
*/
string
break_faith_with_the_club(object player)
{
    string nam;
    object scab;
    if (!player)
	return "Very strange bug.";
    scab = IS_CLUB_MEMBER(player);

    seteuid(getuid(TO));
    if (!scab)
	return "You are not a member!";
    
    tell_room(E(player), QCTNAME(player) + 
	" has just LEFT the Prestigious Knights' Club.\n", player);
    tell_object(player, "You have just left the Prestigious Knights' Club.\n");

    scab->remove_object();
    if (player->query_wiz_level())
	return 0;

    nam = player->query_real_name();
    members = m_delete(members, nam);
    
    write_file(CLUBLOG, player->query_real_name() + " " + ctime(time())[4..15]
	+ " Left.\n");

    write_file(LEAVELOG, player->query_real_name() + "\n");
    return 0;
}

/*
* Function name: is_no_longer_a_member
* Description:   checks if a member is still a member or was expelled during the absence
*                didn't log in for too long / or was expelled by a wizard.
* Arguments:     object player - the player to check.
* Returns:       int 1 if not a member anymore,
*                    0 if everything is ok.
*/
int
is_no_longer_a_member(object player)
{
    string who = player->query_real_name();
    
    if (player->query_wiz_level())
	return 0;
    if (!pointerp(members[who]))
	return 1;
    else
	return 0;
}

/*
* Function name: remove_wizard_from_member_list
* Description:   removes a player from 'members' after he turned wiz so the spot is free again.
* Arguments:     the wizard
* Returns:       void
*/
void
remove_wizard_from_member_list(object player)
{
    if (!player)
	return;

    if (!members[player->query_real_name()])
	return;
    
    members = m_delete(members, player->query_real_name());
    
    write_file(CLUBLOG, player->query_real_name() + " " + ctime(time())[4..15] + " Wizzed.\n");
}

/*
* Function name: display_ranking_list
* Description:   outputs the ranking list of the members
* Arguments:     none
* Returns:       always 1 (command recognized)
*/
int
display_ranking_list()
{
    write("* means active:\n");
    write(get_ranking_list_display());
    return 1;
}

/*
 * Support for the membership reclamation.
 */
int
query_restore_scabbard(object player)
{
    if (is_no_longer_a_member(player) || IS_CLUB_MEMBER(player))
    {
        return 0;
    }
    
    return 1;
}

int
restore_scabbard(object player)
{
    object ob;

    if (!query_restore_scabbard(player))
    {
        return 0;
    }
    
    ob = clone_object(SCABBARD);    
    if (ob->move(player, 1))
    {
        write_file(CLUBLOG, player->query_real_name() + " " + 
            ctime(time())[4..15] + " Failed to reclaim the scabbard.\n");
        return 0;
    }
    
    write_file(CLUBLOG, player->query_real_name() + " " + 
        ctime(time())[4..15] + " Reclaimed the scabbard.\n");
    return 1;
}
