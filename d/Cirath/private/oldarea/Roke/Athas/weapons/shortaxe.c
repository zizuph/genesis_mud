inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("axe");
	set_short("short axe");
	set_long("This is just short enough to fit the small "+
	   "hands of a hobbit. It seems strange that someone "+
	   "would make a weapon for a hobbit, though.\n");
	set_adj("short");

	set_hit(30);
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
