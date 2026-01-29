/*
 *  /d/Gondor/clubs/nisse/manager.c
 *
 *  This room keeps track of and manages these variables:
 *
 *  mapping gNisse
 *  mapping gExpelled
 *  mapping gGraduate
 *
 *  Deagol, March 2003 (inspired by Alto's code)
 * 
 *  Changes: 
 *  Cotillion - 2018-10-31
 *  - Fixed purge code
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <files.h>
#include <language.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "nisse_defs.h"

/*
 *  Global Variables
 */
mapping gNisse		= (["tan" : ({}), "light brown" : ({}),
			    "brown" : ({}), "deep brown" : ({}), 
			    "red" : ({}), "gold": ({}), "bronze" : ({}),
			   ]);
mapping gExpelled	= ([]);
mapping gGraduate	= ([]);

/*
 *  Prototypes
 */
void		startup_checks();
varargs int	send_message(object target, string text, string sender);
int		query_nisse_level(string name);
string		query_nisse_rank(string name);
string *	query_rank_members(int rank);
varargs int	query_nisse(string name, string rank);
int		add_nisse(string name, string rank);
int		remove_nisse(string name);
int		query_expelled_nisse(string name);
string *	query_to_be_expelled(string name);
int		add_to_be_expelled(string name, string reason);
int		remove_to_be_expelled(string name);

void
create_room()
{
    ::create_room();

    set_short("Nisse Club Manager Room");
    set_long("Here is where the Nisse club is managed.\n");

    seteuid(getuid());

    restore_object(MASTER);
    set_alarm(5.0, 0.0, &startup_checks());
}

/*
 * Function:    query_player_inactive
 * Description: Checks to see if a player is inactive for longer than a
 *              set amount of time (90 days). If so, they should be
 *              expelled from the guild.
 */
public int
query_player_inactive(string name)
{
    if (!strlen(name))
    {
        return 0;
    }
    
    name = lower_case(name);
    if (objectp(find_player(name)) || !SECURITY->exist_player(name))
    {
        // Player is in the game. Obviously active.
        return 0;
    }

    object player;
    int bInactive = 0;
    if (objectp(player = SECURITY->finger_player(name)))
    {
        int last_login_time = player->query_login_time();
        // 90 days * 87600 seconds/day = 7,776,000 seconds
        if ((time() - player->query_login_time()) > 7776000)
        {
            // Player hasn't logged in within the last 90 days.
            bInactive = 1;
        }
        player->remove_object();
    }
    return bInactive;
}

/*
 *  Function name: startup_checks
 *  Description  : Cleans up non-existant players
 */
void
startup_checks()
{
    int		i, j;
    int		size;
    string	*player_list;
    string	*rank_list;

    /* Make an array of all the ranks. */
    rank_list = m_indexes(gNisse);

    for (i = sizeof(rank_list) - 1; i >= 0; i--)
    {
        /* Get a list of the players in this rank. */
        player_list = gNisse[rank_list[i]];

        /* Check for non-existant Nisse and remove them. */
        j = -1;
        while(++j < sizeof(player_list))
        {
            /* Remove from list if Nisse no longer exists. */
            if (!SECURITY->exist_player(gNisse[rank_list[i]][j]))
            {
                remove_nisse(gNisse[rank_list[i]][j]);
            }
            else if (!query_to_be_expelled(gNisse[rank_list[i]][j])
                     && query_player_inactive(gNisse[rank_list[i]][j]))
            {
                add_to_be_expelled(gNisse[rank_list[i]][j], "expelled for being inactive too long");
            }
        }
    }
}

/* 
 *  Function name: send_message
 *  Description  : Sends a message to a Nisse
 *  Arguments    : object target - who to send the message from
 *                 string text   - What the message says
 *                 string sender - (optional) Who sent the message,
 *                                 default: Deagol
 *  Returns      : 1/0 success/failure
 */
varargs int
send_message(object target, string text, string sender)
{
    object note;

    if (!objectp(target) || !strlen(text))
    {
        return 0;
    }

    if (!strlen(sender))
    {
        sender = "Deagol";
    }

    target->catch_tell("Thunder and flash! You feel you have been given " +
        "a message from " + CAP(sender) + ".\n");

    note = clone_object(NISSE_OBJ_DIR + "message");
    note->set_message(text);
    note->set_sender(sender);
    note->move(target, 1);
    return 1;
}

/*
 *  Function name: cycle_file
 *  Description  : Cycles a file so that it does not get too big.
 *  Arguments    : string filename - the name of the file
 *                 int size - the number of bytes to preserve
 *  Returns      : 1 if successful, 0 if not
 */
private nomask int
cycle_file(string filename, int size)
{
    int filesize;

    /* To prevent any abuse. */
    if (filename[0..strlen(NISSE_DIR)-1] != NISSE_DIR)
    {
        return 0;
    }

    filesize = file_size(filename);

    /* File doesn't exist (-1), is a directory (-2) or is of 0 bytes */
    if (filesize == -1 || filesize == -2 || filesize == 0)
    {
        return 0;
    }

    if (size > filesize)
    {
        return 0;
    }

    rename(filename, filename + ".old");
    return 1;
}

