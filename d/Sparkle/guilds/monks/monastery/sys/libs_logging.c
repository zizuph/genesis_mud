/*******************************************************************\
| LIBS_LOGGING.C                                                    |
\*******************************************************************/

/*
 * 08/02/01 Arandir     Ported over new domain logging system
 * 07/06/19 Arandir     Fixed an argument type bug in logging
 * 07/06/18 Arandir     Support for poor man stack dumps
 * 07/06/05 Arandir	Somewhat better alignment of situation logging
 * 07/06/03 Arandir     Support for some logs that are never rotated
 *                      Support for logs of mbug, midea and mtypo
 * 06/09/30 Arandir     Better error checking for situation logging
 * 06/09/26 Arandir     Added situation logging
 * 03/06/10 Arandir	Created
 *
 */

#include <filter_funs.h>

#include "../defs.h"

inherit S_LIB_LOGGING;

//-------------------------------------------------------------------

/*
 * Function name : s_log_hook_enumerate_logs
 * Description   : Returns a list of logs that can be selected using a bit mask.
 *                 Selecting logs using a bit mask is useful in cases where the
 *                 same message is logged to multiple destinations.
 *
 */

string *s_log_hook_enumerate_logs ()
{
  return (M_LOGS);
}

/*
 * Function name : s_log_hook_never_rotate
 * Description   : Returns a list of logs that never rotate.
 *
 */

string *s_log_hook_never_rotate ()
{
  return (({ M_FILE_LOG_COUNCIL }));
}

/*
 * Function name : s_log_hook_observers
 * Description   : Returns a list of people that should observe messages.
 *
 */

object *s_log_hook_observers ()
{
  // By default, all wizards of the domain observe logged messages.

  return (FILTER_PLAYERS (map (M_MASTERS_ACTIVE, &find_player ())));
}

//-------------------------------------------------------------------

