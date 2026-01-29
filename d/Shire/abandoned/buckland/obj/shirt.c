
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
   set_name("shirt");
   set_short("plain shirt");
   add_adj("brown");
   set_long("A plain brown shirt, it looks like it would fit a hobbit.\n");
   set_ac(4);
   set_am(({2,1,1,}));
   set_at(A_BODY);
   
   add_prop(OBJ_I_VALUE, 9);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 100);
   
}
