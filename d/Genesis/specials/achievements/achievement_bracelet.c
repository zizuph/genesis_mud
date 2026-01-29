/*
 * Achievements Bracelet
 *
 * This is a bracelet that can be worn by players or simply carried. When
 * worn, it will allow others to see their achievements.
 *
 * Created by Petros, November 2013
 */
#pragma no_shadow
#pragma strict_types

#include <files.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Genesis/specials/lib/database_lib";
inherit "/d/Sparkle/area/city/lib/utility_functions";

// Defines
#define  PLAYER_I_SHOW_ACHIEVEMENTS   "_player_i_show_achievements"
#define  BRACELET_UNIQUE_ID           "_genesis_achievement_bracelet"
#define  ACHIEVEMENT_MASTER           "/d/Genesis/specials/achievements/achievement_master"
#define  ACHIEVEMENT_SHADOW           "/d/Genesis/specials/achievements/achievement_shadow"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

public int discard_bracelet(string arg);

public string
long_description()
{
    return "This is the Genesis Achievements Bracelet. Your achievements are tracked "
        + "through Genesis Badges. Eventually you will be able to <wear> "
        + "this bracelet to show off your <badges> to others. Should you need to, you "
        + "can <discard> it, but you will not earn any badges without it.\n";
}

/*
 * Function:    query_database_file
 * Description: Mask this function to specify where the data should
 *              be stored.
 */
public string
query_database_file()
{
    object player = environment(this_object());
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return 0;
    }
    
    string player_name = player->query_real_name();
    string first_char = player_name[..0];
    return "/d/Genesis/specials/achievements/player_data/" + first_char + "/" + player_name;
}

public void
initialize_achievement_bracelet()
{
    // Configure the database
    ::init_database();
        
    // Achievement Bracelet DB stores the following information
    // 0. Badge Master File
    // 1. Whether the badge has been earned or not
    // 2. A mapping of historical events regarding this badge (time/date earned, etc)
    // 3. Any additional data stored for tracking the progress of this badge
    add_column("badge_file");    // string
    add_column("badge_earned");  // 0 (not yet earned) or 1 (earned) or -1 (internal badge not to be shown)
    add_column("badge_history"); // mixed history, preferably array of arrays
    add_column("badge_data");    // mixed data
}

private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("bracelet");
    add_name(BRACELET_UNIQUE_ID);
    add_adj( ({ "gilded", "azure" }) );
    set_short("gilded azure bracelet");
    set_long(long_description);

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL, 1);

    config_wearable_item(A_L_WRIST, 1, 99, this_object());
    // Must be called in an alarm because the bracelet needs to make it
    // into the person first before we can load and save the data
    // properly.
    set_alarm(0.0, 0.0, &initialize_achievement_bracelet());
}

public int
add_visible_badge(string badge_file)
{
    mixed rows = query_rows( ([ "badge_file" : badge_file ]) );
    if (sizeof(rows))
    {
        return 0;
    }

    object player = environment(this_object());
    send_debug_message("achievement_bracelet", "Initializing " + badge_file
                       + " data for " + capitalize(player->query_real_name()));
    return add_or_update_row( ([
                                   "badge_file" : badge_file,
                                   "badge_earned" : 0,
                                   ]) );
}

public int
add_internal_badge(string badge_file)
{
    mixed rows = query_rows( ([ "badge_file" : badge_file ]) );
    if (sizeof(rows))
    {
        return 0;
    }

    return add_or_update_row( ([
                                   "badge_file" : badge_file,
                                   "badge_earned" : -1,
                                   ]) );
}

public mixed
query_badge_row(string badge_file)
{
    mixed badge_rows = query_rows( ([ "badge_file" : badge_file ]) );
    if (!sizeof(badge_rows))
    {
        return 0;
    }
    return badge_rows[0] + ([ ]); // return a copy, not the real row
}

public mixed
wear(object ob)
{
    write("By wearing the " + short() + ", others will be able to "
          + "see your achievements.\n");
    this_player()->add_prop(PLAYER_I_SHOW_ACHIEVEMENTS, 1);

    return 0;
}

public mixed
remove(object ob)
{
    object player = environment(this_object());
    if (!player)
    {
        return 0;
    }

    /* During remove() never use write as this_player() isn't known. */
    player->catch_tell("By removing the " + short() + ", you no longer "
                       + "advertise your achievements to others.\n");
    player->remove_prop(PLAYER_I_SHOW_ACHIEVEMENTS);

    return 0;
}

public string
query_recover(void)
{
    return (string)0;
}

public string
query_auto_load(void)
{
    return MASTER + ":";
}

