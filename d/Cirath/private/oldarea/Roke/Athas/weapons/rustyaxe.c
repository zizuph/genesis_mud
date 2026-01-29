inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("axe");
	set_short("rusty axe");
	set_long("It must have seen better days. The rust isn't "+
	   "too bad, but it still hinders performance.\n");
	set_adj("rusty");

	set_hit(12);
	set_pen(15);
	set_wt(W_AXE);
	set_dt(W_SLASH);
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
