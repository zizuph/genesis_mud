/*
 *    server.c  
 *
 * Guild server for the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */

#include "../defs.h"
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>
#include <files.h>
inherit "/std/room";

/* Global variables */
string *gMembers = ({});
mapping gAges = ([]);
mapping gBoard_notify = ([]);
int gBoard_last_changed = 0;

/* Prototypes */
int  query_member(string name);
void cleanup_memberlist();

void
create_room()
{
    setuid();
    seteuid(getuid());
    set_short("The server");
    set_long("In the server room.\n");
    restore_object(SERVER_SAVE);
    cleanup_memberlist();
}

/* MEMBER MANAGEMENT */

/*
 * Function name: query_member
 * Description  : Queries if a name is on the members list.
 * Arguments    : string name - the name to query
 */
int
query_member(string name)
{
    return (member_array(name, gMembers) != -1);
}

/*
 * Function name: add_member
 * Description  : Adds a name to the members list.
 * Arguments    : string name - the name to add.
 */
void
add_member(string name)
{
    if (!query_member(name))
    {
        gMembers += ({ name });
	save_object(SERVER_SAVE);
	DEBUG("Successfully added '"+name+"' to the member list.\n");
    }
    else
	DEBUG("Failed to add '"+name+"' to the member list.\n");

}

/*
 * Function name: remove_member
 * Description  : Removes a name from the member list.
 * Arguments    : string name - the name to remove
 */
int
remove_member(string name)
{
    if (query_member(name))
    {
        gMembers -= ({ name });
        
	if (gAges[name])
        {
	    gAges = m_delete(gAges, name);
        }
        
	save_object(SERVER_SAVE);
	DEBUG("Successfully removed '"+name+"' from the member list.\n");
    }
    else
	DEBUG("Failed to remove '"+name+"' from the member list.\n");
}

/*
 * Function name: cleanup_list
 * Description  : Remove names of non-existant players from member list.
 */
void
cleanup_memberlist()
{
    int i, size;

    for (i = sizeof(gMembers) - 1; i >= 0; i--)
    {
        if (!SECURITY->exist_player(gMembers[i]))
	    remove_member(gMembers[i]);
    }
}


void
register_age(object player)
{
    string name = player->query_real_name();
    int age = player->query_age();

    if (!gAges[name])
    {
        gAges += ([ name : age ]);
	save_object(SERVER_SAVE);
    }
}

int
query_age_hours(object player)
{
    int join_hours, current_hours;
    string name = player->query_real_name();

    if (gAges[name])
    {
        current_hours = ((player->query_age() / 3600) * 2);
	join_hours = ((gAges[name] / 3600) * 2);

	return (current_hours - join_hours);
    }
	return 0;
}

void
register_board_change()
{
    gBoard_last_changed	= time();
    save_object(SERVER_SAVE);  
}

int
query_board_change()
{
    return gBoard_last_changed;
}

void
register_board_notify(object player)
{
    string name = player->query_real_name();
    
    if (!query_member(name))
        return;
    
    if (gBoard_notify[name])
    {
	gBoard_notify[name] = time();	
    }
    else
        gBoard_notify += ([ name : time() ]);
    
    save_object(SERVER_SAVE);    
}

int
query_board_notify(object player)
{
    string name = player->query_real_name();
    
    if (gBoard_notify[name])
    {
	return gBoard_notify[name];
    }
    else
        return 0;    
}

/* MISC FUNCTIONS */

/* Function name: query_amazon_race_title
 * Description  : Handles the guild title
 * Returns      : string - the title
 */
public string
query_amazon_race_title(object who)
{
    int race_stat, rank, age, num_titles;
    age = query_age_hours(who);
    race_stat = who->query_stat(SS_RACE);
    num_titles = sizeof(TITLES);
    age = (age / 24);
    
    rank = min(max(0, ((num_titles - 1) * (race_stat)) / 120), num_titles - 1);

    if (rank < 0)
        rank=0;	
    
    rank += age;
    
    if (rank >= num_titles)
        rank = num_titles - 1;
        
    return TITLES[rank]+" Amazon of the Silent Forest";
 /*   int ranking, age;
    float race_stat, num_titles, var1, var2;
    age = query_age_hours(who);
    age = (((age / 24) * 100) / MAX_AGE);
    race_stat = itof((who->query_stat(SS_RACE) * 100) / MAX_STAT);    
    num_titles = itof(sizeof(TITLES));
    
    var1 = ((num_titles / 125.0) * (race_stat) + (num_titles - 12.5)/12.5);
    var2 = (3.14 * itof(1^age));   

    ranking = ftoi(0.67 * var1  +  (1.0 - 0.67) * var2);
    ranking = min(max(0, ranking), sizeof(TITLES) - 1);
    return TITLES[ranking]+" Amazon of the Silent Forest";
    */
}

