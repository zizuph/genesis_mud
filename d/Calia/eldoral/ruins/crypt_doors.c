#pragma strict_types

#include "defs.h"
#include <ss_types.h>

#define OPEN_STRENGTH 250
#define OPEN_TIME     15.0

int door_status,
    str_total,
    open_alarm;
string direction,
       other_room;

public int do_open(string str);
public int do_close(string str);

/*
 * Function name: door_block
 * Description  : VBFC function called to see if the door is open
 *                or not when using the east exit.
 * Arguments    : n/a
 * Returns      : 0 - Doors open.
 *                1 - Doors closed.
 */
public int
door_block()
{
    if (!door_status)
    { 
        write("You can't walk through solid stone.\n");
        return 1;
    }
    else
    {
        write("You pass through the open doors.\n");
        return 0;
    }  
}

/*
 * Function name: set_door_status
 * Description  : Sets the door's status to open (1) or closed (0)
 * Arguments    : i - 0 for closed. 1 for open.
 * Returns      : n/a
 */
public void
set_door_status(int i)
{
    if (!i)
        door_status = 0;
    else
        door_status = 1;
}

/*
 * Function name: query_door_status
 * Description  : Returns the status of the doors.
 * Arguments    : n/a
 * Returns      : 0 - Closed.
 *                1 - Open.
 */
public int
query_door_status()
{
    return door_status;
}

/*
 * Function name: set_other_room
 * Description  : Sets the path to the room on the other side of
 *                the doors.
 * Arguments    : str - String filename.
 * Returns      : n/a
 */
public void
set_other_room(string str)
{
    other_room = str;
    if (!find_object(other_room))
        other_room->load_me();
}

/*
 * Function name: query_other_room
 * Description  : Returns the path to the room ont he other side 
 *                of the doors.
 * Arguments    : n/a
 * Returns      : Filename of the other room as a string.
 */
public string
query_other_room()
{
    return other_room;
}

/*
 * Function name: init_doors
 * Description  : Initializes commands when objects meet.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init_doors()
{
    add_action(do_open, "open");
    add_action(do_close, "close");
}

/*
 * Function name: open_doors
 * Description  : Actually opens the doors.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
open_doors()
{
    door_status = 1;
    other_room->open_other_doors();
}

/*
 * Function name: open_other_doors
 * Description  : Called by the other side of the doors when they're
 *                opened, so this side will open as well.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
open_other_doors()
{
    if (get_alarm(open_alarm))
        remove_alarm(open_alarm);

    tell_room(TO, "Suddenly, the doors slowly swing open, " +
        "apparently all by themselves.\n");
    door_status = 1;
}

/*
 * Function name: finish_opening
 * Description  : The end result of the attempt to open.
 * Arguments    : obarr - Array of object pointers to the players trying
 *                        to open the door.
 * Returns      : n/a
 */
public void
finish_opening(object *obarr)
{
    int i;

    obarr = filter(obarr, &operator(==)(TO) @ environment);

    str_total = 0;

    for (i = 0; i < sizeof(obarr); i++)
        str_total += obarr[i]->query_stat(SS_STR);

    if (sizeof(obarr) == 1)
    {
        tell_object(obarr[0], "Try as you might, you cannot " +
            "even hope to open these doors by yourself.\n");
        tell_room(TO, "Try as " + obarr[0]->query_pronoun() +
            " might, " + QTNAME(obarr[0]) + " cannot seem " +
            "to open the doors.\n", obarr);
        return;
    }

    if (str_total < OPEN_STRENGTH)
    {
        tell_room(TO, "Try as you might, you cannot open the " +
            "doors.\n", all_inventory(TO) - obarr);
        tell_room(TO, "Try as they might, they cannot open the " +
            "doors.\n", obarr);
        return;
    }
    else
    {
        tell_room(TO, "With great effort, the doors slowly " +
            "swing open under your combined strength.\n",
            all_inventory(TO) - obarr);
        tell_room(TO, "With great effort, the doors slowly " +
            "swing open under their combined strength.\n",
            obarr);
        open_doors();
        return;
    }
}

