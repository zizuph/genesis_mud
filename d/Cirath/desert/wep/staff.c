inherit "/std/weapon";
#include "../defs.h"
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("staff");
   set_adj("simple");
   set_long("This is a simple agafari wood staff.  It is probably "
   	+"not intended as a weapon, but more as walking stick.  "
   	+"In a pinch, though, it could inflict some damage.\n");
   set_hit(20);
   set_pen(20);
   set_wt(W_POLEARM);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,1000);
}

