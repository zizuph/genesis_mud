inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>

query_recover()
{
  return MASTER+":"+query_wep_recover();
}

init_recover(arg)
{
  init_wep_recover(arg);
}

create_weapon(){
    set_name("axe");
    set_adj("heavy");
    set_short("heavy axe");
	set_long("It is a heavy, broadbladed axe, commonly used by dwarves.\n");

    set_hit(30);
    set_pen(30);
    set_wt(W_AXE);
	set_hands(W_BOTH);
    set_dt(W_SLASH | W_IMPALE | W_BLUDGEON);
}
