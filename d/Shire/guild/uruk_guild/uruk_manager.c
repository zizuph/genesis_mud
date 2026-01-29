/* 
 *Managing room for the uruk guild, both branches
 *Altrus, December 2005
*/
#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "/d/Shire/guild/uruk_guild/uruk.h"
#include "/d/Shire/guild/uruk_guild/titles.h"

mapping members = (["mordor" : ({}), "isengard" : ({}) ]);

void create_shire_room()
{
    set_short("Uruk-hai Manager Room");
    set_long("This place manages the uruk-hai guilds.\n");
    seteuid(getuid());
    
    members = restore_map(URUKGLD_DIR + "uruks");
}

/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());
   
   if (file_size(URUK_RACE_GUILD_LOG) > LOG_SIZE)
      {
      rename(URUK_RACE_GUILD_LOG, (URUK_RACE_GUILD_LOG + ".old"));
   }
   
   write_file(URUK_RACE_GUILD_LOG, text);
}

/*
* Function name: remove_player_changed_race
* Description  : Whenever a member changes his/her race (s)he is
*                mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void remove_player_changed_race(object tp)
{
   tp->catch_msg("\nYour body, being not of elven-kind, can no longer be sustained by dark sorcery in the form of an orc. Therefore you do not " +
      "belong in the " + URUK_RACE_GUILD_NAME + " any more. You " +
      "are being expelled from the guild.\n");
   
   //lower_skill(tp);
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
      tp->query_race_name() + ") was kicked out.\n");
}

/*
* Function name: remove_player_low_alignment
* Description  : Whenever the alignment of a player is too low, the player
*                is mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void remove_player_high_alignment(object tp)
{
   tp->catch_msg("\nSo you are no longer devoted to bringing about the subjegation of the Free Peoples? Then there is no place for you in the " + URUK_RACE_GUILD_NAME + " any more. " +
      "You are being expelled from the guild.\n");
   
   //lower_skill(tp);
   
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
      tp->query_alignment() + ") was kicked out.\n");
}

/* Function name: query_uruk_type
 * Description  : Returns the type of uruk
 * Args : string name - the name of the person to give type on
 * Returns  : 0 - Not an uruk
 *                1 - uruk of Mordor
 *                2 - uruk of Isengard
 */
public int
query_uruk_type(string name)
{
    if (!strlen(name))
        return 0;

    if(member_array(name, members["mordor"]) != -1)
        return URUK_MORDOR;
    else if(member_array(name, members["isengard"]) != -1)
        return URUK_ISENGARD;
    else
        return 0;
}

/* Function name: query_uruk_rank
 * Description  : Returns the rank of uruk, based on the uruk's branch
 * Args : string name - the name of the person to assign the rank
 *          int level - the assigned level, for determining the appropriate rank
 * Returns  : the rank of the uruk, based on a query of the branch
 *                "No-rank", should never assign this
 */
public string
query_uruk_rank(string name, int level)
{
    //Mordor rank
    if(query_uruk_type(name) == 1)
    {
	return M_TITLES[level];
    }
    
    //Isengard rank
    else if(query_uruk_type(name) == 2)
    {
	return I_TITLES[level];    
    }

    //Shouldn't ever get here, but you never know ;)
    else
	return "No-rank";
}

/* Function name: query_uruk_branch
 * Description  : Returns the appropriate branch for the uruk
 * Args : string name - the name of the person to assign the branch
 * Returns  : "of Mordor" or "of the Red Eye" for Mordor uruks, rank dependant
 *                "of Isengard" or "of the White Hand" for Isengard uruks, rank dependant
 *                "of Nowhere-land", shouldn't ever assign
 */
public string
query_uruk_branch(string name, int level)
{
    string rank;
	
    //Mordor uruk
    if(query_uruk_type(name) == 1)
    {
	rank = query_uruk_rank(name, level);
	
	if(rank == "Brutal Slavedriver" | rank == "Sadistic Slavedriver" | rank == "Cruel Taskmaster" | rank == "Merciless Taskmaster")
	{
	    return "of the Red Eye";
	}
	
	else
	    return "of Mordor";
    }
	
    //Isengard uruk
    else if(query_uruk_type(name) == 2)
    {
	rank = query_uruk_rank(name, level);
	
	if(rank == "Blooded Warrior" | rank == "Skilled Warrior" | rank == "Raging Berserker" | rank == "Indomitable Berserker")
	{
	    return "of the White Hand";
	}
	
	else
	    return "of Isengard";
    }
	
	//Shouldn't ever get this far, but hey, you never know
	else
	    return "of Nowhere-land";
}

/*
 * Function name: query_uruk_title
 * Uruk guild specific function for determining the title
 * called from the shadow to assign the right title
 * Args: string name- name of the player to return the title
 * Returns: title of the player (rank + branch)
*/
public string
query_uruk_title(string name, int level)
{
    return (query_uruk_rank(name, level) + " " + query_uruk_branch(name, level));
}

public void
add_uruk(string name, string branch)
{
    if(!pointerp(members[branch])) 
    {
	members[branch] = ({ });
    }

    members[branch] += ({ name });
    save_map(members, URUKGLD_DIR + "uruks");
}

public void
remove_uruk(string name)
{
	if(query_uruk_type(name) == URUK_MORDOR)
		members["mordor"] -= ({ name });
	
	if(query_uruk_type(name) == URUK_ISENGARD)
		members["isengard"] -= ({ name });
		
	save_map(members, URUKGLD_DIR + "uruks");
}
	