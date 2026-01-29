inherit "/std/weapon";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("longspear");
    add_name("spear");
   set_adj("obsidian-tipped");
   set_long("This looks to be a crudely made, but very effecetive weapon.  "
   	+"Designed simply from a long, sturdy pole with a sharpened piece "
   	+"of obsidian acting as the tip.  It appears to be sharp enough "
   	+"to do a good amount of damage.\n");
   set_hit(20);
   set_pen(30);
   set_wt(W_SPEAR);
   set_dt(W_IMPALE);
   set_hands(W_BOTH);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,1500);
}

