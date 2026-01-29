inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("scythe");
	set_short("polished scythe");
	set_long("A deadly weapon... to sugar cane!\n");
	set_adj("polished");

	set_hit(18);
	set_pen(16);
	set_wt(W_POLEARM);
	set_dt(W_SLASH);
	set_hands(W_BOTH);

}
query_recover()
{
  return MASTER+":"+query_wep_recover();
}
init_recover(arg)
{
  init_wep_recover(arg);
}
