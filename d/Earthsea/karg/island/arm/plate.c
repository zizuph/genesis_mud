inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

#include "defs.h"

void create_armour()
{
 set_name("chainmail");
 add_name("mail");
 add_name("armour");
 set_adj("white");
 add_adj("polished");

 set_ac(20);
 set_at(A_BODY);

 set_long("This chainmail used by kargish invaders. It looks well "+
   "polished and might give some decent defence to the wearer. You "+
   "see sign of karg empire on it.\n");

 add_prop(OBJ_I_WEIGHT,3000);
 add_prop(OBJ_I_VOLUME,3000);
 add_prop(OBJ_I_VALUE,1100);
}

