inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("axe");
   set_adj("sharp");
   add_adj("lightweight");
   set_long("This axe has been crafted from several "
   	+"different materials giving it a strange look. "
   	+"The handle seems to be wooden, while the head "
   	+"looks like it has been crafted from some sort "
   	+"of chitin and bone.  The edge looks incredibly "
   	+"sharp and jagged, which make you think it will "
   	+"easily hit your opponents, but it is very light "
   	+"and most likely will not do much damage.\n");
   set_hit(40);
   set_pen(20);
   set_wt(W_AXE);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,1650);
}

