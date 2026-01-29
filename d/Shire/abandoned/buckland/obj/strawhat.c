
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
   set_name("hat");
   set_short("straw hat");
set_long("A plain straw hat, looks like it would provide some protection "+
"against the sun, but not much else.\n");
   set_ac(4);
   set_am(({2,1,1,}));
   set_at(A_HEAD);
   
   add_prop(OBJ_I_VALUE, 50);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 100);
   
}
