inherit "/std/armour";

#include "/d/Shire/common/defs.h"
#include "../defs.h"
#include <wa_types.h>

void
create_armour()
{
   set_name("hat");
   set_short("small feathered hat");
   set_long("A green and yellow hat with a feather placed within it.\n");
   set_at(A_HEAD);
   set_ac(5);
   
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,30);
   add_prop(OBJ_I_VALUE,40);
}
