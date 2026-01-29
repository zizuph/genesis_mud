/*
 * File:     monk_master
 * Created:  Cirion, 1998.06.01
 * Purpose:  master object for Kaheda -- this keeps track
 *           of all the savevars we need (member list, etc.)
 *           The interface to this object should always
 *           be the monklib.c file.
 * Modification Log:
 *
 */
#include "defs.h"
inherit ROOMBASE;

#define SAVE save_object (MONK_LIB + "monksave")
#define RESTORE restore_object (MONK_LIB + "monksave")

// we are not currently using thie feature
//#define MAX_QUEUED_MESSAGES    6
#define MAX_QUEUED_MESSAGES    0


/* members is a mapping of all the members of the monks, of    */
/* the form:                                                   */
/* ([ name : ({ when joined, council, ({messages}),            */
/*              branch, punishments, age joined,               */
/*              unused, unused, unused  }) ])                  */
/*                                                             */
/* more elements to the mapping to be added as needed...       */
public mapping members = ([]);

/* votes of the form:                                          */
/* ([ name: ({ added_by, end_time, (mapping)votes }) ])        */
public mapping votes = ([]);

/* applications of the form:                                   */
/*  ([ name: ({ status, stamp time }) ])                       */
public mapping applications = ([]);

/* council info of the form:                                   */
/*   ([ name: ({ body_part, short_desc,                        */
/*        long_desc, last_given, member_long_desc, title,      */
/*        unused, unused }) ])                                 */
public mapping council_info = ([]);


public void startup_procs();


// there seems to be some problem with cloning objects from a
// soul that I can't track down. This is to work around the
// problem.
object
do_clone_object(string str)
{
    seteuid(getuid(this_object()));
    return clone_object(str);
}

void
create_room ()
{
    set_short ("Kaheda master room");
    set_long ("This is the Kaheda master room.");

    RESTORE;

    set_alarm(1.0, 0.0, startup_procs); // perform the startup procs
}


/*
 * Function name: get_name
 * Description:   returns the name of an object if an
 *                object was passed in.
 * Arguments:     the object for whom we will be returing a name
 * Returns:       the name (lowercase)
 */
string
get_name (mixed for_who)
{
    if (stringp (for_who))
        return lower_case (for_who);

    if (objectp (for_who))
        return lower_case (for_who->query_real_name ());

    return 0;

}

/*
 * Function name: query_monk
 * Description:   See if a player specified is a monk
 *
 * Arguments:     who - string or object of the player to check
 *                type - type of monk to check for
 * Returns:       1 if they are a monk of the specified type,
 *                    0 if not.
 */
public varargs int
query_monk(mixed who, int type = -1)
{
    string *ind, name = get_name(who);

    ind = m_indices(members);

    if(member_array(name, ind) == -1)
        return 0; // not in the mapping at all

    if(type == -1) // check for any monk
        return 1;

    // check for a specific type
    return members[name][3] == type;
}

/*
 * Function name: query_age_joined
 * Description:   Check the age the player was when they joined
 *                the monks.
 * Arguments:     who - string or object of the player to check
 * Returns:       The age the player was when they joined the
 *                monks.
 */
public varargs int
query_age_joined(mixed who)
{
    string *ind, name = get_name(who);
    int     age;

    ind = m_indices(members);

    if(member_array(name, ind) == -1)
        return 0; // not in the mapping at all

    age = members [name][5];

    // sanity check ..
    if(age <= 0)
        return time ();

    return age;
}


/*
 * Function name: add_member
 * Description:   add a member to the monk member list
 * Arguments:     mixed who - object or string describing the
 *                member.
 *                branch - branch to join (SS_OCCUP or SS_LAYMAN)
 * Returns:       1 if successfully added to the member list
 */
int
add_member (mixed who, int branch)
{
    string  name = get_name (who);
    int     age;

    if (!strlen (name))
        return 0;

    /* person is already a member .... */
    if (member_array (name, m_indices (members)) != -1)
        return 0;

    if (objectp (who))
        age = who->query_age ();

    /* add them to the member list.    */
    members += ([ name : ({ time (), 0, ({}), branch, 0, age,
        0, 0, 0, 0 }) ]);

    SAVE;
    return 1;
}

/*
 * Function name: remove_member
 * Description:   Removes a member from the membership
 *                mapping
 * Arguments:     The string or object of the player to remove
 * Returns:       1 if successfully removed
 */
