inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"

inherit "/d/Shire/common/lib/tell";

create_weapon() {
   set_name("club");
   set_short("huge nailed troll club");
   set_pshort("troll clubs");
   set_adj(({"troll","cruel", "spiked"}));
   set_long("This is a huge nailed troll club made of wood.\n");
   set_hit(25);
   set_pen(35);
   set_wt(W_CLUB);
   set_dt(W_IMPALE | W_BLUDGEON);
   add_item(({"nails","nail","clubs nails", "clubs nail"}),
	"They seem cruel! One hit by those would tear your skin apart.\n");
}

int
query_hands()
{
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
}


string query_recover()
  {
    return MASTER + ":" + query_wep_recover();
  }
void
init_recover(string arg)
    {
    init_wep_recover(arg);
    }
