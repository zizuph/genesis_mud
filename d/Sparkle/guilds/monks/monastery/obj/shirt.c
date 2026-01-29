/*******************************************************************\
| SHIRT.C                                                           |
\*******************************************************************/

/*
 * 99/02/?? Lilith	Created
 * 03/04/04 Arandir	Ported to new area
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

  set_name  ("shirt");
  add_name  (({ "tunic", "garment", "clothing" }));

  set_adj (({ "simple", "woven", "gray", "grey", "monk" }));

  set_short ("simple gray shirt");
  set_long  ("This is a simple shirt, woven from coarse flax fibers " +
             "and dyed a plain, unassuming gray. It resembles a short coat, " +
             "one designed so that the sides overlap at the front " +
             "and are secured at the waist by a belt. The sleeves are wide " +
             "and terminate just above the wrist, allowing the wearer " +
             "unrestricted movement. It is entirely unadorned, and elegant " +
             "in its simplicity and functionality.\n");

  config_wearable_item (A_BODY, 1, 15, this_object ());

  add_prop (OBJ_I_VALUE, 50);
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

  write ("You slip the "+ short () + " over your bare shoulders " +
         "and fold it over in the front.\n");
  tell_room (oRoom, QCTNAME (oPlayer) + " slips the " +
             short () + " over " + QPOS (oPlayer) + " shoulders " +
             "and folds it over in front.\n", oPlayer);

  return (WEAR_OK_SILENT);
}

//-------------------------------------------------------------------

