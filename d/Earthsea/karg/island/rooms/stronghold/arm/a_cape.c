inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

#include "defs.h"

void create_armour()
{
 set_name("cape");
 add_name("robe");
 add_name("armour");
 set_adj("flowing");
 add_adj("white");

 set_ac(17);
 set_at(A_ROBE);

 set_long("This robe used by kargish high officers. This robe is a "+
   "sign of kargish officers , only officers have a privilage to "+
   "wear it. You see sign of karg empire on it.\n");

 add_prop(OBJ_I_WEIGHT,900);
 add_prop(OBJ_I_VOLUME,900);
 add_prop(OBJ_I_VALUE,800);
}

