/*******************************************************************\
| LIBS_LOGGING.C                                                    |
\*******************************************************************/

/*
 * 08/01/29 Arandir     Merged with monk logging system
 * 06/02/14 Arandir     Added rotation of system logs
 * 06/02/13 Arandir	Created
 *
 */

#include <files.h>
#include <filter_funs.h>

#include "defs.h"

/*
 * This library can either be used directly or modified
 * through inheritance. Hooks are provided to modify
 * the list of logs that never rotate, and the list
 * of people notified about records in the logs.
 *
 */

//-------------------------------------------------------------------

// The size limit at which a log gets rotated

#define S_MAX_LOG_SIZE  100000

//-------------------------------------------------------------------

/*******************************************************************\
| Customization hooks                                               |
\*******************************************************************/

/*
 * Function name : s_log_hook_enumerate_logs
 * Description   : Returns a list of logs that can be selected using a bit mask.
 *                 Selecting logs using a bit mask is useful in cases where the
 *                 same message is logged to multiple destinations.
 *
 */

string *s_log_hook_enumerate_logs ()
{
  return (({ }));
}

/*
 * Function name : s_log_hook_never_rotate
 * Description   : Returns a list of logs that never rotate.
 *
 */

string *s_log_hook_never_rotate ()
{
  return (({ }));
}

/*
 * Function name : s_log_hook_observers
 * Description   : Returns a list of people that should observe messages.
 *
 */

object *s_log_hook_observers ()
{
  // By default, all wizards of the domain observe logged messages.

  return (FILTER_PLAYERS (map (SECURITY->query_domain_members (S_DOMAIN), &find_player ())));
}

//-------------------------------------------------------------------

/*
 * Function name : s_rotate_log
 * Description   : Rotates a log if it is above a size limit
 *
 */

void s_rotate_log (string sLog)
{
  // Logs are only rotated if they are not in the no rotate list.

  if (member_array (sLog, s_log_hook_never_rotate ()) < 0)
  {
    if (file_size (sLog) > S_MAX_LOG_SIZE)
    {
      rename (sLog, sLog + "." + time ());
    }
  }
}

//-------------------------------------------------------------------

/*
 * Function name : s_dump
 * Description   : Dumps an information about a variable
 *   xVariable     : The variable to dump
 * Returns       : The variable as a string
 *
 */

string s_dump (mixed xVariable)
{
  switch (typeof (xVariable))
  {
    case T_ARRAY:    return ("ARR");
    case T_FLOAT:    return ("FLT [" + ftoa (xVariable) + "]");
    case T_OBJECT:   return ("OBJ [" + file_name (xVariable) + " " + xVariable->short () + "]");
    case T_STRING:   return ("STR [" + xVariable + "]");
    case T_INTEGER:  return ("INT [" + xVariable + "]");
    case T_MAPPING:  return ("MAP");
    case T_FUNCTION: return ("FUN");
    default:         return ("ERR");
  }
}


/*
 * Function name : s_stack
 * Description   : Dumps the call stack of the function
 * Returns       : The call stack as a string
 *
 */

string s_stack ()
{
  int iLevel = 0;
  string sResult = "";

  object oObject;
  string sFunction;

  while (TRUE)
  {
    oObject = calling_object (iLevel);
    sFunction = calling_function (iLevel);

    if (objectp (oObject) && stringp (sFunction))
    {
      sResult += sprintf ("%03d: %s %s\n", iLevel, s_dump (oObject), sFunction);
      iLevel ++;
    }
    else break;
  }

  return (sResult);
}

//-------------------------------------------------------------------

/*
 * Function name : s_log
 * Description   : Stores a message in the relevant log
 *   mLogs         : The logs to use
 *   sMessage      : The message to store
 *   xData         : Data that this message concerns
 *   bDump         : Indication that stack dump is needed
 *
 */

varargs void s_log (mixed mLogs, string sMessage, mixed xData = NULL, int bDump = FALSE)
{
  string *asPossibleLogs;
  string *asLogs;
  string sText;
  string sLog;

  S_FIXUID;

  // If the logs are specified using a bitmap,
  // convert the bitmap to a list of files.

  if (intp (mLogs))
  {
    // The individual bits in the bitmap correspond
    // the the individual files in the order listed
    // by the log enumeration hook.

    asPossibleLogs = s_log_hook_enumerate_logs ();
    asLogs = ({ });

    while ((mLogs != 0) && (sizeof (asPossibleLogs) != 0))
    {
      if (mLogs & 1) asLogs += ({ asPossibleLogs [0] });
      asPossibleLogs = asPossibleLogs [1 ..];
      mLogs = mLogs >> 1;
    }
  }
  else
  {
    // Alternatively, the log file is provided directly.

    asLogs = ({ mLogs });
  }

  // Construct the entire log message.

  sText = ctime (time ()) + ": " + sMessage + "\n";

  if (xData)
  {
    // Dump the related data, and if it is in
    // an environment, dump the environment.
    sText += "DAT: " + s_dump (xData) + "\n";
    if (objectp (xData)) sText += "-EN: " + s_dump (environment (xData)) + "\n";

    // Dump this object ...
    sText += "TOB: " + s_dump (this_object ()) + "\n";
    sText += "-EN: " + s_dump (environment (this_object ())) + "\n";

    // Dump this player ...
    sText += "TPL: " + s_dump (this_player ()) + "\n";
    sText += "-EN: " + s_dump (environment (this_player ())) + "\n";
  }

  if (bDump) sText += s_stack ();

  // Write the message to all the logs requested.

  foreach (string sLog : asLogs)
  {
    s_rotate_log (sLog);
    write_file (sLog, sText);
  }

  // Send the message to all observers online.

  foreach (object oObserver : s_log_hook_observers ())
  {
    oObserver->catch_tell (sText);
  }
}

//-------------------------------------------------------------------

void s_rotate_system_logs ()
{
  // Symbolic constants are not used for game generated
  // logs because no other code should access them anyway.
  s_rotate_log (S_DOMAIN_LOG_DIR + "bugs");
  s_rotate_log (S_DOMAIN_LOG_DIR + "errors");
  s_rotate_log (S_DOMAIN_LOG_DIR + "ideas");
  s_rotate_log (S_DOMAIN_LOG_DIR + "praise");
  s_rotate_log (S_DOMAIN_LOG_DIR + "runtime");
  s_rotate_log (S_DOMAIN_LOG_DIR + "typos");
}

//-------------------------------------------------------------------

void s_logging_hook_create ()
{
  // The random start time should help avoid load peaks every hour,
  // which is simply chosen too often as a period for regular alarms.
  set_alarm (itof (random (60)), 3600.0, &s_rotate_system_logs ());
}

//-------------------------------------------------------------------

