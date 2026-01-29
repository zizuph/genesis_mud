 /* Myrdoth's greaves.
 code (c) 1998 Damian Horton
 Updated for Raumdor, March 2001
 */

#pragma strict_types
#pragma save_binary

inherit "/std/armour";

#include <wa_types.h>
#include "/d/Cirath/defs.h"
#include <formulas.h>

void create_armour()
{
  set_name("greaves");
  set_short("mekillot greaves");
  set_pname("greaves");
  set_long("These greaves are constructed from specially prepared mekillot "+
      "hide. Mekillot isn't the most attractive of armours, "+ 
      "but it does provide decent protection.\n");
  set_adj("mekillot");

  set_ac(18);
  set_am(({0,0,0}));
  set_at(A_LEGS);

  add_prop(OBJ_I_WEIGHT, 4400);
  add_prop(OBJ_I_VOLUME, 4210);
  add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(18))+ random(50) - random(50));
}

