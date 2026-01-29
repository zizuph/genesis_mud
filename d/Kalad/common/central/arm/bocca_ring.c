/* 
 * /d/Kalad/common/central/arm/bocca_ring.c
 * Purpose    : The citycouncellors ring
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* Bocca's rings. */

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
   set_name("ring");
   switch (random(3))
   {
      case 0:
      set_adj("shining");
      set_long("A shining ring with small, sharp stones inserted "+
         "into the polished metal.\n");
      break;
      case 1:
      set_adj("diamond");
      set_long("A single large diamond sparkles in the light from this "+
         "beautiful ring.\n");
      break;
      case 2:
      set_adj("gold");
      set_long("It is a plain gold ring without any stones in it. "+
         "The gold has been formed into some short, but sharp spikes, "+
         "that have a faint red colour to them. It might be "+
         "old dried blood.\n");
      break;
      case 3:
      set_adj("silver");
      set_long("This silver ring looks fairly plain was it not for "+
         "the small blade attached to it like a miniature knife. Its sharp!\n");
      break;
   }
   set_ac(2);
   set_at(A_ANY_FINGER);
   
   add_prop(OBJ_I_VALUE, random(1000)+1000);
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_WEIGHT, 100);
}

