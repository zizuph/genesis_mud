inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_armour()
{
   ::create_armour();
   set_name("gloves");
   set_short("pair of black gloves");
   set_adj("black");
   set_long("These are a pair of valuable black leather gloves.\n");
   set_ac(12);
   set_at(A_HANDS);
   add_prop(OBJ_I_VALUE, 150);
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_WEIGHT, 400);
}
