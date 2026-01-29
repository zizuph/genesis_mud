/*
 * Neidar admin object.
 * This will overwrite the bits currently being used so that
 * people can be removed from the guild leader position without
 * being online.
 *
 * Louie 2005
 */

/*
<CodeHelp> Mercade:
file_time(PLAYER_FILE(name) + ".o") gives the last logout time (in most cases).

<CodeHelp> Mercade: To get the last login time of the player call
query_login_time() in an active player or in the finger-player object when he
isn't logged in.

> <CodeHelp> Mercade nods. If you don't need the highest form of precision,
then use the logout time as described.

*/

#include "../guild.h"

inherit "/d/Krynn/std/room";

#include <ss_types.h>
#include <std.h> 
#include "/d/Krynn/common/defs.h"
//Ranks= 0 member, 1 council, 2 thane
#define N_RANK          0    /* int: The guild rank */
#define N_MESSAGES      1   /* *string: Messages to tell the player when they log in*/
#define N_SIZE          2   /* The size of the mapping */

// 22 days * 60sec * 60min * 24 hours = 1900800 secs (22 days)
#define MAX_LEADER_IDLE 1900800     
            

mapping members;

varargs int add_member(mixed who);
void save();
int set_guild_leader(mixed who);
void remove_idle_leader();
static string* met_players = ({});
static mapping player_to_time = ([]);

/** 
 * Create the room and restore props
 */
void
create_room()
{
    setuid();
    seteuid(getuid());
    
    members = ([ ]);

    restore_object(SAVE_PATH + "admin");
    set_alarm(15.0, 1800.0, &save());
}

void
save()
{
    save_object(SAVE_PATH + "admin");
}

void
remove_object()
{
    save();
}


varargs int
add_member(mixed who)
{
    string whoname;
    
    if (stringp(who))
        whoname = who;

    if (objectp(who))
        whoname = who->query_real_name();
    
    if (!members)
        members = ([]);

    if (!who || members[whoname])
        return 0;
    
    members[whoname] = allocate(N_SIZE);
    members[whoname][N_MESSAGES] =  ({ });
    members[whoname][N_RANK] = 0;
    
    save();
    
    return 1;
}

public int
remove_member(mixed who)
{
     string whoname;

     if (stringp(who))
         whoname = who;

     if (objectp(who))
         whoname = who->query_real_name();

    if (!members)
        members = ([]);

     if (!members[whoname])
         return 0;
     
     members = m_delete(members, whoname);

     save();
     
     return 1;
}

public int
query_member(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();

    if (!members)
        members = ([]);
    
    return !!members[who];
}

//Is this person a leader?
int
query_guild_leader(mixed who)
{
    if (objectp(who)) {
        who = who->query_real_name();
    }

    if (!members)
        members = ([]);

    if (!members[who]) {
        return 0;
    }

    return (members[who][N_RANK] == 2);
    
}

//Remove the leader position from who
int
remove_guild_leader(mixed who)
{
    if (objectp(who)) {
        who = who->query_real_name();
    }

    if (!members)
        members = ([]);

    if (!members[who]) {
        return 0;
    }

    members = m_delete(members, who);

    save();

    return 1;
    
}

int
set_guild_leader(mixed who)
{
    if (objectp(who)) {
        who = who->query_real_name();
    }
    if (!members)
        members = ([]);

    if (!members[who]) {
        add_member(who);
    }

    members[who][N_RANK] = 2;

    save();
   
    return 1;       
    
}

//Try to become leader.  The only way to do this is if the existing leader
//fails..whatever edits.  In this case, not logging in for 22 days.
int
check_replace_leader(mixed who)
{
    if (objectp(who)) {
        who = who->query_real_name();
    }

    remove_idle_leader();

    mixed s = m_indexes(members);
    int i = sizeof(s);
    while (i--)
    {
        //If any non kings are left after calling remove_idle_leader,
        //return 0
        if (members[s[i]][N_RANK] == 2) {
            return 0;
        }
    }

    //No King, set the requesting person
    return set_guild_leader(who);

}

void
remove_idle_leader()
{
    //Check if any leader has logged in within 22 days
    // 60sec * 60min * 24 hours * 22 days = 1900800 secs
    int t = time() - MAX_LEADER_IDLE;

    if (!members)
        members = ([]);

    mixed s = m_indexes(members);

    int i = sizeof(s);

    while (i--)
    {
 
        //If the player is logged in, skip

        if (find_player(s[i]))
            continue;

        int j = file_time(PLAYER_FILE(s[i]) + ".o");

        //if there is a leader (rank 2) and they have not logged in within
        //the idle time allowed, remove them
        if (members[s[i]][N_RANK] == 2 && 
            (j < t) ) {

            remove_member(s[i]);
        }
    }

    save();
}

void
report_encounter(string player)
{
    if(player)
    {
        met_players -= ({player});
        met_players += ({player});
        m_delete(player_to_time, player);
        player_to_time += ([player : CLOCK->query_time_date_string()]);
    }
}

string
query_encounter_report()
{
    
    int report_length;
    int remaining_frame;
    string report = "";
    string met_player;
    
    report_length = sizeof(met_players);

    // We don't want a report if there is nothing to report.
    if(report_length < 1)
    {
        return "";
    }
    
    report += "**********************************************************************\n";
    report += "*             Report of people encountered while on duty             *\n";
    report += "*                                                                    *\n";


    for(int i = 0; i < report_length; i++)
    {
        met_player = met_players[i];
        report += "* " + met_player+", "+player_to_time[met_player];
        remaining_frame = 70 - 2 - 2 - strlen(met_player) - strlen(player_to_time[met_player]) - 1;
        for(int j = 0 ; j < remaining_frame; j++)
        {
            report += " ";
        }
        report += "*\n";
    }
    report += "*                                                                    *\n";
    report += "**********************************************************************\n";
    return report;
}
