inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("axe");
   set_adj("razor-sharp");
   add_adj("obsidian");
   set_long("This is a large heavy axe crafted from obsidian "
   	+"and painstakingly sharpened so that it could shave "
   	+"a beard easily.  A long agafari wood haft is attached "
   	+"to the obsidian head with some thin strips of mekillot "
   	+"gut fibers.  This weapon could easily cut through flesh "
           +"like a hot knife through butter.\n");
   set_hit(37);
   set_pen(37);
   set_wt(W_AXE);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,5500);
   add_prop(OBJ_I_VOLUME,5000);
}

