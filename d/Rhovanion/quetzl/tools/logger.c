#pragma strict_types

/* This is a meeting sign to aid in conducting and recording meetings
 * It should be using by either cloning this object, or inheriting
 * it and defining create_meeting() to your liking.  Special functions
 * are described here.  They are as follows:
 *
 * You may want to redefine this function:
 *
 * is_valid_operator(object who)
 * This should return 1 if who can perform a command, and perform
 * a write of an error message, and return 0 if the player cannot
 * perform commands on the sign.  help meeting and meeting status
 * are available to all, others depend on the return value from
 * this function.
 * Default is to allow any wizard to perform meeting commands.
 *
 * You may want to call these functions:
 *
 * set_descript_in_room(string desc)
 * sets exactly what the player will see regarding the sign when
 * they perform a look command.  Does not replace set_long.
 *
 * log_change(string log)
 * sets the log file, this can also be changed by hand when in the
 * meeting
 *
 * Coded by Quetzl, April 1994
 */

inherit "/std/object";

#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/secure/std.h"

#define HELP_FILE "/d/Rhovanion/quetzl/open/meeting_help"
#define CHECK_SO_VALID if (!is_valid_operator(this_player())) return 1;

static string log_file,
              descript_in_room,
              *listeners;

static int logging,
           echoing,
           locked;

/*
 * Function name:  create_meeting
 * Description:    constructor
 * Arguments:      none
 * Returns:        void
 */

public void
create_meeting() {}

/*
 * Function name:  create_object
 * Description:    default sign set up
 * Arguments:      none
 * Returns:        void
 */

public nomask void
create_object()
{
    set_name("sign");
    set_adj("meeting");
    set_long("This is a meeting sign. For help type \"help meeting\".  " +
        "To check the status of the meeting type \"meeting status\".\n");
    add_prop(OBJ_M_NO_GET, "Please leave the sign where it is.\n");

    log_file = "";
    descript_in_room = "There is a meeting sign hanging on the wall.\n";
    listeners = ({});
    logging = echoing = locked = 0;

    enable_commands();
    set_no_show_composite(1);
    create_meeting();
}

/*
 * Function name:  init
 * Description:    add commands for sign
 * Arguments:      none
 * Returns:        void
 */

public void
init()
{
    if (locked)
    {
        this_player()->move(this_player()->query_prop(LIVE_O_LAST_ROOM), 1);
        write("The meeting room is locked.\n");
        return;
    }

    add_action("lock_room", "lock");
    add_action("unlock_room", "unlock");
    add_action("begin_things", "begin");
    add_action("stop_things", "stop");
    add_action("add_listener", "add");
    add_action("remove_listener", "remove");
    add_action("get_help", "help");
    add_action("roll_call", "call");
    add_action("meeting_status", "meeting");
    add_action("log_change", "log");
}

/*
 * Function name:  set_descript_in_room
 * Description:    set the description of the sign when in the room.
 * Arguments:      str - Exactly what players should see.
 * Returns:        void
 */

public void
set_descript_in_room(string str)
{
    descript_in_room = str;
}

/*
 * Function name:  query_descript_in_room
 * Description:    get the description players see of the sign
 * Arguments:      none
 * Returns:        The description
 */

public string
query_descript_in_room()
{
    return descript_in_room;
}

/*
 * Function name:  is_valid_operator
 * Description:    defines who can perform commands on the sign, except
 *                     for help meeting, and meeting status
 * Arguments:      ob - object trying to perform the command
 * Returns:        should output fail messages and return 0 if object 
 *                     cannot perform command, else return 1
 */

public int
is_valid_operator(object ob)
{
    if (!ob->query_wiz_level())
        write ("Only a wizard can perform that command.\n");

    return !!ob->query_wiz_level();
}

/*
 * Function name:  lock_room
 * Description:    locks the meeting room
 * Arguments:      arg - should be "meeting"
 * Returns:        1 or 0
 */

public int
lock_room(string arg)
{
    notify_fail("Lock what?\n");
    if (arg != "meeting")
        return 0;

    CHECK_SO_VALID;

    locked = 1;
    write("The meeting is now locked.\n");
    tell_room(environment(this_object()), QCTNAME(this_player()) + 
        " locks the meeting.\n");
    return 1;
}

