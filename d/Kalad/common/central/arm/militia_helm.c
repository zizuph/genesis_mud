/* 
 * /d/Kalad/common/central/arm/militia_helm.c
 * Purpose    : Helmet worn by the militia
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Korat */
create_armour()
{
   ::create_armour();
   set_name("polished helmet");
   add_name("helmet");
   set_long(
      "This armour has been polished to a brilliant shine. The "+
      "two crossed swords at the front of the armour indicate this is the "+
      "standard armour of the Kabal militia officers.\n");
   set_ac(13);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE, 340);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
