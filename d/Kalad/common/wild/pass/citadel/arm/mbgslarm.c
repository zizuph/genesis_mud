inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("armour");
   set_adj("studded");
   add_adj("leather");
   set_long("This looks like any ordinary suit of leather armour, save "+
      "for the metal studs covering its surface.\n");
   set_ac(20);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE, 456);
   add_prop(OBJ_I_VOLUME, 2400);
   add_prop(OBJ_I_WEIGHT, 5600);
}
