/*
 * Voting Box for the Calian Guild
 *
 * This voting box allows Calians to nominate members for the Calian
 * Council and then to vote on it.
 *
 * Created by Petros, February 2010
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include CALIAN_HEADER
#include COUNCIL_HEADER

inherit "/std/object";

public void
create_object()
{
    set_name("box");
    set_adj("voting");
    set_long("@@describe_long");
    add_prop(OBJ_M_NO_GET, 1);

    if (!IS_CLONE)
      return;

    setuid();
    seteuid(getuid());
}

public string
describe_long()
{
    string long_desc = "This is a voting box. The use of the voting box is restricted "
        + "to full Calian Warriors. During the nomination period, any Calian "
        + "Warrior can <nominate> fellow Calian Warriors to serve on the "
        + "Calian Council. Once the period of nomination has passed, each "
        + "Calian Warrior then has the opportunity to <vote> for whom they "
        + "feel would best serve on the Council. Each vote runs for exactly "
        + "one week, and one can view the <results> of the vote when the "
        + "voting period has ended.\n\n";
    
    mapping active_vote = COUNCIL_VOTING_MANAGER->get_active_vote();
    if (!active_vote)
    {
        long_desc += "VOTING IS NOT CURRENTLY ACTIVE\n";
    }
    else
    {
        long_desc += "VOTING ACTION: " + COUNCIL_VOTING_MANAGER->get_formatted_vote_description(active_vote["id"]) + "\n";
        string category = active_vote["category"];
        string * nominees;
        switch (category)
        {
        case "nomination":
            nominees = m_indices(COUNCIL_VOTING_MANAGER->get_vote_results(active_vote["id"]));
            if (sizeof(nominees) == 0)
            {
                long_desc += "\tNo one has been nominated yet for the Calian Council.\n";
            }
            else
            {
                long_desc += "\nThe following Calian Warriors have been nominated "
                    + "for the Calian Council:\n";
                long_desc += "\t" + COMPOSITE_WORDS(map(map(nominees, lower_case), capitalize)) + "\n";
            }
            long_desc += "\n\n" + "Nominations will continue until " + ctime(active_vote["start_time"] + active_vote["duration"]) + ".\n";
            break;
        
        case "council":
            long_desc += "\t" + COMPOSITE_WORDS_WITH(map(map(active_vote["choices"], lower_case), capitalize), "or") + "\n";
            long_desc += "\n\n" + "Voting will continue until " + ctime(active_vote["start_time"] + active_vote["duration"]) + ".\n";
            break;
        }
    }
    return long_desc;
}

void
init()
{
    ::init();
    add_action("nominate", "nominate");
    add_action("vote", "vote");
    add_action("results", "results");
}

public int
vote(string str)
{
    string candidate;
    if (!strlen(str)
        || !parse_command(str, environment(this_player()), "[for] %s", candidate))
    {
        notify_fail("Vote for whom?\n");
        return 0;
    }
    
    candidate = lower_case(candidate);
    string name = this_player()->query_real_name();
    mapping active_vote = COUNCIL_VOTING_MANAGER->get_active_vote();
    if (!active_vote)
    {
        notify_fail("There is no active vote!\n");
        return 0;
    }
    
    if (!CALIAN_MEMBER_HANDLER->query_is_warrior(name))
    {
        notify_fail("Only Calian Warriors can vote for the Calian Council.\n");
        return 0;
    }

    // Check to see if the player has been vote banned. If so, they should not be
    // able to actually vote for someone.
    // Implemented this Vote ban functionality because of seconds logging in to vote.
    // However, if it is abused to keep a Calian Council Member in power instead of
    // just managing seconds voting, then the Council member should be forcibly
    // removed and kicked from the guild.
    if (COUNCIL_CODE->is_vote_banned(this_player()))
    {
        notify_fail("You have been banned from participating in the voting process "
                    + "by the Calian Council.\n");
        return 0;
    }
    
    if (active_vote["category"] == "nomination")
    {
        notify_fail("You can't vote right now. Try to <nominate> a fellow "
            + "Calian for the Calian Council.\n");
        return 0;
    }
    
    string error_message;
    if (stringp(error_message = COUNCIL_VOTING_MANAGER->cast_vote(name, active_vote["id"], candidate)))
    {
        if (error_message != " ")
        {
            // If the error message is just a blank, then it's already processed elsewhere.            
            notify_fail(error_message + "\n");
        }
        return 0;
    }
    
    return 1;
}

public int
nominate(string str)
{
    if (!strlen(str))
    {
        notify_fail("Nominate whom?\n");
        return 0;
    }
    
    str = lower_case(str);
    string name = this_player()->query_real_name();
    mapping active_vote = COUNCIL_VOTING_MANAGER->get_active_vote();
    if (!active_vote)
    {
        notify_fail("There is no active nomination process!\n");
        return 0;
    }
    
    if (!CALIAN_MEMBER_HANDLER->query_is_warrior(name))
    {
        notify_fail("Only Calian Warriors can nominate for the Calian Council.\n");
        return 0;
    }
    
    if (active_vote["category"] == "council")
    {
        notify_fail("You can't nominate right now. Try to <vote> for a fellow "
            + "Calian to the Calian Council.\n");
        return 0;
    }
    
    string error_message;
    if (stringp(error_message = COUNCIL_VOTING_MANAGER->cast_vote(name, active_vote["id"], str)))
    {
        if (error_message != " ")
        {
            // If the error message is just a blank, then it's already processed elsewhere.            
            notify_fail(error_message + "\n");
        }
        return 0;
    }
    
    return 1;
}

public int
results(string str)
{
    mixed * recent_votes = COUNCIL_VOTING_MANAGER->get_most_recent_council_votes(5);
    if (!sizeof(recent_votes))
    {
        notify_fail("Sorry, there are no recent votes to report.\n");
        return 0;
    }
    
    // Go through each of the recent votes and display them.
    foreach (mixed vote_row : recent_votes)
    {
        int id = vote_row["id"];
        mixed * sorted_results = COUNCIL_VOTING_MANAGER->get_ordered_vote_results(id);
        int end_time = vote_row["start_time"] + vote_row["duration"];
        write(sprintf("%|75s\n", "Results for Council Vote Ending " + ctime(end_time)));
        write(sprintf("%-20s %10s\n", "Nominee", "Votes"));
        write(sprintf("%'-'31s\n", ""));
        foreach (mixed result : sorted_results)
        {
            write(sprintf("%-20s %10d\n", capitalize(result[0]), sizeof(result[1])));
        }        
        write("\n\n");
    }
    
    return 1;
}
