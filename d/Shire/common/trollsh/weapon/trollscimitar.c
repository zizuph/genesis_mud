inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"


create_weapon() {
   set_name("scimitar");
   add_name("sword");
   set_short("large scimitar");
   set_pshort("scimitars");
   set_adj(({"troll", "large", "huge", "steel"}));
   set_long("This is a large scimitar made of steel.\n");
   set_hit(35);
   set_pen(30);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
}

int
query_hands()
{
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
}

