inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("club");
   set_adj("obsidian-spiked");
   set_long("This is apparently a standard club made from some form of "
   	+"bone that has been weighted with stones and spiked with small "
   	+"shards of obsidian.  It looks as if it could tear through "
   	+"naked flesh easily.\n");
   set_hit(30);
   set_pen(20);
   set_wt(W_CLUB);
   set_dt(W_IMPALE|W_BLUDGEON);
    set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,1500);
}

