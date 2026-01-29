/*
 * /d/Sparkle/area/jade/obj/burden_helper.c
 *
 * An assistant to burden.c: Follows the player around as ordered by burden.c,
 * refreshing paralysis
 *
 * Martin Berka (Mar), 2017-06-20 Sparkle
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <cmdparse.h> //For paralyze functionality

/* Global variables */
int     cmd_approved, //Flag showing that helper sent this command
        slow_cmd_alarm; //Alarm indicating maximum time burden can be borne
float   time_delay; //Time which player must wait between moves
object  burden; //The burden that created the helper
string  fail_message, //Message displayed when action is not allowed yet.
        planned_cmd, //What the player wants to do next
        carrier; //The name of the burden carrier

/* Prototypes */
void allow_cmd();
void set_time_delay(float new_delay = -1.0);
void stop(string cmd);

/*
 * Function name: create_monster
 * Description  : Constructor: makes invisible object with trigger
 */
void
create_object()
{
    //Hide this in every way
    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();

    slow_cmd_alarm = 0;
    cmd_approved = 0;
    planned_cmd = "";
    set_time_delay();
}


/*
 * Function name: initialize
 * Description	: Init
 * Arguments	: (object) Destination following initialization
 */
void
deliver(object destination)
{
    burden = calling_object();
    if (function_exists("query_burdened", burden))
    {
        carrier = burden->query_burdened();
    }
    else
    {
        carrier = file_name(burden);
    }
    slow_cmd_alarm = set_alarm(time_delay, 0.0, "allow_cmd");
    move_object(destination);
}


/*
 * Function name: init
 * Description	: Applies paralysis action
 */
void
init()
{
    add_action(stop, "", 1);
}


/*
 * Function name: allow_cmd
 * Description  : Leave a room after sufficient time
 */

void
allow_cmd()
{
    object cmd_player = find_player(carrier);
    slow_cmd_alarm = 0;
    if (strlen(planned_cmd))
    {
        cmd_approved = 1;
        write(query_living_name(cmd_player) + "\n");
        //TODO: FIND WHY THIS IS RETURNING 0 instead of executing ->
        write(cmd_player->command(planned_cmd));
        planned_cmd = "";
        slow_cmd_alarm = set_alarm(time_delay, 0.0, "allow_cmd");
        cmd_approved = 0;
        burden->check_new_room();
    }
}


/*
 * Function name: set_fail_message
 * Description  : Setter for message displayed to player when action is delayed
 * Arguments    : (string) new message
 */
void
set_fail_message(string new_message)
{
    fail_message = new_message;
}


/*
 * Function name: set_time_delay
 * Description  : Set the minimum time between commands
 * Arguments    : (float) minimum time between restricted commands (if not
 *      given, determined with default rules)
 */
void
set_time_delay(float new_delay = -1.0)
{
    if (new_delay < 0.0)
    {
        new_delay = 5.0;

        if (living(burden))
        {
            new_delay += 3.0; //Supporting at least a staggering NPC
            if (burden->query_prop(LIVE_I_STUNNED)) //Awkward dead weight
            {
                new_delay += 3.0;
            }
        }   //Otherwise, some sort of load-lightening system.
    }
    time_delay = new_delay;
}


/*
 * Function name: stop
 * Description  : Block commands - adapted from /std/paralyze.c
 * Argument     : string str - The command line argument.
 * Returns      : int 1/0    - success (block) /failure.
 */
int
stop(string cmd)
{
    /* Not burdened? Not our business */
    if (!present( burden, this_player() ))
    {
        return 0;
    }
    /* Some commands may always be issued. Non-room-changing. */
    string verb = query_verb();
    if (CMDPARSE_PARALYZE_CMD_IS_ALLOWED(verb))
    {
        tell_object(find_player("mar"), "Allowed: " + verb + "\n");
        return 0;
    }

    string new_cmd = (strlen(cmd) ? verb + " " + cmd : verb);
    /* If not tired, call allow_cmd to call this command, so that we capture
     * the instant after that action is completed (silently deny the original).
     *  */
    if (!slow_cmd_alarm)
    {
        if (cmd_approved)
        {
            tell_object(find_player("mar"), "Ready: " + planned_cmd + "\n");
            return 0;
        }
        planned_cmd = new_cmd;
        allow_cmd();
        return 1;
    }

    /* Only paralyze mortals - but still track */
    if (this_player()->query_wiz_level())
    {
        if ( member_array(verb, ({"!", "stop", "Clean"}) ) > -1) //Emergency
        {
            return 0;
        }
        write("If you were mortal, '" + verb + "' would be delayed.\n");
        if (cmd_approved)
        {
            write("Returned 0");
            return 0;
        }
        planned_cmd = new_cmd;
        allow_cmd();
        return 1;
        // burden->set_alarm(0.1, 0.0, "check_new_room");
        // return 0;
    }

    if (!strlen(planned_cmd))
    {
        planned_cmd = new_cmd;
        this_player()->catch_msg("You prepare to do so.\n");
    }
    else if (planned_cmd != new_cmd)
    {
        planned_cmd = new_cmd;
        this_player()->catch_msg("You prepare to do that instead.\n");
    }
    else if (fail_message)
    {
        this_player()->catch_msg(fail_message);
    }
    return 1;
}
