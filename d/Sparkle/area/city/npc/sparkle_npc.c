/*
 *  /d/Sparkle/area/city/npc/sparkle_npc.c
 *
 *  The standard file for npcs of Sparkle!
 *  
 *  Please change me as needed!
 *
 *  Created March 2008, by Aeg (Matthew Morin)
 *  Real work done August 2004, by Gorboth (Cooper Sherry)
 *  Modified April 2008, Petros - Support pathfind and time hooks
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
public void         create_sparkle_npc();
public void         catch_question(string question);
public void         create_monster();
public void         add_sparkle_asks();
public void         sparkle_answer();
public void         job_answer();
public void         help_answer();
public void         swear_word_answer();
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
public void         return_object(object obj, object to);
public int          is_busy();
public void         set_busy(int flag);
public int          npcsize(object npc, string hdesc, string wdesc);

/* global variables */
static string       OrigQuestion;
public string       Job_Response;
                    /* Add words as you think of 'em */
public string       *Swear_Words = ({ "shit", "asshole", "ass", "fuck",
                                      "fucker", "fuckface", "shitface",
                                      "shithead", "fuck you", "cunt",
                                      "cocksucker" });
public string *     active_path;
public int          path_step_alarm;
public int          busy_flag;

public void         set_job_response(string s) { Job_Response = s; }
public string       query_job_response() { return Job_Response; }


/*
 * Function name:       create_sparkle_npc
 * Description  :       dummy routine for inheriting files
 */
public void
create_sparkle_npc()
{
} /* create_sparkle_npc() */

/*
 * Function name:       create_monster
 * Description  :       set up some standard things for Sparkle npcs
 */
public void
create_monster()
{
    string master_file;
    object timekeeper;
    
    add_name("_sparkle_npc");
    
    set_default_answer(VBFC_ME("default_answer"));
    add_sparkle_asks();
    default_config_npc(15);
    set_not_here_func("respond_to_player_left_hook");
    
    create_sparkle_npc();
    
    master_file = MASTER_OB(this_object());
    if (!LOAD_ERR(MASTER_TIME_ROOM))
    {
        timekeeper = MASTER_TIME_ROOM->get_timekeeper();
        if (timekeeper)
        {
            timekeeper->register_npc(master_file);
        }
    }
    
    set_dont_answer_unseen(1); // unseen_hook gets called
    busy_flag = 0;
} /* create_monster */


/*
 * Function name:       add_sparkle_asks
 * Description  :       These are standard asks to be inherited by
 *                      other Sparkle npc's, allowing us more varied
 *                      responses without inconsistancy.
 */
public void
add_sparkle_asks()
{
    add_ask( ({ "city", "sparkle", "city of sparkle", "town",
            "village", "area" }),
        VBFC_ME("sparkle_answer"));
    add_ask( ({ "game", "genesis" }),
        VBFC_ME("game_answer"));
    add_ask( ({ "task", "quest", "help"}),
        VBFC_ME("help_answer"));
    add_ask( ({ "job", "occupation", "work", "career" }),
        VBFC_ME("job_answer"));
    add_ask( ( Swear_Words ),
        VBFC_ME("swear_word_answer"));
        
} /* add_sparkle_asks */

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
    // 4. Player object is invalid (player left the game)
    if (!CAN_SEE_IN_ROOM(this_object())
        || !player
        || !CAN_SEE(this_object(), player)
        || environment(this_object()) != environment(player))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:       sparkle_answer
 * Description  :       response to an add_ask
 */
public string
sparkle_answer()
{
    command("say Sparkle is a great place to live! Have you found "
        + "everything our city has to offer?");
    return "";
    
} /* sparkle_answer */

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
    command("say Well, have you explored the city? There are many "
        + "things to do in Sparkle!");
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
        clear_path();
        walk_in_wrong_room_hook();
        return;
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
 * Function name: unseen_hook
 * Description:   This function gets called if this mobile couldn't see
 *		  who asked the question and is not supposed to answer
 *		  in that case.
 */
public void
unseen_hook()
{
    command("emote looks confused.");
    command("say I thought I heard someone speaking to me.");
    command("peer quizzically");
}

/*
 * Function name:       respond_to_player_left_hook
 * Description  :       Override this to customize the behavior
 *                      to use when the player disappears from the
 *                      npc's view for whatever reason.
 * Arguments    :       player - player who left
 * Returns      :       0 - always returns 0
 */
public int
respond_to_player_left_hook(object player)
{
    command("emote looks confused.");
    if (player)
    {        
        command("say Where'd " + player->query_pronoun()
              + " go?");
    }
    else
    {
        command("say Where'd that person go?");
    }
    command("peer quizzically");
    return 0;
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(from))
        return;

    set_alarm(0.5, 0.0, &return_object(ob, from));
}