/*
 * Function name: sort_ranks
 * Description  : Sorts the members list.
 */
int
sort_ranks(object user1, object user2)
{
    string name1  = user1->query_name(),
	   name2  = user2->query_name();
    int    value1 = user1->query_stat(SS_RACE),
           value2 = user2->query_stat(SS_RACE);

    if (value1 != value2)
    {
	/* sort by ranks */
        return value1 - value2; 
    }

    /* the ranks are same, sort by name */

    if (name1 > name2)
    {
        return 1;
    }

    if (name1 < name2)
    {
        return -1;
    }
    /* the names are same */
    return 0; 

}

/*
 * Function name: list_members
 * Description  : List members currently online.
 */
void
list_members()
{
    int i, size;
    object who, *GMs, *players, *LDplayers, *unsorted, *LDunsorted;

    players = users();
    LDplayers = all_inventory(find_object("/d/Genesis/obj/statue"));
    unsorted = ({});
    LDunsorted = ({});
    GMs = ({});

    for (i = sizeof(GUILDMASTERS) - 1; i >= 0; i--)
    {
        if (find_player(lower_case(GUILDMASTERS[i])))
            write(capitalize(GUILDMASTERS[i])+" the Guildmaster.\n");
    }
	
/* Adds the user to the unsorted list if 
   the user is a member, but only mortals. */
    for (i = sizeof(players) - 1;   i >= 0; i--)
    {
        who = players[i];
	if (who->query_wiz_level())
	    continue;
        if (IS_MEMBER(who))
            unsorted += ({ who });        
    }

/* Adds the user to the LDunsorted list if 
   the user is a linkdead member, but only mortals. */
    for (i = sizeof(LDplayers) - 1; i >= 0; i--)
    {
        who = LDplayers[i];	
        if (who->query_wiz_level())
	    continue;   		
        if (IS_MEMBER(who))
        LDunsorted += ({ who });
    }

    unsorted   = sort_array(unsorted, sort_ranks);
    LDunsorted = sort_array(LDunsorted, sort_ranks);

/* Writes the names on the screen, starting with the
   highest ranked member. */
    for (i = sizeof(unsorted) - 1; i >= 0; i--)
    {
        who = unsorted[i];
        write(who->query_name()+" the "+
          who->query_guild_title_race()+".\n");
    }

    for (i = sizeof(LDunsorted) - 1; i >= 0; i--)
    {
        who = LDunsorted[i];
        write("* "+who->query_name()+" the "+
          who->query_guild_title_race()+".\n");
    }

}

int
initiate_member(object who)
{
    string name  = who->query_real_name();

    add_member(name);  
    return 1; 
}

void
leave_amazons(object who, mixed reason = "")
{
	object token;

    setuid();
    seteuid(getuid());
    who->remove_cmdsoul(SOUL);
    who->update_hooks();
    who->clear_guild_stat(SS_RACE);
    who->remove_guild_race();
    remove_member(who->query_real_name());

	if (token = present("amazon_race_token", who))
		token->remove_object();
    
    if (who->query_default_start_location() == START_ROOM)
        who->set_default_start_location(who->query_def_start());
    
    who->catch_tell(reason);
    who->catch_tell("You are no longer an Amazon.\n");
    LOGFILE("join_leave", capitalize(who->query_real_name())+
      " left the guild "+(strlen(reason) ? "- "+reason: "\n")); 
}    
int
list_all()
{
    int i;
    string msg;
    
    if (sizeof(gMembers) < 1)
        write("No members listed.\n");
    else
    {
        write(" --------------- \n");
        write("| Members       |\n");
        write("|---------------|\n");
        for (i=0;i < sizeof(gMembers);i++)
        {  
            write(sprintf("| %-12s  |\n",
              capitalize(gMembers[i])));
        }
        write(" --------------- \n");
        
    }
    return 1;
}

/* This function is only used when checking if there
   are less then three members, if it is anyone can
   join the guild by asking the guardian for a token
*/
int
query_amount_members()
{
	if (sizeof(gMembers))
		return sizeof(gMembers);
	else
		return 0;
}
void
remove_object()
{
    save_object(SERVER_SAVE);
    ::remove_object();
}

void
init()
{
    ::init();
    add_action(list_all, "list");
}
