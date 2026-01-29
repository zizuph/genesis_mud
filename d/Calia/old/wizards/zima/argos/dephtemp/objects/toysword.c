/* A little boys toy sword - can be used as a weak club */
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"sword","toy sword"}));
    set_adj("wooden");
    set_short("toy sword");
    set_long("It is a child's toy sword. It is of course too dull to cut "+
             "or puncture anything, but it would probably hurt to get hit "+
             "in the head with it.\n");
 
    set_hit(3);
    set_hands(W_NONE);
    set_pen(3);
 
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
 
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 176);
}
