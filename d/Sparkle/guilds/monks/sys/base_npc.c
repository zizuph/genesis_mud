/*******************************************************************\
| BASE_NPC.C                                                        |
+-------------------------------------------------------------------+
| Base non player character module for the dragon area.             |
\*******************************************************************/

/*
 * 02/01/27 Arandir	Created
 * 03/12/18 Arandir     Modified to make composites visible from afar
 *
 */

#include <options.h>

#include "../defs.h"

inherit "/std/monster";

//-------------------------------------------------------------------

/*
 * Function name : query_no_show_composite
 * Description   : This function prevents the monster from being
 *                 included in the composite description if it
 *                 is already part of the room description.
 *
 */

int query_no_show_composite ()
{
  object oActor = this_player ();

  // We must be a part of the description of this room and
  // the onlooker has to be in this room if this function
  // is to decide anything at all.

  if ((environment () == environment (oActor)) &&
      (environment ()->dg_is_composite (this_object ())))
  {
    string sVerb = query_verb ();

    switch (sVerb)
    {
      case "l":
      case "look":
        return (TRUE);
      case "glance":
        return (FALSE);
      default:
        return (!oActor->query_option (OPT_BRIEF));
    }
  }

  return (::query_no_show_composite ());
}

//-------------------------------------------------------------------

