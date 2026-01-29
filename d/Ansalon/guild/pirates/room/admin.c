/*
 * Pirate Admin object.
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

/**
 * Navarre November 22nd 2007, completely redo of the admin object to fully support not using
 * quest bits in the pirate guild.
 */
    
#include "../local.h"

inherit "/std/room";

#include <ss_types.h>
#include <std.h> 

// The elements in the members array stored
// Ranks are King 3, Firstmate 2, PressGanger 1, Regular member 0
#define P_RANK          0    /* int: The guild rank */
#define P_MESSAGES      1   /* *string: Messages to tell the player when they log in*/
#define P_SIZE          2   /* The size of the mapping */

// 14 days * 24 hours * 60 minutes * 60 seconds
#define MAX_PIRATE_IDLE 1209600     

mapping members;

// Protypes
int add_member(mixed who, int rank);
int add_pressganger(mixed who);
int check_replace_king(mixed who);
void clear_member_message(mixed who);
int make_normal_member(mixed who);
int query_can_recruit(mixed who);
int query_firstmate(mixed who);
string query_king();
int query_member(mixed who);
string* query_member_message(mixed who);
int query_pirate_king(mixed who);
int query_pressganger(mixed who);
int query_piratelord(mixed who);
void remove_idle_kings();
int remove_member(mixed who);
int remove_pressganger(mixed who);
int remove_firstmate(mixed who);
void save();
int set_pirate_king(mixed who);
int set_firstmate(mixed who);

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


/**
 * This function handles adding a new member,
 * adding a pressganger, adding a firstmate,
 * and adding a king. Which of the operations
 * is to be performed depends on the rank value
 * passed to the function.
 *
 * @param who The person to add
 * @param rank The rank:
 *      0 for adding new member
 *      1 for adding as press ganger,
 *      2 for adding as firstmate,
 *      3 for adding as king.
 * @param by_who The person requesting this operation.
 *
 * @return 0 if 'who' wasn't added as a member, 1 otherwise.
 */
int
add_member(mixed who, int rank)
{
    string whoname;
    
    if (stringp(who))
    {
        whoname = who;
    }
    else if (objectp(who))
    {
        whoname = who->query_real_name();
    }
    
    if (!members)
    {
        members = ([]);
    }
    
    if(!who)
    {
        return 0;
    }
    members[whoname] = allocate(P_SIZE);
    members[whoname][P_MESSAGES] =  ({});
    members[whoname][P_RANK] = rank;
    
    save();
    return 1;
}

/**
 * This function adds a person to be pressganger.
 * The reason we have this function as add_pressganger and not set_pressganger
 * is because we can have more than 1.
 *
 * @param who The person to add to the pressgangers.
 *
 * @return 0 on failure, 1 on success.
 */
int
add_pressganger(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }
    if (!members)
    {
        members = ([]);
    }

    if (!members[who])
    {
        add_member(who, 1);
    }
    else
    {
        //Set this person to Pressganger
        members[who][P_RANK] = 1;
    }
    save();
    return 1;       
}

/**
 * This function enables an attempt to take over the kings position.
 * Which works if there is no king of if the king has been too idle.
 *
 * @param who The person that is trying to become the king.
 *
 * @return 0 if he fails, 1 if he becomes king.
 */
int
check_replace_king(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }
    remove_idle_kings();

    string* s = m_indexes(members);
    int i = sizeof(s);
    while (i--)
    {
        //If any non kings are left after calling remove_idle_kings,
        //return 0
        if (members[s[i]][P_RANK] == 3)
        {
            return 0;
        }
    }

    //No King, set the requesting person
    return set_pirate_king(who);

}

/**
 * This function clears any message that might be for the player.
 * This is designed for being used when a message has been delivered to the player.
 *
 * @param who The person we want the message for.
 *
 * @return the message for the player.
 */
void
clear_member_message(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }
    
    if (!members[who])
    {
        return 0;
    }

    members[who][P_MESSAGES] = ({});
    save();
}

/**
 * This function sets the rank of the specified person to a regular member
 *
 * @param who The person we want to remove from the king position.
 *
 * @return 0 if he wasn't a member, 1 if he was removed from king position.
 */
int
make_normal_member(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }
    
    if (!members[who])
    {
        return 0;
    }
    members[who][P_RANK] = 0;
    save();
    return 1;
}


