/*
 * g_cloak.c
 * By Skippern Dec 20(c)00
 *
 * To be found on some of the ghosts in the Path of the Dead in
 * Gondor.
 */
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define ARM      2

/*
 * Function name:    create_armour
 * Description  :    Creates the armour object.
 */
public void
create_armour()
{
  set_name("cloak");
  add_name("robe");

  set_adj("dirty");
  add_adj("worn-down");
  set_long("This dirty worn-down cloak is so dirty and worn down that it " +
	   "almost impossible to see what colour it had.\n");

  set_default_armour(ARM, A_ROBE, (({ 0, 0, 1})), 0);

  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARM) + random(20) - 50);
}
