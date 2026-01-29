/* 
 * /d/Kalad/common/wild/pass/arm/gg_helm.c
 * Purpose    : Pig iron helm
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
   set_name("helm");
   set_adj("iron");
   set_long("A small and completely wreaking helmet made of pig iron, "+
      "apparently of goblin make. A bloody hand clutching an eyeball "+
      "decorates it.\n");
   set_ac(16);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE,360);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
