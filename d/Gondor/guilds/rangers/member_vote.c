/*
 * /d/Gondor/guilds/rangers/member_vote.c
 *
 * Coded by Gwyneth, October 2003
 * This code is to be included in a designated voting room.
 * Company members can vote for or against apprentices to
 * join their company. Officers, recruiters and Rangers
 * who have made a log entry for the apprentice get more
 * points to vote with. Also included is the joining ceremony
 * for apprentices who have been voted in.
 *
 * Modification log:
 *   Gwyneth - 24 May 2004 - Minor modifications. Removed the
 *             cloning of mortar and spellbook, as they are autoloading
 *             and gained elsewhere.
 *   Tigerlily - August 13, 2004 - Added logs for apprentice votes
 *               August 16, 2004 - Fixed bug in vote calculation
 *               November 29, 2004--added yes/no total votes to log
 *               August 29, 2005--updated to allow reset_room to check
 *               for end of vote time instead of setting an alarm. Also
 *               added a check for legal votes and error logging in
 *               calculation process.
 *
 */
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include "/d/Gondor/guilds/rangers/rangers.h"

// Ex. gVotes = ([ "joe" : ([ "gwyneth" : 1, "tigerlily" : -1 ]) ]);
mapping gVotes = ([]);
// Ex. gVoteTime = ([ "joe" : <end of voting time> ]);
mapping gVoteTime = ([]);
string gCom = "";
static int gAlarm;
static int gStatus = 0;

// Prototypes
public void create_votes(string company);
public void init_member_vote();
public int  query_needs_to_vote(string name);
public void start_vote(string vote);
public int  calculate_results(string name, int val, string vote);
public void end_vote(string vote);
public int  list_candidates(string str);
public int  cast_vote(string str);
public int  join_company(string str);
public void ceremony(object mranger, string name);
public void check_member_end_vote();

/* Function name: create_votes
 * Description  : Sets the company that is using the base and
 *                the vote alarms.
 * Arguments    : The name of the company
 */
public void
create_votes(string company)
{
    int i, time_to_end;
    string *votes;

    restore_object(MASTER);
    gCom = lower_case(company);
}

/* Function name: init_member_vote
 * Description  : Call this function in the inheriting room's init().
 * Arguments    : string company - The company to initiate the room for.
 */
public void
init_member_vote()
{
    add_action(cast_vote,       "vote");
    add_action(list_candidates, "view");
    add_action(join_company,    "enlist");
}

/* Function name: query_needs_to_vote
 * Description  : For use with the shadow. It allows the shadow
 *                to notify Rangers if they have a vote they
 *                haven't voted on and need to.
 * Arguments    : string name - the name of the ranger
 * Returns      : the number of votes to vote on
 */
public int
query_needs_to_vote(string name)
{
    int i, tally = 0;
    string *votes;

    if (!strlen(name))
        return 0;

    name = lower_case(name);
    votes = m_indexes(gVotes);
    for (i = sizeof(votes) - 1; i >= 0; i--)
        if (member_array(name, gVotes[votes[i]]) == -1)
            tally++;

    return tally;
}

/* Function name: query_vote
 * Description  : Checks if there is a specific ongoing vote.
 * Arguments    : string name - the name of the apprentice.
 * Returns      : 1 if there's a vote, 0 if not
 */
public int
query_vote(string name)
{
    if (!strlen(name))
        return 0;

    return (member_array(lower_case(name), m_indexes(gVotes)) != -1);
}

/* Function name: start_vote
 * Description  : Start a vote for an apprentice
 * Arguments    : string vote - the apprentice to start a vote for,
 *                              also the identifier of the vote.
 */
public void
start_vote(string vote)
{
    vote = lower_case(vote);
    if (member_array(vote, m_indexes(gVotes)) != -1)
        return;

    gVotes += ([ vote : ({}) ]);
    gVoteTime += ([ vote : time() + ELECTION_TIME_OUT ]);
    save_object(MASTER);
    return;
}

/* Function name: calculate_results
 * Description  : Calculates the modifier that a member has.
 *                Validation checks--is this a valid voter?.
 * Arguments    : string name - the name of the voter
 *                int val     - 1 for aye, -1 for nay
 *                string vote - the name of the vote (apprentice)
 */
