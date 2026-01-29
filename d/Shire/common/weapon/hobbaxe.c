inherit "/d/Shire/common/weapon/slay_weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"

create_weapon() 
{
   set_name(({"axe","waraxe"}));
   set_short("huge waraxe");
   set_pshort("waraxes");
   set_adj(({"hobbit","huge", "steel"}));
   set_long("This is a huge waraxe made of steel.\n");
   set_hit(20);
   set_pen(40);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_BLUDGEON);
   add_prop(MAGIC_AM_MAGIC, ({ 25, "troll- and orc-slaying" }));
   add_prop(MAGIC_AM_ID_INFO,
	({ "The waraxe seems magical.\n", 1,
	   "The waraxe will hit additionally agains trolls and orcs.\n", 25 }));
   set_slay_map((["orc":25, "troll":25]));
   set_slay_desc("huge waraxe gleams with faint blue nimbus.\n");
}

int
query_hands()
{
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
}

#include "recover"

