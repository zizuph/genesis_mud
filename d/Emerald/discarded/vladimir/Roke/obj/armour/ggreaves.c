inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/d/Roke/common/defs.h"
void
create_armour()

{
   set_name("greaves");
   set_short("pair of greaves");
   set_long("They are made of green steel with three small spikes at the "+
      "knees. On each greave is a symbol of two crossed axes "+
      "over a map of the world.\n");
   set_adj("steel");
   add_adj("green");
   
   set_ac(38);
   set_am(({ 0, 0, 0}));
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE, 800);
}
