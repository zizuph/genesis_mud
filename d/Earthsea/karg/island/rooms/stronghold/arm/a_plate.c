inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

#include "defs.h"

void create_armour()
{
 set_name("fullplate");
 set_name("platemail");
 add_name("plate");
 add_name("armour");
 set_adj("white");

 set_ac(40);
 set_at(A_BODY|A_ARMS|A_LEGS);

 set_long("This platemail used by kargish high officers. It's made "+
   "of studry steel and protects the whole body. You see sign of "+
   "karg empire on it.\n");

 add_prop(OBJ_I_WEIGHT,7000);
 add_prop(OBJ_I_VOLUME,7000);
 add_prop(OBJ_I_VALUE,1000);
}

