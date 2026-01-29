/* 
 * /d/Kalad/common/central/arm/councellor_robe.c
 * Purpose    : The high lords councellors robe
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By:  Zignur increased the ac and made it magic
 */ 

/*
robe worn by The High Lords councellor
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/armour.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("large");
   add_adj("darkened");
   set_long("This large darkened robe covers the body of the wearer and gives some "+
      "protection. Small silver threads decorates the texture of the robe.\n");
   set_ac(35);
   set_at(A_ROBE);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   add_prop(OBJ_S_WIZINFO,"This robe is enchanted with a minor spell, that"+
      " grants the armour additional protection.\n");
   add_prop(MAGIC_AM_ID_INFO,({"This robe seems to be enchanted with a"+
      " minor protection spell. Making this armour more resistant"+
      " against melee attacks.\n",30}));
   add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
   add_prop(OBJ_I_VALUE, 2500);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2000);
}

