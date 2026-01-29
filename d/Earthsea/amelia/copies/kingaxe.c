#pragma save_binary

inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include <macros.h>

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
    set_adj("mithril");
    set_short("mithril axe");
    set_long("A powerful mithril axe, made by dwarven weaponsmiths.\n");

    set_hit(21);
    set_pen(37);
    
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);

}