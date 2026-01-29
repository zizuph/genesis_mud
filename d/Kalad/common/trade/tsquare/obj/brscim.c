inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include <wa_types.h>

void
create_weapon()
{
set_name( ({"scimitar"}) );
set_short("bronze scimitar");
set_pshort("scimitars");
set_adj( ({"bronze"}) );
set_long("A primitive bronze scimitar of medium quality.\n");
set_hit (20);
set_pen (20);
set_wt(W_SWORD);
set_dt(W_SLASH | W_IMPALE);
set_hands(W_ANYH);
add_prop(OBJ_I_VALUE,450);
}
