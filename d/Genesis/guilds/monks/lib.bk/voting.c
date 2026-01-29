/*
 * File:     voting.c
 * Created:  Cirion, 1998.4.25
 * Modified: Cirion, 1999.11.28 Moved the specific votes into
 *               a separate package.
 * Purpose:  Voting/Council/Election functions for the monks
 *
 * This is a package that contains guild-specific votes for the
 * Order of the Dragon.
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>  /* Skill types (SS_OCCUP, et. al.) */
#include <composite.h> /* COMPOSITE_WORDS                 */
#include <std.h>       /* SECURITY                        */
#include <time.h>       /* SECURITY                        */

inherit MONK_LIB + "support";
inherit MONK_LIB + "votelib";

#define MAX_BOARD_HEADER_LENGTH   41

public int m_do_council_expel(string str);
static void m_remove_application(mixed who);


static int
m_member_count ()
{
    return MANAGER->count_members ();
}

/*
 * Function name: m_add_member
 * Description:   low-level function to just add the player name
 *                to the member list. Does not handle shadowing, etc.,
 *                which should be handled in the joining routines.
 * Arguments:     who - the player object or name
 * Returns:       1 if successful, 0 otherwise
 */
static int
m_add_member (mixed who)
{
    return MANAGER->add_member (who);
}

static int
m_add_member_message (mixed who, string msg, int send_now = 0)
{
    object ob;

    msg = m_append_newline(msg);

    if (send_now && (ob = m_get_living_ob(who)))
    {
        ob->catch_msg(msg);
        return 1;
    }
    else
        return MANAGER->add_member_message (who, msg);
}

static int
m_remove_member_message (mixed who, string msg)
{
    msg = m_append_newline(msg);

    return MANAGER->remove_member_message (who, msg);
}


static int
m_add_council_member(mixed who)
{
    int    ret;

    ret = MANAGER->add_council_member (who);


    if(ret) // enqueue a message saying that they have been added
    {
        m_log(m_get_name(who) + " was added as a council member.");

        // inform the member
        m_add_member_message (who, "You have been elected to the council.", 0);
    }
    else
        m_log("ERROR: " + m_get_name(who) + " was elected as a council member, but the "
            + "addition failed.");

    return ret;
}

static int
m_remove_council_member(mixed who)
{
    m_log(m_get_name(who) + " was removed as a council member.");
    return MANAGER->remove_council_member (who);
}


/******************************************************************
 *        Election functions
 */

/*
 * Function name: m_start_council_election
 * Description:   Begin a vote for a council election
 */
static void
m_start_council_election()
{

    // add a new vote for the council election
    m_add_vote("council election", "Vote to decide who will be promoted to "
        + "the council position.",
        (M_VOTE_MEMBERS_ONLY | M_VOTE_PEOPLE | M_VOTE_NO_SELF | M_VOTE_NO_SHOW),
        (60 * 60 * 24 * 7 * 2) + time(),
        MONKLIB, "m_tally_council_election", "the Council");

}

/*
 * Function name: m_tally_council_election
 * Description:   Tally the results of the council election,
 *                add a council member if there is a winner.
 * Arguments:     winners - array of winners
 *                name - the name of the vote (not used)
 *                by_who - the agent who created the vote (not used)
 * Returns:       1 if a council member has been successfully won
 *                    and added. 0 if failure. Failure will cause
 *                    the vote to continue until there is a
 *                    winner.
 */
public int
m_tally_council_election(mixed winners, string name, string by_who, mixed vdata)
{
    int       ret;
    string    msg, vsum;

    if(sizeof(winners) != 1) // we need exactly one winner
        return 0; // this will continue the vote

    ret = m_add_council_member(winners[0]); // add the winner as the council member

    vsum = "\n\nSummary of vote results: " + m_vote_summary(m_values(vdata[3]), 1) + "\n";

    // post a message indicating that the vote is done
    if(ret)
    {
        msg = "The results of the Council Election have been tallied. "
            + "The winner, who is now a new council member, "
            + "is " + capitalize(winners[0]) + "." + vsum + "\n\n";

        m_post_board_msg("Results of Council Election", "Ballot", msg);
    }

    return ret;

}



