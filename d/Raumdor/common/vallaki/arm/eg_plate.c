inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

/* by Sarr*/
create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_short("black silver-striped platemail");
   add_name("mail");
   set_adj("black");
   add_adj("silver-striped");
   set_long("This suit of platemail appears to be very strong. It is "+
   "made of black steel, and decorated with various silver stripes and "+
   "lines. A large golden cross is on the chestplate, gleaming brightly "+
   "in the light.\n");
   set_ac(40);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE, 800);
   add_prop(OBJ_I_VOLUME, 1600);
   add_prop(OBJ_I_WEIGHT, 2200);
}