public int
calculate_results(string name, int val, string vote)
{
    // Wizards don't get a vote!
    if (SECURITY->query_wiz_rank(name) > 0)
        return 0;

    // Only members of the relevant company get a vote.
    if (MANAGER->query_ranger_company(name) != gCom)
        return 0;

    // valid vote = int? else error
    if (!intp(val))
        return 0;

    // val is either 1 for an aye vote or -1 for a nay vote
    return (val);
}

/* Function name: check_member_end_vote
 * Description  : check if it's time to compute results
 *                Do check in reset_room
 * Arguments    : 
 */
public void
check_member_end_vote()
{
    string * votes = m_indexes(gVoteTime);
    int i, time_to_end;

    if (!sizeof(votes))
        return;

    for (i = sizeof(votes) - 1; i >= 0; i--)
    {
        time_to_end = gVoteTime[votes[i]];
        if (time_to_end < time())
            end_vote(votes[i]);
    }
    return;
}

/* Function name: end_vote
 * Description  : End the vote
 * Arguments    : string vote - the name of the vote to end.
 */
public int
end_vote(string vote)
{
    int i, tally = 0, x = 0, yes = 0, no = 0;
    mixed * votes = ({});

    //name of candidate = vote
    vote = lower_case(vote);

    //were there any votes for this candidate?
    if (member_array(vote, m_indexes(gVotes)) == -1)
        return 0;
    //grab the array of votes that is mapped to candidate 
    votes = gVotes[vote];

    // Nobody voted?? New members needed!
    if (!sizeof(votes))
        tally = 1;
    else
    {
        /* votes[i - 1] = company ranger voter
         * votes[i] = +1 or -1 for yay or nay
         * vote = name of apprentice applicant
         */
        for (i = 1; i <= sizeof(votes) - 1; i += 2)
        {
            // x should be 1 or -1 if valid vote
            x = calculate_results(votes[i - 1], votes[i], vote);
            if (x == 0)
            {
                // log error message
                 MANAGER->rlog(RANGERS_WIZ_LOG, "Error in member vote " +
                 "calculation for " + capitalize(vote) + " -- " + 
                 votes[i-1] + ":" + votes[i] + ".");
                 continue;
            }
            tally += x;
            if (x > 0)
                yes++;
            else
                no++;
        }
    }
    // Tie votes allow the apprentice in.
    if (tally >= 0)
        MANAGER->add_voted_in(vote, gCom);
    else
        MANAGER->add_voted_out(vote, gCom);

    //log the total to the events log by company
    MANAGER->rlog(RANGERS_WIZ_LOG, capitalize(vote) + " received " +
        yes + " yes votes and " + no + " no votes to join the " +
        capitalize(gCom) + " company.");
    MANAGER->rlog(APPRENTICE_LOG, capitalize(vote) + " received " +
        yes + " yes votes and " + no + " no votes to join the " +
        capitalize(gCom) + " company.");
    MANAGER->rlog(gCom, capitalize(vote) + " received " +
        yes + " yes votes and " + no + " no votes to join the " +
        capitalize(gCom) + " company.");
    MANAGER->rlog(gCom, capitalize(vote) + " was voted in/out by a margin " +
        "of " + tally + " votes.");

    gVotes = m_delete(gVotes, vote);
    gVoteTime = m_delete(gVoteTime, vote);
    save_object(MASTER);
    return 1;
}

/* Function name: list_candidates
 * Description  : Lists the candidate apprentices up for vote.
 * Arguments    : string str - should be candidates
 * Returns      : 1/0 - Success/Failure
 */
public int
list_candidates(string str)
{
    int i, size;
    string *candidates;

    if (!strlen(str) || lower_case(str) != "candidates")
    {
        notify_fail("View candidates?\n");
        return 0;
    }

    if (!m_sizeof(gVotes))
    {
        write("There are no apprentice candidates up for vote.\n");
        return 1;
    }

    write("The apprentices hoping to join your company are:\n");
    candidates = m_indexes(gVotes);
    for (i = 0, size = sizeof(candidates); i < size; i++)
        write(capitalize(candidates[i]) + "\n");

    write("You may vote yes to allow the apprentice to join or " +
        "no to deny the apprentice.\n");
    return 1;
}

