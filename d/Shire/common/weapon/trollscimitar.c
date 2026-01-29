inherit "/d/Shire/common/weapon/slay_weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"

create_weapon() {
   set_name("scimitar");
   set_short("large scimitar");
   set_pshort("scimitars");
   set_adj(({"troll", "large", "huge", "steel"}));
   set_long("This is a large scimitar made of steel.\n");
   set_hit(35);
   set_pen(30);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(MAGIC_AM_MAGIC, ({ 25, "dwarf-slaying" }));
   add_prop(MAGIC_AM_ID_INFO,
	({ "The scimitar seems magical.\n", 1,
	   "The scimitar will hit additionally against dwarves.\n", 25 }));
   set_slay_map((["elf":25]));
}

int
query_hands()
{
    if(!this_player()) return W_BOTH;
    if(STR(TP)>50) return W_ANYH;
    else return W_BOTH;
}

#include "recover"

