inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("axe");
	set_short("dirty axe");
	set_long("This axe is a bit dirty and looks like it "+
	   "hasn't been maintained very well.\n");
	set_adj("dirty");

	set_hit(15);
	set_pen(20);
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