/*
 *  Function name: rlog
 *  Description  : Log an action.
 *  Arguments    : string text - the text to log
 *  Returns      : 1 on success, 0 on failure
 */
int
rlog(string text)
{
    string *log_arr;

    if (!strlen(text))
    {
        return 0;
    }

    cycle_file(NISSE_LOG, LOG_SIZE);
    write_file(NISSE_LOG, ctime(time()) + ": " + text + "\n");
    return 1;
}

public string *
query_active_club_members()
{
    string * active_club_members = ({ });
    
    foreach (string rank, string * player_list : gNisse)
    {
        foreach (string player_name : player_list)
        {
            if (!query_expelled_nisse(player_name))
            {
                active_club_members += ({ player_name });
            }
        }
    }
    
    return active_club_members;
}

/*
 *  Function name: query_camp_fullness
 *  Description  : Counts club members.
 *  Returns      : int size - number of players
 */
int
query_camp_fullness()
{
    return sizeof(query_active_club_members());
}

/* 
 *  Function name: query_nisse_level
 *  Description  : Returns the colour (level) of member's birthmark
 *  Arguments    : string name - the name of the person to give status on
 *  Returns      : 0 - Not a Nisse at all
 *                 1 - tan
 *                 2 - light brown
 *                 3 - brown
 *                 4 - deep brown
 *                 5 - red
 *                 6 - gold
 *                 7 - bronze
 */
int
query_nisse_level(string name)
{
    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);

    if (member_array(name, gNisse["tan"]) != -1)
        return TAN_LEVEL;
    else if (member_array(name, gNisse["light brown"]) != -1)
        return LIGHT_BROWN_LEVEL;
    else if (member_array(name, gNisse["brown"]) != -1)
        return BROWN_LEVEL;
    else if (member_array(name, gNisse["deep brown"]) != -1)
        return DEEP_BROWN_LEVEL;
    else if (member_array(name, gNisse["red"]) != -1)
        return RED_LEVEL;
    else if (member_array(name, gNisse["gold"]) != -1)
        return GOLD_LEVEL;
    else if (member_array(name, gNisse["bronze"]) != -1)
        return BRONZE_LEVEL;
    else
        return 0;
}

/*
 *  Function name: query_nisse_rank
 *  Description  : Returns the string colour birthmark
 *  Arguments    : string name - the name of the person to give status on
 *  Returns      : tan, light brown, brown, deep brown, red, gold, bronze
 */
string
query_nisse_rank(string name)
{
    if (!strlen(name))
    {
        return "";
    }

    name = CAP(name);

    switch(query_nisse_level(name))
    {
    case TAN_LEVEL :
        return "tan";
    case LIGHT_BROWN_LEVEL :
        return "light brown";
    case BROWN_LEVEL :
        return "brown";
    case DEEP_BROWN_LEVEL :
        return "deep brown";
    case RED_LEVEL :
        return "red";
    case GOLD_LEVEL :
        return "gold";
    case BRONZE_LEVEL :
        return "bronze";
    default :
        return "";
    }
}

/*
 *  Function name: query_rank_members
 *  Description  : What players belong to this rank?
 *  Arguments    : int rank - the rank to check
 *                    0 = non_nisse
 *                    1 = tan
 *                    2 = light brown
 *                    3 = brown
 *                    4 = deep brown
 *                    5 = red
 *                    6 = gold
 *                    7 = bronze
 *  Returns      : an array of rank members
 */
string *
query_rank_members(int rank)
{
    if (!intp(rank))
    {
        return ({});
    }

    switch (rank)
    {
        case 0 :
            return ({});
        case 1 :
            return gNisse["tan"];
        case 2 :
            return gNisse["light brown"];
        case 3 :
            return gNisse["brown"];
        case 4 :
            return gNisse["deep brown"];
        case 5 :
            return gNisse["red"];
        case 6 :
            return gNisse["gold"];
        case 7 :
            return gNisse["bronze"];
        default :
            return ({});
    }
}

/*
 *  Function name: query_nisse
 *  Description  : Returns 1 if the person is a Nisse 
 *  Arguments    : string name - the name to check
 *                 string rank - the rank to check against (optional)
 *  Returns      : 1 if matches, 0 if not
 */
varargs int
query_nisse(string name, string rank = "")
{
    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);

    if (!strlen(rank))
    {
        if (query_nisse_level(name))
        {
            return 1;
        }

        return 0;
    }

    if (rank == query_nisse_rank(name))
    {
        return 1;
    }

    return 0;
}

/*
 *  Function name: add_nisse
 *  Description  : Add a Nisse to the indicated rank
 *  Arguments    : string name - the person to add
 *                 string rank - the rank to add them to: non_nisse
 *                 tan, light brown, brown, deep brown, red, gold, bronze
 *  Returns      : 1 if successful, 0 if not
 */