public int
remove_member(mixed who)
{
    string name = get_name (who);

    if (!strlen (name))
        return 0;

    // person is not a member
    if (member_array (name, m_indices (members)) == -1)
        return 0;

    // remove them from the member list
    members = m_delete(members, name);

    SAVE;
    return 1;
}


/*
 * Function name: clean_members
 * Description:   Go through the member list and make
 *                sure that all members are still legit
 *                players.
 */
void
clean_members()
{
    string *mems;
    int     i;

    mems = m_indices (members);

    for (i=0;i<sizeof(mems);i++)
    {
        // if the applicant is not longer a player, delete him/her
        if(!m_query_is_player(mems[i]))
        {
            remove_member(mems[i]);
            m_log(mems[i] + " was removed as a member since "
                + "they are no longer a polayer.");
            continue;
        }
    }
}

/*
 * Function name: add_member_message
 * Description:   adds a message to a members pending message queue
 * Arguments:     mixed who - object or string describing the
 *                member.
 *                msg - the message to send
 * Returns:       1 if successfully queued message
 */
public int
add_member_message (mixed who, string msg)
{
    string name = get_name (who);
    string *messages;

    if (!strlen (name))
        return 0;

    /* person is not a member .... */
    if (member_array (name, m_indices (members)) == -1)
        return 0;

    messages = members[name][2];

    // same message is already queued
    if(member_array(msg, messages) > -1)
        return 0;


    // disallow too many messages to be queued
    if (sizeof (members[name][2]) > MAX_QUEUED_MESSAGES)
        return 0;

    /* flag them as a council member    */
    members[name][2] += ({ msg });

    SAVE;
    return 1;
}

/*
 * Function name: remove_member_message
 * Description:   removes a message to a member's pending message queue
 * Arguments:     mixed who - object or string describing the
 *                member.
 *                msg - the message to remove
 * Returns:       1 if successfully removed message from queue
 */
public int
remove_member_message (mixed who, string msg)
{
    string name = get_name (who);
    string *messages;

    if (!strlen (name))
        return 0;

    /* person is not a member .... */
    if (member_array (name, m_indices (members)) == -1)
        return 0;

    messages = members[name][2];

    if(member_array(msg, messages) == -1)
        return 0;

    messages -= ({ msg });

    // reset the messages
    members[name][2] = messages;

    SAVE;
    return 1;
}

/*
 * Function name: add_council_member
 * Description:   add a council member to the monks
 *
 * Arguments:     mixed who - object or string describing the
 *                member.
 *                setting - 1 to set them as a council member,
 *                    0 to remove.
 * Returns:       1 if successfully added to the member list
 */
public varargs int
add_council_member (mixed who, int setting = 1)
{
    string name = get_name (who);

    if (!strlen (name))
        return 0;

    /* person is not a member .... */
    if (member_array (name, m_indices (members)) == -1)
        return 0;

    /* flag them as a council member    */
    members[name][1] = setting;

    SAVE;
    return 1;
}


/*
 * Function name: remove_council_member
 * Description:   removes a council member to the monks
 *
 * Arguments:     mixed who - object or string describing the
 *                member.
 * Returns:       1 if successfully removed the council member flag
 */
public int
remove_council_member (mixed who)
{
    return add_council_member (who, 0);
}


/******************************************************************
 *        Punishment interface
 */

/*
 * Function name: add_punishment
 * Description:   Adds a specified punishment to a
 *                player.
 * Arguments:     who - string or object of the player
 *                punishment - punishment to add to the
 *                    bitwise punishment specification.
 * Returns:       1 if successful
 */
public int
add_punishment (mixed who, int punishment)
{
    string name = get_name(who);

    if(!(members[name])) // no such member
        return 0;

    // add the punishment to the bitwise values for the player
    members[name][4] |= punishment;
    SAVE;
    return 1;
}

/*
 * Function name: query_punishment
 * Description:   Returns either the entire punishment
 *                number of the player, or 1 if a specified
 *                punishment is currently in the bitwise
 *                list of punishment values.
 * Arguments:     who - string or name of the player
 *                punishment - -1 to return the entire
 *                    punishment, or the punishment
 *                    to check for.
 * Returns:       Either the entire punishment number, or
 *                    1 if the specified punishment is present
 *                    in the player's punishment specification.
 */
public varargs int
query_punishment (mixed who, int punishment = -1)
{
    string name = get_name(who);

    if(!(members[name])) // no such member
        return 0;

    // return all punishments
    if(punishment == -1)
        return members[name][4];

    // return the check for the specified punishment
    return (members[name][4] & punishment);
}

