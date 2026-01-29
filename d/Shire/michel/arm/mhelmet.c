inherit "/std/armour";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/wa_types.h"

void
create_armour()
{
   set_name("helmet");
   set_adj(({"battered","iron"}));
   set_short("battered iron helmet");
   set_long("This battered iron helmet looks of orcish make "+
   "and as if it has taken a lot of blows from blunt objects, "+
   "as well as arrows, as you note a hole piercing the back "+
  "of the helmet.\n");
   set_ac(10);
   set_at(A_HEAD);
   set_am(({-1,-1,2}));
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_VOLUME,700);
   add_prop(OBJ_I_WEIGHT,2000);
}


