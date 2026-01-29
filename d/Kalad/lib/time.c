/*
   /d/Kalad/lib/time.c

   Time object to be inherited if your object needs to know the time.
   Add init_time() in your init() or init_living() to add a time action.
   Cannot tell the time in rooms containing the ROOM_I_INSIDE or
   ROOM_M_CANNOT_TELL_TIME property. Also you can't tell the time
   outside Kalad because the sun never sets in Kalad.

   By Ashbless w/advice from Olorin, Cedric, and Ellesar.
   
   Code revised by Fysix, Oct 1997
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include "/d/Kalad/sys/time.h"
#include "/d/Kalad/sys/areas.h"

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

    // Check for ROOM_M_CANNOT_TELL_TIME property in time.h
    if (msg = environment(player)->query_prop(ROOM_M_CANNOT_TELL_TIME))
    {
        if (stringp(msg))
            notify_fail(msg);
        else
            notify_fail("It's impossible to tell the time here.\n");
        return 1;
    }

    // Check if player is in Kabal
    // Call to query_in_kabal kept for backwards compatibility
    if ((!environment(player)->query_in_kabal() &&
        environment(player)->query_area() != AREA_KABAL))
    {
        notify_fail("It's impossible to tell the time since the sun " +
            "never sets in Kalad.\n");
        return 1;
    }

    return 0;
}

/* Function name: what_time
 * Description:   Action to see what time it is.
 * Returns:       int 1 if successful
 */
public int
what_time(string unused)
{
   string ret;
   int time;

   if (query_cannot_tell_time(this_player()))
       return 0;

   time = (int) CLOCK->query_time();

   switch (time)
   {
    case 7..11:
      ret = "it is sometime during new-watch.\n";
      break;
    case 12..16:
      ret = "it is sometime during midwatch.\n";
      break;
    case 17..20:
      ret = "it is sometime during latewatch.\n";
      break;
    case 21:
      ret = "it is near the end of latewatch. " +
         "Everyone seems to be heading home for the day.\n";
      break;
    case 22..24:
    case 1..5:
      ret = "it is sometime during endwatch.\n";
      break;
    case 6:
      ret = "it is nearing new-watch and the start of a " +
         "new day. Everyone seems to be getting ready for work.\n";
      break;
   }

   write("Judging from the activity around you, " +
      "you'd say " + ret);

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

/* Function name: query_time
 * Description:   What is the time?
 * Returns:       int time 1..24
 */
public int
query_time()
{
   return (int) TIME;
}

/* Function name: query_raining
 * Description:   Is it raining?
 * Returns:       int 0 not raining, 1 if raining, 2 if raining very hard
 */
public int
query_raining()
{
   return (int) RAIN;
}
