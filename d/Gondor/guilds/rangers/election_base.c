/*
 * /d/Gondor/guilds/rangers/election_base.c
 *
 * Voting code
 *
 * Coded by Gwyneth, 27 March 2002
 *
 *   Fixed a typo (missing '.') in the voting.
 *   Now reads:
 *   'You have cast your vote for <name>.'
 *
 *                   Toby, 25 Sept 2006
 */
#include "rangers.h"

string gImpeacher = "";
string gNominator = "";

public int check_voting(string company);
public int list_candidates(string str);
public int cast_vote(string str);
public int change_vote(string str);
public int nominate(string str);
public int withdraw(string str);
public int impeach(string str);
public int regret(string str);
public void init_vote_actions();

/* Function name: check_voting
 * Description  : Returns 0 if there are no votes going on
 *                Returns 1 if there are nominations being voted on
 *                Returns 2 if there is an election for Captain
 *                Returns 3 if there is an impeachment vote
 * Arguments    : string company - the company to check for voting
 * Returns      : 0, 1 or 2
 */
public int
check_voting(string company)
{
    /* Query the MANAGER for election status. Return the type of
       election ongoing. 0 for no election. 1 for nominations.
       2 for Captain elections and 3 for impeachment votes. */
    return MANAGER->query_election(company);
}

/* Function name: list_candidates
 * Description  : Finds the list of candidates from the MANAGER
 *                for the company of the querying Ranger and
 *                displays them.
 * Arguments    : string str - the argument given, should be
 *                "candidates"
 * Returns      : 1 if the function was successful
 *                0 if it wasn't successful
 */
public int
list_candidates(string str)
{
    int i, size, election_status;
    string company, *candidates;

    /* No or wrong syntax. Inform the Ranger on the correct syntax. */
    if (!strlen(str) || lower_case(str) != "candidates")
    {
        notify_fail("List candidates?\n");
        return 0;
    }

    /* Find Ranger's company name */
    company = this_player()->query_company();

    /* Find what kind of vote if any is going on. */
    election_status = check_voting(company);

    /* No vote is going on. Let them know. */
    if (election_status == NO_ELECTIONS)
    {
        write("There does not seem to be an election underway in your " +
            "company at the moment.\n");
        return 1;
    }

    /* Impeachment vote is going on. Let them know what they can vote. */
    if (election_status == IMPEACHMENT_VOTE)
    {
        write("There is an ongoing vote to impeach " +
            MANAGER->query_council_name(CAPTAIN_POSITION, company) + 
            " vote 'yes' to impeach the Captain or 'no' to retain the " +
            "Captain.\n");
        return 1;
    }

    /* Find an array of the candidates */
    candidates = MANAGER->query_candidates(company);

    /* There are no candidates, probably for nomination votes. */
    if (!sizeof(candidates))
    {
        /* There's a Captain election going on and no candidates! */
        if (election_status == CAPTAIN_ELECTION)
            write("There are no candidates! Please make a bug report!\n");

        write("There are no candidates at this time.\n");
        return 1;
    }

    /* Indicate if it is for nomination or for Captain. */
    write("The candidates up for " + 
        (election_status == CAPTAIN_ELECTION ? "the office of Captain":
        "nomination") + " are:\n");

    /* Display the candidates up for vote. */
    for (i = 0, size = sizeof(candidates); i < size; i++)
    {
        write(candidates[i] + "\n");
    }

    return 1;
}

/* Function name: cast_vote
 * Description  : Calls on the MANAGER to record a vote for a Ranger if
 *                an election is underway.
 * Arguments    : string str - the argument given, should be
 *                             "vote for <name>" where name is the
 *                             candidate they wish to vote for
 * Returns      :  1 if successful, 0 if not
 */