/*
 * Function name: m_start_council_expel
 * Description:   Begin a vote to boot a council member
 */
public int
m_do_council_expel(string str)
{
    notify_fail("Begin a vote to expel who from the council?\n");
    if(!strlen(str))
        return 0;

#define MONK_COUNCIL_EXPEL_VOTE_WARNING  "_monk_council_expel_vote_warned"
    str = lower_case(str);

    if(!m_query_council_member(str))
    {
        notify_fail(capitalize(str) + " is not currently a council member.\n");
        return 0;
    }

    // give them a warning first
    if(this_player()->query_prop(MONK_COUNCIL_EXPEL_VOTE_WARNING) != str)
    {
        this_player()->add_prop(MONK_COUNCIL_EXPEL_VOTE_WARNING, str);
        write("Are you sure you want to begin a vote to expel "
            + capitalize(str) + "?\nEnter the command again to confirm.\n");
        return 1;
    }

    // check to see if the player has been punished against voting
    if(m_query_punishment(this_player(), M_PUNISH_NOVOTE))
    {
        notify_fail("The Council has forbidden you from "
            + "participating in votes.\n");
        return 0;
    }


    // add a new vote for the council election
    if(!m_add_vote("expel counsellor " + str, "Vote to decide if "
        + capitalize(str) + " should be "
        + "expelled from the council.",
        (M_VOTE_MEMBERS_ONLY | M_VOTE_NO_SHOW | M_VOTE_YESNO),
        (60 * 60 * 24 * 7) + time(),
        MONKLIB, "m_tally_expel_election", this_player()->query_name()))
    {
        notify_fail("For some reason, you cannot do that.\n");
        return 0;
    }

    write("You begin a vote to expel " + capitalize(str) + ".\n");
    return 1;
}

/*
 * Function name: m_tally_expel_election
 * Description:   Tally the results of the council expulsion election,
 *                removes the council member is there is a winner.
 * Arguments:     winners - array of winners
 *                name - the name of the vote (not used)
 *                by_who - the agent who created the vote (not used)
 * Returns:       1 if a council member has been successfully won
 *                    and added. 0 if failure. Failure will cause
 *                    the vote to continue until there is a
 *                    winner.
 */
public int
m_tally_expel_election(string *votes, string name, string by_who, mixed vdata)
{
    int       num_winners, punish, dopunish;
    string    vote, vname, vsum;

    vname = name;

    if(sscanf(name, "expel counsellor %s", name) != 1)
        return 0;

    num_winners = sizeof(votes);

    vsum = "\n\nSummary of vote results: " + m_vote_summary(m_values(vdata[3])) + "\n";

    if(num_winners > 1) // a tie between yes and no: do not expel
        dopunish = 0;

    if(num_winners == 0) // no one voted: do not expel
        dopunish = 0;

    vote = votes[0]; // a single yes or no

    if(vote == "no") // we voted against the expulsion
        dopunish = 0;
    else
        dopunish = 1;

    // will we punish or no?
    if(dopunish)
    {
        m_remove_council_member(name); // remove the councellor
        // break the bad news to them, send now if possible
        m_add_member_message(name, "You have been voted out of "
            + "your council position in the Order of the "
            + "Dragon.\n", 1);

        // post the result on the private monk board
        m_post_board_msg("Counsellor " + capitalize(name) + " expelled",
            "Ballot", capitalize(name) + " has been voted to "
            + "be expelled from the council, effective "
            + "immediately.\n" + vsum + "\n",
            MONKBOARD);
    }
    else
    {
        // post the result on the private monk board
        m_post_board_msg("Counsellor " + capitalize(name)
            + " not expelled",
            "Ballot", capitalize(name) + " has been voted to "
            + "not be expelled from the council.\n" + vsum + "\n",
            MONKBOARD);
    }

    return 1;
}


