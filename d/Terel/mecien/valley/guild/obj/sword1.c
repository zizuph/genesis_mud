/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

public void
create_weapon()
{
    set_name("longsword");
    set_adj("silvery-steel");
    add_name("mystic_sword");
    add_name("sword");
    set_long(
      "A beautiful blade of silvery-steel, on which many runes and "
      +"mystic symbols have been inscribed. The guard is a simple cross "
      +"in which three amber stars are set. The hilt and pommel are "
      +"plain. The blade is sharp and sparkling.\n"
    );
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hit(27);
    set_pen(27);
    add_prop("mystic_weapon", 1);
}

public string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

public void
init_recover(string arg)
{
    init_wep_recover(arg);
}
