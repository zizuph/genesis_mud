/*
 * h_cloak.c
 * By Skippern Dec 20(c)00
 *
 * Used by Utmir the lone herbalist of Erech.
 */
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define ARM      3

/*
 * Function name:    create_armour
 * Description  :    Creates the armour object.
 */
public void
create_armour()
{
  set_name("cloak");
  add_name("robe");

  set_adj("blue-spotted");
  set_adj("green");
  set_long("This is an old cloak, probably an hareloom of some sort. " +
	   "It looks like it is made of wool. It is coloured green " +
	   "with blue spots here and there.\n");

  set_default_armour(ARM, A_ROBE, (({ 0, 0, 1})), 0);

  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARM) + random(20) - 5);
}