/******************************************************************
 *        Application functions
 *
 * About applications: prospective members need to apply to
 *    the monks. If there are no current council members,
 *    then the application is automatically accepted (since
 *    there is no one to decide). Otherwise, a vote is
 *    begun in which only the council members may participate.
 *    The vote will end after one week, or when all the existing
 *    council members have case a vote (either "yes" or "no").
 *    If the vote is a tie, the member is accepted.
 *    If no one votes, that indicates that the council is idle
 *    and not doing its job: this, the applicant is accepted
 *    in this case as well.
 *    An applicant is rejected only if there are more "no" votes
 *    than "yes" votes.
 *    Applicant data is saved in the monk_manager save variables
 *    scheme, of the form ([ name : ({ status, stamp time }) ]).
 *    The status is as follows:
 *        0 - new applicant, there is no result of the vote yet
 *        1 - the applicant has been accepted, and can then join
 *        -1 - the applicant has been rejected, and may not join
 *
 *    The applicant information is deleted either when the
 *    player joins the guild, or when a certain amount of
 *    time has passed (MONK_APPLICATION_MAX_TIME: currently
 *    set at two months). In this way, applicants who have
 *    been rejected can re-apply after a certain amount
 *    of time, and players who have passed up their
 *    application chance for too long also can not join.
 */

/*
 * Function name: m_accept_application
 * Description:   accept the applicant into the monks. This
 *                will automatically be called when the application
 *                vote comes to a close and the result was "yes"
 * Arguments:     the name of the player to accept
 * Returns:       1, always (?)
 */
static int
m_accept_application(string name)
{
    // make sure the applicant is truly a player!
    if(!m_query_is_player(name))
        return 1;

    MANAGER->set_application_status (name, 1); // 1 is for approved
    return 1;

}

/*
 * Function name: m_reject_application
 * Description:   reject the applicant. This
 *                will automatically be called when the application
 *                vote comes to a close and the result was "no"
 * Arguments:     the name of the player to accept
 * Returns:       1, always (?)
 */
static int
m_reject_application(string name)
{
    // make sure the applicant is truly a player!
    if(!m_query_is_player(name))
        return 1;

    MANAGER->set_application_status (name, -1); // 1 is for rejected
    return 1;

}

/*
 * Function name: m_start_application
 * Description:   Start an application vote
 *                The vote will end either when all council
 *                members have voted, or the time limit has
 *                passed (one week).
 * Arguments:     who - string or object of the applicant
 */
static void
m_start_application(mixed who, int branch)
{
    string   name = m_get_name (who);
    string   desc;

    if (branch == SS_LAYMAN)
        desc = "Should " + capitalize(name) + " be allowed "
            + "entrance into the Layman branch of the monks?";
    else
        desc = "Should " + capitalize(name) + " be allowed "
            + "entrance into the Occupational branch of the monks?";

    desc += " Vote yes or no. A tie, or if no one votes, will "
        + "result in the application being approved. More no "
        + "votes than yes votes will result in the application "
        + "being rejected.";

    // add a new vote for the application, 30 day limit
    m_add_vote(lower_case(name) + " application", desc,
        (M_VOTE_COUNCIL_ONLY | M_VOTE_YESNO),
        (60 * 60 * 24 * 30) + time(),
        MONKLIB, "m_tally_application",
        "the Council",
        m_count_council_members());

}

/*
 * Function name: m_apply
 * Description:   apply for entrance into the monks. If there is
 *                currently a council, this will add the player
 *                to the application list, and starts up a vote.
 *                Otherwise, the player is immediatley accepted
 *                into the monks.
 * Arguments:     who - string or object of player
 *                branch - which branch of the guild (default = SS_OCCUP)
 * Returns:       1 if vote started, 0 if not, -1 for automatic
 *                    acceptance due to no council
 */
