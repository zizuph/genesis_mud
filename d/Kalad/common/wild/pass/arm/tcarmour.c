/* 
 * /d/Kalad/common/wild/pass/arm/tcarmour.c
 * Purpose    : A large suit of leather armour
 * Located    : I don't know
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
   set_name("armour");
   add_name("leather armour");
   set_adj("leather");
   set_long("A large suit of leather armour. It is almost completely covered "+
      "with bits of meat and other, more sinister-looking stains. A terrible "+
      "stench wafts from it.\n");
   set_ac(16);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE, 300);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,9000);
}
