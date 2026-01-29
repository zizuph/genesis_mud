inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_short("blessed silver platemail");
   add_name("platemail");
   add_name("mail");
   set_adj("blessed");
   add_adj("silver");
   set_long("This suit of platemail looks strong and well made. It has "+
   "a golden cross etched on the breastplate. It glimmers strangely.\n");
   set_ac(40);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE, 850);
   add_prop(OBJ_I_VOLUME, 1500);
   add_prop(OBJ_I_WEIGHT, 2000);
}