/* Function name: cast_vote
 * Description  : Allows a vote to be cast for an apprentice up for vote.
 *                Does not make any checks on membership as those checks
 *                are carried out when the vote is being tallied.
 * Arguments    : string str - as entered by the player
 * Returns      : 1 for success, 0 for failure
 */
public int
cast_vote(string str)
{
    string vote, aye_nay;
    int val = 0, index;
    object tp = this_player();

    string text = "Vote <yes/no> [on] <name>.\n";

    if (!strlen(str))
    {
        notify_fail(text);
        return 0;
    }

    if (!parse_command(str, ({}), "%w [on] %w", aye_nay, vote))
    {
        notify_fail(text);
        return 0;
    }

    aye_nay = lower_case(aye_nay);
    switch(aye_nay)
    {
    case "yes":
    case "y":
    case "aye":
        val = 1;
        break;
    case "no":
    case "n":
    case "nay":
        val = -1;
        break;
    default:
        notify_fail(text);
        return 0;
    }

    vote = lower_case(vote);
    if (member_array(vote, m_indexes(gVotes)) == -1)
    {
        notify_fail("There is no such vote. You may 'view " +
            "candidates' to see the current apprentices hoping to join.\n");
        return 0;
    }

    index = member_array(tp->query_real_name(), gVotes[vote]);

    if (index != -1)
        gVotes[vote][index + 1] = val;
    else
        gVotes[vote] += ({tp->query_real_name(), val });

    save_object(MASTER);
    write("You voted to " + (val == 1 ? "" : "not ") + "let " +
        capitalize(vote) + " join your company.\nYou may change " +
        "your mind up until the vote is finalized by voting again.\n");
    MANAGER->rlog(RANGERS_WIZ_LOG, capitalize(tp->query_real_name()) +
        " voted " + aye_nay + " for admitting " + capitalize(vote) + 
        " into " + "the " + gCom + " company.");
    return 1;
}

public int
join_company(string str)
{
    string name;
    object mranger, *witness, tp;
    
    if (!strlen(str) || !parse_command(lower_case(str), ({}),
      "[in] [the] 'company'"))
    {
        notify_fail("Enlist in the company?\n");
        return 0;
    }

    tp = this_player();
    name = tp->query_real_name();

    if (MANAGER->query_ranger_level(name) < APPROVED_APP_LEVEL)
    {
        notify_fail("You must be at least an Approved Apprentice.\n");
        return 0;
    }
    else if (!MANAGER->query_voted_in(name, gCom))
    {
        notify_fail("You have not been voted into this company.\n");
        return 0;
    }
    else if (MANAGER->query_ranger(name, gCom))
    {
        notify_fail("You are already a ranger of this company.\n");
        return 0;
    }

    mranger = present("_R_enlister_");
    if (!objectp(mranger))
    {
        notify_fail("The Master Ranger is not here to oversee " +
            "your initiation.\n");
        return 0;
    }

    if (!gStatus)
    {
        witness = FILTER_LIVE(all_inventory(this_object()));
        witness = FILTER_PLAYERS(witness);
        witness = filter(witness, &operator(==)(gCom) @ &->query_company());

        if (!sizeof(witness))
        {
            notify_fail("You need a full Ranger of this company to " +
                "witness your enlistment.\n");
            return 0;
        }
        else
        {
            gStatus = 1;
            /* Only have to set the alarm once. */
            mranger->set_ceremony(1);
            gAlarm = set_alarm(35.0, 1.0 + rnd(), &ceremony(mranger, name));
            set_alarm(4.0, 0.0, &mranger->command("emote takes " +
                "a few leaves of athelas from the pouch at his belt " +
                "and crushes them between his fingers. The fragrance " +
                "fills the room and eases your mind."));
            return 1;
        }
    }
    else
    {
        notify_fail("There is already an ongoing ceremony. Please " +
            "wait your turn.\n");
        return 0;
    }
}