public int
cast_vote(string str)
{
    string company, name, vote_choice;

    /* They provided no arguments. Give them the syntax. */
    if (!strlen(str))
    {
        notify_fail("Cast vote for <name>?\n");
        return 0;
    }

    company = this_player()->query_company();
    /* There is no election happening. */
    if (!check_voting(company))
    {
        write("There does not seem to be an election underway in your " +
            "company at the moment.\n");
        return 1;
    }

    /* Make a uniform case */
    str = lower_case(str);

    /* Deal with an impeachment vote */
    if (check_voting(company) == IMPEACHMENT_VOTE)
    {
        /* Wrong syntax. Give directions. */
        if(!parse_command(str, ({}), 
          "'vote' %w [on] [impeachment] [to] [impeach] [the] [captain]", 
          vote_choice))
        {
            notify_fail("There is an ongoing vote to impeach " +
                MANAGER->query_council_name(CAPTAIN_POSITION, company) + 
                ". Vote 'yes' to impeach your Captain or 'no' to retain " +
                "your Captain.\n");
            return 0;
        }

        name = this_player()->query_real_name();

        /* They've already voted. Tell them how to change their vote. */
        if (MANAGER->query_voted(company, name))
        {
            write("You have already cast your vote. If you have changed " +
                "your mind, you may 'change vote to <yes>/<no>'.\n");
            return 1;
        }

        /* This shouldn't happen, since we check in parse for yes or no. */
        if (!MANAGER->cast_vote(company, name, vote_choice))
        {
            write("For some reason, your vote was unsuccessful. Please " +
                "make a bug report.\n");
            return 1;
        }
        /* Vote successful. Let them know it worked and how to change
           their vote if they need to. */
        else
        {
            write("You have voted " + vote_choice + " to impeach the " +
                "Captain. If you change your mind, you may 'change " +
                "vote to <yes>/<no>' at any point during the election.\n");
            return 1;
        }
    }

    /* It is a nomination election or Captain election, parse appropriately */
    if (!parse_command(str, ({}), "'vote' 'for' %w", vote_choice))
    {
        notify_fail("Perhaps you want to cast vote for <name>?\n");
        return 0;
    }

    name = this_player()->query_real_name();

    /* Voter has already cast their vote.  Let them know how to change it. */
    if (MANAGER->query_voted(company, name))
    {
        write("You have already cast your vote. If you have changed " +
            "your mind, you may 'change vote to <name>' to select a " +
            "different candidate.\n");
        return 1;
    }

    /* Attempt to cast their vote. If they give an incorrect candidate,
       give them a failure message. */
    if (!MANAGER->cast_vote(company, name, vote_choice))
    {
        write(capitalize(vote_choice) + " is not a candidate. Please " +
            "try your vote again.\n");
        set_this_player(find_player(lower_case(name)));
        list_candidates(company);
        return 1;
    }

    /* Vote is successful. Let them know, and how to change their vote. */
    else
    {
        write("You have cast your vote for " + capitalize(vote_choice) +
            ". If you change your mind, you may 'change vote to <name>' " +
            "at any point during this election.\n");
        return 1;
    }
}

/* Function name: change_vote
 * Description  : Allows a Ranger to change his/her vote after they
 *                have cast it if the election is still happening.
 * Arguments    : string str - Should be "change vote to <name>" where
 *                             name is the candidate they wish to vote for.
 * Returns      : 1 if function was successful, 0 if not
 */
public int
change_vote(string str)
{
    string company, name, vote_choice;

    /* No syntax provided. Inform them what syntax is. */
    if (!strlen(str))
    {
        notify_fail("Change vote to <name>?\n");
        return 0;
    }

    /* Find the Ranger's company */
    company = this_player()->query_company();

    /* Find out if there is an election */
    if (!check_voting(company))
    {
        write("There does not seem to be an election underway in your " +
            "company at the moment.\n");
        return 1;
    }

    /* Uniform case */
    str = lower_case(str);

    /* Parse the syntax to find out the vote */
    if (!parse_command(str, ({}), "'vote' 'to' %w", vote_choice))
    {
        notify_fail("Perhaps you want to 'change vote to <name>'?\n");
        return 0;
    }

    name = this_player()->query_real_name();

    /* Find out if the player has voted or not. */
    if (!MANAGER->query_voted(company, name))
    {
        write("You can't change a vote that you never cast. Please " +
            "'cast vote for <name>'.\n");
        return 1;
    }

    /* Find out if the candidate voted for is valid or not. */
    if (!MANAGER->cast_vote(company, name, vote_choice))
    {
        write(capitalize(vote_choice) + " is not a candidate. Please " +
            "try to change your vote again.\n");
        set_this_player(find_player(lower_case(name)));
        list_candidates(company);
        return 1;
    }
    else
    {
        /* Vote change successful. Let them know. */
        write("You have changed your vote to " + capitalize(vote_choice) +
            " If you change your mind again, you may 'change vote to " +
            "<name>' for Captain' at any point during this election.\n");
        return 1;
    }
}

