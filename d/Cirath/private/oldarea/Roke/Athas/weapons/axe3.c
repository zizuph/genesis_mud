inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("axe");
   set_short("strange stone axe");
	set_long("This isn't very primitive, but yet, it's "+
     "made of stone. The stone is very odd. It's like "+
     "nothing found in any other part of the world. It is "+
     "incredibly smooth, sharp, and hard. It would seem "+
     "like a perfect substance for crafting weapons. If only "+
     "it were more common, more people could use it for their "+
     "weapons. On the top end is a large, studded ball "+
     "used for bludgeoning attacks.\n");
	set_adj("stone");
   add_adj("strange");

	set_hit(30);
	set_pen(35);
	set_wt(W_AXE);
	set_dt(W_BLUDGEON | W_SLASH);
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
