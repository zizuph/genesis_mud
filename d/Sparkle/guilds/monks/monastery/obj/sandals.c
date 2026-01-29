/*******************************************************************\
| SANDALS.C                                                         |
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

inherit M_OBJ_CLOTHES_ARMOUR_BASE;

//-------------------------------------------------------------------

void create_armour ()
{
  ::create_armour ();

  set_name  ("sandals", TRUE);
  add_name  (({ "pair of sandals", "shoes" }), TRUE);
  set_pname ("sandals");

  set_adj (({ "leather", "thong", "simple", "monk" }));

  set_short  ("pair of leather thong sandals");
  set_pshort ("pairs of leather thong sandals");
  set_long   ("This is a pair of simple sandals. The sole is a " +
              "layer of thick leather. Set into it is a loop for the " +
              "big toe, as well as two other loops near the ankle and " +
              "instep, through which leather thongs are threaded. " +
              "The thongs are laced up the leg to about mid-calf. " +
              "These sandals are very lightweight and comfortable for " +
              "all who wear them.\n");

  set_ac (random (3) + 1);
  set_af (this_object());
  set_at (A_FEET);

  add_prop (OBJ_I_VALUE, 75);
  add_prop (OBJ_I_WEIGHT, 250);
  add_prop (OBJ_I_VOLUME, 200);
}

//-------------------------------------------------------------------

mixed wear (object oThis)
{
  object oPlayer = environment ();
  object oRoom = environment (this_player ());

  if ((oPlayer != this_player ()) ||
      (oThis != this_object ())) return (-1);

  write ("You slide your feet into the " + short () + " and " +
         "lace the thongs up your calves.\n");
  tell_room (oRoom, QCTNAME (oPlayer) + " slides " +
             QPOS (oPlayer) + " feet into the " +
             short () + " and laces them up to mid-calf.\n", oPlayer);

  return (WEAR_OK_SILENT);
}

//-------------------------------------------------------------------