/* Function name: nominate
 * Description  : Puts a Ranger up for nomination if there is a nomination
 *                election going on.
 * Arguments    : string str - Should be "nominate <name> for captain"
 *                             where name is the Ranger they want to nominate
 * Returns      : 1 if the function is successful, 0 if not
 */
public int
nominate(string str)
{
    string company, name, nominee;

    /* No arguments. Provide the syntax. */
    if (!strlen(str))
    {
        notify_fail("Nominate <name> for Captain?\n");
        return 0;
    }

    /* Find out the player's company */
    company = this_player()->query_company();

    /* Is there a vote ongoing for that company? */
    if (!check_voting(company))
    {
        write("There does not seem to be an election underway in your " +
            "company at the moment.\n");
        return 1;
    }

    /* Wrong syntax. Let them know what the syntax is. */
    if (!parse_command(str, ({}), "%w 'for' 'captain'", nominee))
    {
        notify_fail("Nominate <name> for Captain?\n");
        return 0;
    }

    nominee = capitalize(nominee);

    if (gNominator != this_player()->query_real_name())
    {
        /* Find out if the nominee is already nominated. */
        if (member_array(nominee, MANAGER->query_candidates(company)) != -1)
        {
            notify_fail("That person has already been nominated.\n");
            return 0;
        }

        /* Let's make sure that this is a serious nomination that has
           been discussed with the person being nominated. Have them
           re-enter their nomination to proceed. */
        write("Are you sure you wish to nominate " + nominee +
            "? Be sure that " + nominee + " wishes to be " +
            "nominated, or the company may end up with a Captain who " +
            "resigns shortly after being elected. If you are serious " +
            "about this nomination, and " + nominee + " does " +
            "wish to be nominated, enter your nomination again.\n");
        gNominator = this_player()->query_real_name();
        return 1;
    }
    else
    {
        name = this_player()->query_real_name();

        /* Nominee can't be nominated due to eligibility or player has
           already made a nomination. */
        if (!MANAGER->add_candidate(nominee, company, name))
        {
            notify_fail("Either your nominee is not eligible for a " +
                "nomination, or you have already nominated someone.\n");
            return 0;
        }
        else
        {
            /* Nomination successful. Give vote reminder. */
            write("You nominate " + nominee + " for the " +
                "office of Captain. Don't forget to cast your vote!\n");
            return 1;
        }
    }
}

/* Function name: withdraw
 * Description  : Withdraw your name from the election race.
 * Arguments    : string str - Should be "withdraw from election"
 * Returns      : 1 if function is successful, 0 if not
 */
public int
withdraw(string str)
{
    string company, name;

    /* No argument given. Provide syntax. */
    if (!strlen(str))
    {
        notify_fail("Withdraw from the election?\n");
        return 0;
    }

    /* Find out the player's company */
    company = this_player()->query_company();

    /* Is there a vote ongoing for that company? */
    if (!check_voting(company))
    {
        write("There does not seem to be an election underway in your " +
            "company at the moment.\n");
        return 1;
    }

    name = this_player()->query_real_name();

    /* The player is not a candidate. */
    if (!MANAGER->query_is_candidate(name, company))
    {
        write("You are not a candidate.\n");
        return 1;
    }

    /* Can't remove candidate from list. This shouldn't happen. */
    if (!MANAGER->remove_candidate(name, company))
    {
        write("Unable to remove you as a candidate. Please make a " +
            "bug report.\n");
        return 1;
    }
    else
    {
        /* Successfully removed */
        write("You have withdrawn from the election.\n");
        return 1;
    }
}

/* Function name: impeach
 * Description  : Adds a Ranger to the list of Rangers wishing to impeach
 *                a Captain. If there are three on the list, it starts an
 *                impeachment vote.
 * Arguments    : string str - Should be "impeach my Captain"
 * Returns      : 1 if function is successful, 0 if not
 */