/*
 * Function name: ceremony
 * Description  : An alarm is set to call this function at intervals.
 *                Each interval will increment gStatus until the end
 *                when it is set back to 0 and a new Ranger can be
 *                joined in. The second-to-last case promotes the
 *                apprentice to a Ranger of the right company, and
 *                the last case gives him/her a cloak of the right
 *                color.
 * Arguments    : object mranger - the master ranger
 *                string name - the ranger-wannabe
 */
public void
ceremony(object mranger, string name)
{
    string company;
    object mortar, book;
    int ret_val;
    object rshadow;
    object pl = present(name);

    company = (gCom == "north" ? "the North" : "Ithilien");

    //player to be enlisted must remain in room for completion of ceremony
    if (!objectp(pl))
    {
        pl->catch_tell("You need to be in the same room " +
            "with the Master Ranger to complete the ceremony.\n");
        remove_alarm(gAlarm);
        gStatus = 0;
        mranger->set_ceremony(0);
        return;
    }

    switch(gStatus)
    {
    case 1:
        mranger->command("emote softly sings some words " +
            "in ancient Numenorean.\n");
        break;
    case 2:
        tell_room(environment(mranger), "A feeling of peace " +
            "descends.\n");
        break;
    case 3: 
        mranger->command("emote looks at you piercingly, " +
            "as if he can see into your very soul.");
        break;
    case 4:
        mranger->command("say Since the days of Earendur, the seventh " +
            "king that followed Valandil, Rangers have wandered " +
            "secretly in the wild, dedicated to protecting the lands " +
            "and peoples from the growing Shadow in the East.");
        break;
    case 5:
        mranger->command("say The two companies, the North and Ithilien, " +
            "are bound by a common cause and kinship."); 
        break;
    case 6:
        mranger->command("say Our duty is to guard the Free Peoples " +
            "and keep the lands safe.");
        break;
    case 7:
        mranger->command("say However, there is no freedom without " +
            "responsibility and duty. Each company bears a special trust.");
        break;
    case 8:
        mranger->command("say The North patrol the lost realms of Arnor " +
            "and in secrecy protect the peoples and borders of " +
            "the Shire.");
        break;
    case 9:
        mranger->command("say The Company of Ithilien dwells under the " +
            "shadow of Mordor, and strives to guard the White City from " +
            "destruction.");
        break;
    case 10:
        mranger->command("say Both paths are beset with danger in these " +
            "dark times, and not even the wise know all ends.");
        mranger->command("sigh deeply");
        break;
    case 11:
        mranger->command("say But there is yet hope. While " +
            "our hearts are true and we keep faith, our people " +
            "shall not fail.");
        break;
    case 12:
        mranger->command("ponder");
        mranger->command("say You have chosen the Rangers of " + 
            company + ". Having come this far, it seems that your " +
            "brothers and sisters trust you to belong among them " +
            "by voting you into this company.");
        break;
    case 13:
       /* This will promote the approved apprentice unless
           something goes wrong. */
        if (!MANAGER->add_ranger(name, gCom, 1))
        {
            mranger->command("say Something has gone wrong, and " +
                "I cannot add you to the roster. Please make a bug " +
                "report and/or notify your guildmaster.");
            MANAGER->rlog(RANGERS_WIZ_LOG, name + " failed to be " +
                "inducted into " + gCom + ".");
            remove_alarm(gAlarm);
            gStatus = 0;
            mranger->set_ceremony(0);
            return;
        }
        else
        {
            mranger->command("emote enlists " + capitalize(name) +
                " into the company of "+ company + ".");

            if (gCom == "north")
                clone_object(RANGERS_OBJ + "grey_cloak")->move(mranger, 1);
            else
                clone_object(RANGERS_OBJ + "green_cloak")->move(mranger, 1);

            command("give cloak to " + name);
        }
        break;
    case 14: 
        mranger->command("say Mae govannen, " + capitalize(name) + "!\n" +
                "Welcome to the Rangers of " + company + "!");
        break;
    default:
        remove_alarm(gAlarm);
        gStatus = 0;
        mranger->set_ceremony(0);
        // early return--do not increment gStatus
        return;
    }

    gStatus++;
    return;
}

