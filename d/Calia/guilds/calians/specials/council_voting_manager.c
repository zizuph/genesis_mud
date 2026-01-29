/*
 * Calian Council Voting Manager
 *
 * This manager will do the nominations and voting for the Council.
 * The way the voting system works is that it replaces a current "slot"
 * on the Calian Council.
 *
 * Created by Petros, February 2010
 */

#pragma strict_types

#include <files.h>
#include <filepath.h>
#include <macros.h>

inherit "/d/Genesis/specials/guilds/objs/voting_manager";

#include "defs.h"
#include COUNCIL_HEADER

// Prototypes
public mixed    get_vote_replacement(int id);
public void     set_vote_replacement(mixed value, int id);
public int      add_council_vote_entry(string replacement, string * choices);
public int      add_nomination_vote_entry(string replacement);
public void     install_council_member(string winner, int slot);
public string * get_council_winners(int id);
public void     check_council_replacement_vote();

// Global Variables
public int      next_vote_alarm = 0;

public void
create_database()
{
    ::create_database();

    // Each vote for the council will indicate who the replacement will be        
    add_column("replacement");
    
    set_alarm(1.0, 0.0, &check_council_replacement_vote());
}

// Hook functions
/*
 * Function:    hook_vote_cast
 * Description: Hook function to be called whenever a vote is cast by
 *              a player. Use this function to do any post-processing
 *              that needs to be done (sending mail, etc) when a vote
 *              is cast.
 */
public void
hook_vote_cast(int id, object player, mixed value, int bChangedVote)
{
    string category = get_vote_category(id);
    switch (category)
    {
    case "nomination":
        player->catch_tell("Ok! You have successfully nominated " 
            + capitalize(lower_case(value)) + " for the Calian Council.\n");
        break;
    
    case "council":
        if (bChangedVote)
        {
            player->catch_tell("Ok! You have successfully changed your vote to " 
                + capitalize(lower_case(value)) + " for the Calian Council.\n");  
        }
        else
        {
            player->catch_tell("Ok! You have successfully voted for " 
                + capitalize(lower_case(value)) + " for the Calian Council.\n");  
        }
        break;
    }  
}

/*
 * Function:    hook_already_cast_vote
 * Description: Hook function to be called whenever the voter has already
 *              voted. Mask this to define messages that should be sent
 *              to the voter to notify them that they have already voted.
 */
public void
hook_already_cast_vote(object player, int id, mixed old_value, mixed new_value)
{
    string category = get_vote_category(id);
    switch (category)
    {
    case "nomination":
        notify_fail("You have already nominated " + capitalize(old_value)
            + " for Council!\n");
        break;
    
    case "council":
        notify_fail("You have already cast a vote for " + capitalize(old_value)
            + " for Council.\n");
        break;
    }
}

/*
 * Function:    allow_vote_change
 * Description: Function that determines whether someone is allowed to
 *              change their vote. By default, this is set to be false.
 */
public int
allow_vote_change(int id)
{
    string category = get_vote_category(id);
    switch (category)
    {
    case "council":
        // We allow people to change their vote for Council.
        return 1;

    case "nomination":
    default:
        // Don't allow nominations to be changed.
        return 0;
    }
}

/*
 * Function:    hook_start_vote
 * Description: Hook function to be called whenever a vote is started.
 *              This includes when it is being restarted due to Armageddon
 *              or any loading.
 */
public void
hook_start_vote(int id)
{
}

/*
 * Function:    hook_end_vote
 * Description: Hook function to be called whenever the vote officially
 *              ends. Mask this to define behavior that should occur
 *              when voting ends.
 */
