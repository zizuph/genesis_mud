inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

/* by Antharanos */
/* fixed the magic info to be more useful, Cherek July 2016 */

create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_short("glowing holy platemail");
   add_name("mail");
   set_adj("glowing");
   add_adj("holy");
   set_long("This holy platemail gleams with a bright inner light. It "+
   "has been blessed by the powers that be, giving it divine protection "+
   "to the wearer.\n");
   set_ac(45);
   add_prop(OBJ_S_WIZINFO,"This is the great holy armour of the Lord "+
   "of Drakmere. Blessed by the great wizards, it is magical.\n");
   add_prop(MAGIC_AM_MAGIC,({40,"enchanted"}));
   add_prop(MAGIC_AM_ID_INFO,({30,"This armour is blessed, glowing " +
   "with a holy light and providing more protection than a normal platemail.\n"}));
   set_at(A_BODY);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   add_prop(OBJ_I_LIGHT,1);
   add_prop(OBJ_I_VALUE, 850);
   add_prop(OBJ_I_VOLUME, 1500);
   add_prop(OBJ_I_WEIGHT, 2000);
}
