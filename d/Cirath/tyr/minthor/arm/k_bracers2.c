inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("bracers");
   set_adj("studded");
   add_adj("leather");
   set_short("studded leather bracers");
   set_long("This set of studded leather bracers looks to have "
	+"studs made of adamantium or mithril.  The leather itself "
	+"is supple and soft, and they fit your forearms like a "
	+"second skin.  You can almost feel some sort of energy "
	+"flowing through the leather and into your body.\n");
   set_ac(35);
   set_at(A_ARMS);
   set_wf(TO);
}

query_recover()
{
   return 1;
}



