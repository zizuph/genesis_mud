 /* NPC whose kills are logged, with the date, as well as all the players
    in the team who killed him (and their stat average) being noted.
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit STD_MONSTER;

//global variables
string Log_File = ""; //the file to which we will log

/*
  Function name: log_my_kills
  Description:   Logs the deaths of an npc: information about each player in
                 the team which killed the npc (guilds + stat average) is
		 recoded, along with the time of the kill.
  Arguments:     string file - the file to log to
  Note:          The npc must be given rights to the log file, typically
                 though use of setuid; seteuid(getuid()); in create_monster().
*/
void
log_my_kills(string file)
{
    Log_File = file;
}

public void
do_die(object killer)
{
    object* team; //the set of players who helped kill the npc
    object* enemies; // the set of enemies of the NPC at death
    string log; //the log to be written
    int i; //loop index
   
    team = ({});

    if (strlen(Log_File))
    {
	enemies = query_enemy(-1);
	// select enemies who are either in the room, or in the team of the
	// killer
	for (i = 0; i < sizeof(enemies); i++)
	{
	    if ((environment(enemies[i]) == environment(TO)) ||
		(member_array(enemies[i], killer->query_team_others()) != -1))
	    {
		team += ({enemies[i]});
	    }
	}

	log = "";

// print the name, occ + lay guild and stat average of each player who helped
// kill the npc
	for (i = 0; i < sizeof(team); i++)
	{
	    log += team[i]->query_met_name() + " (" + team[i]->
		query_guild_name_occ() + ", " + team[i]->
		query_guild_name_lay() + ", " + team[i]->query_average_stat() +
		")\n";
	}

	//add the time
	log += ctime(time()) + "\n\n";

	write_file(Log_File, log);
    }

    ::do_die(killer);
}






