/* 
 * /d/Kalad/common/central/arm/karoth_helm.c
 * Purpose    : Helmet worn by the arenamaster
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
   set_name("helmet");
   set_adj("solid");
   set_long(
      "This solid-looking helmet has an extra metal-plate "+
      "attached on the front. Some small and sharp "+
      "spikes stick out from it, probably used for "+
      "headbutting the enemy. If you only knew "+
      "how to use it properly!\n");
   set_ac(21);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE, 600);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
