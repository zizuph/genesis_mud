inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("axe");
	set_short("light axe");
   set_long("This is another one of those amazing products "+
     "from Athas. It is made out of remarkable light materials "+
     "that are native only to Athas. This makes better accuracy "+
     "but at the loss of power.\n");
	add_adj("light");

	set_hit(30);
	set_pen(18);
	set_wt(W_AXE);
	set_dt(W_SLASH);
	set_hands(W_ANYH);

	add_prop(OBJ_I_WEIGHT, 800);
}
query_recover()
{
  return MASTER+":"+query_wep_recover();
}
init_recover(arg)
{
  init_wep_recover(arg);
}
