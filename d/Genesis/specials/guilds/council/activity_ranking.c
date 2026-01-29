/*
 * Ranking Object for Guilds
 *
 * This module provides base functionality for guilds that would like to
 * track activity of their members. The higher the rank, the more active
 * one is.
 *
 * Created by Petros, March 2009 
 */
 
#pragma no_clone
#pragma strict_types
#pragma save_binary

#include <std.h>
#include <macros.h>

// Global Variables
public mapping          Scores = ([ ]); // name to score mapping
public mapping          Cycle_scored = ([ ]); // first score each cycle
public mapping          Last_scored = ([ ]); // last time scored

#define SCORE_INTERVAL      3600
#define CYCLE_LENGTH        86400
#define CYCLE_SCORE         23
#define INTERVAL_SCORE      1

public string
query_save_file()
{
    return "/d/Genesis/specials/guilds/data/activity_scores";
}

public void
load_data()
{
    if (!query_save_file())
    {
        return;
    }
    
    restore_object(query_save_file());
}

public void
save_data()
{
    if (!query_save_file())
    {
        return;
    }
    
    save_object(query_save_file());
}

/*
 * Function name: create
 * Description  : Function called when object is loaded
 */
public nomask void
create()
{
    setuid();
    seteuid(getuid());
    
    load_data();

    // Set a repeating alarm to update once every 5 minutes
//    set_alarm(0.0, 600.0, update_scores);
}

public void
add_player(string player)
{
    if (!IN_ARRAY(player, m_indices(Scores)))
    {
        Scores[player] = 0;
        save_data();
    }
}

public void
remove_player(string player)
{
    if (IN_ARRAY(player, m_indices(Scores)))
    {
        m_delkey(Scores, player);
        save_data();
    }
}

public void
update_scores()
{
    object player;
    // In order to maintain the same activity score, you need to be active
    // approx one hour a day.
    // Each day, the first hour of activity will net you 23 points. Every
    // successive hour will increase by one.
    // Every hour you are not awake when the calculation takes place reduces
    // the activity score by one.
    foreach (string name : m_indices(Scores))
    {
        // We score once per specified interval
        if (Last_scored[name] + SCORE_INTERVAL > time())
        {
            continue;
        }
        
        Last_scored[name] = time();
        
        if (!objectp(player = find_player(name))
            || player->query_linkdead())
        {
            // Player is not awake. In this case, we reduce their score
            // by one.
            Scores[name] = max(0, Scores[name] - 1); // can't go below 0
            continue;
        }
        
        // At this point, we know that the player is in the game
        if (Cycle_scored[name] + CYCLE_LENGTH < time())
        {
            Cycle_scored[name] = time();
            Scores[name] += CYCLE_SCORE;
        }
        else
        {
            Scores[name] += INTERVAL_SCORE;
        }
    }
    
    save_data();
}
