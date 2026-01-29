inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("axe");
	set_short("long axe");
	set_long("The blade on this axe is so long that it "+
	   "almost looks like a scythe.");
	set_adj("long");

	set_hit(22);
	set_pen(30);
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
