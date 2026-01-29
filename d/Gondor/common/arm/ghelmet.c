/* Slight increase in AC to strengthen the NPCs that use them, Eowul, 2009 */
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
  set_name(({"helmet"}));
  set_pname("helmets");
  set_short("steel helmet");
  set_pshort("steel helmets");
  set_adj(({"tabarded", "steel", "guard", "shiny"}));
  set_long("The helmet was made by a good armourer in Minas Tirith.\n"+
    "It is the standard helmet for Gondor soldiers.\n");
  set_default_armour(30,A_HEAD,({-1,1,0}),0);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) * (120 - random(21)) / 100);
  add_prop(OBJ_I_WEIGHT,2400);
  add_prop(OBJ_I_VOLUME,1200);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}

