/* 
 * /d/Kalad/common/central/arm/plghelm.c
 * Purpose    : Helmet worn by the militia captain
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
   set_adj("white");
   set_long(
      "An armour that will protect your head. Engraved on it "+
      "there is an image of a fist gripping a sword.\n");
   set_ac(19);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE,480);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
