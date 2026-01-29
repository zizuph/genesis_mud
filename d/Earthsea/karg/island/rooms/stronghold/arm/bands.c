inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

#include "defs.h"

void create_armour()
{
 set_name("bands");
 add_name("bracers");
 add_name("armour");
 set_adj("white");
 add_adj("arm");

 set_ac(25);
 set_at(A_ARMS);

 set_long("These armbands used by kargish invaders. It is made from "+
   "white steel and gleams with sparkling light. You see sign of karg "+
   "empire on them.\n");

 add_prop(OBJ_I_WEIGHT,450);
 add_prop(OBJ_I_VOLUME,450);
 add_prop(OBJ_I_VALUE,510);
}

