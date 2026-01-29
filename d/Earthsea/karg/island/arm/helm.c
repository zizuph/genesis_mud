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
 add_adj("chain");

 set_ac(15);
 set_at(A_HEAD);

 set_long("This helm used by kargish invaders. It is made from some "+
   "kind of chain metal and must give prety decent protection. You "+
   "see sign of karg empire on it.\n");

 add_prop(OBJ_I_WEIGHT,650);
 add_prop(OBJ_I_VOLUME,650);
 add_prop(OBJ_I_VALUE,560);
}