/*
 * Function name: do_open
 * Description  : What to do when someone uses the 'open' command.
 * Arguments    : str - String argument player passed with the command
 *                      verb.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_open(string str)
{
    object *openers,
           paralyze;

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP,
        "[the] [large] [stone] [double] 'door' / 'doors'"))
        return 0;

    if (door_status)
    {
        NF("The doors are already open.\n");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(TP))
    {
        NF("You can't see the doors!\n");
        return 0;
    }

    if (TP->query_attack())
    {
        NF("You're in a fight, you don't have time to worry " +
            "about the doors.\n");
        return 0;
    }

    write("You begin trying to open the doors.\n");
    say(QCTNAME(TP) + " begins trying to open the doors.\n");

    seteuid(getuid());
    paralyze = clone_object("/std/paralyze");
    paralyze->set_standard_paralyze("opening the doors");
    paralyze->set_stop_fun("stop_opening");
    paralyze->set_stop_verb("stop");
    paralyze->set_stop_message("You stop trying to open the doors.\n");
    paralyze->set_remove_time(ftoi(OPEN_TIME));
    paralyze->set_fail_message("You are too busy trying to open " +
        "the doors. You'll have to stop opening the doors to do " +
        "something else.\n");
    paralyze->move(TP, 1);

    if (!get_alarm(open_alarm))
    {
        open_alarm = set_alarm(OPEN_TIME, 0.0, &finish_opening( ({TP}) ));
        return 1;
    }

    else
    {
        openers = get_alarm(open_alarm)[4][0];
        openers += ({TP});
        remove_alarm(open_alarm);
        open_alarm = set_alarm(OPEN_TIME, 0.0, &finish_opening(openers));
        return 1;
    }
    return 0;
}

/*
 * Function name: do_close
 * Description  : Lets players try to close the doors. It can't be
 *                done, but we'll let them try anyway.
 * Arguments    : str - What the player sent as an argument to the
 *                      close command.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_close(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP,
        "[the] [large] [stone] [double] 'door' / 'doors'"))
        return 0;

    if (!door_status)
    {
        NF("The doors are already closed.\n");
        return 0;
    }

    if (!CAN_SEE_IN_ROOM(TP))
    {
        NF("You can't see the doors.\n");
        return 0;
    }

    write("You try to close the doors, but for some reason, " +
        "that doesn't seem possible.\n");
    say(QCTNAME(TP) + " tries to close the doors, but for " +
        "some reason, that doesn't seem possible.\n");
    return 1;
}

/*
 * Function_name: close_doors
 * Description  : Takes care of actual closing of doors. Done
 *                only when the room resets so messages are
 *                delivered.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
close_doors()
{
    if (door_status)
    {
        tell_room(TO, "The doors suddenly swing closed, seemingly " +
            "all by themselves.\n");
        door_status = 0;
    }
    if (other_room->query_door_status())
    {
        tell_room(find_object(other_room), "The doors suddenly " +
            "swing closed, seemingly all by themselves.\n");
        other_room->set_door_status(0);
    }
}

/*
 * Function name: door_extra
 * Description  : Extra description added to the room's long desc
 *                to display the door.
 * Arguments    : n/a
 * Returns      : A string describing the door's status.
 */
public string
door_extra()
{
    if (door_status)
        return "Large stone double doors stand open to the " +
            direction + ".\n";
    else
        return "Large stone double doors close the exit to " +
            "the " + direction + ".\n";
}

/*
 * Function name: extra_desc
 * Description  : Extra message for the add_item of the doors to
 *                say whether they're open or closed.
 * Arguments    : n/a
 * Returns      : String describing status of the door.
 */
public string
extra_desc()
{
    if (door_status)
        return "Amazingly enough, they stand wide open.";
    else
        return "At the moment, they stand firmly closed.";
}

/*
 * Function name: add_crypt_door
 * Description  : Adds a crypt door to the room.
 * Arguments    : path - String containing the path to the room on
 *                       the other side of the doors.
 *                dir - String describing the direction of the door.
 * Returns      : n/a
 */
public void
add_crypt_door(string path, string dir)
{
    TO->add_exit(path, dir, VBFC_ME("door_block"));
    TO->add_my_desc(VBFC_ME("door_extra"), TO);
    TO->add_item(({"door", "double doors", "doors", "large doors",
        "stone doors", "large stone doors", "large double doors",
        "stone double doors", "large stone double doors"}),
        "The doors are very large and probably even heavier than " +
        "they look. Most likely they aren't very easy to open, " +
        "either. @@extra_desc@@\n");
    direction = dir;
    set_other_room(path);
}

/*
 * Function name: reset_doors
 * Description  : Closes the doors at reset.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_doors()
{
    close_doors();
}
    