public string *
query_punish_list ()
{
    int             i;
    string          *people;
    string          *ret = ({});

    people = m_indices (members);

    for (i = 0; i < sizeof (people); i++)
    {
        if (query_punishment (people [i]))
            ret += ({ people [i] });
    }

    return ret;
}

/*
 * Function name: remove_punishment
 * Description:   Removes a given punishment from a player.
 *
 * Arguments:     who - player to remove the punishment from
 *                punishment - -1 to remove all punishments,
 *                    or the specified punishment to extract
 *                    it from the list of values.
 * Returns:       1 if successful
 */
public varargs int
remove_punishment (mixed who, int punishment = -1)
{
    string name = get_name(who);

    if(!(members[name])) // no such member
        return 0;

    // remove all punishments
    if(punishment == -1)
    {
        members[name][4] = 0;
        return 1;
    }

    // remove only the specified punishments
    // ^ construct will extract the specified bit from
    // the list.
    members[name][4] ^= punishment;
    SAVE;
    return 1;
}

/*
 * Function name: query_council_member
 * Description:   Either get a list of all the council
 *                members, or see if a particular player is
 *                a member.
 * Arguments:     who - player name or object to check.
 *                    0 will return a list of all council members.
 * Returns:       Either the list of council members, or 1 if
 *                    the specified player is a council member.
 */
public varargs mixed
query_council_member(mixed who = 0)
{
    string name;
    string *council_members = ({}), *member_names;
    int    i;

    member_names = m_indices(members);

    for(i=0;i<sizeof(member_names);i++)
        if(members[member_names[i]][1])
            council_members += ({ member_names[i] }); // add them to the list

    if(!who) // return the whole list of members
        return council_members;

    name = get_name (who);

    // check to see if the name is in the list
    return (member_array(name, council_members) > -1);
}


/*
 * Function name: check_council_vote
 * Description:   called once per reboot, it will start
 *                a vote for council members if the current
 *                number of council members is not
 *                MONK_MAX_COUNCIL_MEMBERS
 */
public void
check_council_vote()
{

    if(m_count_council_members() < MONK_MAX_COUNCIL_MEMBERS)
        m_start_council_election();
}


/*
 * Function name: count_members
 * Description:   give a count of all the members of the guild
 *
 * Arguments:     none
 * Returns:       the number of members (the number of indices
 *                in the "members" mapping)
 */
int
count_members ()
{
    return m_sizeof (members);
}


/*
 * Function name: query_members
 * Description:   Function to obtain the membership
 *                mapping.
 * Returns:       the mapping of members
 */
mapping
query_members ()
{
    return members;
}


/******************************************************************
 *        Application interface
 */
public int
set_application_status(string who, int stat, int branch)
{
    if(!applications[who])
        applications += ([ who : ({ 0, 0, 0 }) ]);

    // update the status, stamp the time
    applications[who][0] = stat;
    applications[who][1] = time();
    applications[who][2] = branch;

    SAVE;
}

public int
query_application_status(string who)
{
    if(!applications[who])
        return -2; // no applicant!

    return applications[who][0];
}

public int
query_application_time_left(string who)
{
    if(!applications[who])
        return 0; // no applicant!

    return ((applications[who][1] + MONK_APPLICATION_MAX_TIME) - time());
}

/*
 * Function name: m_delete_application
 * Description:   delete an element from the
 *                application mapping.
 * Arguments:     name of the applicant to delete
 */
public void
delete_application(string who)
{
    applications = m_delete(applications, who);
    SAVE;
}

/*
 * Function name: clean_applications
 * Description:   Go through and delete old applications
 *                that have not been stamped for
 *                MONK_APPLICATION_MAX_TIME seconds, or
 *                if the player is no longer around.
 */
void
clean_applications()
{
    string *apps;
    int     i;
    int     *app_data, stamp_time;

    apps = m_indices (applications);

    for (i=0;i<sizeof(apps);i++)
    {
        app_data = applications[apps[i]];

        // if the applicant is not longer a player, delete him/her
        if(!m_query_is_player(apps[i]))
        {
            delete_application(apps[i]);
            continue;
        }

        // have we passed the threshhold of time, after which
        // stale applications will be removed?
        stamp_time = app_data[1];
        if((stamp_time + MONK_APPLICATION_MAX_TIME) <= time())
        {
            delete_application(apps[i]);
            continue;
        }

    }
}


/******************************************************************
 *        Voting interface
 */