public void
hook_end_vote(int id)
{
    string category = get_vote_category(id);
    string * choices = ({ });
    string * winners;
    switch (category)
    {
    case "nomination":
        choices = m_indices(get_vote_results(id));
        if (!sizeof(choices))
        {
            // If there are no choices, then we don't start a council vote
            break;
        }
        else if (sizeof(choices) == 1)
        {
            // Only one person was nominated. Go ahead and make them
            // the council replacement.
            install_council_member(choices[0], atoi(get_vote_replacement(id)));
            break;
        }
        add_council_vote_entry(get_vote_replacement(id), choices);
        break;
        
    case "council":
        winners = get_council_winners(id);
        if (sizeof(winners) == 1)
        {
            install_council_member(winners[0], atoi(get_vote_replacement(id)));
        }
        else if (sizeof(winners) > 1)
        {
            // There was a tie on Council. Restart the vote again. Keep voting
            // until a winner is found.
            // Log something here about there being a tie.
            add_council_vote_entry(get_vote_replacement(id), winners);
            COUNCIL_CODE->log_council_event("A tie occurred during the Calian "
                + "Council election. A run-off election has been started.");
        }
        break;    
    }
}

public void
install_council_member(string winner, int slot)
{
    string council_member = COUNCIL_CODE->get_council_member_at_slot(slot);
    if (lower_case(council_member) != lower_case(winner))
    {
        if ((strlen(council_member) 
             && !COUNCIL_CODE->remove_council_member_internal(council_member))
            || !COUNCIL_CODE->add_council_member_internal(winner))
        {
            COUNCIL_CODE->log_council_event("Unable to install "
                + capitalize(lower_case(winner)) + " on the Calian Council "
                + " following the results of the election. Please contact the "
                + "guildmaster for assistance.");
        }
        else
        {
            COUNCIL_CODE->log_council_event("Installed " + capitalize(lower_case(winner))
                + " onto the Calian Council following the results of the Calian "
                + "Council election.");
        }
    }
    else
    {
        // Log a message about the council member being affirmed at
        // their position.
        COUNCIL_CODE->log_council_event(capitalize(lower_case(winner))
            + " has won the Calian Council election, and remains on the "
            + "Calian Council.");        
    }    
}

public string *
get_council_winners(int id)
{
    string * winners = ({ });
    mixed * ordered_results = get_ordered_vote_results(id);
    if (!sizeof(ordered_results))
    {
        // Nobody in the results
        return winners;
    }

    int winning_total = sizeof(ordered_results[0][1]);        
    foreach (mixed * result : ordered_results)
    {
        if (sizeof(result[1]) == winning_total)
        {
            winners += ({ result[0] });
        }
    }

    return winners;        
}

/*
 * Function:    validate_vote_choice
 * Description: This function will determine whether the vote can be used.
 *              This should be masked if someone wants to customize validation
 *              routines.
 * Returns:     Returns 0 if it is validated. Returns string for error message
 *              otherwise.
 */
public string
validate_vote_choice(int id, string value)
{
    string category = get_vote_category(id);
    object player;
    value = lower_case(value);
    switch (category)
    {
    case "nomination":
        setuid();
        seteuid(getuid());
        if (!CALIAN_MEMBER_HANDLER->query_is_warrior(value))
        {
            return "You can only nominate Calian Warriors for the Council.";
        }

        // If the person is not the one being replaced, and is already on the Calian
        // Council, then they can't be nominated either
        if (IN_ARRAY(capitalize(value), COUNCIL_CODE->query_council_members())
            && value != lower_case(COUNCIL_CODE->get_council_member_at_slot(atoi(get_vote_replacement(id)))))
        {
            return capitalize(value) + " is already on the Calian Council and "
                + "is not eligible to be nominated for this vote.";
        }

        // If nominated a calian warrior, we have to see that they've logged in
        // during the last week.
        int is_wizard = 0;
        if (!objectp(player = find_player(value)))
        {
            // Lets load up the player from security and see 
            if (!objectp(player = SECURITY->finger_player(value)))
            {
                return capitalize(value) + " is not a valid candidate for the Calian Council.";
            }
            int time_since_logout = time() - player->query_logout_time();
            is_wizard = player->query_wiz_level();
            player->remove_object();
            if (time_since_logout >= 604800) // logged in within the last week
            {
                return capitalize(value) + " has not logged in recently enough to "
                    + "be nominated for the Calian Council.";
            }
        }
        
        if (is_wizard || (objectp(player) && player->query_wiz_level()))
        {
            return capitalize(value) + " is a wizard and cannot be nominated for "
                + "the Calian Council.";
        }

        // We need to check whether this person has already been nominated
        // or not.
        mapping results = get_vote_results(id);
        if (results[value])
        {
            return capitalize(value) + " has already been nominated for the Calian "
                + "Council.";
        }   
        break;
    
    case "council":
        return ::validate_vote_choice(id, value);

    default:
        return "An error occurred in the fabric of space. Please contact the "
            + "Guildmaster for assistance.";
    }
       
    return 0;
}

