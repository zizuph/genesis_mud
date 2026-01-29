#include "defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

   inherit "/std/armour";
inherit "/lib/keep";


create_armour()
{
   set_name("ring");
   add_adj("opal");
   set_short("opal ring");
   set_long("As you examine the ring closely, you see that the " +
   "craftsmanship of this ring is exceptional. Thin wires of " +
   "silver and gold wrap around a brightly polished opal.\n");

   set_ac(1);
   set_at(A_R_FINGER);

   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE,   122+random(40));
   add_prop(OBJ_I_LIGHT, 5);
    set_keep();
}

