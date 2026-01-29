/* 
 * /d/Kalad/common/central/arm/glad_shield.c
 * Purpose    : A shield worn by the gladiators in the arena
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
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
   set_name("shield");
   set_adj("battered");
   add_adj("red");
   set_long("A large shield that covers most of your upper body. "+
      "Even though it is fairly battered, it will undoubtedly provide "+
      "good protection. On its red-coloured front you see an engraved "+
      "symbol consisting of two crossed swords.\n");
   set_ac(17);
   set_at(A_SHIELD);
   add_prop(OBJ_I_VALUE, 260);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,2000);
}
