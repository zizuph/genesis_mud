inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("cloak");
   set_short("black-red cloak");
   set_adj("black");
   add_adj("red");
   add_adj("black-red");
   set_long("This is the standard cloak of the Drakmere militia. It is "+
   "black with red stripes and patches, the colors of Drakmere. On each "+
   "side, you see printed, the coat of arms of Drakmere; a large golden "+
   "cross with two swords crossed behind it. On the part where it connects "+
   "around the wearer's neck, you see the symbol of King Raumdor I; a "+
   "white steel circle with a large silver claymore in the center.\n");
   set_ac(15);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_I_VOLUME, 600);
   add_prop(OBJ_I_WEIGHT, 1200);
}