/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    int is_heap, amount;
    
    is_heap = obj->query_prop(HEAP_I_IS);
    amount = (is_heap ? obj->num_heap() : 1);
    
    if (is_heap && amount > 1)
    {
        // Heaps need special handling. Since I can't find
        // a way to reliable use a command to give, we're
        // going to cheat a little and move it to the player's
        // environment and show a message
        if (present(to, environment(this_object())))
        {
            obj->move(to, 1);
            tell_room(environment(this_object()), QCTNAME(this_object())
                    + " gives " + obj->short() + " to "
                    + QTNAME(to) + ".\n", to);
            to->catch_tell(this_object()->query_The_name(to) + " gives "
                         + obj->short() + " to you.\n");
        }
        else
        {
            obj->move(environment(this_object()), 1);
            tell_room(environment(this_object()), QCTNAME(this_object())
                    + " drops " + obj->short() + ".\n");
        }            
    }
    else
    {
        command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
        if (environment(obj) == this_object())
        {
           command("drop " + OB_NAME(obj));
        }
    }
}

/* 
 * Function name:        is_busy
 * Description  :        returns whether the npc is busy doing something
 *                       and should not be interrupted
 * Arguments    :        none
 * Returns      :        0/1 - not busy/busy
 */
public int
is_busy()
{
    return busy_flag;
}

/* 
 * Function name:        set_busy
 * Description  :        Sets the flag on the npc to of whether they are
 *                       busy or not.
 * Arguments    :        flag - 0 or 1
 * Returns      :        nothing
 */
public void
set_busy(int flag)
{
    busy_flag = flag;
}


/*
 * Function name: respond_to_question_busy_hook
 * Description  : Default response when the npc is currently busy
 * Arguments    : player - player asking the question
 *                question - The question asked
 * Returns      : nothing
 */
public void
respond_to_question_busy_hook(object player, string question)
{
    if (cannot_see_person(player))
    {
        unseen_hook();
        return;
    }
    
    say_to_player("I'm a little busy right now. Can you ask me later?",
                  player);
}

/*
 * Function name: catch_question
 * Description:   This function is called in each living being someone asks a
 *                question to.
 * Arguments:     question - The question as put
 */
public void
catch_question(string question)
{
    string      *tmp_arr,                       /* preps/verbs of interest */
                stuff1, stuff2, stuff3;         /* tmp strings */


    if (is_busy() || sizeof(active_path) > 0)
    {
        set_alarm(1.0, 0.0, 
                  &respond_to_question_busy_hook(this_player(), question));
        return;
    }

    if (objectp(query_attack()))
    {
        return; /* no answers if fighting */
    }

    OrigQuestion = question;
    if (strlen(question))
    {
        /* strip off leading "for", "about" and trailing " ?" */
        tmp_arr = ({ "for", "about" });
        if (parse_command(question, ({}), "%p %s", tmp_arr, stuff1))
        {
            question = stuff1;
        }
        if (sscanf(question, "%s ?", stuff1) ||
            sscanf(question, "%s?", stuff1))
        {
            question = stuff1;
        }
    }
    ::catch_question(question);
}

/*
 * Function name:       npcsize
 * Description  :       set CONT_I_HEIGHT, CONT_I_WEIGHT and
 *                      CONT_I_VOLUME of an npc to give the 
 *                      desired appearance
 * Arguments    :       object npc -- the npc
 *              :       string hdesc -- the desired height desc
 *                                       (e.g., "tall")
 *              :       string wdesc -- the desired width desc
 *                                      (e.g., "plump")
 * Returns      :       1 on success, 0 on failure
 */
public int
npcsize(object npc, string hdesc, string wdesc)
{
    int         hindex,
                windex,
                *spread,
                spreadsize,
                height,
                *raceattr;

    if (!objectp(npc) ||
        !npc->query_npc() ||
        !strlen(hdesc) ||
        !strlen(wdesc))
    {
        return 0;
    }
    raceattr = RACEATTR[npc->query_race()];
    if (sizeof(raceattr) < 6 ||
        raceattr[0] <= 0 ||
        raceattr[4] <= 0 ||
        raceattr[5] <= 0)
    {
        return 0;
    }
    if (hdesc == "normal")
    {
        hdesc = "of normal length";
    }

    if ((hindex = member_array(hdesc, HEIGHTDESC)) < 0)
    {
        return 0;
    }
    if (wdesc == "normal")
    {
        wdesc = "of normal width";
    }
    if ((windex = member_array(wdesc, WIDTHDESC)) < 0)
    {
        return 0;
    }
    spread = SPREAD_PROC;
    spreadsize = sizeof(spread);
    if (hindex >= spreadsize ||
        windex >= spreadsize)
    {
        return 0;
    }

    height = ((raceattr[0] * spread[hindex]) / 100);
    npc->add_prop(CONT_I_HEIGHT, height);
    npc->add_prop(CONT_I_WEIGHT,
        (((raceattr[5] * spread[windex]) / 100) * height));
    npc->add_prop(CONT_I_VOLUME,
        (raceattr[4] * 1000));
    return 1;
} /* npcsize */