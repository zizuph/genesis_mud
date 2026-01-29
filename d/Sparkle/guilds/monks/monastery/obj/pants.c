/*******************************************************************\
| PANTS.C                                                           |
\*******************************************************************/

/*
 * 99/02/?? Lilith	Created
 * 03/04/04 Arandir	Ported to new area and bugfixed
 *
 */

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_OBJ_CLOTHES_WEARABLE_BASE;

//-------------------------------------------------------------------

void create_object ()
{
  ::create_object ();

  set_name  ("trousers", TRUE);
  add_name  (({ "pants", "garment", "clothing" }), TRUE);
  set_pname (({ "trousers", "garments", "clothes", "clothing" }));

  set_adj (({ "loose", "woven", "gray", "grey", "monk", "draw-string" }));

  set_short  ("pair of gray draw-string trousers");
  set_pshort ("pairs of gray draw-string trousers");
  set_long   ("These are loose-fitting trousers made of coarsely-woven " +
              "flax fibers and dyed a plain, unassuming gray. They are held " +
              "in place with a draw-string which can be tightened to fit " +
              "most waistlines. The wide-legged pants end a finger's width " +
              "or two above the ankle, allowing the wearer full and " +
              "unrestricted range of motion. This is a simple garment " +
              "for a person of simple needs.\n");

  config_wearable_item (A_LEGS, 1, 15, this_object());

  add_prop (OBJ_I_VALUE, 75);
  add_prop (OBJ_I_WEIGHT, 750);
  add_prop (OBJ_I_VOLUME, 1000);
}

//-------------------------------------------------------------------

mixed wear (object oThis)
{
  object oPlayer = environment ();
  object oRoom = environment (this_player ());

  if ((oPlayer != this_player ()) ||
      (oThis != this_object ())) return (-1);

  write ("You slip into the "+ short () + " and knot the string " +
         "loosely about your waist.\n");
  tell_room (oRoom, QCTNAME (oPlayer) + " slips into the " +
             short () + ".\n", oPlayer);

  return (WEAR_OK_SILENT);
}

//-------------------------------------------------------------------