public mixed
get_vote_replacement(int id)
{
    return get_field_by_id("replacement", id);
}

public void
set_vote_replacement(mixed value, int id)
{
    set_field_by_id("replacement", value, id);
}

public int
add_nomination_vote_entry(string replacement)
{
    int new_id;
    if (!strlen(replacement))
    {
        return -1;
    }
    
    new_id = add_vote_entry("nomination", "Nomination vote for slot number "
        + replacement + " on the Calian Council.");

    set_vote_replacement(replacement, new_id);
    start_votes();
    return new_id;
}

public int
add_council_vote_entry(string replacement, string * choices)
{
    int new_id;
    if (!strlen(replacement))
    {
        return -1;
    }

    new_id = add_vote_entry("council", "Council vote for slot number "
        + replacement + " on the Calian Council.");

    set_vote_replacement(replacement, new_id);
    set_vote_choices(choices, new_id);
    start_votes();
    return new_id;
}

/*
 * Function:    get_active_vote
 * Description: Returns the currently active vote for the Council voting
 *              process. At any time, there should only be one active vote
 */
public mapping
get_active_vote()
{
    mixed * rows = query_rows( ([ "active" : 1 ]) );
    if (!sizeof(rows))
    {
        return 0;
    }
    
    // Return the first row.
    return rows[0];    
}