static int
m_apply(mixed who = this_player(), int branch = SS_OCCUP)
{
    string name = m_get_name(who);
    int    stat;

    // there are no council members -- simply
    // allow the applicant entrance into the
    // monks
    if(!m_count_council_members())
        return -1;

    stat = MANAGER->query_application_status(name);

    if(stat == 0) // already applied, no decision
    {
        notify_fail("You have already submitted your application "
            + "for membership. No decision has yet been made.\n");
        return 0;
    }

    if(stat == 1) // already been accepted
    {
        notify_fail("Your application has already been accepted -- there "
            + "is no need to apply again.\n");
        return 0;
    }

    if(stat == -1) // already been rejected
    {
        /*
        notify_fail("Your application has been rejected. You cannot "
            + "apply again for "
            + CONVTIME(MANAGER->query_application_time_left(name))
            + ".\n");
        return 0;
        */

        // Cirion 1999.11.22: Allow for immediate re-application
        // ### TODO: the tell really shouldn't be here, but in the
        // m_do_apply method.
        m_remove_application (name);

        if (objectp (who))
            who->catch_tell ("You resubmit your application...\n");
    }


    // set the application status in the manager
    MANAGER->set_application_status (name, 0, branch); // 0 is for a new applicant

    // start the application voting process
    m_start_application (who, branch);
    return 1;
}

/*
 * Function name: m_remove_application
 * Description:   Remove an applicant, when they
 *                join the guild.
 * Arguments:     string or object of the player to remove
 * Returns:       void
 */
static void
m_remove_application(mixed who)
{
    string name = m_get_name(who);

    MANAGER->delete_application(name);
}

/*
 * Function name: m_tally_application
 * Description:   Tally the results of the application
 * Arguments:     votes - the winning votes (array of "yes" or "no")
 *                name - the name of the vote, which happens to
 *                    also be the name of the player to accept
 *                by_who - the agent who created the vote (not used)
 * Returns:       1 if the vote successfully completed
 */
public int
m_tally_application(string *votes, string name, string by_who)
{
    int       num_winners;
    string    vote;

    num_winners = sizeof(votes);

    // vote name should be "cirion application", e.g.
    if(!sscanf(name, "%s application", name))
        return 0;

    if(num_winners > 1) // a tie between yes and no: allow the applicant in
        return m_accept_application(name);

    if(num_winners == 0) // no one voted: idle council (BAAAD council!) Accept the applicant.
        return m_accept_application(name);

    vote = votes[0]; // a single yes or no

    if(vote == "no") // we voted against him
        return m_reject_application(name);
    else
        return m_accept_application(name);

}



/******************************************************************
 *        Punishment functions
 */

/*
 * Function name: m_add_punishment
 * Description:   Adds a specified punishment to a
 *                player.
 * Arguments:     who - string or object of the player
 *                punishment - punishment to add to the
 *                    bitwise punishment specification.
 * Returns:       1 if successful
 */
static int
m_add_punishment(mixed who, int punishment)
{
    return MANAGER->add_punishment(m_get_name(who), punishment);
}

/*
 * Function name: m_remove_punishment
 * Description:   Removes a given punishment from a player.
 *
 * Arguments:     who - player to remove the punishment from
 *                punishment - -1 to remove all punishments,
 *                    or the specified punishment to extract
 *                    it from the list of values.
 * Returns:       1 if successful
 */
static varargs int
m_remove_punishment(mixed who, int punishment = -1)
{
    return MANAGER->remove_punishment(m_get_name(who), punishment);
}

/*
 * Function name: m_punishment_from_name
 * Description:   Returns the punishment ID from
 *                the string description of the punishment.
 * Arguments:     the string to check for
 * Returns:       the punishment ID, or -2 if the string
 *                is invalid.
 */
static int
m_punishment_from_name(string str)
{
    switch(str)
    {
        case "notrain":
            return M_PUNISH_NOTRAIN;
        case "exile":
            return M_PUNISH_EXILE;
        case "banish":
            return M_PUNISH_BANISH;
        case "nobuy":
            return M_PUNISH_NOBUY;
        case "disgrace":
            return M_PUNISH_DISGRACE;
        case "novote":
            return M_PUNISH_NOVOTE;

        default:
            return -2;
    }

    return -2;
}

