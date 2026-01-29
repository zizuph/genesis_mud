inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name(({ "warhammer", "hammer" }));
	set_short("Athasian warhammer");
   set_long("This, by normal definition, isn't a warhammer at "+
     "at, but Athas is one of those odd places. The weapon has "+
     "a large, blunt head opposing a long, narrow axe blade, that "+
     "is usually used to puncture.\n");
	   "great skill. It has a large head, perfect for bashing "+
	   "enemies, and a long, sharp spike protruding from the back "+
	   "for those who like to make more visisble wounds.\n");
	set_adj("war");
	add_adj("Athasian");
   add_adj("athasian");

	set_hit(35);
	set_pen(35);
	set_wt(W_AXE);
	set_dt(W_BLUDGEON | W_IMPALE);
	set_hands(W_ANYH);

}
query_recover()
{
  return MASTER+":"+query_wep_recover();
}
init_recover(arg)
{
  init_wep_recover(arg);
}
