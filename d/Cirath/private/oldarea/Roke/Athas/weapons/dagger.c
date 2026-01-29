inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
   set_name(({"Athasian dagger","athasian dagger","dagger"}));
   set_short("sleek Athasian dagger");
   set_long("This is a dagger only found in Athas. It long "+
     "and slightly curved, with one edge jagged. When "+
     "created out of rare metals found only in Athas, it can "+
     "be a very powerful dagger.\n");
	set_adj("sleek");

	set_hit(20);
	set_pen(20);
	set_wt(W_KNIFE);
	set_dt(W_IMPALE | W_SLASH);
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
