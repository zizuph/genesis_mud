inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("helm");
   set_adj("worn");
   add_adj("bone");
   set_short("worn bone helm");
   set_long("This is simply a modified skull, worn as a weak form "
   	+"of armour.  It could probably offer your head some protection.\n");
   set_ac(10);
   set_at(A_HEAD);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,500);
}

