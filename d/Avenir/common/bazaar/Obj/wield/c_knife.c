 //Glinda may -95
 //A weapon for my cook.

inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include "/sys/stdproperties.h"
#include "/d/Avenir/common/common.h"


create_weapon()
{
   set_name("knife");
   set_pname("knives");
   add_adj(({"kitchen","long-bladed","steel"}));
   set_short("long-bladed kitchen knife");
   set_pshort("long-bladed kitchen knives");
   set_long("This looks like a good all-purpose knife for various " +
            "kitchen activities like skinning eels, chopping vegetables " +
            "and such. It has a long steel blade, and the hilt is " +
            "comfortable to hold.\n");
   set_wt(W_KNIFE);
   set_dt(W_SLASH || W_IMPALE);
   set_hands(W_ANYH);
   set_hit(10);
   set_pen(17);

   add_prop(OBJ_I_VOLUME,150);
   add_prop(OBJ_I_WEIGHT,870);
   add_prop(OBJ_I_VALUE,385);
}
