
/* 
   Room tell room, basically a unification of Aridor's room tell code
   and the handling of the turning on/off in enter_inv and leave_inv.

   Compiled by Maniac 5/1/96.
*/

#pragma save_binary

inherit "/std/room";

#include <filter_funs.h>

int interactive_count;
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

/* Function:    remove_tell
 * Arguments:   str:   the tell string to remove from the room.
 * Description: Removes a string from the list of tells for a room.
 *              The string can be a VBFC.
 * Returns:     void
 */
void
remove_tell(string str)
{
    tell_strings -= ({ str, 0 });
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

    if (interactive_count = 
             sizeof(FILTER_PLAYERS(all_inventory(this_object()))))
        tell_alrm = 
             set_alarm(itof(10 + random(repeat_tell)),0.0,"do_room_tell");
    else
        tell_alrm = 0;
}


/* Function:    start_room_tells
 * Arguments:   -
 * Description: Start the room_tells if they're not on.
 *              This function is called from enter_inv().
 *
 * Returns:     void
 */
void
start_room_tells()
{
    if (tell_alrm || !sizeof(tell_strings))
        return;
    tell_alrm = set_alarm(itof(random(10 + repeat_tell)),0.0,"do_room_tell");
}


/* Function:    stop_room_tells
 * Arguments:   -
 * Description: Stop the room_tells even if someone is still in the room.
 * Returns:     void
 */
void
stop_room_tells()
{
    if (!tell_alrm)
      return;
    remove_alarm(tell_alrm);
    tell_alrm = 0;
}


/* Function: enter_inv
   We mask this to (a) start up room tells when an interactive enters, and
   (b) keep track of the number of interactives in the room so we can turn
   off room tells immediately when there are none left (this saves having
   a lot of alarms going when someone runs through an area quickly). 
*/
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob)) {
        interactive_count++;
        start_room_tells();
    }
}

/* Function: leave_inv
   We mask this to turn off the room tell alarm immediately when the last 
   interactive leaves.
*/
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (interactive(ob))
        interactive_count--;
    if (interactive_count == 0)
        stop_room_tells();
}

