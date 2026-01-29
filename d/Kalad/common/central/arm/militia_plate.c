/* 
 * /d/Kalad/common/central/arm/militia_plate.c
 * Purpose    : Platemail worn by the militia officers
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
   set_name("polished platemail");
   add_name("platemail");
   add_name("mail");
   set_long("This armour has been polished to a brilliant shine. The "+
      "two crossed swords at the front of the armour indicate this is the "+
      "standard suit of armour for the Kabal militia officers.\n");
   set_ac(24);
   set_at(A_BODY);
  add_prop(OBJ_I_VALUE, 480);
   add_prop(OBJ_I_VOLUME, 3800);
   add_prop(OBJ_I_WEIGHT, 5600);
}
