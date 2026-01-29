inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

#include "defs.h"

void create_armour()
{
 set_name("cape");
 add_name("robe");
 add_name("armour");
 set_adj("white");
 add_adj("silk");

 set_ac(7);
 set_at(A_ROBE);

 set_long("This robe used by kargish officers. This robe is a sign "+
   "of kargish officers , only officers have a privilage to wear it. "+
   "You see sign of karg empire on it.\n");

 add_prop(OBJ_I_WEIGHT,500);
 add_prop(OBJ_I_VOLUME,500);
 add_prop(OBJ_I_VALUE,700);
}

