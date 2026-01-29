 /* One of the two pieces of armour worn by Avena.
 code (c) 1998 Damian Horton 
 Update for Raumdor, March 2001
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
  set_short("inix-leather greaves");
  set_pname("greaves");
  set_pshort("inix-leather greaves");
  set_long("Supple greaves made from cured inix leather.\n");
  set_adj("leather");
  add_adj("inix-leather");
  add_adj("inix");

  set_ac(9);
  set_am(({0,0,0}));
  set_at(A_LEGS);

  add_prop(OBJ_I_WEIGHT, 1900);
  add_prop(OBJ_I_VOLUME, 2000);
  add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(9)) + random(25) - random(25));
}
