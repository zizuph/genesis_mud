inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("cross");
   set_short("holy cross");
   set_adj("holy");
   set_long("This is a beautiful holy cross necklace made of gold. It "+
   "gleams brightly in the light, and you feel an aura of holiness "+
   "radiating off it.\n");
   set_ac(1);
   set_at(A_NECK);
   add_prop(OBJ_I_VALUE, 800);
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_WEIGHT, 200);
}
