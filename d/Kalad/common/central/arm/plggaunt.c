/* 
 * /d/Kalad/common/central/arm/plggaunt.c
 * Purpose    : Gauntlets worn by the militia captain
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
   set_adj("white");
   set_pshort("white gauntlets");
   set_long(
      "White coloured plates that protects your arms. Engraved upon "+
      "it is an image of a fist gripping a sword.\n");
   set_ac(18);
   set_at(A_ARMS);
   add_prop(OBJ_I_VALUE, 420);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,2000);
}
