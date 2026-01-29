/* 
 * Badge Base File
 *
 * This is the base file for all achievement badges.  It provides the basic
 * interface that all badges will implement.
 *
 * Created by Petros, November 2013
 */

#pragma strict_types
#pragma save_binary

#include <files.h>
#include <macros.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define  ACHIEVEMENT_MASTER           "/d/Genesis/specials/achievements/achievement_master"
#define  BRACELET_UNIQUE_ID           "_genesis_achievement_bracelet"

// Interfaces
public void        create_badge();
public void        trigger_event(object player, string event_name, mixed data);
public int         is_listening_to_event(string event_name);
public object      find_achievement_bracelet(object player, int bShowWizardsAndJuniors);
public void        hook_notify_player_earned_badge(object player);
public void        reset_badge(object player);
public int         reset_badge_row(object player, mixed badge_row);
public void        earn_badge(object player);

// Getters and Setters
public string      query_badge_name();
public void        set_badge_name(string name);
public string      query_badge_description();
public void        set_badge_description(string description);
public string *    query_listening_events();
public void        set_listening_events(string * events);

// Global Variables
public string      m_strBadgeName;
public string      m_strBadgeDescription;
public string *    m_listeningEvents = ({ });

/*
 * Function:    register_with_achievement_master
 * Description: Call to the achievement master to register the badge information
 *              Usually called by alarm from the create() function.
 */
public void
register_with_achievement_master()
{
    ACHIEVEMENT_MASTER->register_badge(this_object());
}

/*
 * Function:    create
 * Description: base create function. Sets the UID and EUID, calls
 *              the overridable create_badge, and registers with
 *              the achievement master.
 */
private nomask void
create()
{
    setuid();
    seteuid(getuid());

    create_badge();
    // Call to register must be after the details are set
    set_alarm(0.0, 0.0, &register_with_achievement_master());
}

/*
 * Function:    create_badge
 * Description: Override this create function to set up the badge details.
 */
public void
create_badge()
{
    set_badge_name("Basic Achievement");
    set_badge_description("For doing absolutely nothing, you have achieved the "
                          + query_badge_name() + " Badge!\n");
    set_listening_events( ({ }) );
}

public string
query_badge_name()
{
    return m_strBadgeName;
}

public void
set_badge_name(string name)
{
    m_strBadgeName = name;
}

public string
query_badge_description()
{
    return m_strBadgeDescription;
}

public void
set_badge_description(string description)
{
    m_strBadgeDescription = description;
}

/*
 * Function:    query_listening_events
 * Description: This gets called by the achievement master when registeriing
 *              this badge. It should return all the events that this badge
 *              depends on.
 */
public string *
query_listening_events()
{
    return m_listeningEvents;
}

public void
set_listening_events(string * events)
{
    if (!sizeof(events))
    {
        m_listeningEvents = ({ });
    }
    else
    {
        m_listeningEvents = events + ({ });
    }
}

/*
 * Function:    is_listening_to_event
 * Description: This is called in the achievement master to determine whether
 *              to continue processing this badge. To disable this badge, simply
 *              return 0.
 */
public int
is_listening_to_event(string event_name)
{
    return IN_ARRAY(event_name, m_listeningEvents);
}

/*
 * Function:    initialize_badge_data
 * Description: Call this to ensure that the player's data file has the
 *              information for this badge.
 */
public void
initialize_badge_data(object player)
{
    object bracelet = find_achievement_bracelet(player, 1);
    if (!objectp(bracelet))
    {
        return;
    }

    // First, make sure that the badge info is in the player's bracelet
    string badge_file = MASTER_OB(this_object());
    bracelet->add_visible_badge(badge_file);
}

/*
 * Function:    has_earned_badge
 * Description: Returns whether or not the player has earned this
 *              badge.
 */
public int
has_earned_badge(object player)
{
    // has_earned_badge is called by the achievement master first. This
    // will ensure that initialization of the data is always first.
    initialize_badge_data(player);

    object bracelet = find_achievement_bracelet(player, 1);
    if (!objectp(bracelet))
    {
        return 0;
    }

    string badge_file = MASTER_OB(this_object());
    mixed badge_row = bracelet->query_badge_row(badge_file);
    if (!badge_row)
    {
        return 0;
    }
    
    return (badge_row["badge_earned"] == 1);
}

/*
 * Function:    does_event_apply
 * Description: This function should be overridden by the individual badge. It should
 *              determine whether the event that just came in should trigger any
 *              further processing.
 */
public int
does_event_apply(object player, string event_name, mixed data)
{
    return 0;
}

/*
 * Function:    update_badge_history_and_data
 * Description: This function should be overridden by the individual badge. It should
 *              update the badge_row with the information it wants to store. If it
 *              changes anything, it should return 1.
 * Returns:     1 if anything was changed. 0 otherwise.
 */