/**
 * This function checks if a specific person has the power to recruit new pirates.
 *
 * @param who The person we want to check if he can recruit.
 *
 * @return 0 if he can't recruit, 1 if he can.
 */
int
query_can_recruit(mixed who)
{
    if (objectp(who))
    {
        //Pirate Lords may recruit as Press Gangers.
        if(query_piratelord(who))
            return 1;

        who = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }

    if (!members[who])
    {
        return 0;
    }
    // He can recruit if he is king, firstmate or press ganger.
    return (members[who][P_RANK] == 3 || 
            members[who][P_RANK] == 2 ||
            members[who][P_RANK] == 1);    
}

/**
 * This function checks if a specific person is a pirate lord rank.
 *
 * @param who The person we want to check if he is the first mate
 *
 * @return 0 if he is not the firstmate, 1 otherwise.
 */
int
query_piratelord(mixed who)
{
    if (objectp(who))
    {
        // Rank 1 for Pirate Lords, the equivalent of Press Gangers.
        if(PIRATE_RANK(who) == IS_PIRATE_LORD)
            return 1;
    }

    return 0;    
}

/**
 * This function checks if a specific person is the first mate.
 *
 * @param who The person we want to check if he is the first mate
 *
 * @return 0 if he is not the firstmate, 1 otherwise.
 */
int
query_firstmate(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }

    if (!members[who])
    {
        return 0;
    }
    // Rank 2 is the first mate
    return (members[who][P_RANK] == 2);    
}

/**
 * This function returns the name of the king if we have one.
 *
 * @return The name of the king, or 0 if we dont have any.
 */
string
query_king()
{
    string name;

    if(!members)
    {
        members = ([]);
    }

    string* s = m_indexes(members);
    int i = sizeof(s);

    for(int j = 0; j < i; j++)
    {
      name = s[j];
        if(members[name][P_RANK] == 3)
        {
	  return name;
        }
    }
    return 0;
}

/**
 * This function checks if a specific person is a member of the pirate guild.
 *
 * @param who The person we are checking for membership.
 *
 * @return 0 if 'who' is not a member, 1 otherwise.
 */
int
query_member(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }
    return !!members[who];
}


/**
 * This function returns any message that might be for the player.
 *
 * @param who The person we want the message for.
 *
 * @return the message for the player.
 */
string*
query_member_message(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }
    return members[who][P_MESSAGES];
}

/**
 * This function checks if the specified person is the king.
 *
 * @param who The person we want to check if he is the king, can be his name of player object.
 *
 * @return 0 if he isn't the king, 1 if he was the king.
 */
int
query_pirate_king(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }

    if (!members[who])
    {
        return 0;
    }

    return (members[who][P_RANK] == 3);    
}

/**
 * This function checks if the specified person is a press ganger.
 *
 * @param who The person to check if he is a press ganger.
 *
 * @return 0 if he is not,  1 if he is.
 */
int
query_pressganger(mixed who)
{
    if (objectp(who))
    {
        who = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }

    if (!members[who])
    {
        return 0;
    }
    // Rank 1 is the press ganger.
    return (members[who][P_RANK] == 1);    
}


/**
 * This is a helper function used to turn a king into a regular member
 * if he has been idle for too long and someone is trying to assume command.
 */
void
remove_idle_kings()
{
    int t = time() - MAX_PIRATE_IDLE;

    if (!members)
    {
        members = ([]);
    }

    string* s = m_indexes(members);

    int i = sizeof(s);

    while (i--)
    {
 
        //If the player is logged in, skip
        if (find_player(s[i]))
            continue;

        int j = file_time(PLAYER_FILE(s[i]) + ".o");

        //if there is a king (rank 3) and they have not logged in within
        //the idle time allowed, remove them
        if (members[s[i]][P_RANK] == 3 && 
            (j < t) )
        {
            // Set them to normal member.
            members[s[i]][P_RANK] = 0;
        }
    }

    save();
}

/**
 * This function removes a remember from the members file.
 * Note: It doens't remove shadows, soul etc.
 *
 * @param who The person we are going to remove from the members file.
 *
 * @return 0 if he didn't exist already, 1 if he was successfully removed.
 */
int
remove_member(mixed who)
{
    string whoname;

    if (stringp(who))
    {
        whoname = who;
    }
    else if (objectp(who))
    {
        whoname = who->query_real_name();
    }

    if (!members)
    {
        members = ([]);
    }

    if (!members[whoname])
    {
         return 0;
    }
    
    members = m_delete(members, whoname);
    save();
    return 1;
}

