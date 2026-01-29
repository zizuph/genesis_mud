/*
 * File:     voting.c
 * Created:  Cirion, 1998.4.25
 * Purpose:  Voting/Council/Election functions for the monks
 *
 * About voting: The is a somewhat generic set of
 *    procedures that enables voting on various
 *    topics. The voting data is stored in the
 *    MANAGER object (which uses save_object). When
 *    a vote is created, an end time is specified for
 *    the vote, after which the reults will be tallied.
 *    Also specified is a procedure to call (and the
 *    file in which it will be called), which will be
 *    passed the following parameters:
 *        winners - array of the highest values of the
 *            vote.
 *        name - the name of the vote
 *        who - the name of the person that created the vote
 *
 *    The default procedure is simply one that will send a
 *    Genesis mail to the creator of the vote with the
 *    results. If this procedure returns 1, then the vote
 *    is ended and the vote is deleted. Otherwise, the vote
 *    is re-tallied every hour until a successful call to
 *    the voting procedure. This can be used to ensure that
 *    the winner of the vote is unique, etc.
 *
 *    The vote_data mapping is as follows:
 *
 *    [0]by_who - name of the player who created the vote
 *    [1]props - bitwise properties of the vote
 *    [2]end_time - the time() time at which the vote will end
 *    [3]votes - mapping of ([ player : vote ])
 *    [4]end_file - file in which to call a function when the vote ends
 *    [5]end_proc - name of the function to call when the vote ends
 *    [6]vote_desc - textual description of the vote
 *    [7]end_threshhold - the number of votes after which the vote will be
 *        forced to end (default = -1, vote only ends after time limit
 *        is exceeded)
 *
 *        -Cirion, 1998.07.16
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>  /* Skill types (SS_OCCUP, et. al.) */
#include <composite.h> /* COMPOSITE_WORDS                 */
#include <std.h>       /* SECURITY                        */
#include <time.h>       /* SECURITY                        */

inherit MONK_LIB + "support";

#define MAX_BOARD_HEADER_LENGTH   41

/******************************************************************
 *        Interface to the Kaheda Master
 */


/*
 * Function name: m_add_vote
 * Description:   adds a new vote
 *
 * Arguments:     name - the title of the vote
 *                vote_desc - the description of the vote
 *                pros - bitwise voting properties. E.g.:
 *                    (M_VOTE_MEMBERS_ONLY | M_VOTE_PEOPLE)
 *                end_time - the time after which the voting will
 *                    be closed and results will be tallied (default
 *                    is one week)
 *                end_file - the file (object) in which a function
 *                    will be called to end the voting (default is
 *                    the monklib)
 *                end_proc - the function to call in the file when
 *                    the voting is closed (default is "m_post_vote_result")
 *                by_who - the person who created the vote (default is
 *                    the name of this_player())
 *                end_threshhold - some votes can automatically be ended
 *                    when a certain number of people have voted. If this
 *                    should not happen, setting it to -1 will force
 *                    the vote to wait until the time limit has
 *                    ended.
 * Returns:       1 if successful in creating the vote
 */
varargs static int
m_add_vote (string name, string vote_desc,
    int props, int end_time = time() + (60 * 60 * 24 * 7),
    string end_file = MONKLIB,
    string end_proc = "m_post_vote_result",
    string by_who = this_player()->query_real_name(),
    int end_threshhold = -1)
{
    // sinply add the vote in the manager
    return MANAGER->add_vote (name, props, end_time, end_file, end_proc,
        by_who, vote_desc, end_threshhold);
}

/*
 * Function name: m_may_see_vote
 * Description:   Check to see if the player is allowd
 *		  to see the vote
 * Arguments:     who: the player to check for
 *	          vote_data: the data of the vote to check
 * Returns:       1 if they may see the vote, 0 otherwise
 */
