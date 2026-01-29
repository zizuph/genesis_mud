inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("sword");
   set_adj("sharp");
   add_adj("obsidian");
   set_long("This weapon has been formed from a skillfully crafted "
   	+"piece of obsidian which has been meticulously sharpened to "
   	+"rival that of any razor.  Some form of cloth has been wrapped "
   	+"around the butt of the obsidian forming a crude hilt with "
   	+"which to wield the sword.\n");
   set_hit(28);
   set_pen(34);
   set_wt(W_SWORD);
   set_dt(W_SLASH|W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,1500);
}

