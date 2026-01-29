inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("axe");
   set_adj("sharpened");
   add_adj("obsidian");
   set_long("Made from a piece of sharpened obsidian lashed to a stout "
   	+"bone, this weapon seems to pack a powerful punch.  The weight "
   	+"of the stone is the main factor in the damage caused by this "
   	+"weapon.\n");
   set_hit(27);
   set_pen(28);
   set_wt(W_AXE);
   set_dt(W_SLASH|W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,1500);
}

