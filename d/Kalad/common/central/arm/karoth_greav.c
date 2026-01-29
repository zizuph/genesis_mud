/* 
 * /d/Kalad/common/central/arm/karoth_greav.c
 * Purpose    : Greaves worn by the arenamaster
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
   set_adj("bloodied");
   set_pshort("bloodied greaves");
   set_long(
      "These leg-armours looks oldfashioned, and shows signs "+
      "of much use. They are filled with dark-red stains of "+
      "dried blood.\n");
   set_ac(17);
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE, 400);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME,4000);
}
