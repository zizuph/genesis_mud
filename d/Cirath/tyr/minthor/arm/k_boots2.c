inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("boots");
   set_pname("boots");
   set_adj("grey");
   add_adj("thin-soled");
   set_short("grey thin-soled boots");
   set_long("Made of some form of animal hide, these grey boots "
	+"are soft to the touch and their thin-soles help the "
	+"wearer to move quickly and silently when others would "
	+"be unable to.\n");
   set_ac(20);
   set_at(A_FEET);
   add_prop(OBJ_I_WEIGHT,10);
   add_prop(OBJ_I_VOLUME,200);
    set_wf(TO);
}
query_recover()
{
   return 1;
}



