/* 
 * /d/Kalad/common/central/arm/apron.c
 * Purpose    : The arena-cooks apron
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* The cooks apron */

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
   set_name("apron");
   set_adj("dirt");
   set_short("dirty apron");
   set_long("The apron is littered with dirt and grease. You wonder "+
      "which cook would consider to wear this while making food!\n");
   set_ac(3);
   set_at(A_BODY);
   
   add_prop(OBJ_I_VALUE, 200);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, 2000);
}
