/*
 * manager.c
 *
 * This room keeps track of and manages these variables:
 *
 * mapping gAnghoth
 * mapping gExpelled
 * mapping gInvited
 * mapping gSponsors
 *
 * Alto, 02 June 2002 (inspired by Gwyneth)
 */

#pragma save_binary
inherit "/std/room";

#include "anghoth_defs.h"
#include "/d/Gondor/defs.h"

#include <files.h>
#include <language.h>
#include <macros.h>

/* Global Variables */

mapping gAnghoth          = (["durub" : ({}),    "dath" : ({}), 
                              "korrak" : ({}), "kriechek" : ({}), ]);
mapping gExpelled         = ([]);
mapping gInvited          = ([]);
mapping gSponsors         = ([]);

/* Prototypes */

public void        startup_checks();
public varargs int send_message(object target, string text, string sender);
public int         query_anghoth_level(string name);
public int         query_anghoth_rank(string name);
public string *    query_rank_members(int rank);
public int         query_ashuk(string name);
public varargs int query_anghoth(string name, string rank);
public int         add_anghoth(string name, string rank, string sponsor);
public int         remove_anghoth(string name);
public mixed       query_anghoth_sponsor(string name);
public int         add_sponsor(string name, string sponsor);
public int         query_expelled_anghoth(string name);
public string *    query_to_be_expelled(string name);
public int         add_to_be_expelled(string name, string reason);
public int         remove_to_be_expelled(string name);
public string      query_inviting_sponsor(string name);
public int         add_inviting_sponsor(string name, string sponsor);
public int         remove_inviting_sponsor(string name);

public void
create_room()
{
    set_short("Anghoth Club Manager Room");
    set_long("Here is where the Anghoth club is managed.\n");
    seteuid(getuid());
    restore_object(MASTER);
    set_alarm(360.0, 0.0, &startup_checks());
}

/* Function name: startup_checks
 * Description  : Cleans up non-existant players and apprentices who
 *                have run out of time.
 */
public void
startup_checks()
{
    int i, j, size; 
    string *player_list, *rank_list;

    /* Make an array of all the ranks. */
    rank_list = m_indexes(gAnghoth);

    for (i = sizeof(rank_list) - 1; i >= 0; i--)
    {
        /* Get a list of the players in this rank. */
        player_list = gAnghoth[rank_list[i]];

        /* Check for non-existant Anghoth and remove them. */
        j = -1;
        while(++j < sizeof(player_list))
        {
            /* Remove from list if Anghoth no longer exists. */
            if (!SECURITY->exist_player(gAnghoth[rank_list[i]][j]))
                remove_anghoth(gAnghoth[rank_list[i]][j]);
        }
    }

    /* Make an array of all the invited supplicants. */
    rank_list = m_indexes(gInvited);

    for (i = sizeof(rank_list) - 1; i >= 0; i--)
    {
        /* Check for non-existant invitees and remove them. */
            if (!SECURITY->exist_player(rank_list[i]))
                remove_inviting_sponsor(rank_list[i]);
    }

}

/* Function name: send_message
 * Description  : Sends a message to an Anghoth
 * Arguments    : object target - who to send the message from
 *                string text   - What the message says
 *                string sender - (optional) Who sent the message,
 *                                default: The Nine
 * Returns      : 1/0 success/failure
 */
public varargs int
send_message(object target, string text, string sender)
{
    object note;

    if (!objectp(target) || !strlen(text))
        return 0;

    if (!strlen(sender))
        sender = "The Nine";

    target->catch_tell("A tiny black bat flutters onto your forearm.\n" +
            "You retrieve the message clutched in its claws.\n" +
            "The tiny black bat flutters away again.\n");

    note = clone_object(ANGHOTH_OBJ + "scroll");
    note->set_message(text);
    note->set_sender(sender);
    note->move(target, 1);
    return 1;
}

/* Function name: cycle_file
 * Description  : Cycles a file so that it does not get too big.
 * Arguments    : string filename - the name of the file
 *                int size - the number of bytes to preserve
 * Returns      : 1 if successful, 0 if not
 */
private nomask int
cycle_file(string filename, int size)
{
    int filesize;

    /* To prevent any abuse. */
    if (filename[0..strlen(ANGHOTH_DIR)-1] != ANGHOTH_DIR)
        return 0;

    filesize = file_size(filename);

    /* File doesn't exist (-1), is a directory (-2) or is of 0 bytes */
    if (filesize == -1 || filesize == -2 || filesize == 0)
        return 0;

    if (size > filesize)
        return 0;

    rename(filename, filename + ".old");
    return 1;
}

/* Function name: rlog
 * Description  : Log an action.
 * Arguments    : string text - the text to log
 * Returns      : 1 on success, 0 on failure
 */
public int
rlog(string text)
{
    string *log_arr;

    if (!strlen(text))
        return 0;

    cycle_file(ANGHOTH_LOG, LOG_SIZE);
    write_file(ANGHOTH_LOG, ctime(time()) + ": " + text + "\n");
    return 1;
}


