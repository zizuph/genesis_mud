/* 
 * Badge for Achieving The Hero Mortal Level
 *
 * This is a sample badge demonstrating a badge that is given when a mortal
 * achieves the hero mortal level.
 *
 * Created by Petros, November 2013
 */

#pragma strict_types
#pragma save_binary

#include <files.h>
#include <state_desc.h>

inherit "/d/Genesis/specials/achievements/badge_base";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function:    create_badge
 * Description: Override this create function to set up the badge details.
 */
public void
create_badge()
{
    set_badge_name("Mortal Hero");
    set_badge_description("For achieving the hero mortal level, you are awarded the Mortal Here Badge!\n");
    set_listening_events( ({ "event_mortal_level" }) ); // string array of events we're listening to
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
    string new_level = data["new_level"];
    if (new_level == "hero")
    {
        return 1;
    }
    
    // For all other levels, use a comparison directly against the index
    if (member_array(new_level, SD_AV_TITLES) >= member_array("hero", SD_AV_TITLES))
    {
        return 1;
    }

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
    string old_level = data["old_level"];
    string new_level = data["new_level"];
    int timestamp = data["timestamp"];
    badge_row["badge_history"][timestamp] = ({ old_level, new_level });

    return 1;
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
    if (m_sizeof(badge_row["badge_history"]))
    {
        return 1;
    }
    return 0;
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
    player->catch_tell("You've reached hero level! For that, you have earned the "
                       + query_badge_name() + " Badge!\n");
    player->catch_tell("-----------------------------------------------------------------------------------\n");
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
    return 0; // temporarily disabling this badge

    return ::is_listening_to_event(event_name);
}
