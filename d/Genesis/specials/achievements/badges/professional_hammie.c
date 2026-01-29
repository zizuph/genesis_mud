/* 
 * Christmas Event 2013 Badge - Professional Hammie
 *
 * This is a badge for the Christmas Event 2013. You get this for
 * collecting and reaching 500 points
 *
 * Created by Petros, December 2013
 */

#pragma strict_types
#pragma save_binary

#include <files.h>

inherit "/d/Genesis/specials/achievements/badge_base";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define CONTROLROOM "/d/Genesis/ateam/aoe/events/christmasham2013/controlroom"

/*
 * Function:    create_badge
 * Description: Override this create function to set up the badge details.
 */
public void
create_badge()
{
    set_badge_name("Professional Hammie");
    set_badge_description("You can activate that rune stone without even thinking! Your "
                          + "life's work has been summed up in your amazing ability "
                          + "to locate ham and chips and put them together. They don't "
                          + "call you a Professional Hammie for nothing! You've "
                          + "collected 500 points so far. Keep it up and you just "
                          + "might be fit to become something this Donut has "
                          + "never seen!\n");
    set_listening_events( ({ "event_christmas_event_2013_collect" }) ); // string array of events we're listening to
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
    // Can only earn this badge if you've earned a previous one (pre-req)
    object bracelet = present("_genesis_achievement_bracelet", player);
    if (!objectp(bracelet))
    {
        return 0;
    }

    mixed earned_badge_rows = bracelet->query_earned_badge_rows();
    foreach (mixed badge_row : earned_badge_rows)
    {
        string badge_file = badge_row["badge_file"];
        if (wildmatch("*my_middle_name_is_hammie", badge_file))
        {
            return 1;
        }
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
    if (!badge_row["badge_history"]["player name"])
    {
        badge_row["badge_history"]["player name"] = lower_case(player->query_real_name());
        return 1;
    }
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
    mapping total_score = CONTROLROOM->calculate_total_score();
    string name = badge_row["badge_history"]["player name"];
    if (total_score[name] >= 500)
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
    player->catch_tell("You've collected so much that you're pretty sure your middle name is Hammie!\n"
                       + "For that reason, you have earned the " 
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
    return ::is_listening_to_event(event_name);
}

/*
 * Function:    reveal_unearned_badge
 * Description: If you want this badge to appear in a list even when it is unearned,
 *              you should return 1.
 */
public int
reveal_unearned_badge()
{
    return 1;
}
