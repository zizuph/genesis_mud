inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("helm");
   set_adj(({"black", "golden-studded"}));
   set_short("black golden-studded helm");
   set_long("This helm is strong and made of black steel. All around the "+
   "edges are golden studs. A large golden cross is carved on the front "+
   "part.\n");
   set_ac(40);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE, 440);
   add_prop(OBJ_I_VOLUME, 800);
   add_prop(OBJ_I_WEIGHT, 1500);
}