/*
 * Function name: appraise_object
 * Description  : When you inherit /lib/wearable_item.c into any object
 *                other than /std/armour.c you MUST also define the function
 *                appraise_object() as copy of this function. It MUST make
 *                the call to appraise_wearable_item() as well. If you omit
 *                this, then the player will not be able to appraise this
 *                item properly.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : int num - the semi-randomised appraise skill.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public mixed
query_earned_badge_rows()
{
    object player = environment(this_object());
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return 0;
    }
    
    mixed earned_badge_rows = query_rows( ([ "badge_earned" : 1 ]) );
    return earned_badge_rows;
}

public mixed
query_unearned_badge_rows()
{
    object player = environment(this_object());
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return 0;
    }
    
    mixed unearned_badge_rows = query_rows( ([ "badge_earned" : 0 ]) );
    return unearned_badge_rows;
}

public string
display_earned_badges(object player = 0)
{
    if (!objectp(player))
    {
        player = this_player();
    }

    object bracelet = present(BRACELET_UNIQUE_ID, player);

    string message = "";

    mixed earned_badge_rows = bracelet->query_earned_badge_rows();
    int num_earned = sizeof(earned_badge_rows);
    message += "You have earned " + num_earned + (num_earned == 1 ? "badge" : " badges") + "!\n";
    if (num_earned == 0)
    {
        return "";
    }

    message += sprintf("%20-=s %50-=s\n", "Badge Name", "Badge Description");
    message += sprintf("%71'='s\n", "");
    foreach (mixed badge_row : earned_badge_rows)
    {
        string badge_file = badge_row["badge_file"];
        object badge_master = safely_load_master_file(badge_file);
        if (!objectp(badge_master))
        {
            continue;
        }
        message += sprintf("%20-=s %50-=s", badge_master->query_badge_name(), badge_master->query_badge_description());
    }
    
    return message;
}

public string
display_unearned_badges(object player = 0)
{
    if (!objectp(player))
    {
        player = this_player();
    }

    object bracelet = present(BRACELET_UNIQUE_ID, player);
    mixed unearned_badge_rows = bracelet->query_unearned_badge_rows();

    int num_unearned = 0;
    string message = "";
    foreach (mixed badge_row : unearned_badge_rows)
    {
        string badge_file = badge_row["badge_file"];
        object badge_master = safely_load_master_file(badge_file);
        if (!objectp(badge_master) || !badge_master->reveal_unearned_badge())
        {
            continue;
        }
        num_unearned += 1;
        message += sprintf("%s\n", badge_master->query_badge_name());
    }
    if (num_unearned == 0)
    {
        return "";
    }
    message = "You know about " + num_unearned + " unearned badges.\n" + message;
    return message;
}

public int
do_checkin(string arg)
{
    notify_fail("Where do you want to check in? Here?\n");
    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    if (arg != "here")
    {
        return 0;
    }

    // Load the "data" variable to pass to all listening badges
    ACHIEVEMENT_MASTER->trigger_event_location_checkin(this_player());
    write("You have checked in at " + environment(this_player())->short()
          + ".\n");

    return 1;
}

public int
show_badges(string arg)
{
    object player = this_player();
    if (strlen(arg) && player->query_wiz_level())
    {
        object target_player = find_player(lower_case(arg));
        if (objectp(target_player))
        {
            object old_tp = player;
            player = target_player;
            set_this_player(player);
            string message = display_earned_badges(player) + "\n" + display_unearned_badges(player);
            set_this_player(old_tp);
            write("Showing Badge Information for " + capitalize(arg) + "\n");
            this_player()->more(message);
            
            return 1;
        }
        else
        {
            notify_fail("Cannot find player " + capitalize(arg) + " to show badges.\n");
            return 0;
        }
    }

    string message = display_earned_badges() + "\n" + display_unearned_badges();
    this_player()->more(message);

    return 1;
}

public void
init()
{
    ::init();

//    add_action(do_checkin, "checkin");
    add_action(show_badges, "badges");
    add_action(discard_bracelet, "discard");
}

/*
 * Function name: leave_env
 * Description  : When you inherit /lib/wearable_item.c into any object other
 *                than /std/armour.c you MUST also define the function
 *                leave_env() as copy of this function. It MUST make the
 *                call to wearable_item_leave_env(from, to) as well. If
 *                you omit this, then the item will not be automatically
 *                removed when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
public void
leave_env(object from, object to)
{
    send_debug_message("achievement_bracelet", "leaving environment");

    if (from->has_achievement_shadow())
    {
        from->remove_achievement_shadow();
    }

    ::leave_env(from, to);

    wearable_item_leave_env(from, to);
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    /* There can be only one. */
    if (sizeof(filter(all_inventory(dest), &->id(BRACELET_UNIQUE_ID))) > 1)
    {
        set_alarm(0.1,0.0, remove_object);
        return;
    }

    if (IS_LIVING_OBJECT(dest)
        && !dest->has_achievement_shadow())
    {
        setuid();
        seteuid(getuid());
        object achievement_shadow = clone_object(ACHIEVEMENT_SHADOW);
        achievement_shadow->set_bracelet_object(this_object());
        // We use catch just in case nomask is on move_living
        catch(achievement_shadow->shadow_me(dest));
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

    ::remove_object();
}

public int
discard_bracelet(string str)
{
    notify_fail("What do you wish to discard?\n");
    if (!strlen(str))
    {
        return 0;
    }
    
    object target = PARSE_COMMAND_ONE(str, 0, "[the] %i");
    if (!objectp(target)
        || target != this_object())
    {
        return 0;
    }
    
    write("You discard the " + short() + " and it turns to dust.\n");
    // Save the player's targets in case they get the stone back.
    set_alarm(0.0, 0.0, remove_object);
    return 1;
}