static string
m_punish_desc (int level)
{
    string          *strs = ( {} );

    if (level & M_PUNISH_NOTRAIN)
        strs += ({ "notrain" });
    if (level & M_PUNISH_EXILE)
        strs += ({ "exile" });
    if (level & M_PUNISH_BANISH)
        strs += ({ "banish" });
    if (level & M_PUNISH_NOBUY)
        strs += ({ "nobuy" });
    if (level & M_PUNISH_DISGRACE)
        strs += ({ "disgrace" });
    if (level & M_PUNISH_NOVOTE)
        strs += ({ "novote" });

    return COMPOSITE_WORDS (strs);
}

/******************************************************************
 *        Council functions
 */

/*
 * Function name: m_tally_punish_vote
 * Description:   called as a result of the punishment vote,
 *                it will tally the results, and, if there
 *                are more yes votes than no, then the
 *                punishment is added for the player. Will
 *                also post the results of the vote on the
 *                monk council board.
 * Arguments:     votes - the votes
 *                name - the name of the vote, will be of
 *                    the form "punish <player name> <punishment>"
 * Returns:       1 if the successful
 */
public int
m_tally_punish_vote(string *votes, string name, string by_who, mixed vdata)
{
    int       num_winners, punish, dopunish;
    string    vote, ptype, vname, vsum;

    vname = name;

    if(sscanf(name, "punish %s %s", name, ptype) != 2)
        return 0;

    // get the punishment name from the vote
    if((punish = m_punishment_from_name(ptype)) == -2)
        return 0;

    num_winners = sizeof(votes);

    vsum = "\n\nSummary of vote results: " + m_vote_summary(m_values(vdata[3])) + "\n";

    if(num_winners > 1) // a tie between yes and no: do not punish
        dopunish = 0;

    if(num_winners == 0) // no one voted: do not punish
        dopunish = 0;

    vote = votes[0]; // a single yes or no

    if(vote == "no") // we voted against him
        dopunish = 0;
    else
        dopunish = 1;

    // will we punish or no?
    if(dopunish)
    {
        // actually add the punishment type for the player
        if(!m_add_punishment(name, punish))
            m_log("punishment addition for " + name + " of type "
                + ptype + "(" + punish + ") returned 0");
        else
        {
            m_log("punishment of type " + ptype + " (" + punish
                + ") was added for " + name);

            // post the result on the private monk board
            m_post_board_msg("Results of vote: " + vname,
                "Ballot", capitalize(name) + " has been voted to "
                + "be punished with type: " + ptype + vsum + "\n",
                MONKBOARDPRIV);

        }
    }
    else
    {
        // post the result on the private monk board
        m_post_board_msg("Results of vote: " + vname,
            "Ballot", capitalize(name) + " has been voted to "
            + "not be punished with type: " + ptype + vsum + "\n",
            MONKBOARDPRIV);

    }

    return 1;
}

/*
 * Function name: m_do_punish
 * Description:   Command to start a punishment vote
 *
 * Arguments:     the string passed to the command
 * Returns:       1 if the command completed successfully
 */
public int
m_do_punish(string str)
{
    string name, punish;

    // security check
    if(!m_query_council_member(this_interactive(), 1))
    {
        notify_fail("You are not allowed.\n");
        return 0;
    }

    notify_fail("punish <who> <how>? Possible punishments are: "
        + "notrain, novote, nobuy, banish, exile, disgrace\n");
    if(!strlen(str))
        return 0;

    if(sscanf(str, "%s %s", name, punish) < 2)
        return 0;

    if(!m_query_monk(name))
    {
        notify_fail(name + " is not a monk.\n");
        return 0;
    }

    // check to see if it is a valid punishment
    if(m_punishment_from_name(punish) == -2)
    {
        notify_fail("Invalid punishment type: " + punish
            + ": possible punishments are "
            + "notrain, novote, nobuy, banish, exile, disgrace\n");
        return 0;
    }

    // check to make sure they are not currently
    // punished with that type
    if(m_query_punishment(name, m_punishment_from_name(punish)))
    {
        notify_fail(capitalize(name) + " is already "
            + "punished with " + punish + ".\n");
        return 0;
    }

    // add a new vote for the application
    if(!m_add_vote("punish " + lower_case(name) + " " + punish,
        "Should " + capitalize(name) + " be punished with type "
        + punish + "? A tie, or if no one votes, will result "
        + "in the punishment not being added.",
        (M_VOTE_COUNCIL_ONLY | M_VOTE_YESNO),
        (60 * 60 * 24 * 7) + time(),
        MONKLIB, "m_tally_punish_vote",
        this_player()->query_real_name(),
        m_count_council_members()))
    {
        write("That vote has already been started.\n");
        return 1;
    }

    write("You start a vote for whether " + capitalize(name)
        + " should be punished with type " + punish + "\n");
    return 1;
}


