/*
 *  /d/Sparkle/area/wild/npc/wild_npc.c
 *
 *  The standard file for npcs in the Wild area of Sparkle!
 *  
 *  Please change me as needed!
 *
 *  Adapted from the Sparkle City file, April 30 2008, by Styles
 *  Real work done March 2008, by Aeg (Matthew Morin)
 *  Real real work done August 2004, by Gorboth (Cooper Sherry)
 *  Modified April 2008, Petros - Support pathfind and time hooks
 *
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include <login.h>
#include <macros.h>
#include <files.h>
inherit PATHFIND_LIB;

/* prototypes */
public void         create_wild_npc();
public void         create_monster();
public void         add_wild_asks();
public void         wild_answer();
public void         job_answer();
public void         help_answer();
public void         swear_word_answer();
public int          not_here_func();
public string       default_answer();
public void         alert_hour_change(int time_seconds);
public void         alert_hour_change_hook(int hour);
public int          is_fighting();
public void         walk_in_wrong_room_hook();
private mixed       get_path_to_room(string roomfile);
public int          walk_to_room(string roomfile);
public void         clear_path();
public void         walk_prestep(string direction, string room);
public void         walk_poststep(string direction, string room);
private void        walk_step();
public void         walk_in_wrong_room_hook();
public void         walk_destination_reached_hook();
public int          walk_precondition_hook(string direction, 
                                           string roomfile);
public int          cannot_see_person(object player);

/* global variables */
static string       OrigQuestion;
public string       Job_Response;
                    /* Add words as you think of 'em */
public string       *Swear_Words = ({ "shit", "asshole", "ass", "fuck",
                                      "fucker", "fuckface", "shitface",
                                      "shithead" });
public string *     active_path;
public int          path_step_alarm;


public void         set_job_response(string s) { Job_Response = s; }
public string       query_job_response() { return Job_Response; }




/*
 * Function name:       create_wild_npc
 * Description  :       dummy routine for inheriting files
 */
public void
create_wild_npc()
{
} /* create_wild_npc() */




/*
 * Function name:       create_monster
 * Description  :       set up some standard things for Sparkle Wild npcs
 */
public void
create_monster()
{
    string master_file;
    object timekeeper;
    
    add_name("_wild_npc");
    
    set_default_answer(VBFC_ME("default_answer"));
    add_wild_asks();
    default_config_npc(15);
    set_not_here_func("not_here_func");
    
    create_wild_npc();
    
    master_file = MASTER_OB(this_object());
    if (!LOAD_ERR(MASTER_TIME_ROOM))
    {
        timekeeper = MASTER_TIME_ROOM->get_timekeeper();
        if (timekeeper)
        {
            timekeeper->register_npc(master_file);
        }
    }
} /* create_monster */


/*
 * Function name:       add_wild_asks
 * Description  :       These are standard asks to be inherited by
 *                      other Wild npc's, allowing us more varied
 *                      responses without inconsistancy.
 */
public void
add_wild_asks()
{
    add_ask( ({ "county", "wilderness", "area" }),
        VBFC_ME("wild_answer"));
    add_ask( ({ "game", "genesis" }),
        VBFC_ME("game_answer"));
    add_ask( ({ "task", "quest", "help"}),
        VBFC_ME("help_answer"));
    add_ask( ({ "job", "occupation", "work", "career" }),
        VBFC_ME("job_answer"));
    add_ask( ( Swear_Words ),
        VBFC_ME("swear_word_answer"));
        
} /* add_wild_asks */

/*
 * Function name:       cannot_see_person
 * Description  :       Checks the conditions to see whether
 *                      the player being interacted with can be
 *                      seen or is in the room. This is important 
 *                      especially for quest interaction.
 * Arguments    :       player - player to check
 * Returns      :       0/1 - can see/cannot see
 */
