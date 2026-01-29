/*
 * /d/Gondor/guilds/rangers/soul/obscure.c
 *
 * Included in the soul. Ability for a Ranger to obscure their trail
 * by wiping away the tracks to make it harder for them to be tracked.
 * One can obscure trail, which is fast but very chancy, or obscure
 * trail carefully, which is slower but more reliable. Success and
 * speed depend on SS_TRACKING and SS_WIS of the player.
 *
 * Originally coded by Mayhem Liege of Emerald - 8 Dec, 1994
 *
 * Modification log:
 * 13 April 2001 Gwyneth: General cleanup and move
 * 27 July 2004 Tigerlily: Changed fail message
 */

#define OBSCURE_TIME        2
#define LONG_OBSCURE_TIME   3
#define OBSCURE_FATIGUE     5

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

varargs int stop_obscure(mixed arg);
public varargs void do_obscure(object who, int success, object room);

#define RANGER_I_OBS_ALARM    "_ranger_i_obs_alarm"
#define RANGER_I_OBS_SUCCESS  "_ranger_i_obs_success"

/* Function name: obscure
 * Description  : Attempt to obscure the tracks behind you. 
 * Arguments    : string str - the argument
 * Returns      : 1 on success, 0 on failure
 */
public int
obscure(string str)
{
    int alarm, success;
    object paralyze,
           room = this_player()->query_prop(LIVE_O_LAST_ROOM);

    if (!strlen(str))
    {
        notify_fail("Obscure the trail?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[the] 'trail' [carefully]"))
    {
        notify_fail("Obscure the trail?\n");
        return 0;
    }

    if (!room->query_prop(ROOM_I_IS))
    {
        notify_fail("There is no trail to obscure here.\n");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        notify_fail("You can't see your hand in front of your face, " +
            "let alone the trail behind you.\n");
        return 0;
    }

    if (this_player()->query_fatigue() < OBSCURE_FATIGUE)
    {
        notify_fail("You are too tired to do that.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());
    paralyze = clone_object("/std/paralyze");
    paralyze->set_standard_paralyze("tracking");
    paralyze->set_stop_fun("stop_obscure");
    paralyze->set_stop_verb("stop");
    paralyze->set_stop_message("You stop obscuring the trail behind you.\n");
    paralyze->set_fail_message("You are busy obscuring the trail behind " +
      "you.  You must 'stop' or finish to do something else.\n");
 
    switch(str)
    {
    case "trail":
        paralyze->set_remove_time(OBSCURE_TIME);
        paralyze->move(this_player(), 1);
        this_player()->add_fatigue(-OBSCURE_FATIGUE);

        write("You begin obscuring the path behind you.\n");
        say(QCTNAME(this_player()) + " bends down and starts doing " +
            "something to the trail behind " + 
            this_player()->query_objective() + ".\n");

        if(this_player()->resolve_task(TASK_DIFFICULT,
          ({ TS_WIS, SS_TRACKING } )) > 0)
            success = 1;

        alarm = set_alarm(OBSCURE_TIME.0, 0.0, &do_obscure(TP, success, room));

        TP->add_prop(RANGER_I_OBS_ALARM, alarm);

        break;
    case "trail carefully":
        paralyze->set_remove_time(LONG_OBSCURE_TIME);
        paralyze->move(this_player(), 1);

        write("You begin obscuring the path behind you.\n");
        say(QCTNAME(this_player()) + " bends down and starts doing " +
            "something to the trail behind " + 
            this_player()->query_objective() + ".\n");

        if(this_player()->resolve_task(TASK_ROUTINE,
          ({ TS_WIS, SS_TRACKING })) > 0)
            success = 1;

        alarm = set_alarm(LONG_OBSCURE_TIME.0, 0.0, &do_obscure(TP, success, room));

        TP->add_prop(RANGER_I_OBS_ALARM, alarm);

        break;
    default:
        return 0;
    }
    return 1;
} 

varargs int
stop_obscure(mixed arg)
{
    remove_alarm(TP->query_prop(RANGER_I_OBS_ALARM));
    say(QCTNAME(TP) + " straightens back up, having finished "+
        POSSESSIVE(TP) + " work.\n");
    return 0;
}

public varargs void
do_obscure(object who, int success, object room)
{
    if (!objectp(who))
        return;

    set_this_player(who);

    if (success)
    {
        room->remove_prop(ROOM_S_DIR);
        write("You have obscured the trail behind you.\n");
    }
    else
    {
        write("Traces of tracks remain on the trail behind you.\n");
    }

}