public varargs int
add_vote(string name, int props, int end_time, string end_file,
    string end_proc, string by_who, string vote_desc = "", int end_threshhold = -1)
{
    mixed    vote_data;

    if(member_array(name, m_indices(votes)) > -1)
    {
        notify_fail("A vote with the name: " + name
            + " is already being cast.\n");
        return 0;
    }

//    write("Adding: " + name + by_who + props + end_time + end_file + end_proc + "\n");
    vote_data = ({ by_who, props, end_time, ([]),
        end_file, end_proc, vote_desc, end_threshhold });


    votes += ([ name : vote_data ]);
    SAVE;
    return 1;
}

/*
 * Function name: remove_vote
 * Description:   removes a vote from the vote list
 *
 * Arguments:     the name of the vote
 * Returns:       1 if successful
 */
public int
remove_vote(string name)
{
    votes = m_delete(votes, name);
    SAVE;
    return 1;
}

public varargs mixed
query_vote(string name = "")
{
    if(!strlen(name))
        return votes; // return the whole mapping
    else
        return votes[name]; // return only the specific vote
}

public varargs int
cast_vote(string vote_name, string vote,
    string by_who = this_player()->query_real_name())
{
    mixed      vote_data;
    int        end_time;
    mapping    vote_map;

    if(member_array(vote_name, m_indices(votes)) == -1)
    {
        notify_fail("There is no such vote.\n");
        return 0;
    }

    vote_data = votes[vote_name];
    end_time = vote_data[2];
    vote_map = vote_data[3];

    vote_map[by_who] = vote; // set the vote for the player

    // save back the data to the vote mapping
    vote_data[3] = vote_map;
    votes[vote_name] = vote_data;
    SAVE;

    return 1;    
}


/*
 * Function name: get_council_info
 * Description:   Query the mapping of council info
 * Arguments:     The name of the council member
 * Returns:       The array of council info
 */
public mapping
get_council_info(string who)
{
    if(council_info[who])
        return council_info[who];
    else
        return 0;
}

public void
delete_council_info(string who)
{
    council_info = m_delete(council_info, lower_case(who));
    SAVE;
}

varargs public void
set_council_info(string who, int last_given = 0, int location = 0,
        string short_desc = "", string long_desc = "",
        string council_desc = "", string council_title = "")
{
    mixed    info;

    // check to see if we already have some info for this player, and
    // if so, fill in the blanks.
    info = council_info[who];
    if(pointerp(info))
    {
        if(location == 0)
            location = info[0];

        if(short_desc == "")
            short_desc = info[1];

        if(long_desc == "")
            long_desc = info[2];

        if(last_given == 0)
            last_given = info[3];

        if((council_desc == "") && (info[4] == ""))
            council_desc = m_describe_living(find_living(who));
    }

    if(council_desc == "")
        council_desc = m_describe_living(find_living(who));

    council_info[who] = ({ location, short_desc, long_desc, last_given,
        council_desc, council_title, 0, 0});
    SAVE;
}

public int
set_council_title (string who, string council_title)
{
    mixed    info;

    info = council_info[who];
    if(!pointerp(info))
        return 0;

    council_info[who][5] = council_title;

    SAVE;
}

public string
get_council_title (string who)
{
    mixed    info;

    info = council_info[who];
    if(!pointerp(info))
        return "";

    return council_info[who][5];

    SAVE;
}

public string find_council_title (string check_title)
{
    string      *people;
    int         i;
    string      title;

    people = m_indices (council_info);
    for (i = 0; i < sizeof (people); i++)
    {
        title = council_info[people[i]][5];
        if (title == check_title)
            return people[i];
    }

    return "";
}

/*
 * Function name: startup_procs
 * Description:   Function in which all functions which
 *                need to be called when the master is
 *                loaded will be places.
 *                Currently, the function will do the following:
 *                 * start a repeating alarm that will tally
 *                   any outstanding votes
 *                 * start an alarm to clean out members that
 *                   may no longer be players
 *                 * start an alarm to clean out applicants
 *                   who are no longer players
 *                 * if there are not the current requisite
 *                   number of council members, start a vote
 *                   for a council member
 */
public void
startup_procs()
{
    // every hour, check to see if any outstanding votes have completed
    set_alarm(10.0, 3600.0, m_tally_votes);

    // clean up the members once / day
    set_alarm(50.0, (60.0 * 60.0 * 24.0), clean_members);

    // clean up the applications once / day
    set_alarm(20.0, (60.0 * 60.0 * 24.0), clean_applications);

    // start a council election if there are currently
    // not enough council members
    set_alarm(60.0, (60.0 * 60.0 * 24.0), check_council_vote);
}


