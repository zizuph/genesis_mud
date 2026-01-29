/*
 * Generic Voting Manager for Genesis Guilds
 *
 * This manager will manage all the voting needs of Genesis Guilds
 *
 * Created by Petros, February 2010
 */

#pragma strict_types

#include <files.h>
#include <filepath.h>
#include <macros.h>

inherit "/d/Genesis/specials/lib/database";

// Voting Data Structure
// - category (string)
// - description (string)
// - start time (number)
// - duration (number)
// - vote choices (array) // if empty, then free form
// - actual votes (mapping of person name => vote)
// - active

// Global Variables
public mapping  vote_alarms = ([ ]);

// Prototypes
public void     start_votes();
public void     start_vote(int id);

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return FILE_PATH(MASTER_OB(this_object())) + "voting_data";
}

public void
create_database()
{
    add_column("category");
    add_column("description");
    add_column("start_time");
    add_column("duration");
    add_column("choices");
    add_column("votes");
    
    // Status Information
    add_column("active"); 
    
    set_alarm(0.0, 0.0, start_votes);
}

/*
 * Function:    add_vote_entry
 * Description: Adds a new vote into the system. It will return
 *              the id of the row that was added into the voting
 *              database.
 */
public int
add_vote_entry(string category, string description)
{
    int result;
    
    setuid();
    seteuid(getuid());
    
    result = add_row( ([ 
                "category"   : category,
                "description": description,
                "start_time" : time(), // starts immediately
                "duration"   : 604800, // 1 week
                "choices"    : ({ "aye", "nay", "abstain" }),
                "votes"      : ([ ]),
                "active"     : 1 ]) );

    if (result == 1) // success
    {
        return query_num_rows() - 1;
    }
    
    // Not successful, return a non-valid row number
    return -1;
}

// Getters and Setters
public void
set_field_by_id(string field, mixed value, int id)
{
    mapping row;
    
    row = query_row_by_id(id);
    if (!mappingp(row))
    {
        return;
    }
    
    row[field] = value;
    save_data();    
}

public mixed
get_field_by_id(string field, int id)
{
    mapping row;
    
    row = query_row_by_id(id);
    if (!mappingp(row))
    {
        return 0;
    }
    
    return row[field];
}

public void
set_vote_category(mixed value, int id)
{
    set_field_by_id("category", value, id);
}

public void
set_vote_description(mixed value, int id)
{
    set_field_by_id("description", value, id);
}

public void
set_vote_start_time(mixed value, int id)
{
    set_field_by_id("start_time", value, id);
}

public void
set_vote_duration(mixed value, int id)
{
    set_field_by_id("duration", value, id);
}

public void
set_vote_choices(mixed value, int id)
{
    set_field_by_id("choices", value, id);
}

public void
set_vote_active(mixed value, int id)
{
    set_field_by_id("active", value, id);
}

public void
set_votes_cast(mixed value, int id)
{
    set_field_by_id("votes", value, id);
}

public mixed
get_vote_category(int id)
{
    return get_field_by_id("category", id);
}

public mixed
get_vote_description(int id)
{
    return get_field_by_id("description", id);
}

public mixed
get_vote_start_time(int id)
{
    return get_field_by_id("start_time", id);
}

public mixed
get_vote_duration(int id)
{
    return get_field_by_id("duration", id);
}

public mixed
get_vote_choices(int id)
{
    return get_field_by_id("choices", id);
}

public mixed
get_vote_active(int id)
{
    return get_field_by_id("active", id);
}

public mixed
get_votes_cast(int id)
{
    return get_field_by_id("votes", id);
}

public int
is_voting_enabled(int id)
{
    // Voting is active when
    // 1. Active flag is set
    // 2. The current time is between start and end times
    if (!get_vote_active(id))
    {
        return 0;
    }
    
    if (time() < get_vote_start_time(id)
        || time() > get_vote_start_time(id) + get_vote_duration(id))
    {
        return 0;
    }
    
    return 1;
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
    // Mask this function to do something with the vote cast
    // by the player.
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
    // By default the validation routine just checks to see if the 
    // vote is one of the choices.
    mixed choices = get_vote_choices(id);
    if (!IN_ARRAY(lower_case(value), choices))
    {
        return "You can only vote for one of the available "
            + "choices.";
    }
    
    return 0;
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
    notify_fail("You have already cast a vote!\n");
}

/*
 * Function:    allow_vote_change
 * Description: Function that determines whether someone is allowed to
 *              change their vote. By default, this is set to be false.
 */
public int
allow_vote_change(int id)
{
    return 0;
}

// Voting Functions

/*
 * Function:    cast_vote
 * Description: This function will return 0 if the vote was
 *              successful, and an error string or any error
 *              conditions.
 */