/*
 * Function name: m_tally_reprieve_vote
 * Description:   called as a result of the reprieve vote,
 *                it will tally the results, and, if there
 *                are more yes votes than no, or a tie, then the
 *                punishment is removed for the player. Will
 *                also post the results of the vote on the
 *                monk council board.
 * Arguments:     votes - the votes
 *                name - the name of the vote, will be of
 *                    the form "reprieve <player name> <punishment>"
 * Returns:       1 if the successful
 */
public int
m_tally_reprieve_vote(string *votes, string name, string by_who, mixed vdata)
{
    int       num_winners, punish, doreprieve;
    string    vote, ptype, vname, vsum;

    vname = name;

    if(sscanf(name, "reprieve %s %s", name, ptype) != 2)
        return 0;

    // get the punishment name from the vote
    if((punish = m_punishment_from_name(ptype)) == -2)
        return 0;

    num_winners = sizeof(votes);

    vsum = "\n\nSummary of vote results: " + m_vote_summary(m_values(vdata[3])) + "\n";

    if(num_winners > 1) // a tie between yes and no: reprieve
        doreprieve = 0;

    if(num_winners == 0) // no one voted: do not reprieve
        doreprieve = 0;

    vote = votes[0]; // a single yes or no

    if(vote == "no") // we voted against him
        doreprieve = 0;
    else
        doreprieve = 1;

    // will we reprieve or no?
    if(doreprieve)
    {
        // actually add the punishment type for the player
        if(!m_remove_punishment(name, punish))
            m_log("punishment removal for " + name + " of type "
                + ptype + "(" + punish + ") returned 0");
        else
        {
            m_log("punishment of type " + ptype + " (" + punish
                + ") was removed for " + name);

            // post the result on the private monk board
            m_post_board_msg("Results of vote: " + vname,
                "Ballot", capitalize(name) + " has been voted to "
                + "have lifted the punishment with type: " + ptype + vsum + ".\n",
                MONKBOARDPRIV);

        }
    }
    else
    {
        // post the result on the private monk board
        m_post_board_msg("Results of vote: " + vname,
            "Ballot", capitalize(name) + " has been voted to "
            + "not have the punishment of type: " + ptype + " lifted. " + vsum + "\n",
            MONKBOARDPRIV);

    }

    return 1;
}


/*
 * Function name: m_do_reprieve
 * Description:   Command to start a reprieve punishment vote
 *
 * Arguments:     the string passed to the command
 * Returns:       1 if the command completed successfully
 */
public int
m_do_reprieve(string str)
{
    string name, punish;

    // security check
    if(!m_query_council_member(this_interactive(), 1))
    {
        notify_fail("You are not allowed.\n");
        return 0;
    }

    notify_fail("reprieve <who> <punishment>? Possible punishments are: "
        + "notrain, novote, nobuy, banish, disgrace, exile\n");
    if(!strlen(str))
        return 0;

    if(sscanf(str, "%s %s", name, punish) < 2)
        return 0;

    if(!m_query_monk(name))
    {
        notify_fail(name + " is not a monk.\n");
        return 0;
    }

    // check to see if it is a valid punishment
    if(m_punishment_from_name(punish) == -2)
    {
        notify_fail("Invalid punishment type: " + punish
            + ": possible punishments are "
            + "notrain, novote, nobuy, banish, disgrace, exile\n");
        return 0;
    }

    // check to make sure they really are currently
    // punished with that type
    if(!m_query_punishment(name, m_punishment_from_name(punish)))
    {
        notify_fail(capitalize(name) + " is not currently "
            + "punished with " + punish + ".\n");
        return 0;
    }

    // add a new vote for the application
    if(!m_add_vote("reprieve " + lower_case(name) + " " + punish,
        "Should the punishment of " + punish + " be lifted from "
        + capitalize(name) + "? Vote yes or no. A tie will result "
        + "in the punishment being lifted.",
        (M_VOTE_COUNCIL_ONLY | M_VOTE_YESNO),
        (60 * 60 * 24 * 7) + time(),
        MONKLIB, "m_tally_reprieve_vote",
        this_player()->query_real_name(),
        m_count_council_members()))
    {
        write("That vote has already been started.\n");
        return 1;
    }

    write("You start a vote for whether " + capitalize(name)
        + " should have the punishment of type " + punish
        + " lifted\n");
    return 1;

}

