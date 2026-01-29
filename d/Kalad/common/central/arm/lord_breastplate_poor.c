/*
 *  /d/Kalad/common/central/arm/lord_breastplate_poor.c
 *
 *  The poor quality breastplate worn by urian when he 
 *  does not have his good one.
 *
 *  Created November 2017, by Andreas Bergstrom (Zignur)
 */

inherit "/d/Kalad/std/armour.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

create_armour()
{
   ::create_armour();
   set_name("breastplate");
   set_adj("black");
   set_long("A black breastplate, it is crafted by some unknown black metal."+
      " Even though it looks quite formidable, you have a feeling it is more"+
      " a ornamental armour than something you would rely on for protection" +
      " in a battle.\n");
   set_ac(40);
   set_at(A_BODY);
   set_af(TO);
   add_prop(OBJ_I_VALUE,2500);
   add_prop(OBJ_I_WEIGHT,10500);
   add_prop(OBJ_I_VOLUME,11000);
}

