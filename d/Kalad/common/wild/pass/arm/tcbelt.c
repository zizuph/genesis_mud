/* 
 * /d/Kalad/common/wild/pass/arm/tcbelt.c
 * Purpose    : A steel belt, not used in hitlocs
 * Located    : Goliath?
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("belt");
   set_adj("steel-adorned");
   add_adj("leather");
   set_long("A large belt made out of suprisingly supple leather. It is "+
      "encrusted with many bits of steel, making it look like a garish "+
      "version of some noble's belt.\n");
   set_ac(10);
   set_at(A_WAIST);
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_WEIGHT,600);
   add_prop(OBJ_I_VOLUME,600);
}
