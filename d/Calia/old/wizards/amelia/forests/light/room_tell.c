/* 
 * With this file you can add sounds and other repeating output
 * to rooms and containers.
 *
 * By Aridor, 09/14/94
 */

#include <filter_funs.h>

int tell_alrm;
int repeat_tell = 0;
string *tell_strings = ({ });
string *tell_strings_left;

/*
 * Function:    set_tell_time
 * Arguments:   tim: Intervall
 * Description: Set the mean value for room_tell intervall
 * Returns:     void
 */
void
set_tell_time(int tim)
{
    repeat_tell = tim;
}

/* Function:    add_tell
 * Arguments:   str:   the tell string to add to the room.
 * Description: Adds a string to the list of tells for a room.
 *              The string can be a VBFC.
 * Returns:     void
 */
void
add_tell(string str)
{
    tell_strings += ({ str });
}

/* Function:    do_room_tell()
 * Arguments:   -
 * Description: Perform one tell in the room.
 * Returns:     void
 */
void
do_room_tell()
{
    int i;
    string this_tell_string;
    if (!tell_strings_left || !sizeof(tell_strings_left))
      tell_strings_left = tell_strings + ({ });

    i = random(sizeof(tell_strings_left));
    this_tell_string = tell_strings_left[i];
    tell_strings_left -= ({ this_tell_string, 0 });

    tell_room(this_object(),
	      this_object()->check_call(this_tell_string));

    if (sizeof(FILTER_PLAYERS(all_inventory(this_object()))))
      tell_alrm = set_alarm(itof(10 + random(repeat_tell)),0.0,"do_room_tell");
    else
      tell_alrm = 0;
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
void
start_room_tells()
{
    if (tell_alrm)
      return;
    tell_alrm = set_alarm(itof(10 + random(repeat_tell)),0.0,"do_room_tell");
}
