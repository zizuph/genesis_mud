
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
   set_name("pants");
   set_short("pair of green pants");
   add_adj("brown");
   set_long("A pair of green pants, it looks like it would fit a hobbit.\n");
   set_ac(4);
   set_am(({2,1,1,}));
   set_at(A_LEGS);
   
   add_prop(OBJ_I_VALUE, 9);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 100);
   
}
