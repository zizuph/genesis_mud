/* The slave gladiators collar */

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
   set_name("collar");
   set_adj("iron");
   set_short("iron collar");
   set_long("This iron collar is the symbol of being a "+
      "slave gladiator of Kabal.\n");
   set_ac(3);
   set_at(A_NECK); /* It protects the neck */
   
   add_prop(OBJ_I_VALUE, 100);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 1000);
}

