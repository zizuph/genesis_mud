/*******************************************************************\
| ROOM_CLOCK.H                                                      |
+-------------------------------------------------------------------+
| Room fragment responsible for clock functions.                    |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Created
 *
 */

// This file is included rather than inherited
// because LPC cannot handle diamond inheritance

//-------------------------------------------------------------------

/*
 * Function name : s_action_time
 * Description   : Executed when somebody issues the time action.
 *
 */

int s_action_time ()
{
  if ((query_prop (ROOM_I_INSIDE)) || s_is_night ())
  {
    write ("It's " +
           LANG_ADDART (s_get_stime_season ()) + " " +
           s_get_stime_period () + ", " +
           "but you are not sure what time it is exactly.\n");
  }
  else
  {
    write ("It's " +
           s_get_stime_hour_of_period () + " o'clock on " +
           LANG_ADDART (s_get_stime_season ()) + " " +
           s_get_stime_period () + ".\n");
  }
  return (TRUE);
}

//-------------------------------------------------------------------