public int
cannot_see_person(object player)
{
    // Three Conditions currently
    // 1. Has enough light to see in the room
    // 2. Has the skills/awareness to see the player
    // 3. Both are in the same room
    if (!CAN_SEE_IN_ROOM(this_object())
        || !CAN_SEE(this_object(), player)
        || environment(this_object()) != environment(this_player()))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:       wild_answer
 * Description  :       response to an add_ask
 */
public string
wild_answer()
{
    command("say The whole county of Sparkle is a wild area. "
        + "This wilderness can be profitable for the bold explorer.");
    return "";
    
} /* wild_answer */

/* 
 * Function name:       job_answer
 * Description  :       response to add_ask
 */
public string
job_answer()
{
    command("say Actually, I am currently unemployed. Are you hiring?");
    return "";
    
} /* job_answer */


/*
 * Function name:       help_answer
 * Description  :       response to add_ask
 */
public string
help_answer()
{
    command("say Well, have you explored Sparkle county? There are both "
        + "wealth and danger in this savage wilderness!");
    return "";
} /* help_answer */

/*
 * Function name:       swear_word_answer
 * Description  :       response for cursing at NPCs
 */
public string
swear_word_answer()
{
    command("say How rude!");

    return "";
} /* swear_word_answer */

/*
 * Function name:       not_here_func
 * Description  :       called when player asks question and leaves
 * Returns      :       0 = No answer
 */
public int
not_here_func()
{
    command("say Uuuh, where'd you go?");
    return 0;
} /* not_here_func */

/*
 * Function name:       default_answer
 * Description  :       give an answer to unknown questions.
 */
public string
default_answer()
{
    command("shrug");
    command("say What can I say? I don't know about that.");
    return "";
} /* default_answer */

/*
 * Function name:       alert_hour_change
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 *                      Usually, you will not override this. See
 *                      alert_hour_change_hook
 * Arguments    :       time_seconds - number of seconds in Sparkle time
 * Returns      :       nothing
 */
public void
alert_hour_change(int time_seconds)
{
    string str_ctime, day, month;
    string * strarray;    
    int hour, minute, second, date, year;
    
    str_ctime = ctime(time_seconds);
    sscanf(str_ctime, "%s %s %d %d:%d:%d %d", 
           day, month, date, hour, minute, second, year);
    
    // Call the npc specific hook for the hour
    alert_hour_change_hook(hour);
}

/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function is called from within
 *                      alert_hour_change. Override this in your
 *                      own npcs when you want to handle the hourly
 *                      hourly change.
 * Arguments    :       hour - Current hour in Sparkle time
 * Returns      :       nothing
 */
public void
alert_hour_change_hook(int hour)
{
}

/*
 * Function name:       is_fighting
 * Description  :       this method returns whether the npc is 
 *                      currently engaged in combat.
 * Arguments    :       none
 * Returns      :       0/1 - not fighting/is fighting
 */
public int
is_fighting()
{
    if (query_combat_object()->cb_query_attack())
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name: is_valid_room
 * Arguments  : str - the path of the room
 * Returns   : 1 = can be used in the pathfinding, 0 if not
 */
public int is_valid_room(string str)
{
    return 0;
}

/*
 * Function name:       get_path_to_room
 * Description  :       Calls the path find algorithm to retrieve a
 *                      path from the current room to the passed in
 *                      room
 * Arguments    :       roomfile - the file name of the destination
 * Returns      :       the array path as returned by find_path
 */
private mixed
get_path_to_room(string roomfile)
{
    string startroom;
    
    startroom = MASTER_OB(environment(this_object()));
    
    return find_path(startroom, roomfile); 
}

/*
 * Function name:       walk_to_room
 * Description  :       this method calls get_path_to_room and sets
 *                      up the path in this npc and creates the alarm
 *                      that will cause the npc to do the walking
 * Arguments    :       roomfile - file name of the destination
 * Returns      :       whether the path was created correctly or not
 */
public int
walk_to_room(string roomfile)
{
    clear_path();  
    active_path = get_path_to_room(roomfile);
    if (active_path && sizeof(active_path) > 0)
    {
        path_step_alarm = set_alarm(3.0, 3.0, &walk_step());
        return 1;
    }

    return 0;
}

/*
 * Function name:       clear_path
 * Description  :       Clears all the state variables associated with
 *                      walking a path
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
clear_path()
{
    active_path = ({ });
    if (path_step_alarm != -1)
    {
        remove_alarm(path_step_alarm);
    }
    path_step_alarm = -1;            
}

/*
 * Function name:       walk_prestep
 * Description  :       Override this method to have the npc perform
 *                      any commands before performing the walk action
 * Arguments    :       direction - direction that npc will go
 *                      room - the current room file
 * Returns      :       nothing
 */
public void
walk_prestep(string direction, string room)
{
}

/*
 * Function name:       walk_poststep
 * Description  :       Override this method to have the npc perform
 *                      any commands after performing the walk action
 * Arguments    :       direction - direction that npc went
 *                      room - the current room file
 * Returns      :       nothing
 */
public void
walk_poststep(string direction, string room)
{
}

/*
 * Function name:       walk_step
 * Description  :       Perform the actual walking. This will do some
 *                      basic checking and alarm handling. Should not
 *                      override this if not necessary. Override the
 *                      prestep and poststep if you need to perform
 *                      any other actions.
 * Arguments    :       none
 * Returns      :       nothing
 */
private void
walk_step()
{
    if (is_fighting())
    {
        // If we're fighting, we will simply return and
        // allow the path to continue at a later time
        return;
    }
    
    if (sizeof(active_path) < 2)
    {
        // There's no more walking to be done. Remove the alarm
        clear_path();
        return;
    }
    
    if (active_path[1] != MASTER_OB(environment(this_object())))
    {
        walk_in_wrong_room_hook();
        clear_path();
    }
    
    if (!walk_precondition_hook(active_path[0], active_path[1]))
    {
        // Allow the npc to define a precondition as to whether to
        // allow this walk command.
        return;
    }
    
    // Perform the actual walking step
    walk_prestep(active_path[0], active_path[1]);
    command("$" + active_path[0]);
    walk_poststep(active_path[0], active_path[1]);
    if (sizeof(active_path) > 2)
    {
        // Now remove the front item from the array
        active_path = active_path[2..];
    }
    else
    {
        // If there's only one item, then just clear the array.
        clear_path();
        walk_destination_reached_hook();
    }
}

/*
 * Function name:       walk_in_wrong_room_hook
 * Description  :       Override this to do something different if the
 *                      npc somehow ends up in a room that they should
 *                      not be in.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
walk_in_wrong_room_hook()
{
    command("$emote looks a bit lost.");
    command("$peer");    
}

/*
 * Function name:       walk_destination_reached_hook
 * Description  :       Override this to do something when the 
 *                      npc arrives at his destination.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
walk_destination_reached_hook()
{
}

/*
 * Function name:       walk_precondition_hook
 * Description  :       Override this to define something that the npc
 *                      will check before moving onto the next step.
 * Arguments    :       direction - direction the next move is
 *                      roomfile  - current room location
 * Returns      :       0/1 - allow walk step or not
 */
public int
walk_precondition_hook(string direction, string roomfile)
{
    return 1;
}

/*
 * Function name:       say_to_player
 * Description  :       Helper function to have the NPC talk to the player
 *                      by actually speaking directly to them. It will
 *                      check for the presence of the player.
 * Arguments    :       message - message to say
 *                      player  - the person being spoken to
 * Returns      :       nothing
 */
public void
say_to_player(string message, object player)
{
    if (cannot_see_person(this_player()))
    {
        return;
    }
    
    command("$say to " + player->query_real_name() + " " + message);
}

/*
 * Function name:       respond_to_unseen_player_hook
 * Description  :       Override this to customize the behavior
 *                      to use when responding to someone who cannot
 *                      be seen for whatever reason.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
respond_to_unseen_player_hook()
{
    command("emote looks confused.");
    command("$say I thought I heard someone speaking to me.");
    command("peer quizzically");
}

/*
 * Function name:       respond_to_player_left_hook
 * Description  :       Override this to customize the behavior
 *                      to use when the player disappears from the
 *                      npc's view for whatever reason.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
respond_to_player_left_hook()
{
    command("emote looks confused.");
    command("$say Where'd " + this_player()->query_pronoun()
          + " go?");
    command("peer quizzically");
}
