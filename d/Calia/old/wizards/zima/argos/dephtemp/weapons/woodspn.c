/* A wooden spoon used by the servants in the kitchen */
inherit "std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
 
void
create_weapon()
{
    set_name(({"wood spoon","wooden spoon","spoon"}));
    set_adj("wooden");
    set_adj("long");
    set_short("long wooden spoon");
    set_long("It is a long wooden spoon used for cooking.\n");
 
    set_hit(2);
    set_hands(W_NONE);
    set_pen(2);
 
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
 
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 50);
}
