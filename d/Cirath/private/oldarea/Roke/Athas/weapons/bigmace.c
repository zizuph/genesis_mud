inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("mace");
	set_short("big fat mace");
	set_long("It is a very large metal ball on the "+
   "end of a very fat stick.\n");
	set_adj("big");
	add_adj("fat");

	set_hit(29);
	set_pen(20);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
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
