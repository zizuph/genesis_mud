inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
   set_name("breastplate");
   add_adj("leather");
   add_adj("studded");
   set_short("studded leather breastplate");
   set_long("This is hardened leather breastplate with many gleaming, "+
   "steel studs. Intricate dwarven designs adorn the front and back "+
   "of it.\n");
   set_ac(26);
   set_at(A_TORSO);
   add_prop(OBJ_I_VALUE,300);
   add_prop(OBJ_I_VOLUME, 2400);
   add_prop(OBJ_I_WEIGHT, 3000);
}
