inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
set_name("sword");
set_adj(({"grey","narrow"}));
set_short("grey narrow sword");
set_long("This is the sword from a big swordfish. The grey blade is "+
       " long and narrow with a razor-sharp edge. The lower end is round"+
       " making it possible to hold without causing damage to yourself."+
       " This looks like a awesome weapon.\n");

set_hit(35);
set_pen(43);
set_wt(W_SWORD);
set_dt(W_IMPALE);
set_hands(W_BOTH);

add_prop(OBJ_I_WEIGHT,3000);
add_prop(OBJ_I_VOLUME,1500);
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
