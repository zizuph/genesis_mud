 /* Bracers for Myrdoth.
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
  set_name("bracers");
  set_pname("bracers");
  set_short("bone-studded bracers");
  set_pshort("bone-studded bracers");
  set_long("These bracers are composed of cured inix leather. For "+
      "additional protection, pieces of bone have been sewn into the "+ 
      "leather, resulting in armour comparable to that of the metal "+
      "studded leather armours of more metal rich societies.\n");
  set_adj("studded");
  add_adj("bone");
  add_adj("bone-studded");

  set_ac(13);
  set_am(({0,0,0}));  
  set_at(A_ARMS);

  add_prop(OBJ_I_WEIGHT, 2750);
  add_prop(OBJ_I_VOLUME, 2200);
  add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(13)) - random(25) + random(25)); 
}
