inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("spear");
   add_adj("agafari");
   set_adj("obsidian-tipped");
   set_long("A spear standing only 5 feet tall, this "
   	+"appears to have been designed primarily for "
   	+"one-handed use.  The strong, yet flexible "
   	+"agafari wood used in making the shaft ensures "
   	+"durability, while the razor sharap obsidian tip "
   	+"will tear through your opponents flesh with "
   	+"ease.\n");
   set_hit(28);
   set_pen(34);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,1954);
}