/* Function name: query_anghoth_level
 * Description  : Returns the membership level
 * Arguments    : string name - the name of the person to give status on
 * Returns      : 0 - Not an Anghoth at all
 *                1 - Kriechek (coward)
 *                2 - Korrak
 *                3 - Dath
 *                4 - Durub
 */
public int
query_anghoth_level(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, gAnghoth["kriechek"]) != -1)
        return KRIECHEK_LEVEL;
    else if (member_array(name, gAnghoth["korrak"]) != -1)
        return KORRAK_LEVEL;
    else if (member_array(name, gAnghoth["dath"]) != -1)
        return DATH_LEVEL;
    else if (member_array(name, gAnghoth["durub"]) != -1)
        return DURUB_LEVEL;
    else
        return 0;
}

/* Function name: query_anghoth_rank
 * Description  : Returns the string rank name
 * Arguments    : string name - the name of the person to give status on
 * Returns      : kriechek, korrak, dath, durub
 */
public string
query_anghoth_rank(string name)
{
    if (!strlen(name))
        return "";

    name = capitalize(name);

    switch(query_anghoth_level(name))
    {
    case KRIECHEK_LEVEL:
        return "kriechek";
    case KORRAK_LEVEL:
        return "korrak";
    case DATH_LEVEL:
        return "dath";
    case DURUB_LEVEL:
        return "durub";
    default:
        return "";
    }
}

/* Function name: query_rank_members
 * Description  : What players belong to this rank?
 * Arguments    : int rank - the rank to check
 *                   0 = bogus (not a member)
 *                   1 = kriechek
 *                   2 = korrak
 *                   3 = dath
 *                   4 = durub
 * Returns      : an array of rank members
 */
public string *
query_rank_members(int rank)
{
    if (!intp(rank))
        return ({});

    switch (rank)
    {
        case 0:
            return ({});
        case 1:
            return gAnghoth["kriechek"];
        case 2:
            return gAnghoth["korrak"];
        case 3:
            return gAnghoth["dath"];
        case 4:
            return gAnghoth["durub"];
        default:
            return ({});
    }
}

/* Function name: query_ashuk
 * Description  : Is this person ashuk? (lost without a mage sponsor)
 * Arguments    : string name - the name of the person to give status on
 * Returns      : 0 - Not an ashuk
 *                1 - Is an ashuk
 */
public int
query_ashuk(string name)
{
    string sponsor;

    if (!strlen(name))
        return 0;

    name = capitalize(name);
    sponsor = query_anghoth_sponsor(name);

    if (!query_anghoth(name))
    {
        return 0;
    }

    if (MAGE_MANAGER->query_is_mage(sponsor))
    {
        return 0;
    }
    return 1;
}


/* Function name: query_anghoth
 * Description  : Returns 1 if the person is an Anghoth or in the indicated 
 *                rank
 * Arguments    : string name - the name to check
 *                string rank - the rank to check against (optional)
 * Returns      : 1 if matches, 0 if not
 */
public varargs int
query_anghoth(string name, string rank = "")
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!strlen(rank))
    {
        if (query_anghoth_level(name))
            return 1;
        return 0;
    }

    if (rank == query_anghoth_rank(name))
        return 1;
    return 0;
}

/* Function name: add_anghoth
 * Description  : Add an Anghoth to the indicated rank 
 * Arguments    : string name - the person to add
 *                string rank - the rank to add them to: dishounoured, 
 *                korrak, dath, durub
 *                string sponsor - the sponsor of the Anghoth
 * Returns      : 1 if successful, 0 if not
 */
int
add_anghoth(string name, string rank, string sponsor)
{
    string current_rank;

    if (!strlen(name) || !strlen(rank) || !strlen(sponsor))
        return 0;

    name = capitalize(name);
    sponsor = capitalize(sponsor);
    rank = lower_case(rank);

    if (query_anghoth(name, rank))
        return 0;

    current_rank = query_anghoth_rank(name);
    if (strlen(current_rank))
    {
        /* Remove him from his present rank so
           we can add him to his new rank. */
        remove_anghoth(name);
    }

    /* Add him to the new rank. */
    gAnghoth[rank] += ({ name });

    save_object(MASTER);

    add_sponsor(name, sponsor);

    return 1;
}

/* Function name: remove_anghoth
 * Description  : Update the lists when an Anghoth is removed
 * Arguments    : string name - the Anghoth to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_anghoth(string name)
{
    string rank, sponsor;

    if (!strlen(name))
        return 0;

    name = capitalize(name);

    /* Find out the Anghoth's rank name. */
    rank = query_anghoth_rank(name);
    if (!strlen(rank))
        return 0;

    /* Find out the Anghoth's sponsor name. */
    sponsor = query_anghoth_sponsor(name);
    if (!strlen(sponsor))
        return 0;

    /* Remove the Anghoth from the anghoth array by rank. */
    gAnghoth[rank] -= ({ name });

    /* Remove the Anghoth from the sponsor array by name. */
    gSponsors = m_delete(gSponsors, name);

    /* Remove the Anghoth from the expelled array by name. */
    gExpelled = m_delete(gExpelled, name);

    save_object(MASTER);
    return 1;
}

