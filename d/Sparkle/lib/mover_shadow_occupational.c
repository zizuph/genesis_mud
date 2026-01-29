/*******************************************************************\
| MOVER_SHADOW_OCCUPATIONAL.C                                       |
+-------------------------------------------------------------------+
| Base shadow mover to be used when moving things in live game.     |
\*******************************************************************/

/*
 * 06/03/18 Arandir     Modified the log message
 * 06/02/14 Arandir     Added logging
 * 06/01/30 Arandir     Created
 *
 */

#include <macros.h>

#include "defs.h"

inherit "/std/guild/guild_occ_sh";

inherit S_LIB_PLAYER;
inherit S_LIB_LOGGING;

//-------------------------------------------------------------------

object oReplacement;


string get_replacement_file ()
{
  // To be overridden by the child objects ...
  return (0);
}


nomask void init_occ_shadow (string sArgs)
{
  S_FIXUID;
  oReplacement = clone_object (get_replacement_file ());

  oReplacement->shadow_me (shadow_who,
                           oReplacement->query_guild_type (),
                           oReplacement->query_guild_style_occ (),
                           oReplacement->query_guild_name_occ,
                           sArgs);

  shadow_who->remove_autoshadow (MASTER);
  set_alarm (0.0, 0.0, remove_shadow ());

  s_log (MASTER + ".log", "Replaced " + oReplacement->query_guild_name_occ () + " shadow for " + s_get_Name (shadow_who) + ".");
}


nomask int query_guild_not_allow_join_occ (object oWho,
                                           string sType,
                                           string sStyle,
                                           string sName)
{
  // We are disappearing soon so we do not collide with anything.
  return (FALSE);
}

//-------------------------------------------------------------------

