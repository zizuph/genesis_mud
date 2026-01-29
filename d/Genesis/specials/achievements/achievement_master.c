/* 
 * Achievements Master Object
 *
 * This manager will take care of managing the creation and setting of
 * badges. It will be the main interface through which all triggered events
 * will go through.
 *
 * Created by Petros, November 2013
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <filepath.h>
#include <files.h>

inherit "/d/Genesis/specials/lib/database_lib";
inherit "/d/Sparkle/area/city/lib/utility_functions";

// Defines
#define  BRACELET_UNIQUE_ID           "_genesis_achievement_bracelet"

// Global Variables
public mapping  m_registeredEvents = ([ ]);

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    return MASTER_OB(this_object()) + "_data";
}

public void
add_listening_event(string listening_event, string badge_file)
{
    if (!m_registeredEvents[listening_event])
    {
        m_registeredEvents[listening_event] = ({ });
    }
    if (!IN_ARRAY(badge_file, m_registeredEvents[listening_event]))
    {
        send_debug_message("achievement_master", "Badge " + badge_file + " listening for "
                           + listening_event + " event.");
        m_registeredEvents[listening_event] += ({ badge_file });
    }
}

public void
create()
{
    setuid();
    seteuid(getuid());
    
    ::init_database();
        
    add_column("badge_file"); // registered badge file

    // On subsequent loads, we should loop through the rows in the database
    // and repopulate m_registeredEvents
    foreach (mixed row : m_rows)
    {
        string badge_file = row["badge_file"];
        string * listening_events = badge_file->query_listening_events();
        if (!sizeof(listening_events))
        {
            continue;
        }
        foreach (string listening_event : listening_events)
        {
            add_listening_event(listening_event, badge_file);
        }
    }    
}

/*
 * Function:    register_badge
 * Description: This adds the entry for the badge file into the database. It lets
 *              this master knows that this badge exists. 
 */
public int
register_badge(object obj)
{
    if (!objectp(obj))
    {
        return 0;
    }

    string badge_file = MASTER_OB(obj);
    string * listening_events = obj->query_listening_events();
    if (!sizeof(listening_events))
    {
        send_debug_message("achievement_master", "Badge " + badge_file + " is not listening "
                           + "to any events. Will not add to database.");
        return 0;
    }

    mixed badge_rows = query_rows( ([ "badge_file" : badge_file ]) );
    if (!sizeof(badge_rows))
    {
        foreach (string listening_event : listening_events)
        {
            add_listening_event(listening_event, badge_file);
        }

        send_debug_message("achievement_master", "Adding badge database entry for " + badge_file);
        return add_or_update_row( ([ 
                                       "badge_file"      : badge_file,
                                       ]) );
    }

    send_debug_message("achievement_master", "Badge already exists in database. No need to register again.");
    return 0;
}

private void
alarmed_trigger_event(object badge_obj, object player, string event_name, mixed data)
{
    // No need to process this badge if the player has already earned it
    if (badge_obj->has_earned_badge(player)
        || !badge_obj->does_event_apply(player, event_name, data))
    {
        return;
    }

    send_debug_message("achievement_master", "Triggering event " + event_name
                       + " for player " + capitalize(player->query_real_name()));
    badge_obj->trigger_event(player, event_name, data);
}

/*
 * Function:    trigger_event
 * Description: Called to trigger an event that a badge may be listening
 *              for. Will loop through all the badges that are listening
 *              for that event.
 */             
public void
trigger_event(string event_name, object player, mixed data)
{    
    string * matching_badges = m_registeredEvents[event_name];
    if (!sizeof(matching_badges))
    {
        return;
    }
    
    // The player must have the achievement bracelet. Otherwise, no point in continuing.
    if (!objectp(present(BRACELET_UNIQUE_ID, player)))
    {
        return;
    }

    // Loop through all the badges and check whether each one wants to listen to
    // this event
    foreach (string badge_file : matching_badges)
    {
        object badge_master_obj = safely_load_master_file(badge_file);
        if (!objectp(badge_master_obj))
        {
            continue;
        }
        
        if (!badge_master_obj->is_listening_to_event(event_name))
        {
            continue;
        }
        // Use an alarm in case the triggering event takes too much calculation on
        // on the badge, or if the total amount of badge processing takes too much
        set_alarm(0.0, 0.0, &alarmed_trigger_event(badge_master_obj, player, event_name,data));
    }
}

/*
 * Function:    remove_object
 * Description: This function must be copied "as is" to any inheriting
 *              object in order to guarantee that data is saved upon
 *              object destruction. It cannot be part of the lib itself.
 */
public void
remove_object()
{
    save_data();
    // We call destruct() on purpose because this is not a real object.
    destruct();
}

// SPECIFIC FUNCTIONS FOR EACH EVENT TYPE