int
add_nisse(string name, string rank)
{
    string current_rank;

    if (!strlen(name) || !strlen(rank))
    {
        return 0;
    }

    name = CAP(name);
    rank = lower_case(rank);

    if (query_nisse(name, rank))
    {
        return 0;
    }

    current_rank = query_nisse_rank(name);
    if (strlen(current_rank))
    {
        /* Remove him from his present rank so
           we can add him to his new rank. */
        remove_nisse(name);
    }

    /* Add him to the new rank. */
    gNisse[rank] += ({ name });

    save_object(MASTER);

    return 1;
}

/*
 *  Function name: remove_nisse
 *  Description  : Update the lists when a Nisse is removed
 *  Arguments    : string name - the Nisse to remove
 *  Returns      : 1 if successful, 0 if not
 */
int
remove_nisse(string name)
{
    string rank;

    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);

    /* Find out the Nisse's rank name. */
    rank = query_nisse_rank(name);
    if (!strlen(rank))
    {
        return 0;
    }

    /* Remove the Nisse from the nisse array by rank. */
    gNisse[rank] -= ({ name });

    /* Remove the Nisse from the expelled array by name. */
    gExpelled = m_delete(gExpelled, name);

    save_object(MASTER);
    return 1;
}

/*
 *  Function name: query_expelled_nisse
 *  Description  : Is this person on the list of nisse to be expelled?
 *  Arguments    : string name - the name to check
 *  Returns      : 1 if on the list, 0 if not
 */
int
query_expelled_nisse(string name)
{
    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);

    if (member_array(name, m_indexes(gExpelled)) != -1)
    {
        return 1;
    }
    else
        return 0;
}


/*
 *  Function name: query_to_be_expelled
 *  Description  : Is this person on the list of nisse to be expelled?
 *  Arguments    : string name - the name to check
 *  Returns      : the reason for being expelled
 */
string
query_to_be_expelled(string name)
{
    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);

    if (member_array(name, m_indexes(gExpelled)) != -1)
    {
        return gExpelled[name];
    }

    return 0; 
}
 
/*
 *  Function name: add_to_be_expelled
 *  Description  : Adds a name to the list of Nisse to be expelled.
 *  Arguments    : string name - the name to add
 *                 string reason - the reason for being expelled
 *  Returns      : 1 if successful, 0 if not
 */
varargs int
add_to_be_expelled(string name, string reason)
{
    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);

    if (!query_nisse(name))
    {
        return 0;
    }

    if (!strlen(reason))
    {
        reason = "expelled";
    }

    if (!query_to_be_expelled(name))
    {
        string expeller = "guild manager";
        if (objectp(this_interactive()))
        {
            expeller = capitalize(this_interactive()->query_real_name());
        } 
        if (!objectp(find_player(lower_case(name))))
            rlog(name + " was marked to be " +
                "expelled by " + 
                expeller + ".");
        else
            rlog(name + " was expelled by " + 
                expeller + ".");
        gExpelled += ([ name : reason ]);
        save_object(MASTER);
        return 1;
    }

    return 0;
}

/*
 *  Function name: remove_to_be_expelled
 *  Description  : Removes a name from the list of Nisse to be expelled.
 *  Arguments    : string name - the name to remove
 *  Returns      : 1 if successful, 0 if not
 */
int
remove_to_be_expelled(string name)
{
    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);
    if (query_to_be_expelled(name))
    {
        rlog(name + " was removed from the " + 
            "list of Nisse to be expelled by " +
            capitalize(this_interactive()->query_real_name()) + ".");

        gExpelled = m_delete(gExpelled, name);
        save_object(MASTER);
        return 1;
    }

    return 0;
}

/*
 *  Function name: query_to_graduate
 *  Description  : Is this person on the list of nisse to graduate?
 *  Arguments    : string name - the name to check
 *  Returns      : 1 if success, 0 if not
 */
int
query_to_graduate(string name)
{
    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);

    if (member_array(name, m_indexes(gGraduate)) != -1)
    {
        return 1;
    }
    else
        return 0;
}

/*
 *  Function name: add_to_graduate
 *  Description  : Adds a name to the list of Nisse to graduate.
 *  Arguments    : string name - the name to add
 *  Returns      : 1 if successful, 0 if not
 */
varargs int
add_to_graduate(string name, string rank)
{
    if (!strlen(name) || !strlen(rank))
    {
        return 0;
    }

    name = CAP(name);

    if (!query_nisse(name))
    {
        return 0;
    }

    if (!query_to_graduate(name))
    {   
        if (!objectp(find_player(lower_case(name))))
            rlog(name + " was marked to " +
                "graduate by " + 
                capitalize(this_interactive()->query_real_name()) + ".");
        else
            rlog(name + " was graduated by " + 
                capitalize(this_interactive()->query_real_name()) + ".");
        gGraduate += ([ name : rank ]);
        save_object(MASTER);
        return 1;
    }

    return 0;
}

/*
 *  Function name: remove_to_graduate
 *  Description  : Removes a name from the list of Nisse to graduate.
 *  Arguments    : string name - the name to remove
 *  Returns      : 1 if successful, 0 if not
 */
int
remove_to_graduate(string name)
{
    if (!strlen(name))
    {
        return 0;
    }

    name = CAP(name);

    gGraduate = m_delete(gGraduate, name);
    save_object(MASTER);
    return 1;
}
