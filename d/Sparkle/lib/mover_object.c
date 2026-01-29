/*******************************************************************\
| MOVER_OBJECT.C                                                    |
+-------------------------------------------------------------------+
| Base object mover to be used when moving things in live game.     |
\*******************************************************************/

/*
 * 06/03/18 Arandir     Modified the log message
 * 06/02/13 Arandir     Added logging
 * 06/01/26 Arandir     Created
 *
 */

#include <macros.h>
#include <language.h>

#include "defs.h"

inherit "/std/object";

inherit S_LIB_PLAYER;
inherit S_LIB_LOGGING;

//-------------------------------------------------------------------

object oReplacement;


string get_replacement_file ()
{
  // To be overridden by the child objects ...
  return (0);
}


nomask void create_object ()
{
  S_FIXUID;
  oReplacement = clone_object (get_replacement_file ());

  // If we are not moved within 10 seconds, something is most
  // likely wrong, so at least get rid of ourselves ...
  set_alarm (10.0, 0.0, &remove_object ());
}


void enter_env (object oTo, object oFrom)
{
  oReplacement->move (oTo, MOVE_SUBLOC_ALWAYS);
  set_alarm (0.0, 0.0, &remove_object ());
  s_log (MASTER + ".log", "Replaced " + LANG_ASHORT (oReplacement) + " for " + s_get_Name () + ".");
}


string query_auto_load () { return (oReplacement->query_auto_load ()); }
void init_arg (string sArgs) { oReplacement->init_arg (sArgs); }

string query_recover () { return (oReplacement->query_recover ()); }
void init_recover (string sArgs) { oReplacement->init_recover (sArgs); }

//-------------------------------------------------------------------

