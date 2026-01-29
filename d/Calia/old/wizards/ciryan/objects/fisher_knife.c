
inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("knife");
    set_adj("sharp");
    set_short("sharp knife");
    set_long("This is a quite sharp knife with a long narrow blade" +
	     " and a roughly carved wooden handle. The blade is jagged" +
	     " on the upper edge and you can see some dark red stains" +
	     " appearing to be dried blood on it." +
	     " It looks very well used and sharpened several times.\n");
    set_hit(20);
    set_pen(20);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 400);
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