public int 
m_may_see_vote (object who, mixed vote_data)
{
    int vote_props;

    vote_props = vote_data[1];

    // is it a council-only vote?
    if((vote_props & M_VOTE_COUNCIL_ONLY) && 
	!m_query_council_member(who, 1))
    {
        notify_fail("You may not see that vote.\n");
        return 0;
    }

    if((vote_props & M_VOTE_COUNCIL_ELDER_ONLY) && 
	!m_query_council_or_elder(who, 1))
    {
        notify_fail("You may not see that vote.\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: m_remove_vote
 * Description:   removes a vote from the mapping
 *
 * Arguments:     the name of the vote to remove
 * Returns:       1 if successful
 */
static int
m_remove_vote (string name)
{
    return MANAGER->remove_vote(name);
}

/*
 * Function name: m_vote_winner
 * Description:   Checks the vote that has the highest
 *                number of inctances.
 * Arguments:     the name of the vote
 * Returns:       array of the highest values (one value would
 *                    signify a unique winner)
 */
static mixed
m_vote_winner (string vote_name)
{
    mixed      vote_data;
    int        end_time;
    mapping    vote_map;
    mapping    votes;

    votes = MANAGER->query_vote(); // get all the votes from the manager

    if(member_array(vote_name, m_indices(votes)) == -1)
    {
        notify_fail("There is no such vote.\n");
        return 0;
    }

    vote_data = votes[vote_name];
    end_time = vote_data[2];
    vote_map = vote_data[3];

    // return the element of the array with the most instances
    return m_most_values_array(m_values(vote_map));
}

/*
 * Function name: m_tally_votes
 * Description:   run through the votes and tally the
 *                results if the voting is ended
 * Arguments:     force - set to 1 to force the tallying of
 *                    all votes (without wailing until the end time)
 */
varargs void
m_tally_votes (int force = 0)
{
    mapping    votes;
    mixed      winners;
    mixed      vote_data;
    string     *indices, vote_file, vote_proc, by_who;
    mixed      values;
    int        i, end_threshhold, num_votes;

    votes = MANAGER->query_vote(); // get all the votes from the manager

    indices = m_indices(votes);
    values = m_values(votes);

    for(i=0;i<sizeof(indices);i++)
    {
        vote_data = votes[indices[i]];
        end_threshhold = vote_data[7];

        num_votes = sizeof (m_indices (vote_data[3]));

        // possible ways in which a vote can end:
        // 1. the end time has passed
        // 2. we have reached our threshhold of votes
        // 3. we specified the force flag (debugging only)
        if((vote_data[2] <= time()) || force ||
            ((end_threshhold > -1) && (num_votes >= end_threshhold)))
        {
            winners = m_vote_winner (indices[i]);

            vote_file = vote_data[4];
            vote_proc = vote_data[5];
            by_who = vote_data[0];

            // call the end proc, which will return 1 for success
            if(call_other(vote_file, vote_proc, winners, indices[i], by_who, vote_data))
            {
                m_remove_vote(indices[i]); // get rid of the vote now
                m_log("vote for \"" + indices[i] + "\" completed. Winner(s): "
                    + COMPOSITE_WORDS(winners), "vote");

            }
            else // log the failure
            {
                // Votes like council elections may not be removed for
                // a while, so it may not be necessary to fill the logs
                // with this message
                m_log("Error: vote for \"" + indices[i] + "\" completed, "
                    + "but vote proc: " + vote_proc + " (in " + vote_file
                    + ") returned 0. Vote is not removed.", "vote");

            }

        }
    }
}

/*
 * Function name: m_cast_vote
 * Description:   casts a vote from a player for an
 *                existsing vote.
 * Arguments:     vote_name - the name of the vote
 *                vote - the vote to case
 *                by_who - the person casting the vote
 * Returns:       1 if success
 */
static varargs int
m_cast_vote (string vote_name, string vote,
    string by_who = this_player()->query_real_name())
{
    mixed      vote_data;
    int        props, end_threshhold, num_votes, ret;
    mapping    vote_map, votes;
    mixed      member_data;
    int        join_time;

    votes = MANAGER->query_vote();

    if(member_array(vote_name, m_indices(votes)) == -1)
    {
        notify_fail("There is no such vote.\n");
        return 0;
    }

    vote_data = votes[vote_name];
    props = vote_data[1];

    // Validate the vote based on its peoperties
    if (props & M_VOTE_PEOPLE) // may only vote for people
    {
        notify_fail("No such player: " + vote + ".\n");
        vote = lower_case(vote);
        if(!(SECURITY->exist_player(vote)))
            return 0;
    }

    if (props & M_VOTE_MEMBERS_ONLY) // only members may vote
    {
        notify_fail("Only members may vote.\n");
        if(!m_query_monk())
            return 0;
    }

    // check to see if the player has been punished against voting
    if(m_query_punishment(this_player(), M_PUNISH_NOVOTE))
    {
        notify_fail("The Council has forbidden you from "
            + "participating in votes.\n");
        return 0;
    }


    member_data = (MANAGER->query_members())[m_get_name(this_player ())];
    if(sizeof(member_data))
    {
        join_time = member_data[0]; // get the join time for that member

        // Only allow players who have been with the guild for
        // over a month participate in the vote.
        if (join_time > (time () - (30 * 24 * 60 * 60)))
        {
            notify_fail ("You may only participate in a vote once "
                + "you have been with the Order for over a month.\n");
            return 0;
        }
    }

    if (props & M_VOTE_DISALLOW_WIZARDS) // wizards can't vote
    {
        notify_fail("Wizards may not participate in this vote.\n");
        if(m_query_wizard_or_jr())
            return 0;
    }

    if (props & M_VOTE_NO_SELF) // cannot vote for yourself
    {
        notify_fail("You cannot vote for yourself.\n");
        if (lower_case(by_who) == lower_case(vote))
            return 0;
    }

    if (props & M_VOTE_YESNO) // can only vote yes or no
    {
        vote = lower_case(vote);
        if(vote == "yae")
            vote = "yes";
        if(vote == "aye")
            vote = "yes";
        if(vote == "nae")
            vote = "no";

        notify_fail("You may only vote yes or no for this vote.\n");
        if(vote != "yes" && vote != "no")
            return 0;
    }

    ret = MANAGER->cast_vote(vote_name, vote, by_who);

    // if we specified an ending threshhold, and
    // the new vote has reached that threshhold, then
    // we will set an alarm to tally the votes immediatley.
    end_threshhold = vote_data[7];
    num_votes = sizeof (m_indices (vote_data[3]));

    if((end_threshhold > -1) && (num_votes >= end_threshhold))
        set_alarm(1.0, 0.0, m_tally_votes);

    return ret;
}


/*
 * Function name: m_dump_votes
 * Description:   debugging function to dump the values
 *                of all the votes.
 */
public void
m_dump_votes ()
{
    dump_mapping(MANAGER->query_vote());
}

/*
 * Function name: m_has_voted
 * Description:   Returns the vote if the player has voted for
 *		  this particular vote, or 0 if the player
 *		  has not voted.
 */
public string
m_has_voted (mixed who, string vote_name)
{
    mapping votes = MANAGER->query_vote();
    mapping vt_data;
    string name = m_get_name (who);

    if (!(votes [vote_name]))
	return 0;

    vt_data = votes [vote_name][3];
    if (!vt_data)
	return 0;


    if (vt_data [name])
	return vt_data [name];
    else
	return 0;
}

/*
 * Function name: m_vote_summary
 * Description:   Gives a textual description of the
 *                votes so far
 * Arguments:     vts - an array of votes, e.g. ({ "yes", "no", "no", "no" })
 *                cap - 1 if you want the results to be capitalized
 * Returns:       a summary of the votes. e.g., "one vote for yes,
 *                    three votes for no."
 */
static varargs string
m_vote_summary(string *vts, int cap = 0)
{
    mapping    vt_map = ([]);
    int        i;
    string     *ind, *desc = ({}), nm;

    if(!sizeof(vts))
        return "";

    for(i=0;i<sizeof(vts);i++)
    {
        if(!vt_map[vts[i]])
            vt_map[vts[i]] = 1;
        else
            vt_map[vts[i]]++;
    }    

    ind = m_indices(vt_map);
    for(i=0;i<sizeof(ind);i++)
    {
        if(cap)
            nm = capitalize(ind[i]);
        else
            nm = ind[i];

        if(vt_map[ind[i]] == 1)
            desc += ({ "one vote for " + nm });
        else
            desc += ({ LANG_WNUM(vt_map[ind[i]]) + " votes for " + nm });
    }

    return COMPOSITE_WORDS(desc); // return the composite for the vote summary array
}


/*
 * Function name: m_mail_vote_result
 * Description:   default end proc for votes: it will
 *                simply mail the result of the vote to
 *                the person that created it.
 * Arguments:     winners - array of winners of the vote
 *                name - name of the vote
 *                by_who - the person to whom the mail should
 *                    be sent
 *                vote_data - the voting data
 * Returns:       1 if success
 * Note:          Function needs to be public, as it is called
 *                from the vote repository.
 */
public int
m_mail_vote_result (mixed winners, string name, string by_who, mixed vote_data)
{
    string msg = "";

    msg = "\nThis message is informing you that the vote you "
        + "created by the name of: " + name + " has ended. The "
        + "following specified the winner(s) of the vote:\n\n";

    msg += COMPOSITE_WORDS(winners);
    msg += "\n\n";

    m_sendmail(by_who, "Results of the vote: " + name, msg);

    // even if we fail to send the mail, we should end
    // the vote anyway, since failure to do so may result
    // in a 'stuck' vote that is tallied every hour and
    // never ends.
    return 1;
}


/*
 * Function name: m_post_vote_result
 * Description:   default end proc for votes: it will
 *                simply post the result of the vote on
 *                the monks board.
 * Arguments:     winners - array of winners of the vote
 *                name - name of the vote
 *                by_who - the person to whom the mail should
 *                    be sent
 *                vote_data - the voting data
 *                board - the board on which to post
 * Returns:       1 if success
 * Note:          Function needs to be public, as it is called
 *                from the vote repository.
 */
public int
m_post_vote_result (mixed winners, string name, string by_who,
    mixed vote_data, string board = MONKBOARD)
{
    string    msg = "";
    string    subject;
    string    winner;
    mapping   vote_results;


    msg = "\nThe vote: \"" + name + "\" has ended.\n";

    msg += "The description of the vote is as follows: "
        + vote_data[6] + "\n\n";

    msg+= "The winner(s) of the vote: ";

    winner = COMPOSITE_WORDS(winners);

    if (!strlen(winner))
        msg += "no votes were cast\n";
    else
        msg += winner + "\n";

    msg += "\n\n";

    vote_results = vote_data[3];
    msg += "Current summary of vote results: "
        + m_vote_summary(m_values(vote_results)) + "\n";

    subject = "Results of vote: \"" + name + "\"";

    if (strlen(subject) > MAX_BOARD_HEADER_LENGTH)
        subject = "Results of vote";

    if(!m_post_board_msg(subject,
        "Ballot", msg, board))
        m_log ("tried to post the results of the "
            + "vote: \"" + name + "\", but m_post_board_msg() "
            + "returned 0.", "vote");

    // even if we fail to post the note, we should end
    // the vote anyway, since failure to do so may result
    // in a 'stuck' vote that is tallied every hour and
    // never ends.
    return 1;
}

public string *
m_get_vote_list ()
{
    mixed     votes, vote_data;
    string   *vote_names;
    string    vname, vres, end_desc;
    int       i, vote_props, saw_votes;
    string   *allowed_vote_names = ({ });

    votes = MANAGER->query_vote();
    vote_names = m_indices (votes);

    for (i=0;i<sizeof(vote_names);i++)
    {
        vote_data = votes[vote_names[i]];
        vote_props = vote_data[1];

	if (!m_may_see_vote (this_interactive (), vote_data))
	    continue;

        allowed_vote_names += ({ vote_names [i] });
    }

    return allowed_vote_names;    
}


/*
 * Function name: m_do_vote
 * Description:   cast a vote for a pre-existing vote
 *
 * Arguments:     str - the argument to the command
 * Returns:       1 is successful
 */
public int
m_do_vote (string str)
{
    mixed     votes, vote_data;
    string   *vote_names;
    string    vname, vres;
    string    has_voted;
    int       ind, vote_props;

    votes = MANAGER->query_vote();
    vote_names = m_indices (votes);

    notify_fail ("Vote <vote name> for <vote>?\n");
    if (!strlen(str))
        return 0;

    sscanf (str, "%s for %s", vname, vres);
    if(!strlen(vname) || !strlen(vres))
        return 0;

    if (!sizeof(vote_names))
    {
        notify_fail ("There are currently no active votes which "
            + "you may participate in.\n");
        return 0;
    }

    // check to see if the player has been punished against voting
    if(m_query_punishment(this_player(), M_PUNISH_NOVOTE))
    {
        notify_fail("The Council has forbidden you from "
            + "participating in votes.\n");
        return 0;
    }

    notify_fail ("No such votes. Available votes are: "
        + COMPOSITE_WORDS (m_get_vote_list ()) + ".\n");
    if ((ind = member_array (vname, vote_names)) == -1)
        return 0;

    vote_data = votes[vname];
    vote_props = vote_data[1];

    // is it a council-only vote?
    if (!m_may_see_vote (this_interactive (), vote_data))
    {
	notify_fail ("No such votes. Available votes are: "
	    + COMPOSITE_WORDS (m_get_vote_list ()) + ".\n");
	return 0;
    }

    // actually cast the vote
    has_voted = m_has_voted (this_player (), vname);

    if (m_cast_vote (vname, vres))
    {
	if (has_voted && has_voted == vres)
	    write ("You have already cast your vote for \"" + has_voted
		+ "\" for the vote \"" + vname + "\".\n");
	else if (has_voted)
	    write ("You change your vote from \"" + has_voted
		+ "\" to \"" + vres
		+ "\" for the vote \"" + vname + "\".\n");
	else
	    write ("You cast your vote for \"" + vres
		+ "\" for the vote \"" + vname + "\".\n");

        return 1;
    }
    else
        return 0; // m_cast_vote() handles notify_fail()

}

/*
 * Function name: m_do_vote_list
 * Description:   List all active votes
 *
 * Arguments:     The string passed in
 * Returns:       1 is success
 */
public int
m_do_vote_list (string str, int quiet_and_return_count = 0, 
    object for_who = this_player ())
{
    mixed     votes, vote_data;
    string   *vote_names;
    string    vname, vres, end_desc;
    int       i, vote_props, saw_votes;
    int	      num_unvoted_votes = 0;
    string    prefix = "";

    votes = MANAGER->query_vote();
    vote_names = m_indices (votes);

    if (!sizeof(vote_names))
    {
        notify_fail ("There are currently no active votes which "
            + "you may see.\n");
        return 0;
    }

    saw_votes = 0;

    if (!quiet_and_return_count)
    {
	write (" ______________________________________________"
	    + "_______________________________\n");
	write (sprintf ("%-77s%s",
	    "| The following votes are available:", "|") + "\n");
	write(sprintf("%-40s%-37s%s\n", "| Vote Name", "Time Remaining","|"));
	write ("|_____________________________________________"
	    + "_______________________________|\n");
    }


    for (i=0;i<sizeof(vote_names);i++)
    {
        vote_data = votes[vote_names[i]];
        vote_props = vote_data[1];

	if (!m_may_see_vote (this_interactive (), vote_data))
	    continue;

        if (vote_data[2] <= time())
            end_desc = "ended";
        else
            end_desc = CONVTIME (vote_data[2] - time());

        saw_votes++;

	if (!m_has_voted (for_who, vote_names [i]))
	{
	    prefix = "*";
	    num_unvoted_votes++;
	}
	else
	{
	    prefix = " ";
	}

	if (!quiet_and_return_count)
	    write(sprintf("%s%-38s%-38s%s\n", "|", prefix + vote_names[i], 
		end_desc, "|"));
    }

    if (!quiet_and_return_count)
	write ("|_____________________________________________"
	    + "_______________________________|\n");

    if (saw_votes && !quiet_and_return_count)
    {
        write (sprintf ("%-77s%s", 
	    "| For more information on a particular vote, "
            + "do \"voteinfo <vote name>\"", "|") + "\n");
	write ("|______________________________________________"
	    + "______________________________|\n");
    }

    if (!quiet_and_return_count)
	return 1;
    else
	return num_unvoted_votes;
}


/*
 * Function name: m_get_vote_data
 * Description:   Gets the data associated with
 *                a particular vote.
 * Arguments:     the name of the vote
 * Returns:       the vote data
 */
public mixed
m_get_vote_data (string vote_name)
{
    mixed     votes;
    string   *vote_names;
    string    vname, vres;
    int       ind;

    votes = MANAGER->query_vote();
    vote_names = m_indices (votes);

    notify_fail ("No such vote.\n");
    if (!sizeof(vote_names))
        return 0;

    notify_fail ("No such vote. Available votes are: "
        + COMPOSITE_WORDS (m_get_vote_list ()) + ".\n");
    if (!strlen(vote_name))
        return 0;

    if ((ind = member_array (vote_name, vote_names)) == -1)
        return 0;

    return votes[vote_name];
}


/*
 * Function name: m_do_vote_add
 * Description:   Command to add a new vote.
 *
 * Arguments:     the string passed in
 * Returns:       1 if success
 */
public int
m_do_vote_add (string str)
{
    string    helpstr, vote_name, vote_desc, props;
    int       vote_props, end_time, res;

    helpstr = "Syntax: "
        + query_verb ()
        + " <vote name>,<end time>,<vote description>,"
        + "[properties]\n"
        + "  <vote name>         - the name of the vote to create\n"
        + "  <end time>          - the number of days before which the vote\n"
        + "        will end and the results will be tallied.\n"
        + "  <vote description>  - a brief description of the vote.\n"
        + "  [vote properties]   - the properties of the vote, separated by spaces:\n"
        + "        membersonly: only members may perticipate in the vote\n"
        + "        playervotes: a vote can only be cast for players\n"
        + "        yesnovotes:  a vote can be only \"yes\" or \"no\"\n"
        + "        anonymous:   the vote is by secret ballot\n";

    if (m_query_council_member (this_interactive (), 1))
	helpstr += "        council:     only council members may vote\n";

    if (m_query_council_or_elder (this_interactive (), 1))
	helpstr += "        elders:       only council "
	    + "members or elders may vote\n";

    helpstr +=
        "\nExample: " + query_verb() + " greatest warrior,10,Who is the\n"
        + "         greatest warrior in Genesis,playervotes membersonly anonymous\n";

    notify_fail (helpstr);
    if (!strlen(str))
        return 0;

    if (sscanf (str, "%s,%d,%s,%s", vote_name, end_time, vote_desc, props) < 3)
        return 0;

    if (end_time > 30) // max of 1 month for a vote
    {
        notify_fail ("The vote cannot last for more than thirty days.\n");
        return 0;
    }

    if (end_time < 1) 
    {
        notify_fail ("The vote must last for at least one day.\n");
        return 0;
    }

    if (strlen(vote_name) > 25)
    {
        notify_fail ("The name of that vote is too long. Please shorten it.\n");
        return 0;
    }

    // check to see if the player has been punished against voting
    if(m_query_punishment(this_player(), M_PUNISH_NOVOTE))
    {
        notify_fail("The Council has forbidden you from "
            + "participating in votes.\n");
        return 0;
    }

    if(wildmatch("*membersonly*", props))
        vote_props |= M_VOTE_MEMBERS_ONLY;

    if(wildmatch("*playervotes*", props))
        vote_props |= M_VOTE_PEOPLE;

    if(wildmatch("*yesnovote*", props))
        vote_props |= M_VOTE_YESNO;

    if(wildmatch("*anonymous*", props))
        vote_props |= M_VOTE_NO_SHOW;

    if(wildmatch("*elders*", props))
        vote_props |= M_VOTE_COUNCIL_ELDER_ONLY;

    if(wildmatch("*council*", props))
        vote_props |= M_VOTE_COUNCIL_ONLY;

    res = m_add_vote (vote_name, vote_desc, vote_props, ((end_time * 60 * 60 * 24) + time()));

    if (!res)
        return 0;

    write ("You add the vote named: \"" + vote_name + "\".\n");
    return 1;
}


public int
m_do_vote_remove (string str)
{
    mixed   vote_data = MANAGER->query_vote (str);
    int	    end_time, vote_props;
    string  creator;
    int	    success;

    if (!vote_data || !m_may_see_vote (this_interactive (), vote_data))
    {
	notify_fail ("No such vote \"" + str + "\"\n");
	return 0;
    }

    end_time = vote_data[2];
    creator = vote_data[0];
    vote_props = vote_data[1];

    if (creator != this_interactive ()->query_real_name () &&
	!m_query_auth_wizard (this_interactive ()))
    {
	notify_fail ("Only the creator of a vote may remove it.\n");
	return 0;
    }

    if ((vote_props & M_VOTE_COUNCIL_ONLY) ||
	(vote_props & M_VOTE_COUNCIL_ELDER_ONLY))
    {
	if (!m_query_auth_wizard (this_interactive ()))
	{
	    notify_fail ("Council or Elder votes may not ever be "
		+ "removed.\n");
	    return 0;
	}

    }

    if (!(success = m_remove_vote (str)))
	write ("You fail to remove the vote \"" + str + "\" for "
	    + "some reason.\n");
    else
	write ("You remove the vote \"" + str + "\".\n");

    m_log (this_interactive ()->query_name () + " removed the "
	+ "vote \"" + str + "\" (" + (success ? "success" : "failed")
	+ ")");
    return 1;
}



/*
 * Function name: m_do_vote_stats
 * Description:   Command to get the current status
 *                of a vote.
 * Arguments:     The name of the vote
 * Returns:       1 if successful
 */
public int
m_do_vote_status (string str)
{
    mixed      vote_data;
    mapping    vote_results;
    int        end_time, i, vote_props, remaining_votes;
    string     creator, *voters, end_desc, voter_show;

    if(!(vote_data = m_get_vote_data (str)))
        return 0;

    end_time = vote_data[2];
    vote_results = vote_data[3];
    creator = vote_data[0];
    vote_props = vote_data[1];

    if (!m_may_see_vote (this_interactive (), vote_data))
	return 0;

    voters = sort_array (m_indices (vote_results));

    if (end_time <= time())
        end_desc = "This vote has ended. Results will be tallied shortly.\n";
    else
    {
        end_desc = "Vote will end in " + CONVTIME (end_time - time());

        // we also have an end treshhold for the voting
        if (vote_data[7] > -1)
        {
            remaining_votes = vote_data[7] - sizeof(voters);

            if(remaining_votes>0)
                end_desc += ", or when " + LANG_WNUM(remaining_votes)
                     + (remaining_votes > 1 ? " more votes have been cast" :
                        " more vote has been cast");
            else // all the votes needed have been cast. Describe this.
                end_desc = "This vote has ended because "
                    + (vote_data[7] == 1 ? "the one vote required has been "
                    + "cast." : "all of the " + LANG_WNUM(vote_data[7])
                    + " required votes have been cast.")
                    + " Results will be tallied shortly.\n";
        }

        end_desc += ".\n";
    }

    write ("Status of vote \"" + str + "\":\n");
    write ("---------------------------------------\n");
    write ("Vote was created by " + capitalize (creator) + ".\n");
    write (end_desc);
    write ("Description: " + vote_data[6] + "\n");

    if (vote_props & M_VOTE_NO_SHOW)
        write("This vote is by secret ballot.\n");
    else
    {
        write ("Current votes:\n");

        for (i=0; i<sizeof (voters); i++)
        {
            if (vote_props & M_VOTE_NO_SHOW)
                voter_show = "Anonymous";    
            else
                voter_show = capitalize (voters[i]);
            write (sprintf ("%-20s%s\n", voter_show,
                capitalize(vote_results[voters[i]])));    
        }
    }

    if (vote_props & M_VOTE_COUNCIL_ONLY)
        write("This vote is for the Council only.\n");

    if (vote_props & M_VOTE_COUNCIL_ELDER_ONLY)
        write("This vote is for the Council or Elders only.\n");

    // show a summary
    if (!(vote_props & M_VOTE_NO_SHOW))
        write("Current summary of vote results: "
            + m_vote_summary(m_values(vote_results)) + "\n");


    write ("---------------------------------------\n");
    return 1;
}