/*
 * Function name: m_do_resign
 * Description:   command to allow a player to resign
 *                from the council. Will first give a
 *                warning before removing the player from
 *                the council.
 * Arguments:     argument passed to the command
 * Returns:       1 if the command executed successfully
 */
public int
m_do_resign (string str)
{
#define MONK_RESIGN_WARNING_PROP    "monk_resign_warning_prop"


    // give a warning first
    if(!(this_interactive()->query_prop(MONK_RESIGN_WARNING_PROP)))
    {
        this_interactive()->add_prop(MONK_RESIGN_WARNING_PROP, 1);
        write("Are you sure you want to permemently step down "
            + "from the council? Enter the command again to "
            + "confirm.n");
        return 1;
    }

    if(!m_remove_council_member(this_interactive()))
    {
        write("A problem has occured: you have not been removed.\n"
            + "Please leave a bug report.\n");
        m_log("ERROR: " + this_interactive()->query_real_name()
            + " tried to resign from the council, but failed.");
        return 1;

    }

    write("You resign from the council.\n");
    m_log(this_interactive()->query_real_name() + " resigned from "
        + "the council.");

    // start a new council election vote, if necessary
    MANAGER->check_council_vote();

    return 1;
}

public int
m_list_punishment (string str)
{
    string          *punished;
    int             i;

    write ("The following members are punished:\n");
    write ("-----------------------------------\n");

    punished = MANAGER->query_punish_list ();

    for (i = 0; i < sizeof (punished); i++)
    {
        write (sprintf ("%-10s", capitalize (punished [i])));
        write (m_punish_desc (m_query_punishment (punished [i])) + "\n");
    }

    if (i == 0)
        write ("No members are currently punished.\n");

    return 1;
}

/*
 * Function name: m_council_init
 * Description:   initialize council commands. Will
 *                check to verify that the player is
 *                allowed to execute the commands.
 */
public void
m_council_init()
{
    if(m_query_council_member(this_interactive(), 1))
    {
        add_action(m_list_punishment, "punishlist");
        add_action(m_list_punishment, "list punished");
        add_action(m_do_punish, "punish");
        add_action(m_do_punish, "mpunish");
        add_action(m_do_reprieve, "reprieve");
        add_action(m_do_reprieve, "mreprieve");
        add_action(m_do_resign, "resign");
        add_action(m_do_resign, "mresign");
    }
}


/*
 * Function name: m_vote_init
 * Description:   Initialize voting commands
 */
public void
m_vote_init ()
{
    add_action (m_do_vote, "vote");
    add_action (m_do_vote, "mvote");
    add_action (m_do_vote_list, "votelist");
    add_action (m_do_vote_list, "mvotelist");
    add_action (m_do_vote_add, "voteadd");
    add_action (m_do_vote_add, "mvoteadd");
//    add_action (m_do_vote_remove, "voteremove");
//    add_action (m_do_vote_help, "help");
    add_action (m_do_vote_status, "votestatus");
    add_action (m_do_vote_status, "mvotestatus");
    add_action (m_do_vote_status, "voteinfo");
    add_action (m_do_vote_status, "mvoteinfo");

    // this is monk-specific, and not generic to the
    // voting procedures, but really seems to be the only place
    // to put it.
    add_action (m_do_council_expel, "expel");
    add_action (m_do_council_expel, "mexpel");

}

