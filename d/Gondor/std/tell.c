/* 
 * With this file you can add sounds and other repeating output
 * to rooms and containers.
 *
 * By Aridor, 09/14/94
 *
 * 950405 Modified by Rastlin
 *
 * 990527 Modified by Milan 
 *  bugfixes + allarms use functions
 *  VBFC tells can now also be of function type.
 *  Also added possibility to make tells go all the time regardless if player
 *  is present or not. See function set_tell_all_time(int i);
 */

#include <filter_funs.h>

static int gTell_alarm = 0;
static int gRepeat_tell = 0;
static mixed *gTell_strings = ({ });
static mixed *gTell_strings_left = ({ });
static int gTell_all_time = 0;

/*
 * Function:    set_tell_all_time
 * Arguments:   int on: TRUE - tell go all time
 *			FALSE - tells are stopped when no player in
 * Description: Toggle all time running of tells on/off
 * Returns:     void
 */
public void
set_tell_all_time(int on)
{
    gTell_all_time = on;
}

int
query_tell_all_time() { return gTell_all_time; }

/*
 * Function:    set_tell_time
 * Arguments:   tim: Intervall
 * Description: Set the mean value for room_tell intervall
 * Returns:     void
 */
public void
set_tell_time(int tim)
{
    if(tim > 0)
	gRepeat_tell = tim;
}

/* Function:    add_tell
 * Arguments:   str:   the tell string to add to the room.
 * Description: Adds a string to the list of tells for a room.
 *              The string can be a VBFC.
 *		Also can be a function VBFC. Function should return string.
 * Returns:     void
 */
public void
add_tell(mixed str)
{
    int i;

    if (pointerp(str))
    {
	for (i=0; i<sizeof(str); i++)
	    if (stringp(str[i]) || functionp(str[i]))
		gTell_strings += ({ str[i] });
    }
    else if (stringp(str) || functionp(str))
        gTell_strings += ({ str });
}

mixed *
query_tells() { return gTell_strings; }

/* Function:    do_room_tell()
 * Arguments:   -
 * Description: Perform one tell in the room.
 * Returns:     void
 */
static void
do_room_tell()
{
    int i;
    mixed this_tell_string;

    gTell_alarm = 0;

    if (!gTell_strings_left || !sizeof(gTell_strings_left))
	gTell_strings_left = gTell_strings + ({ });

    if (!(i = sizeof(gTell_strings_left)))
	return;

    this_tell_string = gTell_strings_left[random(i)];
    gTell_strings_left -= ({ this_tell_string });
    tell_room(this_object(), this_object()->check_call(this_tell_string));

    if (gTell_all_time || sizeof(FILTER_PLAYERS(all_inventory(this_object()))))
	gTell_alarm = set_alarm(itof(10 + random(gRepeat_tell)), 0.0, do_room_tell);
}

/* Function:    start_room_tells
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
public void
start_room_tells()
{
    if (gTell_alarm)
	return;
    gTell_alarm = set_alarm(itof(random(10 + gRepeat_tell)), 0.0, do_room_tell);
}

/* Function:    stop_room_tells
 * Arguments:   -
 * Description: Stop the room_tells even if someone is still in the room.
 * Returns:     void
 */
public void
stop_room_tells()
{
    if (!gTell_alarm)
	return;
    remove_alarm(gTell_alarm);
    gTell_alarm = 0;
}
