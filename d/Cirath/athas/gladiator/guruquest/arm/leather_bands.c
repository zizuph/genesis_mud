 /* Arm bands for Derryn.
 code (c) 1998 Damian Horton 
 updated for Raumdor, March 2001 */

#pragma strict_types
#pragma save_binary

#include <wa_types.h>
#include "/d/Cirath/defs.h"
#include "/sys/formulas.h"

inherit "/std/armour";

void create_armour()
{
  set_name("armbands");
  set_pname("armbands");
  add_name("bands");
  set_short("leather armbands");
  set_pshort("leather armbands");
  set_long("Made of cured inix leather, these armbands provide some "+
	   "protection to your forearms. They are actually quite "+
	   "comfortable to wear.\n");
  set_adj("leather");

  set_ac(7);
  set_am(({0,0,0}));  
  set_at(A_ARMS);

  add_prop(OBJ_I_WEIGHT, 1700);
  add_prop(OBJ_I_VOLUME, 1550);
  add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(7) + random(20) - random(20)));
}