/*
 * Function name:  unlock_room
 * Description:    unlocks the room
 * Arguments:      arg - should be "meeting"
 * Returns:        1 or 0
 */

public int
unlock_room(string arg)
{
    notify_fail("Unlock what?\n");
    if (arg != "meeting")
        return 0;

    CHECK_SO_VALID;

    locked = 0;
    write("The meeting is now unlocked.\n");
    tell_room(environment(this_object()), QCTNAME(this_player()) + 
        " unlocks the meeting.\n");
    return 1;
}

/*
 * Function name:  begin_log
 * Description:    activates logging function in sign
 * Arguments:      none
 * Returns:        always 1
 */

public int
begin_log()
{
    if (logging)
    {
        write("A log has already been started.\n");
        return 1;
    }

    logging = 1;
    tell_room(environment(this_object()), "LOG STARTED: " + ctime(time()) + 
        "\n");
    return 1;
}

/*
 * Function name:  begin_echo
 * Description:    activates echoing feature of sign
 * Arguments:      none
 * Returns:        Always 1
 */

public int
begin_echo()
{
    if (!sizeof(listeners))
    {
        write ("There are no listeners, so it would be pointless to echo.\n");
        return 1;
    }

    if (echoing)
    {
        write ("Echoing is already enabled.\n");
        return 1;
    }

    echoing = 1;
    tell_room(environment(this_object()), "MEETING ECHO ENABLED: " + 
        ctime(time()) + "\n");
    return 1;
}

/*
 * Function name:  begin_things
 * Description:    merely calls begin_echo or begin_log, used by player
 * Arguments:      arg - should be "log" or "echo"
 * Returns:        1 or 0
 */

public int
begin_things(string arg)
{
    notify_fail("Begin what?\n");
    if (!strlen(arg))
        return 0;

    CHECK_SO_VALID;

    switch (arg)
    {
        case "log": return begin_log();
        case "echo": return begin_echo();
        default: return 0;
    }
}

/*
 * Function name:  stop_log
 * Description:    deactivates logging function of sign
 * Arguments:      none
 * Returns:        always 1
 */

public int
stop_log()
{
    if (!logging)
    {
        write("Logging is not active.\n");
        return 1;
    }

    tell_room(environment(this_object()), "LOG STOPPED: " + ctime(time()) + 
        "\n");
    logging = 0;
    return 1;
}

/*
 * Function name:  stop_echo
 * Description:    deactivates echoing function of sign
 * Arguments:      none
 * Returns:        always 1
 */

public int
stop_echo()
{
    if (!echoing)
    {
        write("Echoing is not active.\n");
        return 1;
    }

    tell_room(environment(this_object()), "MEETING ECHO STOPPED: " + 
        ctime(time()) + "\n");
    echoing = 0;
    return 1;
}

/*
 * Function name:  stop_things
 * Description:    calls either stop_log or stop_echo
 * Arguments:      arg - should be "log" or "echo"
 * Returns:        1 or 0
 */

public int
stop_things(string arg)
{
    notify_fail("Stop what?\n");
    if (!strlen(arg))
        return 0;

     CHECK_SO_VALID;

     switch (arg)
     {
         case "log": return stop_log();
         case "echo": return stop_echo();
         default: return 0;
     }
}

/*
 * Function name:  add_listener
 * Description:    adds a player currently logged on to the echoing list
 * Arguments:      who - name of the player to add
 * Retunrs:        1 or 0
 */

public int
add_listener(string who)
{
    object whom;

    notify_fail("Whom do you wish to add?\n");
    if (!strlen(who))
        return 0;

    CHECK_SO_VALID;

    notify_fail("Could not find that player.\n");
    whom = find_player(lower_case(who));
    if (!whom)
        return 0;

    listeners += ({ lower_case(who) });
    tell_room(environment(this_object()), "ADDED ECHOING TO: " + 
        whom->query_name() + "\n");
    return 1;
}

/*
 * Function name:  remove_listener
 * Description:    removes a player's name from the echoing list
 * Arguments:      who - name of the player
 * Returns:        1 or 0
 */

