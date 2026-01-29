inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("armour");
   set_adj("adamantine");
   add_adj("chain");
   set_long("A complete suit of adamantine chain armour, it consists of "+
      "interlocking helmet, chainmail, gauntlets and greaves. Emblazoned "+
      "onto the chainmail is an image of a black widow spider perched "+
      "atop two crossed halberds.\n");
   set_ac(19);
   set_at(A_HEAD | A_BODY | A_ARMS | A_LEGS);
   add_prop(OBJ_I_VALUE, 900);
   add_prop(OBJ_I_WEIGHT,35000);
   add_prop(OBJ_I_VOLUME,35000);
}