public int
impeach(string str)
{
    int num_impeaching = 0;
    string company, name;
    if (!strlen(str))
    {
        notify_fail("Impeach your Captain?\n");
        return 0;
    }

    company = this_player()->query_company();

    /* Is there a vote ongoing for that company? */
    if (check_voting(company) > 0)
    {
        write("There is an election underway. You must wait for " +
            "a Captain to be elected before you can impeach them.\n");
        return 1;
    }

    /* Is there a Captain to impeach? */
    if (!MANAGER->query_council_name(CAPTAIN_POSITION, company))
    {
        write("Your company has no Captain to impeach!\n");
        return 1;
    }

    /* Uniform case */
    str = lower_case(str);

    /* How many have already signed on to impeach the Captain? */
    num_impeaching = sizeof(MANAGER->query_impeaching(company));

    /* Correct syntax */
    if (str == "my captain")
    {
        if (gImpeacher != this_player()->query_real_name())
        {
            switch(num_impeaching)
            {
            case 0:
            case 1:
                /* Their name is already on the list, or they aren't
                   allowed to impeach. */
                if (!MANAGER->add_impeaching(name, company))
                {
                    write("You have already added your name to the " +
                        "list to impeach your Captain, or you are not " +
                        "allowed to impeach your Captain.\n");
                    return 1;
                }

                /* Successfully signed the impeachment list. Give them
                   the rules on what needs to happen for an impeachment
                   vote to occur. */
                write("You sign your name to the list of those wishing to " +
                    "impeach the Captain. Your name is the " +
                    (num_impeaching ? "second" : "first") + 
                    " name on the list. Three people need to sign the " +
                    "list within three days of each other for an " +
                    "impeachment vote to be called.\n");
                return 1;
            case 2:
                /* Already two people on the list. If this person signs the
                   list an impeachment vote will be called. Let's make sure
                   they really wish to do this. Make them enter it again. */
                write("There are already two people on the list. If you " +
                    "really wish to impeach your Captain an election will " +
                    "be called as soon as a third name is added to the list." +
                    " Are you sure you wish to impeach your Captain? " +
                    "Please enter 'impeach my captain' again if you are " +
                    "sure.\n");
                gImpeacher = this_player()->query_real_name();
                return 1;
            }    
        }

        /* Their name is already on the impeachment list, or they are not
           allowed to impeach their Captain. */
        if (!MANAGER->add_impeaching(name, company))
        {
            write("You have already added your name to the list to " +
                "impeach your Captain, or you are not allowed to impeach " +
                "your Captain.\n");
            return 1;
        }

        /* Successful. An impeachment vote will be called by MANAGER. */
        write("You sign your name to the list of those wishing to impeach " +
            "your Captain! Since your name is the third on the list, an " +
            "impeachment vote will be held, lasting one week. If your " +
            "Captain is impeached, nominations for a new Captain will " +
            "be taken for week. After that, the top nominees will be " +
            "voted on for a week. Don't forget to cast your vote on the " +
            "impeachment.\n");
        return 1;
    }

    /* Wrong syntax. Let them know the right syntax. */
    notify_fail("Impeach your Captain?\n");
    return 0;
}

/* Function name: regret
 * Description  : Removes a Ranger's name from the list of Rangers wishing
 *                to impeach a Captain if the vote hasn't been started yet.
 * Arguments    : string str - Should be "regret impeachment"
 * Returns      : 1 if function is successful, 0 if not
 */
public int
regret(string str)
{
    string name, company;
    /* No argument. Give info on what they should type. */
    if (!strlen(str))
    {
        notify_fail("Regret impeachment?\n");
        return 0;
    }

    name = this_player()->query_real_name();
    company = this_player()->query_company();

    if (member_array(name, MANAGER->query_impeaching(company)) == -1)
    {
        /* Name isn't on list. */
        write("Your name is not on the list of those wanting to " +
            "impeach your Captain. A name only stays on the list " +
            "for three days.\n");
        return 1;
    }
    else if (!MANAGER->remove_impeaching(name, company))
    {
        /* Removal was unsuccessful. This shouldn't happen. */
        write("Unable to remove your name from the list of those " +
            "wanting to impeach your Captain. Please make a bug report!\n");
        return 1;
    }
    else
    {
        /* Removal was successful. */
        write("Successfully removed your name from the list of those " +
            "wanting to impeach your Captain.\n");
        return 1;
    }
}

/* Function name: init_vote_actions
 * Description  : Add this function to the inheriting room's init
 */
public void
init_vote_actions()
{
    add_action("list_candidates", "list");
    add_action("cast_vote",       "cast");
    add_action("change_vote",     "change");
    add_action("nominate",        "nominate");
    add_action("withdraw",        "withdraw");
    add_action("impeach",         "impeach");
    add_action("regret",          "regret");
}