public int
remove_listener(string who)
{
    int num;

    who = lower_case(who);

    CHECK_SO_VALID;

    notify_fail(capitalize(who) + " is not on the echoing list.\n");
    if (num = member_array(who, listeners) == -1)
        return 0;

    listeners = exclude_array(listeners, num, num);
    tell_room(environment(this_object()), "REMOVED ECHOING FROM: " + 
        capitalize(who) + "\n");
    return 1;
}

/*
 * Function name:  get_help
 * Description:    display the help file
 * Arguments:      arg - should be "meeting"
 * Returns:        1 or 0
 */

public int
get_help(string arg)
{
    if (arg != "meeting")
        return 0;

    reset_euid();

    this_player()->more(HELP_FILE);
    return 1;
}

/*
 * Function name:  roll_call
 * Description:    prints out the names and domains of all those present
 * Arguments:      arg - should be "roll"
 * Returns:        1 or 0
 */

public int
roll_call(string arg)
{
    object *people;
    string who = "";
    int i;

    notify_fail("Call what?\n");
    if (arg != "roll")
        return 0;

    CHECK_SO_VALID;

    people = FILTER_PLAYERS(all_inventory(environment(this_object())));

    for (i = 0; i < sizeof(people); i++)
    {
        if (people[i]->query_wiz_level())
            who += "    " + SECURITY->query_wiz_pretitle(people[i]) +
                " " + people[i]->query_name() + " of " +        
                people[i]->query_domain() + "\n";
        else
            who += "    " + people[i]->query_name() + " - Mortal\n";
    }

    tell_room(environment(this_object()), 
        "ROLLCALL:  Present are:\n\n" + who + "\n", 0, this_object());
    return 1;
}

/*
 * Function name:  do_echoes
 * Description:    echo the meeting to those listening
 * Arguments:      message - the string to be given to those listening.
 * Returns:        void
 */

public void
do_echoes(string message)
{
    int i;
    object who, speaker;

    for (i = 0; i<sizeof(listeners); i++)
    {
        who = find_player(listeners[i]);
        if (who)
        {
            speaker = present("_meeting_receiver_", who);
            if (!speaker)
                break;

            if (speaker->query_active_listen())
                who->catch_msg("Meeting: " + message, this_object());
        }
    }
}

/*
 * Function name:  meeting_status
 * Description:    show locked, echoing, and logging status
 * Arguments:      arg - should be "status"
 * Returns:        0 or 1
 */

public int
meeting_status(string arg)
{
    notify_fail("Meeting what?\n");
    if (arg != "status")
        return 0;

    write ("The meeting is currently ");
    (locked) ? (write("locked.\n")) : (write("unlocked.\n"));
    write ("Echoing is currently ");
    (echoing) ? (write("on.\n")) : (write("off.\n"));
    write("Logging is currently ");
    (logging) ? (write("on.\n")) : (write("off.\n"));
    return 1;
}

/*
 * Function name:  log_change
 * Description:    sets the file to log to
 * Arguments:      arg - path to the log file
 * Returns:        0 or 1
 */

public int
log_change(string arg)
{
    notify_fail("Log what?\n");
    if (!strlen(arg))
        return 0;

    notify_fail("You can't switch logs while logging.\n");
    if (logging)
        return 0;
    log_file = arg;
    return 1;
}

/*
 * Function name:  query_met
 * Description:    called when action happens in room
 * Arguments:      blah - object responsible for action
 * Returns:        always 1
 */

public int
query_met(object blah)
{
    return 1;
}

/*
 * Function name:  catch_msg
 * Description:    takes care of echoing and logging
 * Arguments:      str - string or array of strings
 *                 blah - object responsible for message
 * Returns:        void
 */

public void
catch_msg(mixed str, object blah)
{
    string message;
    (pointerp(str)) ? (message = str[0]) : (message = process_string(str, 1));
 
    reset_euid();

    if (echoing)
        do_echoes(message);
    
    if (logging)
        write_file(log_file, message + "\n");
}

/*
 * Function name:  enter_env
 * Description:    takes care of adding description in room.
 * Arguments:      to - object moved into
 *                 blah - object moved from
 * Returns:        void
 */

public void
enter_env(object to, object blah)
{
    ::enter_env(to, blah);
    to->add_my_desc(descript_in_room, this_object());
}
