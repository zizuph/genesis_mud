/* 
 * /d/Kalad/common/central/arm/karoth_gaunt.c
 * Purpose    : Gauntlets worn by the arenamaster
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
   set_name("gauntlets");
   set_adj("dirty");
   set_pshort("dirty gauntlets");
   set_long(
      "Even though these gauntlets are filled with "+
      "stains from food and dirt, they seem to be "+
      "a well-made pair of armours that will protect your arms "+
      "fairly well.\n");
   set_ac(18);
   set_at(A_ARMS);
   add_prop(OBJ_I_VALUE,900);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,2000);
}