/* Function name: query_anghoth_sponsor
 * Description  : what is the name of sponsor of this Anghoth?
 * Arguments    : string name - the Anghoth to check
 * Returns      : the name of the sponsor in that Anghoth
 */
public mixed
query_anghoth_sponsor(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gSponsors)) != -1)
        return gSponsors[name];

    return 0;
}


/* Function name: add_sponsor
 * Description  : Add an Anghoth to the indicated Sponsor 
 * Arguments    : string name - the person to add
 *                string sponsor - the sponsor to add them to
 * Returns      : 1 if successful, 0 if not
 */
int
add_sponsor(string name, string sponsor)
{
    if (!strlen(name) || !strlen(sponsor))
        return 0;

    name = capitalize(name);
    sponsor = capitalize(sponsor);

    if (query_anghoth_sponsor(name))
        return 0;

    /* Add name and sponsor. */
    gSponsors += ([ name : sponsor ]);

    save_object(MASTER);
    return 1;
}


/* Function name: query_expelled_anghoth
 * Description  : Is this person on the list of anghoth to be expelled?
 * Arguments    : string name - the name to check
 * Returns      : 1 if on the list, 0 if not
 */
public int
query_expelled_anghoth(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gExpelled)) != -1)
        return 1;
    else
        return 0;
}


/* Function name: query_to_be_expelled
 * Description  : Is this person on the list of rangers to be expelled?
 * Arguments    : string name - the name to check
 * Returns      : the reason for being expelled
 */
public string *
query_to_be_expelled(string name)
{
    if (!strlen(name))
        return ({});

    name = capitalize(name);

    if (member_array(name, m_indexes(gExpelled)) != -1)
        return gExpelled[name];
    else
        return ({});
}
 
/* Function name: add_to_be_expelled
 * Description  : Adds a name to the list of Anghoth to be expelled.
 * Arguments    : string name - the name to add
 *                string reason - the reason for being expelled
 * Returns      : 1 if successful, 0 if not
 */
public varargs int
add_to_be_expelled(string name, string reason)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (!query_anghoth(name))
        return 0;

    if (!strlen(reason))
        reason = "expelled";

    if (!sizeof(query_to_be_expelled(name)))
    {   
        if (!objectp(find_player(lower_case(name))))
            rlog(name + " was marked to be " +
                "expelled by " + 
                capitalize(this_interactive()->query_real_name()) + ".");
        else
            rlog(name + " was expelled by " + 
                capitalize(this_interactive()->query_real_name()) + ".");
        gExpelled += ([ name : reason ]);
        save_object(MASTER);
        return 1;
    }

    return 0;
}
 
/* Function name: remove_to_be_expelled
 * Description  : Removes a name from the list of Anghoth to be expelled.
 * Arguments    : string name - the name to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_to_be_expelled(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);
    if (strlen(query_to_be_expelled(name)[0]))
    {
        rlog(name + " was removed from the " + 
            "list of Anghoth to be expelled by " +
            capitalize(this_interactive()->query_real_name()) + ".");

        gExpelled = m_delete(gExpelled, name);
        save_object(MASTER);
        return 1;
    }

    return 0;
}

/* Function name: query_invited_sponsor
 * Description  : what is the name of sponsor who invited this supplicant?
 * Arguments    : string name - the supplicant to check
 * Returns      : the name of the sponsor who invited that supplicant
 */
public mixed
query_inviting_sponsor(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    if (member_array(name, m_indexes(gInvited)) != -1)
        return gInvited[name];

    return 0;
}


/* Function name: add_inviting_sponsor
 * Description  : Add a supplicant to the indicated inviting Sponsor 
 * Arguments    : string name - the person to add
 *                string sponsor - the sponsor to add them to
 * Returns      : 1 if successful, 0 if not
 */
int
add_inviting_sponsor(string name, string sponsor)
{
    if (!strlen(name) || !strlen(sponsor))
        return 0;

    name = capitalize(name);
    sponsor = capitalize(sponsor);

    if (query_inviting_sponsor(name))
        return 0;

    /* Add name and sponsor. */
    gInvited += ([ name : sponsor ]);

    save_object(MASTER);
    return 1;
}

/* Function name: remove_inviting_sponsor
 * Description  : Update the lists when an inviting sponsor is removed
 * Arguments    : string name - the inviting sponsor to remove
 * Returns      : 1 if successful, 0 if not
 */
public int
remove_inviting_sponsor(string name)
{
    if (!strlen(name))
        return 0;

    name = capitalize(name);

    /* Remove the supplicant from the invited sponsor array by name. */
    gInvited = m_delete(gInvited, name);

    save_object(MASTER);
    return 1;
}
