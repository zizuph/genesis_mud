/*******************************************************************\
| BASE_ROOM_BRIDGE.C                                                |
+-------------------------------------------------------------------+
| Base room module for bridges in the mountain area.                |
\*******************************************************************/

/*
 * 02/07/21 Arandir	Created
 *
 */

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit MT_ROOM_BASE;

inherit DG_OBJ_LIBS;

//-------------------------------------------------------------------

void mt_wash_downstream (object oItem, object oFrom);

//-------------------------------------------------------------------

/*
 * Function name : enter_inv
 * Description   : Used to send small items dropped on the bridge
 *                 through the planks and downstream to the meadows.
 *
 */

void enter_inv (object oItem, object oFrom)
{
  if ((!living (oItem)) &&
      (oItem->query_prop (OBJ_I_VOLUME) < 1000))
  {
    // This is tricky. We have to call the inherited function, because
    // it may do all sorts of important things and not doing so could
    // introduce subtle bugs. But we do not want the item to coalesce
    // with heaps, because we could not move it away then. The flag
    // that prevents coalescing lasts until the end of tick only.

    oItem->set_no_merge (TRUE);
    ::enter_inv (oItem, oFrom);
    set_alarm (0.0, 0.0, &mt_wash_downstream (oItem, oFrom));
  }
  else
  {
    ::enter_inv (oItem, oFrom);
  };
}

/*
 * Function name : mt_wash_downstream
 * Description   : Used to send small items dropped on the bridge
 *                 through the planks and downstream to the meadows.
 *
 */

void mt_wash_downstream (object oItem, object oFrom)
{
  object oHere = this_object ();

  if (present (oItem))
  {
    if (interactive (oFrom))
    {
      if (dg_is_singular (oItem))
      {
        oFrom->catch_msg (
          "Before you realize that " + LANG_THESHORT (oItem) + " is too " +
          "small, it falls through the planks of the bridge.\n");
        tell_room (oHere,
          "As " + QTNAME (oFrom) + " drops " + LANG_THESHORT (oItem) + ", " +
          "it falls through the planks of the bridge.\n", oFrom);
      }
      else
      {
        oFrom->catch_msg (
          "Before you realize that the " + LANG_THESHORT (oItem) + " are too " +
          "small, they fall through the planks of the bridge.\n");
        tell_room (oHere,
          "As " + QTNAME (oFrom) + " drops the " + LANG_THESHORT (oItem) + ", " +
          "they fall through the planks of the bridge.\n", oFrom);
      };
    }
    else
    {
      tell_room (oHere,
        capitalize (LANG_THESHORT (oItem)) +
        dg_is_singular (oItem) ? " falls " : " fall " +
        "through the planks of the bridge.\n");
    };

    oItem->move (dg_normalize_room ("stream"), MOVE_SUBLOC_ALWAYS);
  };
}

//-------------------------------------------------------------------