private int
sort_recent_council_vote(mixed a, mixed b)
{
    // Each vote is an array of two items: ({ choice, ({ voters }) })
    // We go in descending order of number of votes (rank), so we reverse it.
    if ((a["start_time"] + a["duration"]) > (b["start_time"] + b["duration"]))
    {
        return -1;
    }
    if ((a["start_time"] + a["duration"]) < (b["start_time"] + b["duration"]))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    get_most_recent_council_votes
 * Description: Returns the most recent votes ordered by date
 *              in reverse order of end date.
 * Arguments:   Maximum number of rows to return
 */
public mixed *
get_most_recent_council_votes(int max_rows)
{
    mixed * rows = query_rows( ([ "category" : "council",
                                  "active"   : 0 ]) ) + ({ });
    sort_array(rows, sort_recent_council_vote);
    mixed * result_rows = ({ });
    foreach (mixed row : rows)
    {
        if (mappingp(row) && sizeof(m_indices(row["votes"])))
        {
            result_rows += ({ row });
        }
    }
    
    if (max_rows <= 0 || max_rows >= sizeof(result_rows))
    {
        return result_rows;
    }
    
    return result_rows[..(max_rows - 1)];
}

/*
 * Function:    get_formatted_vote_description
 * Description: Creates the description to be used in the Calian voting
 *              box.
 */
public string
get_formatted_vote_description(int id)
{
    string formatted_desc;
    // Replacement is simply a text index (need to convert to number) of
    // the Council Slot.
    int slot = atoi(get_vote_replacement(id));
    string council_member = COUNCIL_CODE->get_council_member_at_slot(slot);
    switch (get_vote_category(id))
    {
    case "nomination":
        if (strlen(council_member))
        {
            formatted_desc = "Nominate a fellow Calian to take "
                + capitalize(council_member) + "'s place on the Calian "
                + "Council.";
        }
        else
        {
            formatted_desc = "Nominate a fellow Calian to take "
                + "the empty slot on the Calian Council.";
        }
        break;
    
    case "council":
        if (strlen(council_member))
        {
            formatted_desc = "Vote for the fellow Calian you would like "
                + "to take " + capitalize(council_member) + "'s place "
                + "on the Calian Council.";
        }
        else
        {
            formatted_desc = "Vote for the fellow Calian you would like "
                + "to take the empty slot on the Calian Council.";
        }
        break;
    }
    
    return formatted_desc;
}

/*
 * Function:    start_council_replacement_vote
 * Description: Alarmed function that gets called every month.
 */
public void
start_council_replacement_vote()
{
    if (mappingp(get_active_vote()))
    {
        // There is already an active vote. No need to start a vote.
        return;
    }

    string dow, month;
    int day, hour, minute, second, year, current_time;
    current_time = time();
    sscanf(ctime(current_time), "%s %s %d %d:%d:%d %d", dow, month, day, hour, minute, second, year);
    int month_num = 0;
    switch (month)
    {
    case "Jan":
        month_num = 1;
        break;
    case "Feb":
        month_num = 2;
        break;
    case "Mar":
        month_num = 3;
        break;
    case "Apr":
        month_num = 4;
        break;
    case "May":
        month_num = 5;
        break;
    case "Jun":
        month_num = 6;
        break;
    case "Jul":
        month_num = 7;
        break;
    case "Aug":
        month_num = 8;
        break;
    case "Sep":
        month_num = 9;
        break;
    case "Oct":
        month_num = 10;
        break;
    case "Nov":
        month_num = 11;
        break;
    case "Dec":
        month_num = 12;
        break;
    }
    int slot_num = month_num % 3;
    // Kickstart the nomination process.
    add_nomination_vote_entry(sprintf("%d", slot_num));
}

/*
 * Function:    check_council_replacement_vote
 * Description: Calians have an automatic voting system where at the beginning
 *              of every month, one member of Council gets voted upon.
 *              This function gets called whenever this voting manager
 *              gets created. It should check to see if there is an ongoing
 *              vote. If not, it will set an alarm to kick off the vote on
 *              the first of the month.
 */
public void
check_council_replacement_vote()
{
    if (mappingp(get_active_vote()))
    {
        // There is already an active vote. No need to start a vote.
        return;
    }
    
    string dow, month;
    int day, hour, minute, second, year, current_time;
    current_time = time();
    sscanf(ctime(current_time), "%s %s %d %d:%d:%d %d", dow, month, day, hour, minute, second, year);
    
    if (day <= 7)
    {
        // If we are in the first seven days of the month, we should just
        // start a new nomination process.
        remove_alarm(next_vote_alarm);
        next_vote_alarm = set_alarm(0.0, 0.0, &start_council_replacement_vote());
        return;
    }
    
    // If we are not in the first week, we set an alarm to start the vote at
    // the beginning of the month.
    int next_time = current_time - ((hour * 3600) + (minute * 60) + second);
    int days_in_month = 30;
    switch (month)
    {
    case "Jan":
    case "Mar":
    case "May":
    case "Jul":
    case "Aug":
    case "Oct":
    case "Dec":
        days_in_month = 31;
        break;
        
    case "Feb":
        if ((year % 4) == 0 && (year % 200) != 0)
        {
            // Leap years are on years divisible by 4, but not 200.
            days_in_month = 29;
        }
        else
        {
            days_in_month = 28;
        }
        break;
        
    case "Apr":
    case "Jun":
    case "Sep":
    case "Nov":
        days_in_month = 30;
        break;
    }
    
    // Now add the number of seconds (86400) by the number of days until
    // the next month.
    next_time += (86400 * (days_in_month - day + 1));
    remove_alarm(next_vote_alarm);
    next_vote_alarm = set_alarm(max(3600.00, itof(next_time - current_time)), 0.0, &check_council_replacement_vote());
}
