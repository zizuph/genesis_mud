inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

#include "defs.h"

void create_armour()
{
 set_name("helm");
 add_name("helmet");
 add_name("armour");
 set_adj("white");
 add_adj("winged");

 set_ac(35);
 set_at(A_HEAD);

 set_long("This helm used by kargish high officers. It is made from "+
   "good metal and must give prety good protection. You "+
   "see sign of karg empire on it.\n");

 add_prop(OBJ_I_WEIGHT,1500);
 add_prop(OBJ_I_VOLUME,1500);
 add_prop(OBJ_I_VALUE,600);
}

