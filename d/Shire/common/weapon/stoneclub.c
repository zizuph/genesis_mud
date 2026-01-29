inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"

create_weapon() {
   set_name("club");
   set_short("huge stone troll club");
   set_pshort("stone clubs");
   set_adj(({"troll","huge", "stone"}));
   set_long("This is a heavy stone club with spikes in it.\n");
   set_hit(25);
   set_pen(30);
   set_wt(W_CLUB);
   set_dt(W_IMPALE | W_BLUDGEON);
   add_item(({"stone"}),
	"It seems awful! And in the same time strange.\n");
}

int
query_hands()
{
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
}

#include "recover"

