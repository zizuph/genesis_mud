/* 
 * /d/Kalad/common/central/arm/plggreav.c
 * Purpose    : Greaves worn by the militia captain
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by korat */
create_armour()
{
   ::create_armour();
   set_name("greaves");
   set_adj("white");
   set_pshort("white greaves");
   set_long(
      "A pair of armours that will protect your legs. Engraved "+
      "on them you see an image of a fist gripping a sword.\n");
   set_ac(19);
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE, 420);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME,4000);
}
