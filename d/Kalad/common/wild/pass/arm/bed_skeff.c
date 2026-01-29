/* 
 * /d/Kalad/common/wild/pass/arm/bed_skeff.c
 * Purpose    : Silk keffiyehs
 * Located    : Used by the Bedlams
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("keffiyeh");
   set_adj("stunning");
   add_adj("white");
   set_pshort("stunning white keffiyehs");
   set_long("A cloth made from the smoothest silk, it is wrapped around "+
      "one's head, to help protect one's self from the harsh rays of the "+
      "Kaladian sun.\n");
   set_ac(2);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE,120);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,1000);
}
