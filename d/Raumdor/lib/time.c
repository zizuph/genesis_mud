/*
   Time object to be inherited if your object needs to know the time.
   Add init_time() in your init() or init_living() to add a time action.
   Cannot tell the time in rooms containing the ROOM_I_INSIDE or
   ROOM_M_CANNOT_TELL_TIME property.

   By Ashbless w/advice from Olorin, Cedric, and Ellesar.
   
   Code revised by Fysix, Oct 1997

   2017-09-17 Malus: Removed rain effects

 */
#pragma strict_types
#pragma save_binary

#include "defs.h"

/* Function name: query_cannot_tell_time
 * Description:   Player cannot tell the time somehow.
 *                Has to use notify_fail in case of a fail.
 * Arguments:     object player, defaults to this_player()
 * Returns:       int 1 if player can't tell time, 0 if he can.
 */
public varargs int
query_cannot_tell_time(object player = this_player())
{
    mixed msg;

    if (environment(player)->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("It's impossible to tell the time from inside.\n");
        return 1;
    }

    // Check for ROOM_M_CANNOT_TELL_TIME property
    if (msg = environment(player)->query_prop(ROOM_M_CANNOT_TELL_TIME))
    {
        if (stringp(msg))
            notify_fail(msg);
        else
            notify_fail("It's impossible to tell the time here.\n");
        return 1;
    }

    return 0;
}

/* Function name: what_time
 * Description:   Action to see what time it is.
 * Returns:       int 1 if successful
 */
int
what_time(string unused)
{
    string ret;
    string msg;

    if( E(TP)->query_prop(ROOM_I_INSIDE))
    {
      write("It's impossible to tell from inside.\n");
      return 1;
    }

    // Check for ROOM_M_CANNOT_TELL_TIME property
    if (msg = environment(this_player())->query_prop(ROOM_M_CANNOT_TELL_TIME))
    {
        if (stringp(msg))
            notify_fail(msg);
        else
            notify_fail("It's impossible to tell the time here.\n");
        return 0;
    }

    write("Judging from the sky, you would say it is " +
            CLOCK->query_time_desc() + ".\n");
    return 1;
}

/* Function name: init_time
 * Description:   Add "time" action.
 */
public void
init_time()
{
   add_action(what_time, "time");
}
