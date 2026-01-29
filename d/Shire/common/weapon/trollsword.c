inherit "/d/Shire/common/weapon/slay_weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include "defs.h"

inherit "/d/Shire/common/lib/tell";

create_weapon() {
   set_name("sword");
   set_short("huge troll sword");
   set_pshort("troll swords");
   set_adj(({"troll","huge", "steel"}));
   set_long("This is a huge troll sword made of steel.\n");
   set_hit(35);
   set_pen(25);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(MAGIC_AM_MAGIC, ({ 25, "elf-slaying" }));
   add_prop(MAGIC_AM_ID_INFO,
	({ "The sword seems magical.\n", 1,
	   "The sword will hit additionally against elves.\n", 25 }));
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