public string
cast_vote(mixed player, int id, mixed value)
{
    string name;
    object player_obj;
    if (stringp(player) && objectp(player_obj = find_player(player)))
    {
        name = player;
    }
    else if (objectp(player_obj = player) && IS_PLAYER_OBJECT(player))
    {
        name = player->query_real_name();
    }
    else
    {
        // Not a player, so cannot vote.
        return "Only a player can vote.";
    }
    
    // Check to make sure the voting is currently active
    if (!is_voting_enabled(id))
    {
        return "Voting is not currently active.";
    }
    
    if (!get_alarm(vote_alarms[id]))
    {
        start_vote(id);
    }
    
    // Validate the vote choice.
    string errorMessage;
    if (stringp(errorMessage = validate_vote_choice(id, value)))
    {
        return errorMessage;
    }    
    
    // Check to see if the voter has already cast a vote
    int bChangedVote = 0;
    mapping votes = get_votes_cast(id);
    if (votes[name])
    {
        // Player has already cast a vote
        bChangedVote = 1;
        if (!allow_vote_change(id))
        {
            hook_already_cast_vote(player_obj, id, votes[name], value);
            return " "; // return a space string to indicate that there was an error.
        }
        else if (votes[name] == value)
        {
            return "You've already cast the same vote!";
        }
    }
    
    votes[name] = value;
    set_votes_cast(votes, id);
    // Call the hook function.
    hook_vote_cast(id, player_obj, value, bChangedVote);
    
    // Success!
    return 0;
}

/*
 * Function:    get_vote_results
 * Description: Returns a mapping of the vote choices and the people
 *              who voted for it.
 *              Choice => ({ list of people })
 */
public mapping
get_vote_results(int id)
{
    // We're essentially building a reverse mapping. The votes_cast is a mapping
    // from the name to the choice. We are building a mapping the other
    // way around.
    mapping votes = get_votes_cast(id);
    mapping results = ([ ]);
    foreach (string name, mixed choice : votes)
    {
        if (!pointerp(results[choice]))
        {
            results[choice] = ({ });
        }
        
        results[choice] += ({ name });
    }
    
    return results;
}

private int
sort_vote(mixed a, mixed b)
{
    // Each vote is an array of two items: ({ choice, ({ voters }) })
    // We go in descending order of number of votes (rank), so we reverse it.
    if (sizeof(a[1]) > sizeof(b[1]))
    {
        return -1;
    }
    else if (sizeof(a[1]) < sizeof(b[1]))
    {
        return 1;
    }
    
    return 0;
}

public mixed *
get_ordered_vote_results(int id)
{
    mixed * sorted_results = ({ });
    mapping results = get_vote_results(id);
    foreach (mixed choice, string * votes : results)
    {
        sorted_results += ({ ({ choice, votes }) });
    }
    sort_array(sorted_results, sort_vote);
    return sorted_results;
}

/*
 * Function:    end_vote
 * Description: Called by the alarm when this vote has expired
 */
public void
end_vote(int id)
{
    remove_alarm(vote_alarms[id]);
    m_delkey(vote_alarms, id);
    
    // When a vote ends, we need to set it to be inactive
    set_vote_active(0, id);
    
    hook_end_vote(id);
}

/*
 * Function:    start_vote
 * Description: Start the vote for an individual ID
 */
public void
start_vote(int id)
{
    remove_alarm(vote_alarms[id]);
    // Calculate how much time is left
    int end_time = get_vote_start_time(id) + get_vote_duration(id);
    float duration = itof(max(0, end_time - time()));
    vote_alarms[id] = set_alarm(duration, 0.0, &end_vote(id));
    send_debug_message("voting_manager", "Adding alarm with id of " + vote_alarms[id]
        + " with duration " + ftoi(duration));
        
    hook_start_vote(id);
}

/*
 * Function:    start_votes
 * Description: This goes through all the active votes in the database and
 *              kicks off alarms for all of them.
 */
public void
start_votes()
{
    mixed * records = query_rows( ([ ]) );
    foreach (mapping record : records)
    {
        int current_id = record["id"];
        if (!record["active"])
        {
            // This vote isn't active.
            continue;
        }
        
        if (!is_voting_enabled(current_id))
        {
            // Voting has ended. It's also active, meaning we haven't
            // called end_vote on it before. We go ahead and call the end_vote 
            // using an alarm
            set_alarm(0.0, 0.0, &end_vote(current_id));
            continue;
        }
        
        // If voting is enabled, we start the vote (again)
        start_vote(current_id);
    }
}

/*
 * Function:    remove_cast_vote
 * Description: This function removes a vote that was cast.
 */
public void
remove_cast_vote(int id, string player)
{
    mapping votes = get_votes_cast(id);
    if (votes[player])
    {
        m_delkey(votes, player);
        set_votes_cast(votes, id);
    }    
}
