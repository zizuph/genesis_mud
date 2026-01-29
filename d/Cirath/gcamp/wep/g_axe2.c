inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("axe");
   set_adj("wood-handled");
   add_adj("obsidian");
   set_long("The sharp wedge shaped blade of this axe has been placed "
   	+"atop a handle of sturdy agafari wood.  The heft on the axe is "
   	+"very nice.  You can't wait to embed this in someone's skull.\n");
   set_hit(28);
   set_pen(34);
   set_wt(W_AXE);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,1500);
}

