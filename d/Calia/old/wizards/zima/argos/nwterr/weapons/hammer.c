inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"masonry hammer","hammer"}));
    set_adj("iron");
    set_short("masonry hammer");
    set_long("A thick iron hammer used to shape marble.\n");
 
    set_hit(10);
    set_hands(W_NONE);
    set_pen(10);
 
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
 
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
}
 
string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}
 
void
init_recover(string arg)
{
    init_wep_recover(arg);
}