/**
 * This function removes pressganger privileges from a player.
 *
 * @param who The person we wish to remove as pressganger.
 *
 * @return 0 if we fail, 1 if we succeed.
 */
int
remove_pressganger(mixed who)
{
    // It's the same action as removing king.
    return make_normal_member(who);
}

/**
 * This function removes firstmate privileges from a player.
 *
 * @param who The person we wish to remove as firstmate
 *
 * @return 0 if we fail, 1 if we succeed.
 */
int
remove_firstmate(mixed who)
{
    // It's the same action as removing king.
    return make_normal_member(who);
}

/**
 * This function sets a specific person to be the pirate king.
 *
 * @param who The person we want to be the king.
 *
 * @return 0 if we fail, 1 if we succeed.
 */
int
set_pirate_king(mixed who)
{
    object mate;
    
    if (objectp(who))
    {
        who = who->query_real_name();
    }
    if (!members)
    {
        members = ([]);
    }

    string* pirates = m_indexes(members);

    int i = sizeof(pirates);

    // Since we are setting a new first mate
    // first remove the old one
    for(int j = 0; j < i; j++)
    {
        if (members[pirates[j]][P_RANK] == 3)
        {
            if(pirates[j] == who)
            {
                // No need to do anything more he is already king.
                // Should really be checked else where, but just in case
                // it is not, we allow it here.
                return 1;
            }
            members[pirates[j]][P_RANK] = 0;

            mate = find_player(pirates[j]);
            if(mate)
            {
                mate->catch_tell("You have been replaced as king.\n");
            }            
            else
            {
                if (!pointerp(members[pirates[j]][P_MESSAGES]))
                {
                    members[pirates[j]][P_MESSAGES]= ({ });
                }
                members[pirates[j]][P_MESSAGES] += ({"You have been replaced as king.\n"});
            }
            // There can only be one firstmate so we break.
            break;
        }
    }
    if (!members[who])
    {
        add_member(who, 3);
    }
    else
    {
        // Make the new guy king
        members[who][P_RANK] = 3;
        mate = find_player(who);
        if(mate)
        {
            mate->catch_tell("You have been made the new king of the pirates!\n");
        }
        else
        {
            if (!pointerp(members[who][P_MESSAGES]))
            {
                members[who][P_MESSAGES]= ({ });
            }
            members[who][P_MESSAGES] += ({"You have been made the new king of the pirates!\n"});
        }

    }
    save();
    return 1;       
}

/**
 * This function sets a specific person to be the firstmate.
 *
 * @param who The person we want to be the firstmate
 *
 * @return 0 if we fail, 1 if we succeed.
 */
int
set_firstmate(mixed who)
{
    object mate;

    if (objectp(who))
    {
        who = who->query_real_name();
    }
    if (!members)
    {
        members = ([]);
    }

    string* pirates = m_indexes(members);

    int i = sizeof(pirates);

    // Since we are setting a new first mate
    // first remove the old one
    for(int j = 0; j < i; j++)
    {
        if (members[pirates[j]][P_RANK] == 2)
        {
            if(pirates[j] == who)
            {
                // No need to do anything more he is already first mate.
                // Should really be checked else where, but just in case
                // it is not, we allow it here.
                return 1;
            }
            members[pirates[j]][P_RANK] = 1;

            mate = find_player(pirates[j]);
            if(mate)
            {
                mate->catch_tell("You have been replaced as the firstmate.\n");
            }            
            else
            {
                if (!pointerp(members[pirates[j]][P_MESSAGES]))
                {
                    members[pirates[j]][P_MESSAGES]= ({ });
                }
                members[pirates[j]][P_MESSAGES] += ({"You have been replaced as the firstmate.\n"});
            }
            // There can only be one firstmate so we break.
            break;
        }
    }
    if (!members[who])
    {
        add_member(who, 2);
    }
    else
    {
        // Make the new guy firstmate
        members[who][P_RANK] = 2;
        mate = find_player(who);
        if(mate)
        {
            mate->catch_tell("You have been made the new firstmate of the pirates!\n");
        }
        else
        {
            if (!pointerp(members[who][P_MESSAGES]))
            {
                members[who][P_MESSAGES]= ({ });
            }
            members[who][P_MESSAGES] += ({"You have been made the new firstmate of the pirates!\n"});
        }

    }
    save();
    return 1;       
}

