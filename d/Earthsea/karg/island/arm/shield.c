inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

#include "defs.h"

void create_armour()
{
 set_name("shield");
 add_name("armour");
 set_adj("white");
 add_adj("tower");

 set_ac(20);
 set_at(A_SHIELD);

 set_long("This shield used by kargish invaders. It is made from "+
   "white steel and covers you perfectly. You see sign of karg "+
   "empire on them.\n");

 add_prop(OBJ_I_WEIGHT,1700);
 add_prop(OBJ_I_VOLUME,1700);
 add_prop(OBJ_I_VALUE,720);
}

