inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"


create_weapon() {
   set_name("club");
   set_short("huge spiked troll club");
   set_pshort("troll clubs");
   set_adj(({"troll","huge", "spiked"}));
   set_long("This is a huge spiked troll club made of steel.\n");
   set_hit(25);
   set_pen(35);
   set_wt(W_CLUB);
   set_dt(W_IMPALE | W_BLUDGEON);
   add_item(({"spikes","spike","clubs spikes", "clubs spike"}),
	"They seems awful! You wouldn't be hit by them.\n");
}

int
query_hands()
{
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
}

