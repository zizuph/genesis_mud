/* A little boys toy club  - can be used as a weak club */
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"club","toy club"}));
    set_adj("wooden");
    set_short("toy club");
    set_long("It is a child's toy club made of wood. It is pretty small, "+
             "but it would probably hurt to get hit "+
             "in the head with it.\n");
 
    set_hit(3); set_pen(3);
    set_hands(W_NONE);
    set_wt(W_CLUB); set_dt(W_BLUDGEON);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 176);
}
