/* 
 * /d/Kalad/common/wild/pass/arm/bed_ekeff.c
 * Purpose    : A cloth keffiyehs
 * Located    : Used by the Bedlans in the desert
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("keffiyeh");
   set_adj("bleach");
   add_adj("white");
   set_pshort("bleach white keffiyehs");
   set_long("A cloth that is wrapped around one's head, to help protect "+
      "one's self from the harsh rays of the Kaladian sun.\n");
   set_ac(5);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE,100);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,1000);
}