public int
update_badge_history_and_data(object player, string event_name, mixed data, object bracelet, mixed badge_row)
{
    return 0;
}

/*
 * Function:    qualified_for_badge
 * Description: This function should be overridden by the individual badge. It should
 *              check the badge_row to see if the player is now qualified to earn the
 *              badge. If so, earn_badge will be called.
 */
public int
qualified_for_badge(mixed badge_row)
{
    return 0;
}

/*
 * Function:    trigger_event
 * Description: This gets called by the achievement master when an event
 *              occurs that this badge is waiting for. This is a nomask function.
 *              Override the functions called to customize the badge.
 */
public nomask void 
trigger_event(object player, string event_name, mixed data)
{
    object bracelet = find_achievement_bracelet(player, 1);
    if (!objectp(bracelet))
    {
        return;
    }

    // First, make sure that the badge info is in the player's bracelet
    string badge_file = MASTER_OB(this_object());
    mixed badge_row = bracelet->query_badge_row(badge_file);
    if (!badge_row)
    {
        return;
    }
    
    if (!m_sizeof(badge_row["badge_history"]))
    {
        badge_row["badge_history"] = ([ ]);
    }
    // Allow the badge to update the data row based on its own rules
    if (update_badge_history_and_data(player, event_name, data, bracelet, badge_row))
    {
        bracelet->update_rows(badge_row, ([ "badge_file" : badge_file ]) );
    }

    // Check to see if the changes to the data has now qualified the player for the badge
    if (!qualified_for_badge(badge_row))
    {
        return;
    }

    // Qualified for badge, so call the earn_badge function
    earn_badge(player);
}

/*
 * Function:    find_achievement_bracelet
 * Description: Locates the achievement bracelet for the player. Returns
 *              0 if none can be found.
 */
public object      
find_achievement_bracelet(object player, int bShowWizardsAndJuniors = 1)
{
    if (!objectp(player))
    {
        return 0;
    }

    if (!bShowWizardsAndJuniors)
    {
        if (player->query_wiz_level() || wildmatch("*jr", player->query_real_name()))
        {
            return 0;
        }
    }

    return present(BRACELET_UNIQUE_ID, player);
}

/*
 * Function:    reset_badge_row
 * Description: Called by reset_badge and does the actual work of resetting
 *              the data.
 * Returns:     0 if nothing changed, 1 if the changes should be saved
 */
public int
reset_badge_row(object player, mixed badge_row)
{
    if (badge_row["badge_earned"] == 1
        || badge_row["badge_history"]
        || badge_row["badge_data"])
    {
        badge_row["badge_earned"] = 0;
        badge_row["badge_history"] = 0;
        badge_row["badge_data"] = 0;
        return 1;
    }
    
    return 0;
}

/*
 * Function:    reset_badge
 * Description: Resets all the data for the badge for this particular player
 */
public void
reset_badge(object player)
{
    object bracelet = find_achievement_bracelet(player, 1);
    if (!objectp(bracelet))
    {
        return;
    }

    string badge_file = MASTER_OB(this_object());
    mixed badge_row = bracelet->query_badge_row(badge_file);
    if (!badge_row)
    {
        return;
    }

    if (reset_badge_row(player, badge_row))
    {
        bracelet->update_rows(badge_row, ([ "badge_file" : badge_file ]) );
    }
}

/*
 * Function:     earn_badge
 * Description:  Call this function to mark that a player has earned this
 *               badge. It calls a hook to notify the player of this
 *               achievement.
 */
public void
earn_badge(object player)
{
    object bracelet = find_achievement_bracelet(player, 1);
    if (!objectp(bracelet))
    {
        return;
    }

    string badge_file = MASTER_OB(this_object());
    mixed badge_row = bracelet->query_badge_row(badge_file);
    if (!badge_row)
    {
        return;
    }

    badge_row["badge_earned"] = 1;
    bracelet->update_rows(badge_row, ([ "badge_file" : badge_file ]) );
    
    hook_notify_player_earned_badge(player);
}

/*
 * Function:    hook_notify_player_earned_badge
 * Description: This is the hook that gets called whenever the player earns a badge.
 *              It should give the proper message about how and why the player earned
 *              this particular badge/achievement.
 */
public void
hook_notify_player_earned_badge(object player)
{
    player->catch_tell("------------------------- *** ACHIEVEMENT ALERT *** -------------------------------\n");
    player->catch_tell("You've earned the " + query_badge_name() + " Badge!\n");
    player->catch_tell("-----------------------------------------------------------------------------------\n");
}

/*
 * Function:    reveal_unearned_badge
 * Description: If you want this badge to appear in a list even when it is unearned,
 *              you should return 1.
 */
public int
reveal_unearned_badge()
{
    return 0;
}
