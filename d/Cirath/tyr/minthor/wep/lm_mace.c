inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("mace");
   set_adj("flanged");
   add_adj("steel");
   set_short("flanged steel mace");
   set_long("This mace is made of a large solid piece of "
	+"steel with a handle wrapped in worn leather.  "
	+"The head of the mace is made up of four large "
	+"flanges that protrude outward, ensuring that "
	+"anyone hit by it will be severely wounded.\n");
   set_hit(30);
   set_pen(35);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,1200);
}

