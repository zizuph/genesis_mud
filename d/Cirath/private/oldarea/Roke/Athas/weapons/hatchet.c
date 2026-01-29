inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("hatchet");
	set_short("sturdy hatchet");
	set_long("This was made to chop small pieces of wood. "+
	   "Killing enemies might also have been on the crafter's "+
	   "mind when he made it.\n");
	set_adj("sturdy");

	set_hit(25);
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