/*
 * Function:    trigger_event_location_checkin
 * Description: Call this function to trigger a check-in for this player.
 *              The event will notify all listening badges about this
 *              checkin. It's a convenience function so that the construction
 *              of the "data" variable is here in the master.
 */
public void
trigger_event_location_checkin(object player)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }

    // Load the "data" variable to pass to all listening badges
    mixed data = ([ ]);
    data["location"] = environment(player);
    data["timestamp"] = time();
    trigger_event("event_location_checkin", player, data);
}

/*
 * Function:    trigger_event_enemy_kill
 * Description: Call this function to indicate that the player has killed someone.
 *              The event will notify all listening badges about this
 *              kill. It's a convenience function so that the construction
 *              of the "data" variable is here in the master.
 */
public void
trigger_event_enemy_kill(object player, object enemy)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player) || !objectp(enemy))
    {
        return;
    }

    // Load the "data" variable to pass to all listening badges
    mixed data = ([ ]);
    if (IS_PLAYER_OBJECT(enemy))
    {
        data["enemy"] = enemy->query_real_name();
    }
    else
    {
        data["enemy"] = MASTER_OB(enemy);
    }
    data["stat_avg"] = enemy->query_average_stat();
    data["timestamp"] = time();
    trigger_event("event_enemy_kill", player, data);
}

/*
 * Function:    trigger_event_mortal_level
 * Description: Call this function to indicate that the player's mortal level
 *              has changed.
 *              The event will notify all listening badges about this change.
 *              It's a convenience function so that the construction
 *              of the "data" variable is here in the master.
 */
public void
trigger_event_mortal_level(object player, string old_level, string new_level)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }

    // Load the "data" variable to pass to all listening badges
    mixed data = ([ ]);
    data["timestamp"] = time();
    data["old_level"] = old_level;
    data["new_level"] = new_level;
    trigger_event("event_mortal_level", player, data);
}

/*
 * Function:    trigger_event_stat_level
 * Description: Call this function to indicate that the player's stat level
 *              has changed.
 *              The event will notify all listening badges about this change.
 *              It's a convenience function so that the construction
 *              of the "data" variable is here in the master.
 */
public void
trigger_event_stat_level(object player, int stat_id, string old_level, string new_level)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }

    // Load the "data" variable to pass to all listening badges
    mixed data = ([ ]);
    data["timestamp"] = time();
    data["stat"] = stat_id;
    data["old_level"] = old_level;
    data["new_level"] = new_level;
    trigger_event("event_stat_level", player, data);
}

/*
 * Function:    trigger_event_skill_train
 * Description: Call this function to indicate that the player's skill has been
 *              trained.
 *              The event will notify all listening badges about this change.
 *              It's a convenience function so that the construction
 *              of the "data" variable is here in the master.
 */
public void
trigger_event_skill_train(object player, int skill_num, int level)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }

    // Load the "data" variable to pass to all listening badges
    mixed data = ([ ]);
    data["timestamp"] = time();
    data["skill"] = skill_num;
    data["level"] = level;
    trigger_event("event_skill_train", player, data);
}

/*
 * Function:    trigger_event_christmas_event_2013_collect
 * Description: Call this function to indicate that the player has collected
 *              an object for the Christmas 2013 Event
 *              The event will notify all listening badges about this change.
 *              It's a convenience function so that the construction
 *              of the "data" variable is here in the master.
 */
public void
trigger_event_christmas_event_2013_collect(object player, string object_id)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }

    // Load the "data" variable to pass to all listening badges
    mixed data = ([ ]);
    data["timestamp"] = time();
    data["location"] = environment(player);
    data["object_id"] = object_id;
    trigger_event("event_christmas_event_2013_collect", player, data);
}

/*
 * Function:    trigger_event_christmas_event_2013_smoke
 * Description: Call this function to indicate that the player has smoked
 *              an object for the Christmas 2013 Event
 *              The event will notify all listening badges about this change.
 *              It's a convenience function so that the construction
 *              of the "data" variable is here in the master.
 */
public void
trigger_event_christmas_event_2013_smoke(object ham_player, object chips_player, string ham_id, string chips_id)
{
    if (!objectp(chips_player) || !IS_PLAYER_OBJECT(chips_player)
        || !objectp(ham_player) || !IS_PLAYER_OBJECT(ham_player))
    {
        return;
    }

    // Load the "data" variable to pass to all listening badges
    mixed data = ([ ]);
    data["timestamp"] = time();
    data["location"] = environment(chips_player);
    data["ham_player"] = ham_player;
    data["chips_player"] = chips_player;
    data["ham_id"] = ham_id;
    data["chips_id"] = chips_id;
    trigger_event("event_christmas_event_2013_smoke", ham_player, data);
    trigger_event("event_christmas_event_2013_smoke", chips_player, data);
}
