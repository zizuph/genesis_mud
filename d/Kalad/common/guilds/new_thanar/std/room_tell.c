/* 
 * With this file you can add sounds and other repeating output
 * to rooms and containers.
 *
 * By Aridor, 09/14/94
 *
 * Brought over to the Thanar directory so that it could be used. Credit
 * to Aridor, always. Just don't want Gondor changing it on me.
 */

#include <filter_funs.h>

public void    do_room_tell();

static int     tell_alarm;
static float   repeat_tell = 0.0;
static string *tell_strings = ({ }),
              *tell_strings_left;

/*
 * Function:    set_tell_time
 * Arguments:   tim: Intervall
 * Description: Set the mean value for room_tell intervall
 * Returns:     void
 */
public void
set_tell_time(int time)
{
    if (time > 0)
        repeat_tell = itof(time);
}

/*
 * Function:    add_tell
 * Arguments:   str:   the tell string to add to the room.
 * Description: Adds a string to the list of tells for a room.
 *              The string can be a VBFC.
 * Returns:     void
 */
public void
add_tell(string str)
{
    tell_strings += ({ str });
}

/*
 * Function:    do_room_tell()
 * Arguments:   -
 * Description: Perform one tell in the room.
 * Returns:     void
 */
public void
do_room_tell()
{
    int     i;
    string  this_tell_string;
    if (!pointerp(tell_strings_left) || !sizeof(tell_strings_left))
         tell_strings_left = tell_strings + ({ });

    if (!pointerp(tell_strings_left) || !sizeof(tell_strings_left))
    {
        tell_alarm = 0;
        return;
    }

    i = random(sizeof(tell_strings_left));
    this_tell_string = tell_strings_left[i];
    tell_strings_left -= ({ this_tell_string, 0 });

    tell_room(this_object(),
        this_object()->check_call(this_tell_string));

    if (sizeof(FILTER_PLAYERS(all_inventory(this_object()))) &&
        !(tell_alarm && sizeof(get_alarm(tell_alarm))))
        tell_alarm = set_alarm(10.0 + repeat_tell / 2.0 + rnd() * repeat_tell,
            0.0, do_room_tell);
    else
        tell_alarm = 0;
}

/*
 * Function:    start_room_tells
 * Arguments:   -
 * Description: Start the room_tells if they're not on.
 *              This function is typically called from enter_inv().
 *
 *              Example:
 *              void
 *              enter_inv(object ob, object from)
 *              {
 *                  start_room_tells();
 *                  ::enter_inv(ob, from);
 *              }
 * Returns:     void
 */
void
start_room_tells()
{
    if (tell_alarm && sizeof(get_alarm(tell_alarm)))
        return;
    tell_alarm = set_alarm(10.0 + repeat_tell / 2.0 + rnd() * repeat_tell,
        0.0, do_room_tell);
}

/*
 * Function:    stop_room_tells
 * Arguments:   -
 * Description: Stop the room_tells even if someone is still in the room.
 * Returns:     void
 */
void
stop_room_tells()
{
    if (!tell_alarm)
        return;
    remove_alarm(tell_alarm);
    tell_alarm = 0;
}

