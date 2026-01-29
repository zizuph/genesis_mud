inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
   set_name(({ "Athasian axe", "athasian axe", "axe" }));
   set_short("nifty Athasian axe");
   set_long("This is a nice axe, modeled after it's larger "+
     "counterpart to get maximum efficiency out of it. "+
     "It's shaft is bent at the proper angle to allow use of "+
     "the blade or the hammer. There is also a point on the "+
     "end for those dramatic moments when stabbing is just "+
     "more heroic or fun.\n");
	set_adj("nifty");

	set_hit(20);
	set_pen(25);
	set_wt(W_AXE);
	set_dt(W_SLASH | W_BLUDGEON | W_IMPALE);
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
