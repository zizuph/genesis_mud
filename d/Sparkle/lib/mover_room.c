/*******************************************************************\
| MOVER_ROOM.C                                                      |
+-------------------------------------------------------------------+
| Base room mover to be used when moving things in live game.       |
\*******************************************************************/

/*
 * 06/02/14 Arandir     Added logging
 * 06/02/02 Arandir     Clone rather than master was created
 * 06/01/30 Arandir     Created
 *
 */

#include <macros.h>

#include "defs.h"

inherit "/std/room";

inherit S_LIB_PLAYER;
inherit S_LIB_LOGGING;

//-------------------------------------------------------------------

string get_replacement_file ()
{
  // To be overridden by the child objects ...
  return (0);
}


nomask void create_room ()
{
  S_LOAD (get_replacement_file ());
}


void enter_inv (object oWhat, object oFrom)
{
  // If it is a player who is entering, we check whether
  // this room happens to be his starting location. If
  // it is, it is changed to the new starting location.

  if (interactive (oWhat))
  {
    if (oWhat->query_default_start_location () == MASTER)
    {
      oWhat->set_default_start_location (get_replacement_file ());
      s_log (MASTER + ".log", "Replaced startloc for " + s_get_Name (oWhat) + ".");
    }
  }

  oWhat->move (get_replacement_file (), MOVE_SUBLOC_ALWAYS);

  if (interactive (oWhat)) s_log (MASTER + ".log", "Moved " + s_get_Name (oWhat) + ".");
                      else s_log (MASTER + ".log", "Moved " + oWhat->short () + ".");
}

//-------------------------------------------------------------------

