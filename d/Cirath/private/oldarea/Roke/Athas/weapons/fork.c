inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("pitchfork");
	set_short("old pitchfork");
	set_long("This is just a pitchfork that farmers use to "+
	   "pitch their hay. However, it does make a decent improvised "+
	   "weapon.\n");
	set_adj("old");
	add_adj("pitch");

	set_hit(15);
	set_pen(12);
	set_wt(W_POLEARM);
	set_dt(W_IMPALE);
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
