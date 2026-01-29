/* 
 * Christmas Event 2013 Badge - Krynnish Hammie
 *
 * This is a badge for the Christmas Event 2013. You get this for
 * collecting one in this badge's domain.
 *
 * Created by Petros, December 2013
 */

#pragma strict_types
#pragma save_binary

#include <files.h>
#include <math.h>
#include "/d/Genesis/ateam/aoe/events/christmasham2013/defs.h"

inherit "/d/Genesis/specials/achievements/badge_base";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function:    create_badge
 * Description: Override this create function to set up the badge details.
 */
public void
create_badge()
{
    set_badge_name("Krynnish Hammie");
    set_badge_description("Neither the Knights of Solamnia nor the Dragonarmies stand "
                          + "a chance against you finding the Christmas ham and chips! "
                          + "Keep it up and maybe you can become "
                          + "a Donut Trotter Hammie!\n");
    set_listening_events( ({ "event_christmas_event_2013_collect" }) ); // string array of events we're listening to
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
    player->catch_tell("You've managed to collect something in the Krynn domains! For that, you \n"
                       + "have earned the " + query_badge_name() + " Badge!\n");
    player->catch_tell("-----------------------------------------------------------------------------------\n");
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
    string room_file = MASTER_OB(data["location"]);
    if (wildmatch("/d/Krynn/*", room_file)
        || wildmatch("/d/Ansalon/*", room_file))
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
    object room = data["location"];
    int timestamp = data["timestamp"];
    badge_row["badge_history"][timestamp] = MASTER_OB(room);

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
    int num_collected = m_sizeof(badge_row["badge_history"]);
    if (num_collected > 0)
    {
        return 1;
    }
    return 0;
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
