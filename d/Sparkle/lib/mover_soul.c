/*******************************************************************\
| MOVER_SOUL.C                                                      |
+-------------------------------------------------------------------+
| Base soul mover to be used when moving things in live game.       |
\*******************************************************************/

/*
 * 06/02/14 Arandir     Added logging
 * 06/01/30 Arandir     Created
 *
 */

#include <macros.h>

#include "defs.h"

inherit "/cmd/std/command_driver";

inherit S_LIB_PLAYER;
inherit S_LIB_LOGGING;

//-------------------------------------------------------------------

string get_replacement_file ()
{
  // To be overridden by the child objects ...
  return (0);
}


nomask string *replace_soul ()
{
  // Not sure if TP is set correctly here ...
  s_log (MASTER + ".log", "Replaced soul for " + s_get_Name () + ".");
  return (({ get_replacement_file ()}));
}

//-------------------------------------------------------------------

