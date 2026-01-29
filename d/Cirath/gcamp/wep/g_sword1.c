inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("sword");
   set_adj("heavy");
   add_adj("obsidian");
   set_long("A large piece of sharpened obsidian forms the blade of "
   	+"this crude sword.  A piece of horn to be used as a hilt "
   	+"has been attached to the stone using what appears to be some "
   	+"sort of cord.\n");
   set_hit(23);
   set_pen(25);
   set_wt(W_SWORD);
   set_dt(W_SLASH|W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,1500);
}

