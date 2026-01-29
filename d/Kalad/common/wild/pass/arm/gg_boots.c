/* 
 * /d/Kalad/common/wild/pass/arm/gg_boots.c
 * Purpose    : Iron boots
 * Located    : Used by the goblins in the caves
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("boots");
   set_adj("iron");
   set_pshort("iron boots");
   set_long("A rather large, smelly and uncomfortable pair of iron "+
      "boots. It looks to be of goblin make. A bloody hand clutching an eyeball "+
      "decorates it.\n");
   set_ac(9);
   set_at(A_FEET);
   add_prop(OBJ_I_VALUE,360);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
