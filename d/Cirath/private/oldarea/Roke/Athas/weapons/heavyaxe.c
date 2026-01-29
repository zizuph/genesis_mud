inherit "/std/weapon";
#include <wa_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

void
create_weapon()
{
	set_name("axe");
	set_short("heavy axe");
	set_long("This axe is pretty banged up but it still "+
     "looks like it can deliver a good deal of damage. "+
     "The top end is large, blunt, metal, and sticks out "+
     "just far enough to smash enemies when they least "+
     "want to be.\n");
	set_adj("heavy");

	set_hit(25);
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
